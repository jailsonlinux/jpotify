#include "playlistdao.h"

/**
 * @brief PlaylistDao::PlaylistDao
 * @param userid
 * construção da playlist está associada a um usuário cadastrado.
 */
PlaylistDao::PlaylistDao(const int userid) :
    m_tablename(QStringLiteral("playlist")),
    m_userid{userid}
{
    createTable();
}

PlaylistDao::PlaylistDao():
    m_tablename(QStringLiteral("playlist"))
{
    createTable();
}

/**
 * @brief PlaylistDao::loadAll
 * @param playlists
 * @return verdadeiro, se consulta preencher com playlists do user cadastrada.
 */
bool PlaylistDao::loadAll(Playlists *playlists)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(getQueryStr(TypeQuery::All));
    return readData(query, playlists);
}

/**
 * @brief PlaylistDao::loadFromId
 * @param playlists
 * @param id
 * @return verdadeiro, se consulta preencher com playlists do id informado.
 */
bool PlaylistDao::loadFromId(Playlists *playlists, const int id)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    QString qry = getQueryStr(TypeQuery::All);
    qry += QStringLiteral(" AND id = :id");
    query.prepare(qry);
    query.bindValue(QStringLiteral(":id"), id);
    return readData(query, playlists);
}

/**
 * @brief PlaylistDao::add
 * @param playlist
 * @return verdadeiro, se persiste a playlist na base local.
 */
bool PlaylistDao::add(PlayList *playlist)
{
    if (!openConnection()) {
        return false;
    }
    QString fieldid = QStringLiteral("");
    QString bindid = QStringLiteral("");

    if(playlist->getId() > 0){
        QString fieldid = QStringLiteral("id, ");
        QString bindid = QStringLiteral(":id, ");
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("INSERT OR REPLACE INTO %1 (%2 userid, nome, descricao, apiid) "
                                 "VALUES(%3  :userid, :nome, :descricao, :apiid)").arg(m_tablename).arg(fieldid).arg(bindid));
    query.bindValue(QStringLiteral(":id"), playlist->getId());
    query.bindValue(QStringLiteral(":userid"), playlist->userid());
    query.bindValue(QStringLiteral(":nome"), playlist->nome());
    query.bindValue(QStringLiteral(":descricao"), playlist->descricao());
    query.bindValue(QStringLiteral(":apiid"), playlist->apiId());

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Erro tentando inserir nova playlist" << query.lastError().text() << "Query: " << query.lastQuery();

    closeConnection();
    return exec;
}

/**
 * @brief PlaylistDao::remove
 * @param playlist
 * @return verdadeiro, se playlist for excluida.
 */
bool PlaylistDao::remove(PlayList *playlist)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("DELETE FROM %1 WHERE id=:id AND userid=:userid").arg(m_tablename));
    query.bindValue(QStringLiteral(":id"), playlist->getId());
    query.bindValue(QStringLiteral(":userid"), playlist->userid());

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Erro tentando remover playlist." << query.lastError().text();

    closeConnection();
    return exec;
}

/**
 * @brief PlaylistDao::removeAll
 * @return verdadeiro, se remover todas as playlists do user.
 */
bool PlaylistDao::removeAll()
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("DELETE FROM %1 WHERE userid=:userid").arg(m_tablename));
    query.bindValue(QStringLiteral(":userid"), m_userid);

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Erro tentando remover todas as playlists do user." << query.lastError().text();

    closeConnection();
    return exec;
}

/**
 * @brief PlaylistDao::getUsuarioid
 * @return id do usuario atual das playlists.
 */
int PlaylistDao::getUsuarioid() const
{
    return m_userid;
}

/**
 * @brief PlaylistDao::setUsuarioid
 * @param userid
 * define o usuario atual na manipulacao da playlist.
 */
void PlaylistDao::setUsuarioid(int userid)
{
    m_userid = userid;
}

/**
 * @brief PlaylistDao::createTable
 * cria a tabela caso ela nao exista na base.
 */
void PlaylistDao::createTable()
{
    if (!openConnection()) {
        return;
    }

    const QString createTableStr(QStringLiteral("CREATE TABLE IF NOT EXISTS %1 ("
                                                "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                "userid	INTEGER NOT NULL,"
                                                "nome	TEXT NOT NULL,"
                                                "descricao	TEXT,"
                                                "apiid	TEXT"
                                                ");").arg(m_tablename));

    QSqlQuery query(getConnection());
    query.prepare(createTableStr);

    if (!query.exec())
        qCritical() << "Erro tentando criar tabela " << m_tablename << ". " << query.lastError().text() << query.lastQuery();

    closeConnection();
}

/**
 * @brief PlaylistDao::readData
 * @param query
 * @param playlists
 * @return verdadeiro, caso a execução de consultas seja válida,
 * preenchendo playlists com dados da base.
 */
bool PlaylistDao::readData(QSqlQuery &query, Playlists *playlists)
{
    const bool exec = query.exec();
    if (!exec) {
        qCritical() << "Erro tentando ler dados da tabela " << m_tablename << ". " << query.lastError().text();
    } else {
        constexpr auto fieldId = 0;
        constexpr auto fieldUsuarioid = 1;
        constexpr auto fieldNome = 2;
        constexpr auto fieldDescricao = 3;
        constexpr auto fieldApiId = 4;

        playlists->clear();
        while (query.next()) {
            PlayList *playlist = new PlayList;

            playlist->setId(query.value(fieldId).toInt());
            playlist->setUsuarioid(query.value(fieldUsuarioid).toInt());
            playlist->setNome(query.value(fieldNome).toString());
            playlist->setDescricao(query.value(fieldDescricao).toString());
            playlist->setApiid(query.value(fieldApiId).toString());

            playlists->addPlaylist(playlist);
        }
    }

    closeConnection();
    return exec;
}

/**
 * @brief PlaylistDao::getQueryStr
 * @param type
 * @return consulta SQL com todos os campos da tabela para o usuario da playlist.
 */
QString PlaylistDao::getQueryStr(AbstractDao::TypeQuery type)
{
    QString queryStr(QStringLiteral("SELECT id, userid, nome, descricao, apiid "));
    queryStr += QStringLiteral(" FROM %1  WHERE userid = %2 ").arg(m_tablename).arg(m_userid);

    if(type == TypeQuery::All){
        qInfo() << "Retornando consulta para todos os dados da tabela.";
    }

    return queryStr;
}

/**
 * @brief PlaylistDao::getQueryStr
 * @param type
 * @param id
 * @return consulta SQL com todos os campos da tabel para o usuario da playlist,
 * aplicando a condição do identificador unico de uma playlist.
 */
QString PlaylistDao::getQueryStr(AbstractDao::TypeQuery type, const int id)
{
    QString queryStr = getQueryStr(TypeQuery::All);
    if(type == TypeQuery::Id){
      queryStr += QStringLiteral(" AND id = %1 ").arg(id);
    }

    return queryStr;
}
