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
