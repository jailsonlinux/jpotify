#include "uiusuarios.h"
#include "ui_uiusuarios.h"

Usuarios::Usuarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Usuarios)
{
    ui->setupUi(this);
}

Usuarios::~Usuarios()
{
    delete ui;
}
