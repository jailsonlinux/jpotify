#pragma once

#include <QObject>
#include <QMap>
#include <QVariantList>
#include "playlist.h"

class Playlists
{

public:
    explicit Playlists() = default;
    ~Playlists();

    QList<PlayList*> getPlaylists();

    void clear();
    int getSize() const;

    int getUserid() const;
    void setUserid(int userid);

    void addPlaylist(PlayList *playlist);
    void removePlaylistByName(const QString &playlistName);
    void removePlaylistById(const int id);

    PlayList *getPlaylistById(const int id);
    PlayList *getPlaylistByName(const QString &playlistName);

private:
    QList<PlayList*> m_playlists;
    int m_userid;
};
