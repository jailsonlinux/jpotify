#pragma once

#include "dbconn.h"

/**
 * @brief The AbstractDao class
 * Herda de DbConn, pois cada DAO gerencia sua propria conexao/transacao com o banco.
 * Todas classes de persistencia de DTO's(Data transfer objects), derivam desta.
 * TypeQuery: pode-se implementar retornar todos os registros, ou por id/pk unico da base.
 * createTable: deve ser implementada para cada DAO  iniciar sua propria tabela na base.
 */
class AbstractDao : public DbConn
{
public:
    explicit AbstractDao();
    ~AbstractDao();

    enum class TypeQuery
    {
        All = 1,
        Id  = 2,
        Nome = 3
    };

    bool openConnection();
    bool isOpen();
    void closeConnection();

    QSqlDatabase &getConnection();

    virtual void createTable() = 0;

private:
    QString m_connId;
    QSqlDatabase m_dbConn;
};

