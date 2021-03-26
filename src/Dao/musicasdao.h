#pragma once

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

#include "../Db/abstractdao.h"
#include "musica.h"
#include "musicalist.h"

class MusicasDao: public AbstractDao
{
    const QString m_tablename;

public:
    explicit MusicasDao(const int playlistId);
    bool loadAll( MusicaList *musicas );
    bool loadFromKey(MusicaList *musicas, const QString &key);
    bool add(Musica *musica);
    bool remove(Musica *musica);
    bool removeAll();

    int playlistid() const;
    void setPlaylistid(int playlistid);

private:
    int m_playlistid;
    void createTable() override;
    bool readData(QSqlQuery &query, MusicaList *musicas);
    QString getQueryStr(TypeQuery type);
    QString getQueryStr(TypeQuery type, const QString key);
};

