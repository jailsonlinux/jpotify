#pragma once

#include <QObject>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

#include "../Db/abstractdao.h"
#include "usuario.h"
#include "usuariolist.h"

class Usuario;
class UsuarioList;

class UsuariosDao : public AbstractDao
{
    const QString m_tablename;
public:
    UsuariosDao();
     ~UsuariosDao() = default;
    bool loadAll(UsuarioList *usuarioslist);
    bool loadFromId(UsuarioList *usuarioslist, const int id);
    bool loadFromNome(UsuarioList *usuarioslist, const QString &nome);
    bool add(Usuario *user);    
    bool remove(Usuario *user);

private:
    void createTable() override;
    bool read(QSqlQuery &query, UsuarioList *usuarioslist);
    QString getQueryStr(TypeQuery type);    
};

