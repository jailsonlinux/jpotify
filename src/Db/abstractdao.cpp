#include "abstractdao.h"
#include "QUuid"

/**
 * @brief AbstractDao::AbstractDao
 * sqlite tip: Cada conexcao tem um identificador unico internamente.
 * gerenciado pelo QDatabase do Qt.
 */
AbstractDao::AbstractDao():
    m_connId(QUuid::createUuid().toString()),
    m_dbConn(create(m_connId))
{}

/**
 * @brief AbstractDao::~AbstractDao
 * cuida do fechamento do QSqlDatabase na destruicao.
 */
AbstractDao::~AbstractDao()
{
    m_dbConn = QSqlDatabase();
    destroy(m_connId);
}

/**
 * @brief AbstractDao::openConnection
 * @return verdadeiro se conexao foi aberta.
 */
bool AbstractDao::openConnection()
{
    return connect(m_connId);
}

/**
 * @brief AbstractDao::isOpen
 * @return verdadeiro se conectado.
 */
bool AbstractDao::isOpen()
{
    return connected(m_connId);
}

/**
 * @brief AbstractDao::closeConnection
 * fecha um conexao.
 */
void AbstractDao::closeConnection()
{
    disconect(m_connId);
}

/**
 * @brief AbstractDao::getConnection
 * @return retorna a conexao atual.
 */
QSqlDatabase &AbstractDao::getConnection()
{
    return m_dbConn;
}
