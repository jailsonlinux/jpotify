#include "uiresultadopesquisa.h"
#include "ui_uiresultadopesquisa.h"

ResultadoPesquisa::ResultadoPesquisa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultadoPesquisa)
{
    ui->setupUi(this);
}

ResultadoPesquisa::~ResultadoPesquisa()
{
    delete ui;
}

void ResultadoPesquisa::resizeEvent(QResizeEvent *event)
{
    constexpr int col0 = 120;
    constexpr int col3 = 120;
    const int col1 = (this->width() - (col0 + col3)) / 2;
    const int col2 = (this->width() - (col0 + col3)) / 2;

    ui->tabelaResultados->setColumnWidth(0, col0); //id
    ui->tabelaResultados->setColumnWidth(1, col1); //nome
    ui->tabelaResultados->setColumnWidth(2, col2); //album
    ui->tabelaResultados->setColumnWidth(3, col3);  //tempo
    QWidget::resizeEvent(event);
}

