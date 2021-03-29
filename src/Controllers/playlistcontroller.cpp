#include "Controllers/playlistcontroller.h"

PlayListController::PlayListController()
{

}

void PlayListController::loadAll()
{
    PlaylistDao playlistDao;
    playlistDao.loadAll(&m_playlists);
    emit on_playlistsCarregado();
}

void PlayListController::clearAll()
{
    PlaylistDao playlistDao;
    if(playlistDao.removeAll()){
        m_playlists.clear();
        m_playlistAtual = nullptr;

        emit on_playlistsChanged();
    }
}

bool PlayListController::addicionarPlaylist(PlayList *playlist)
{
    PlaylistDao playlistDao;
    playlistDao.setUsuarioid(m_usuario->id());

    const bool adicionou = playlistDao.add(playlist);
    if(adicionou)
        emit on_playlistsChanged();

    return adicionou;
}

bool PlayListController::removerPlaylist(PlayList *playlist)
{
    PlaylistDao playlistDao;
    playlistDao.setUsuarioid(m_usuario->id());
    const bool removeu  = playlistDao.remove(playlist);
    if(removeu)
        emit on_playlistsChanged();

    return removeu;
}

Usuario *PlayListController::usuario() const
{
    return m_usuario;
}

void PlayListController::setUsuario(Usuario *usuario)
{
    m_usuario = usuario;
}

Playlists PlayListController::playlists() const
{
    return m_playlists;
}
