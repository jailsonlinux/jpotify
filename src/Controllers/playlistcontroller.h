#pragma once

#include <QObject>
#include "Dao/playlist.h"
#include "Dao/playlists.h"
#include "Dao/playlistdao.h"
#include "Dao/usuario.h"
#include "Dao/musica.h"
#include "Dao/musicasdao.h"

class PlayListController: public QObject
{
    Q_OBJECT
public:
    explicit PlayListController();

    void loadAll();
    void clearAll();
    bool addicionarPlaylist(PlayList *playlist);
    bool removerPlaylist(PlayList *playlist);
    void setUsuario(Usuario *usuario);
    void adicionarMusicaAPlaylist(const int playlistId, Musica *musica);

    Playlists playlists() const;
    Usuario *usuario() const;

private:
    PlayList *m_playlistAtual;
    Playlists m_playlists;
    Usuario *m_usuario;

signals:
    void on_playlistsChanged();
    void on_playlistsCarregado();
};

