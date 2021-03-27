#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->btnLogin->setEnabled((!ui->edtNome->text().isEmpty() &&
                              !ui->edtUser->text().isEmpty() &&
                              !ui->edtSecret->text().isEmpty() ));

}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{

}

void Login::on_btnCancelar_clicked()
{
    emit on_loginCancel();
}

void Login::on_cmbUsuarios_currentIndexChanged(const QString &arg1)
{

}
