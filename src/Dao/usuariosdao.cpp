#include "usuariosdao.h"

/**
 * @brief UsuariosDao::UsuariosDao
 * constroi instancia definindo qual tabela é do dominio e a iniciando.
 */
UsuariosDao::UsuariosDao():
    m_tablename(QStringLiteral("usuarios"))
{
    createTable();
}

/**
 * @brief UsuariosDao::loadAll
 * @param userslist
 * @return verdadeiro, se consulta a base estiver ok.
 * retornando em userslist todos os usuarios da base.
 */
bool UsuariosDao::loadAll(UsuarioList *usuarioslist)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(getQueryStr(TypeQuery::All));
    return read(query, usuarioslist);
}

/**
 * @brief UsuariosDao::loadFromId
 * @param userslist
 * @param id
 * @return verdadeiro, se consulta a base estiver ok.
 * retornando em userslist o user da base com o id encontrado.
 */
bool UsuariosDao::loadFromId(UsuarioList *usuarioslist, const int id)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(getQueryStr(TypeQuery::Id, id));
    return read(query, usuarioslist);
}

/**
 * @brief UsuariosDao::add
 * @param user
 * @return verdadeiro, se usuario adicionado com sucesso.
 */
bool UsuariosDao::add(Usuario *user)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("INSERT OR REPLACE INTO %1 (id, nome, clientid, secret, access_token, autologin) VALUES(:id, :nome, :clientid, :secret, :access_token, :autologin)").arg(m_tablename));
    query.bindValue(QStringLiteral(":id"), user->id());
    query.bindValue(QStringLiteral(":nome"), user->nome());
    query.bindValue(QStringLiteral(":clientid"), user->clientid());
    query.bindValue(QStringLiteral(":secret"), user->secret());
    query.bindValue(QStringLiteral(":access_token"), user->access_token());
    query.bindValue(QStringLiteral(":autologin"), user->autologin());

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Erro tentando inserir novo usuario" << query.lastError().text();

    closeConnection();
    return exec;
}

/**
 * @brief UsuariosDao::remove
 * @param user
 * @return verdadeiro, se executado com sucesso e removido usuario.
 */
bool UsuariosDao::remove(Usuario *user)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("DELETE FROM %1 WHERE id=:id ").arg(m_tablename));
    query.bindValue(QStringLiteral(":id"), user->id());

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Erro tentando remover usuario" << query.lastError().text();

    closeConnection();
    return exec;
}

/**
 * @brief UsuariosDao::createTable
 * inicia a tabela, caso nao exista.
 */
void UsuariosDao::createTable()
{
    if (!openConnection()) {
        return;
    }

    const QString createTableStr(QStringLiteral("CREATE TABLE IF NOT EXISTS %1 ( "
                                                "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                "nome	TEXT UNIQUE, "
                                                "clientid	TEXT UNIQUE, "
                                                "secret	TEXT, "
                                                "access_token	TEXT,"
                                                "autologin	INTEGER DEFAULT 0 "
                                                ");").arg(m_tablename));

    QSqlQuery query(getConnection());
    query.prepare(createTableStr);

    if (!query.exec())
        qCritical() << "Erro tentando criar tabela " << m_tablename << ". " << query.lastError().text() << query.lastQuery();

    closeConnection();
}

/**
 * @brief UsuariosDao::read
 * @param query
 * @param userslist
 * @return verdadeiro, caso a execução de consultas seja válida,
 * preenchendo usuarios com dados da base.
 */
bool UsuariosDao::read(QSqlQuery &query, UsuarioList *usuarioslist)
{
    const bool exec = query.exec();
    if (!exec) {
        qCritical() << "Erro tentando ler dados da tabela " << m_tablename << ". " << query.lastError().text();
    } else {
        constexpr auto fieldId = 0;
        constexpr auto fieldNome = 1;
        constexpr auto fieldClientId = 2;
        constexpr auto fieldSecret = 3;
        constexpr auto fieldAcessToken = 4;
        constexpr auto fieldAutoLogin = 5;

        usuarioslist->clear();
        while (query.next()) {
            Usuario *user = new Usuario;

            user->setId(query.value(fieldId).toInt());
            user->setNome(query.value(fieldNome).toString());
            user->setClientid(query.value(fieldClientId).toString());
            user->setSecret(query.value(fieldSecret).toString());
            user->setAccess_token(query.value(fieldAcessToken).toString());
            user->setAutologin(query.value(fieldAutoLogin).toBool());

            usuarioslist->addUsuario(user);
        }
    }

    closeConnection();
    return exec;
}

/**
 * @brief UsuariosDao::getQueryStr
 * @param type
 * @return consulta SQL generica para todos os registros da base.
 */
QString UsuariosDao::getQueryStr(AbstractDao::TypeQuery type)
{
    QString queryStr(QStringLiteral("SELECT"));
    queryStr += QStringLiteral(" id, nome, clientid, secret, access_token, autologin");
    queryStr += QStringLiteral(" FROM %1").arg(m_tablename);

    if (type == TypeQuery::All) {
        qInfo() << QStringLiteral("Retornar todos registros da tabela: ") << m_tablename;
    }

    return queryStr;
}

/**
 * @brief UsuariosDao::getQueryStr
 * @param type
 * @param id
 * @return consulta SQL generica para todos os registros da base de determinado id.
 */
QString UsuariosDao::getQueryStr(AbstractDao::TypeQuery type, const int id)
{
    QString queryStr = getQueryStr(type);

    if (type == TypeQuery::Id) {
        queryStr += QStringLiteral(" WHERE id = %1 ").arg(id);
    }

    return queryStr;
}
