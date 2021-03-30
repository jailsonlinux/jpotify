#include "widgetutil.h"


void WidgetUtil::resizeGrid(int parentWidget, QTableWidget *tabelaResultados)
{
    constexpr int col0{60};
    constexpr int col3{120};
    constexpr int col4{1};
    const int col1 = (parentWidget - (col0-10 + col3)) / 2;
    const int col2 = (parentWidget - (col0-10 + col3)) / 2;

    tabelaResultados->setColumnWidth(WidgetUtil::as_integer(WidgetUtil::ColunasTabela::Indice), col0); //idx
    tabelaResultados->setColumnWidth(WidgetUtil::as_integer(WidgetUtil::ColunasTabela::Nome), col1); //nome
    tabelaResultados->setColumnWidth(WidgetUtil::as_integer(WidgetUtil::ColunasTabela::Album), col2); //album
    tabelaResultados->setColumnWidth(WidgetUtil::as_integer(WidgetUtil::ColunasTabela::Duracao), col3);  //tempo
    tabelaResultados->setColumnWidth(WidgetUtil::as_integer(WidgetUtil::ColunasTabela::Key), col4);  //chave escondida
    tabelaResultados->setColumnHidden(WidgetUtil::as_integer(WidgetUtil::ColunasTabela::Key), true);
}

void WidgetUtil::preencheGrid(QTableWidget *tabelaResultados, MusicaList *musicaList)
{
    tabelaResultados->clearContents();
    tabelaResultados->setRowCount(0);

    std::for_each(std::begin(musicaList->getMusicas()), std::end(musicaList->getMusicas()), [=](Musica *musica){
        tabelaResultados->insertRow(tabelaResultados->rowCount());

        //ToDo: Ler icones para Col 0...
        QTableWidgetItem *itemIndice = new QTableWidgetItem(QString::number(tabelaResultados->rowCount()).rightJustified(2, '0'));
        itemIndice->setFlags(itemIndice->flags() &  ~Qt::ItemIsEditable);
        tabelaResultados->setItem( tabelaResultados->rowCount()-1, WidgetUtil::as_integer(ColunasTabela::Indice), itemIndice);


        QTableWidgetItem *itemNome = new QTableWidgetItem(musica->nome());
        itemNome->setFlags(itemNome->flags() &  ~Qt::ItemIsEditable);
        tabelaResultados->setItem(tabelaResultados->rowCount()-1, WidgetUtil::as_integer(ColunasTabela::Nome), itemNome);

        QTableWidgetItem *itemAlbum = new QTableWidgetItem(musica->album());
        itemAlbum->setFlags(itemAlbum->flags() &  ~Qt::ItemIsEditable);
        tabelaResultados->setItem( tabelaResultados->rowCount()-1, WidgetUtil::as_integer(ColunasTabela::Album), itemAlbum);

        QTableWidgetItem *itemDuracao = new QTableWidgetItem(musica->getDuracaoMinSec());
        itemDuracao->setFlags(itemDuracao->flags() &  ~Qt::ItemIsEditable);
        tabelaResultados->setItem( tabelaResultados->rowCount()-1, WidgetUtil::as_integer(ColunasTabela::Duracao), itemDuracao);

        //Esconde a chave aqui
        QTableWidgetItem *itemChave = new QTableWidgetItem(musica->key());
        itemChave->setFlags(itemChave->flags() &  ~Qt::ItemIsEditable);
        tabelaResultados->setItem( tabelaResultados->rowCount()-1, WidgetUtil::as_integer(ColunasTabela::Key), itemChave);
    });
}
