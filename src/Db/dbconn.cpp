#include "dbconn.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

#include <QDir>
#include <QFile>
#include <QTextStream>

/**
 * @brief DbConn::connect
 * @param connId
 * @return verdadeiro, se conectado, ou forca uma conexao nova.
 */
bool DbConn::connect(const QString &connId)
{
    if (connected(connId))
        return true;

    QSqlDatabase db = QSqlDatabase::database(connId);
    if (db.open()){
        return true;
    }

    qCritical() << "Error ao se conectar com o banco de dados: " << connId << ": " << db.lastError();
    return false;
}

/**
 * @brief DbConn::connected
 * @param connId
 * @return verdadeiro, se conectado.
 */
bool DbConn::connected(const QString &connId)
{
    return QSqlDatabase::database(connId).isOpen();
}

/**
 * @brief DbConn::disconect
 * @param connId
 * desconecta, caso conectado.
 */
void DbConn::disconect(const QString &connId)
{
    if (connected(connId))
        QSqlDatabase::database(connId).close();
}

/**
 * @brief DbConn::create
 * @param connId
 * @return inicia o banco de dados nos caminhos,
 * criando-os caso nao exista.
 * Define identificadores para a base 'global' do QSqlDatabase.
 */
QSqlDatabase DbConn::create(const QString &connId)
{
    const QString dbPath(QStringLiteral("%1/database").arg(ROOT_PATH));
    QDir dir;

    if (!dir.exists(dbPath))
        dir.mkpath(dbPath);

    const QString &databaseName(QStringLiteral("%1/jspot.db").arg(dbPath));
    qDebug() << "BD em: " << databaseName;

    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), connId);
    db.setDatabaseName(databaseName);

    //    if(!initDb(QStringLiteral("%1/jspot.sql").arg(dbPath)))
    //        return db;

    return db;
}

/**
 * @brief DbConn::destroy
 * @param connId
 * destroy as conexoes pelo identificador.
 */
void DbConn::destroy(const QString &connId)
{
    if (QSqlDatabase::contains(connId))
        QSqlDatabase::removeDatabase(connId);
}

/**
 * @brief DbConn::initDb
 * @param script
 * @return verdadeiro, caso encontre e execute script unico de criacao da base.
 * *deprecated. sem uso no momento...pois cada tabela pode se iniciar,e, o
 * sqlite cria a base no path.
 */
bool DbConn::initDb(const QString &script)
{
    QFile file(script);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    QSqlDatabase db = create("uid");

    db.transaction();
    QSqlQuery query;
    const QString qry = in.readAll();
    if(!query.exec(qry)){
        qCritical() << "Erro ao iniciar o banco em: " << script;
        qCritical() << "Error: " << db.lastError();
        return false;
    }
    db.commit();
    return true;

}
