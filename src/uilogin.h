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
    void preencheUsuario(Usuario *usuario);

signals:
    void on_escolheuUsuario();
    void on_loginErro();
    void on_loginCancel();

private slots:
    void habilitaBotaoLogin();


    void on_btnLogin_clicked();
    void on_btnCancelar_clicked();
    void on_edtNome_textChanged(const QString &arg1);
    void on_edtUsuario_textChanged(const QString &arg1);
    void on_edtSecret_textChanged(const QString &arg1);

    void on_cmbUsuarios_currentIndexChanged(int index);

    void on_btnRemove_clicked();

private:
    void reloadComboUsuarios();

    Ui::Login *ui;
    Usuario *m_usuario;
    UsuariosController *usuariosController;
    Api *api;
};

