#include "musicasdao.h"

/**
 * @brief MusicasDao::MusicasDao
 * @param playlistId
 * @param key
 * construção da lista de músicas está associada a uma playlist.
 */
MusicasDao::MusicasDao(const int playlistId) :
    m_tablename(QStringLiteral("musicas"))
  , m_playlistid{playlistId}

{
    createTable();
}

/**
 * @brief MusicasDao::loadAll
 * @param musicas
 * @return verdadeiro se consulta preencher com todas musicas da Playlist cadastrada.
 */
bool MusicasDao::loadAll(MusicaList *musicas)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(getQueryStr(TypeQuery::All));
    return readData(query, musicas);
}

/**
 * @brief MusicasDao::loadFromId
 * @param musicas
 * @param key
 * @return verdadeiro, se consulta preencher com musicas da key informada.
 * restrito ao id da playlist.
 */
bool MusicasDao::loadFromKey(MusicaList *musicas, const QString &key)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    QString qry = getQueryStr(TypeQuery::All);
    qry += QStringLiteral(" AND key = :key");
    query.prepare(qry);
    query.bindValue(QStringLiteral(":key"), key);
    return readData(query, musicas);
}

/**
 * @brief MusicasDao::add
 * @param musica
 * @return  verdadeiro, se persiste as musica na base local.
 */
bool MusicasDao::add(Musica *musica)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("INSERT OR REPLACE INTO %1 (key, playlistid, nome, artista, album, duracao, ordem, track, previewUrl, imagem) "
                                 "VALUES(:key, :playlistid, :nome, :artista, :album, :duracao, :ordem, :track, :previewUrl, :imagem)").arg(m_tablename));
    query.bindValue(QStringLiteral(":key"), musica->key());
    query.bindValue(QStringLiteral(":playlistid"), m_playlistid);
    query.bindValue(QStringLiteral(":nome"), musica->nome());
    query.bindValue(QStringLiteral(":artista"), musica->artista());
    query.bindValue(QStringLiteral(":album"), musica->album());
    query.bindValue(QStringLiteral(":duracao"), musica->duracao());
    query.bindValue(QStringLiteral(":ordem"), musica->ordem());
    query.bindValue(QStringLiteral(":track"), musica->track());
    query.bindValue(QStringLiteral(":previewUrl"), musica->previewUrl());
    query.bindValue(QStringLiteral(":imagem"), musica->imagem());

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Erro tentando inserir nova musica" << query.lastError().text();

    closeConnection();
    return exec;
}

/**
 * @brief MusicasDao::remove
 * @param musica
 * @return verdadeiro se musica for removida .
 */
bool MusicasDao::remove(Musica *musica)
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("DELETE FROM %1 WHERE key=:key AND playlistid=:playlistid").arg(m_tablename));
    query.bindValue(QStringLiteral(":key"), musica->key());
    query.bindValue(QStringLiteral(":playlistid"), m_playlistid);

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Erro tentando remover musica." << query.lastError().text();

    closeConnection();
    return exec;
}

/**
 * @brief MusicasDao::removeAll
 * @return verdadeiro se remover todas as musicas de determinada playlist.
 */
bool MusicasDao::removeAll()
{
    if (!openConnection()) {
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("DELETE FROM %1 WHERE playlistid=:playlistid").arg(m_tablename));
    query.bindValue(QStringLiteral(":playlistid"), m_playlistid);

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Erro tentando remover todas as musicas da playlist." << query.lastError().text();

    closeConnection();
    return exec;
}

/**
 * @brief MusicasDao::playlistid
 * @return identificador da playlist a qual a musica pertence. Chave composta, e Fk da tabela playlist.
 */
int MusicasDao::playlistid() const
{
    return m_playlistid;
}

/**
 * @brief MusicasDao::setPlaylistid
 * @param playlistid
 * define identificador da playlist.
 */
void MusicasDao::setPlaylistid(int playlistid)
{
    m_playlistid = playlistid;
}

/**
 * @brief MusicasDao::createTable
 * cria a tabela caso ela nao exista na base.
 */
void MusicasDao::createTable()
{
    if (!openConnection()) {
        return;
    }

    const QString createTableStr(QStringLiteral("CREATE TABLE IF NOT EXISTS %1 ("
                                                "key	TEXT, "
                                                "playlistid	INTEGER, "
                                                "nome	TEXT, "
                                                "artista	TEXT, "
                                                "album	TEXT, "
                                                "duracao	INTEGER, "
                                                "ordem	INTEGER, "
                                                "track TEXT, "
                                                "previewUrl TEXT, "
                                                "imagem TEXT, "
                                                "PRIMARY KEY('key','playlistid') "
                                                ");").arg(m_tablename));

    QSqlQuery query(getConnection());
    query.prepare(createTableStr);

    if (!query.exec())
        qCritical() << "Erro tentando criar tabela " << m_tablename << ". " << query.lastError().text() << query.lastQuery();

    closeConnection();
}

/**
 * @brief MusicasDao::readData
 * @param query
 * @param musicas
 * @return verdadeiro, caso a execução de consultas seja válida,
 * preenchendo musicas com dados da base.
 */
bool MusicasDao::readData(QSqlQuery &query, MusicaList *musicas)
{
    const bool exec = query.exec();
    if (!exec) {
        qCritical() << "Erro tentando ler dados da tabela " << m_tablename << ". " << query.lastError().text();
    } else {
        constexpr auto fieldKey = 0;
        constexpr auto fieldPlaylistid = 1;
        constexpr auto fieldNome = 2;
        constexpr auto fieldArtista = 3;
        constexpr auto fieldAlbum = 4;
        constexpr auto fieldDuracao = 5;
        constexpr auto fieldOrdem = 6;
        constexpr auto fieldTrack = 7;
        constexpr auto fieldPreviewUrl = 8;
        constexpr auto fieldImagem = 9;

        musicas->clear();
        while (query.next()) {
            Musica *musica = new Musica;

            musica->setKey(query.value(fieldKey).toString());
            musica->setPlaylistid(query.value(fieldPlaylistid).toInt());
            musica->setNome(query.value(fieldNome).toString());
            musica->setArtista(query.value(fieldArtista).toString());
            musica->setAlbum(query.value(fieldAlbum).toString());
            musica->setDuracao(query.value(fieldDuracao).toInt());
            musica->setOrdem(query.value(fieldOrdem).toInt());
            musica->setTrack(query.value(fieldTrack).toString());
            musica->setPreviewUrl(query.value(fieldPreviewUrl).toString());
            musica->setImagem(query.value(fieldImagem).toString());

            musicas->addMusica(musica);
        }
    }

    closeConnection();
    return exec;
}

/**
 * @brief MusicasDao::getQueryStr
 * @param type
 * @return consulta SQL com todos os campos da tabela para as musicas da playlist.
 */
QString MusicasDao::getQueryStr(AbstractDao::TypeQuery type)
{
    QString queryStr(QStringLiteral("SELECT key, playlistid, nome, artista, album, duracao, ordem, track, previewUrl, imagem "));
    queryStr += QStringLiteral(" FROM %1  WHERE playlistid = %2 ").arg(m_tablename).arg(m_playlistid);

    if(type == TypeQuery::All){
        qInfo() << "Retornando consulta para todos os dados da tabela.";
    }

    return queryStr;
}

/**
 * @brief MusicasDao::getQueryStr
 * @param type
 * @param id
 * @return consulta SQL com todos os campos da tabel para o usuario da playlist,
 * aplicando a condição do identificador unico de uma musica da playlist.
 */
QString MusicasDao::getQueryStr(AbstractDao::TypeQuery type, const QString key)
{
    QString queryStr = getQueryStr(TypeQuery::All);
    if(type == TypeQuery::Id){
      queryStr += QStringLiteral(" AND key = %1 ").arg(key);
    }

    return queryStr;
}
