#pragma once
#include <QString>
#include <QtSql/QSqlDatabase>

class DbConn{
public:
    explicit DbConn() = default;
    ~DbConn() = default;

    static bool connect(const QString &connId);

    static bool connected(const QString &connId);

    static void disconect(const QString &connId);

    static QSqlDatabase create(const QString &connId);

    static void destroy(const QString &connId);

    static bool initDb(const QString &script);

    //AbstractDao precisa acessar essas funcionalidade da conexão;
    friend class AbstractDao;
};

