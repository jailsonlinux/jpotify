#include "uiresultadopesquisa.h"
#include "ui_uiresultadopesquisa.h"

#include <QUrl>
#include <QtDebug>
#include <QWidget>
#include <QPoint>
#include <QMenu>

ResultadoPesquisa::ResultadoPesquisa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultadoPesquisa)
{
    ui->setupUi(this);
    ui->tabelaResultados->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tabelaResultados, &QTableWidget::customContextMenuRequested, this, &ResultadoPesquisa::addplaylistMenuRequested);
}

ResultadoPesquisa::~ResultadoPesquisa()
{
    delete ui;
}

void ResultadoPesquisa::addplaylistMenuRequested(QPoint pos){
    QMenu *menu = new QMenu();
    QMenu* mnuPlaylists = menu->addMenu("Adicionar à playlist->");

    QList<QAction *> actionsPlaylist;

    std::for_each(std::begin(m_playlists.getPlaylists()), std::end(m_playlists.getPlaylists()), [&](PlayList *playlist){
        actionsPlaylist.append( new QAction(playlist->nome()));
    });
    mnuPlaylists->addActions(actionsPlaylist);

    menu->popup(ui->tabelaResultados->viewport()->mapToGlobal(pos));
}

void ResultadoPesquisa::resizeEvent(QResizeEvent *event)
{
    constexpr int col0 = 60;
    constexpr int col3 = 120;
    constexpr int col4 = 1;
    const int col1 = (this->width() - (col0-10 + col3)) / 2;
    const int col2 = (this->width() - (col0-10 + col3)) / 2;

    ui->tabelaResultados->setColumnWidth(0, col0); //id
    ui->tabelaResultados->setColumnWidth(1, col1); //nome
    ui->tabelaResultados->setColumnWidth(2, col2); //album
    ui->tabelaResultados->setColumnWidth(3, col3);  //tempo
    ui->tabelaResultados->setColumnWidth(4, col4);  //chave escondida
    ui->tabelaResultados->setColumnHidden(4, true);
    QWidget::resizeEvent(event);
}

void ResultadoPesquisa::setPlaylists(Playlists playlists)
{
    m_playlists = playlists;
}

void ResultadoPesquisa::setMusicaList(MusicaList *musicaList)
{
    m_musicaList = musicaList;

    preencheGrid();
}

void ResultadoPesquisa::setTermo(const QString &termo)
{
    ui->lblTodas->setText(QStringLiteral("%1 referências encontradas para a pesquisa: %2").arg(m_musicaList->size()).arg(termo));
}

void ResultadoPesquisa::preencheGrid()
{
    ui->tabelaResultados->clearContents();
    ui->tabelaResultados->setRowCount(0);

    std::for_each(std::begin(m_musicaList->getMusicas()), std::end(m_musicaList->getMusicas()), [=](Musica *musica){
        ui->tabelaResultados->insertRow(ui->tabelaResultados->rowCount());
        qDebug() << "url imagem:" << musica->imagem();

        //ToDo: Ler icones para Col 0...


        ui->tabelaResultados->setItem( ui->tabelaResultados->rowCount()-1,
                                       0,
                                       new QTableWidgetItem(QString::number(ui->tabelaResultados->rowCount()).rightJustified(2, '0')));

        ui->tabelaResultados->setItem(ui->tabelaResultados->rowCount()-1,
                                      1,
                                      new QTableWidgetItem(musica->nome()));

        ui->tabelaResultados->setItem( ui->tabelaResultados->rowCount()-1,
                                       2,
                                       new QTableWidgetItem(musica->album()));

        ui->tabelaResultados->setItem( ui->tabelaResultados->rowCount()-1,
                                       3,
                                       new QTableWidgetItem(musica->getDuracaoMinSec()));

        //Esconde a chave aqui
        ui->tabelaResultados->setItem( ui->tabelaResultados->rowCount()-1,
                                       3,
                                       new QTableWidgetItem(musica->key()));

    });
}

