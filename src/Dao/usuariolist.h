#pragma once

#include <QObject>
#include <QList>

#include "usuario.h"

class UsuarioList
{
public:
    explicit UsuarioList() = default;
    ~UsuarioList();
    void clear();
    int size() const;
    void addUsuario(Usuario *usuario);
    void removeUsuario(Usuario *usuario);
    Usuario *getUsuarioByName(const QString &nome);
    Usuario *getUsuarioById(const int id);
    Usuario *getUsuarioByClientId(const QString &clientid);

    QList<Usuario *> getUsuarios() const;
    void setUsuarios(const QList<Usuario *> &usuarios);

private:
    QList<Usuario *> m_usuarios;

};

