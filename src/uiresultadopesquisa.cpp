#include "uiresultadopesquisa.h"
#include "ui_uiresultadopesquisa.h"

#include <QUrl>
#include <QtDebug>
#include <QWidget>
#include <QPoint>
#include <QMenu>
#include "widgetutil.h"

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
    //Devido a semelhança da pesquisa com a playlist do usuario, foi centralizado numa util..
    WidgetUtil::resizeGrid(this->width(), ui->tabelaResultados);
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
    WidgetUtil::preencheGrid(ui->tabelaResultados, m_musicaList);
}

