#pragma once

#include <QObject>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

#include "../Db/abstractdao.h"
#include "user.h"
#include "userlist.h"

class User;
class UserList;

class UsersDao : public AbstractDao
{
    const QString m_tablename;
public:
    UsersDao();
    bool loadAll(UserList *userlists);
    bool loadFromId(UserList *userlists, const int id);
    bool add(User *user);
    bool remove(User *user);


private:
    void createTable() override;
    bool read(QSqlQuery &query, UserList *userlists);
    QString getQueryStr(TypeQuery type);
    QString getQueryStr(TypeQuery type, const int id);

};

