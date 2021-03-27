#include "uibiblioteca.h"
#include "ui_uibiblioteca.h"

uiBiblioteca::uiBiblioteca(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::uiBiblioteca)
{
    ui->setupUi(this);
}

uiBiblioteca::~uiBiblioteca()
{
    delete ui;
}
