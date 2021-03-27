#pragma once

#include <QWidget>

#include "Api/api.h"
#include "Dao/usuario.h"
#include "Controllers/usuarioscontroller.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();


    Usuario *getUsuario() const;
    void setUsuario(Usuario *value);
    void reloadComboUsuarios();
signals:
    void on_loginsucess();
    void on_loginErro();
    void on_loginCancel();

private slots:
    void habilitaBotaoLogin();

    void preencheUsuario(const QString &nome);
    void onLoginSucess();

    void on_btnLogin_clicked();
    void on_btnCancelar_clicked();
    void on_edtNome_textChanged(const QString &arg1);
    void on_edtUsuario_textChanged(const QString &arg1);
    void on_edtSecret_textChanged(const QString &arg1);

    void on_cmbUsuarios_currentIndexChanged(int index);

    void on_btnRemove_clicked();

private:

    Ui::Login *ui;
    Usuario *usuario;
    UsuariosController *usuariosController;
    Api *api;
};

