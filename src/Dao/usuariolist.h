#pragma once

#include <QList>

#include "usuario.h"

class UsuarioList
{
public:
    explicit UsuarioList() = default;
    ~UsuarioList();
    void clear();
    int size() const;
    void addUsuario(Usuario *Usuario);
    void removeUsuario(Usuario *Usuario);
    Usuario *getUsuarioByName(const QString &nome);
    Usuario *getUsuarioById(const int id);
    Usuario *getUsuarioByClientId(const QString &clientid);

private:
    QList<Usuario*> m_usuario;

};

