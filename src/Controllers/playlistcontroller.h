#pragma once

#include <QObject>
#include "Dao/playlist.h"
#include "Dao/playlists.h"
#include "Dao/playlistdao.h"
#include "Dao/usuario.h"

class PlayListController: public QObject
{
    Q_OBJECT
public:
    PlayListController();

    void loadAll();
    void clearAll();
    bool addicionarPlaylist(PlayList *playlist);
    bool removerPlaylist(PlayList *playlist);
    Usuario *usuario() const;
    void setUsuario(Usuario *usuario);

    Playlists playlists() const;

private:
    PlayList *m_playlistAtual;
    Playlists m_playlists;
    Usuario *m_usuario;

signals:
    void on_playlistsChanged();
    void on_playlistsCarregado();
};

