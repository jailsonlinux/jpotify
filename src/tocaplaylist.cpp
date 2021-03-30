#include "tocaplaylist.h"
#include "ui_tocaplaylist.h"

/**
 * @brief TocaPlaylist::TocaPlaylist
 * @param parent
 */
TocaPlaylist::TocaPlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TocaPlaylist)
{
    ui->setupUi(this);
}

/**
 * @brief TocaPlaylist::~TocaPlaylist
 */
TocaPlaylist::~TocaPlaylist()
{
    delete ui;
}

/**
 * @brief TocaPlaylist::setMusicaList
 * @param musicaList
 */
void TocaPlaylist::setMusicaList(MusicaList *musicaList)
{
    m_musicaList = musicaList;

    preencheGrid();
}

/**
 * @brief TocaPlaylist::setPlaylists
 * @param playlists
 */
void TocaPlaylist::setPlaylists(Playlists playlists)
{
    m_playlists = playlists;

}

/**
 * @brief TocaPlaylist::resizeEvent
 * @param event
 */
void TocaPlaylist::resizeEvent(QResizeEvent *event)
{
    constexpr int col0{60};
    constexpr int col3{120};
    constexpr int col4{1};
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
 * @brief TocaPlaylist::preencheGrid
 */
void TocaPlaylist::preencheGrid()
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
