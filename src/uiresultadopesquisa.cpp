#include "uiresultadopesquisa.h"
#include "ui_uiresultadopesquisa.h"

#include <QUrl>
#include <QtDebug>
#include <QWidget>
#include <QPoint>
#include <QMenu>

/**
 * @brief ResultadoPesquisa::ResultadoPesquisa
 * @param parent
 * Tela de pesquisa de tracks pela api.
 * Menu de contexto para adicionar tracks a playlsits previamente cadastradas.
 */
ResultadoPesquisa::ResultadoPesquisa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultadoPesquisa),
    m_musica(nullptr),
    m_musicaList(new MusicaList)
{
    ui->setupUi(this);
    ui->tabelaResultados->setContextMenuPolicy(Qt::CustomContextMenu);

    //Menu de escolha de playlist a adicionar item atualmente selecionado.
    connect(ui->tabelaResultados, &QTableWidget::customContextMenuRequested, this, &ResultadoPesquisa::addplaylistMenuRequested);
}

/**
 * @brief ResultadoPesquisa::~ResultadoPesquisa
 */
ResultadoPesquisa::~ResultadoPesquisa()
{
    delete ui;
}

/**
 * @brief ResultadoPesquisa::addplaylistMenuRequested
 * @param pos
 */
void ResultadoPesquisa::addplaylistMenuRequested(QPoint pos){
    QMenu *menu = new QMenu();
    QMenu* mnuPlaylists = menu->addMenu("Adicionar à playlist->");

    QList<QAction *> actionsPlaylist;

    std::for_each(std::begin(m_playlists.getPlaylists()), std::end(m_playlists.getPlaylists()), [&](PlayList *playlist){
        QAction *playlistAction = new QAction(playlist->nome());
        playlistAction->setData(playlist->getId()); //pk
        actionsPlaylist.append(playlistAction);
    });
    mnuPlaylists->addActions(actionsPlaylist);
    connect(mnuPlaylists, SIGNAL(triggered(QAction*)) , SLOT(on_clickAddNaPlaylist(QAction*)));
    menu->popup(ui->tabelaResultados->viewport()->mapToGlobal(pos));
}

/**
 * @brief ResultadoPesquisa::on_clickAddNaPlaylist
 * @param action
 */
void ResultadoPesquisa::on_clickAddNaPlaylist(QAction* action)
{
    QTableWidgetItem *item =  ui->tabelaResultados->item(ui->tabelaResultados->currentRow(), ColunasTabela::Key);
    const QString keyMusica = item->text();
    Musica *musica = m_musicaList->getMusicaByKey(keyMusica);
    const int playlistId = action->data().toInt(); //pk

    if(musica != nullptr && !musica->key().isEmpty() && action->data().toInt() > -1){
        musica->setPlaylistid(playlistId);
        emit on_addMusicaNaPlaylist(playlistId, musica);
    }
}

/**
 * @brief ResultadoPesquisa::resizeEvent
 * @param event
 * Permite ao grid redimensionar conforme a tela sem perder a escala das colunas.
 */
void ResultadoPesquisa::resizeEvent(QResizeEvent *event)
{
    constexpr int col0 = 60;
    constexpr int col3 = 120;
    constexpr int col4 = 1;
    const int col1 = (this->width() - (col0-10 + col3)) / 2;
    const int col2 = (this->width() - (col0-10 + col3)) / 2;

    ui->tabelaResultados->setColumnWidth(ColunasTabela::Indice, col0); //idx
    ui->tabelaResultados->setColumnWidth(ColunasTabela::Nome, col1); //nome
    ui->tabelaResultados->setColumnWidth(ColunasTabela::Album, col2); //album
    ui->tabelaResultados->setColumnWidth(ColunasTabela::Duracao, col3);  //tempo
    ui->tabelaResultados->setColumnWidth(ColunasTabela::Key, col4);  //chave escondida
    ui->tabelaResultados->setColumnHidden(ColunasTabela::Key, true);
    QWidget::resizeEvent(event);
}

/**
 * @brief ResultadoPesquisa::setPlaylists
 * @param playlists
 */
void ResultadoPesquisa::setPlaylists(Playlists playlists)
{
    m_playlists = playlists;
}

/**
 * @brief ResultadoPesquisa::setMusicaList
 * @param musicaList
 */
void ResultadoPesquisa::setMusicaList(MusicaList *musicaList)
{
    m_musicaList = musicaList;

    preencheGrid();
}

/**
 * @brief ResultadoPesquisa::setTermo
 * @param termo
 */
void ResultadoPesquisa::setTermo(const QString &termo)
{
    ui->lblTodas->setText(QStringLiteral("%1 referências encontradas para a pesquisa: %2").arg(m_musicaList->size()).arg(termo));
}

/**
 * @brief ResultadoPesquisa::preencheGrid
 * XOR de flags para desabilitar edicao de grid: itemIndice->flags() &  ~Qt::ItemIsEditable
 */
void ResultadoPesquisa::preencheGrid()
{
    ui->tabelaResultados->clearContents();
    ui->tabelaResultados->setRowCount(0);

    std::for_each(std::begin(m_musicaList->getMusicas()), std::end(m_musicaList->getMusicas()), [=](Musica *musica){
        ui->tabelaResultados->insertRow(ui->tabelaResultados->rowCount());
//        qDebug() << "url imagem:" << musica->imagem();
//        qDebug() << "musica key:" << musica->key();

        //ToDo: Ler icones para Col 0...
        QTableWidgetItem *itemIndice = new QTableWidgetItem(QString::number(ui->tabelaResultados->rowCount()).rightJustified(2, '0'));
        itemIndice->setFlags(itemIndice->flags() &  ~Qt::ItemIsEditable);
        ui->tabelaResultados->setItem( ui->tabelaResultados->rowCount()-1, ColunasTabela::Indice, itemIndice);


        QTableWidgetItem *itemNome = new QTableWidgetItem(musica->nome());
        itemNome->setFlags(itemNome->flags() &  ~Qt::ItemIsEditable);
        ui->tabelaResultados->setItem(ui->tabelaResultados->rowCount()-1, ColunasTabela::Nome, itemNome);

        QTableWidgetItem *itemAlbum = new QTableWidgetItem(musica->album());
        itemAlbum->setFlags(itemAlbum->flags() &  ~Qt::ItemIsEditable);
        ui->tabelaResultados->setItem( ui->tabelaResultados->rowCount()-1, ColunasTabela::Album, itemAlbum);

        QTableWidgetItem *itemDuracao = new QTableWidgetItem(musica->getDuracaoMinSec());
        itemDuracao->setFlags(itemDuracao->flags() &  ~Qt::ItemIsEditable);
        ui->tabelaResultados->setItem( ui->tabelaResultados->rowCount()-1, ColunasTabela::Duracao, itemDuracao);

        //Esconde a chave aqui
        QTableWidgetItem *itemChave = new QTableWidgetItem(musica->key());
        itemChave->setFlags(itemChave->flags() &  ~Qt::ItemIsEditable);
        ui->tabelaResultados->setItem( ui->tabelaResultados->rowCount()-1, ColunasTabela::Key, itemChave);
    });
}

