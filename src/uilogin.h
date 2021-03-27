#pragma once

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();


signals:
    void on_loginsucess();
    void on_loginErro();
    void on_loginCancel();

private slots:
    void on_btnLogin_clicked();

    void on_btnCancelar_clicked();

    void on_cmbUsuarios_currentIndexChanged(const QString &arg1);

private:
    Ui::Login *ui;
};

