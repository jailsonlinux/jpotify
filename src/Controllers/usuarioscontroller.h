#pragma once

#include <QObject>
#include "Dao/usuario.h"
#include "Dao/usuariolist.h"
#include "Dao/usuariosdao.h"

class UsuariosController: public QObject
{
    Q_OBJECT
public:
    UsuariosController();

    Usuario *getUsuarioAtual() const;
    void setUsuarioAtual(Usuario *value);

    UsuarioList *getUsuarios() const;
    void setUsuarios(UsuarioList *value);

    void loadAll();
    void addicionaUsuario(Usuario *usuario);
    void removerUsuario(Usuario *usuario);

private:
    Usuario *m_usuarioAtual;
    UsuarioList *m_usuarios;

signals:
    void on_usuariosChanged();
    void on_usuariosLoaded();
    void on_usuarioAdicionado();
    void on_usuarioRemovido();

};

