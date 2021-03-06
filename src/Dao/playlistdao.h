#pragma once

#include <QObject>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

#include "../Db/abstractdao.h"
#include "playlist.h"
#include "playlists.h"

class Playlists;

class PlaylistDao : public AbstractDao
{
    const QString m_tablename;

public:
    PlaylistDao(const int userid);
    PlaylistDao();
    ~PlaylistDao() =default;

    bool loadAll(Playlists *playlists);
    bool loadFromId(Playlists *playlists, const int id);
    bool add(PlayList *playlist);
    bool remove(PlayList *playlist);
    bool removeAll();

    int getUsuarioid() const;
    void setUsuarioid(int userid);

private:
    int m_userid;
    void createTable() override;
    bool readData(QSqlQuery &query, Playlists *playlists);
    QString getQueryStr(TypeQuery type);
    QString getQueryStr(TypeQuery type, const int id);
};

