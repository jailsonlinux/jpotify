#include "Controllers/playlistcontroller.h"

/**
 * @brief PlayListController::PlayListController
 * Controlar o uso de playlists e suas respectivas associações de usuario e musicas.
 */
PlayListController::PlayListController():
    m_playlistAtual(new PlayList),
    m_usuario(new Usuario)
{

}

/**
 * @brief PlayListController::loadAll
 * Ao ler todas playlists, associar suas musicas.
 */
void PlayListController::loadAll()
{
    PlaylistDao playlistDao = PlaylistDao(m_usuario->id());
    if(playlistDao.loadAll(&m_playlists)){
        std::for_each(std::begin(m_playlists.getPlaylists()), std::end(m_playlists.getPlaylists()), [&](PlayList *playlist){
            MusicasDao musicasDao = MusicasDao(playlist->getId());
            musicasDao.loadAll(playlist->getMusicas());
            qDebug() << "Qtd de musicas na pl: " << playlist->getMusicas()->size();
        });

        emit on_playlistsCarregado();
    }
}

/**
 * @brief PlayListController::clearAll
 *Limpar todas as playlists e suas musicas associadas.
 */
void PlayListController::clearAll()
{
    PlaylistDao playlistDao = PlaylistDao(m_usuario->id());
    std::for_each(std::begin(m_playlists.getPlaylists()), std::end(m_playlists.getPlaylists()), [&](PlayList *playlist){
        MusicasDao musicasDao = MusicasDao(playlist->getId());
        musicasDao.removeAll();
        playlist->getMusicas()->clear();
    });

    if(playlistDao.removeAll()){
        m_playlists.clear();
        m_playlistAtual = nullptr;

        emit on_playlistsChanged();
    }
}

/**
 * @brief PlayListController::addicionarPlaylist
 * @param playlist
 * @return verdadeiro, se playlist adicionada co sucesso.
 */
bool PlayListController::addicionarPlaylist(PlayList *playlist)
{
    PlaylistDao playlistDao = PlaylistDao(m_usuario->id());
    const bool adicionou = playlistDao.add(playlist);
    if(adicionou)
        emit on_playlistsChanged();

    return adicionou;
}

/**
 * @brief PlayListController::removerPlaylist
 * @param playlist
 * @return verdadeiro, ao remover uma playlist e suas musicas associadas.
 */
bool PlayListController::removerPlaylist(PlayList *playlist)
{
    PlaylistDao playlistDao = PlaylistDao(m_usuario->id());
    playlistDao.setUsuarioid(m_usuario->id());
    MusicasDao musicasDao = MusicasDao(playlist->getId());
    musicasDao.removeAll();
    playlist->getMusicas()->clear();

    const bool removeu  = playlistDao.remove(playlist);
    if(removeu)
        emit on_playlistsChanged();

    return removeu;
}

/**
 * @brief PlayListController::usuario
 * @return usuario logado fazendo uso dessa instancia controller.
 */
Usuario *PlayListController::usuario() const
{
    return m_usuario;
}

/**
 * @brief PlayListController::setUsuario
 * @param usuario
 * define usuario para esse controler
 */
void PlayListController::setUsuario(Usuario *usuario)
{
    m_usuario = usuario;
}

/**
 * @brief PlayListController::adicionarMusicaAPlaylist
 * @param playlistId
 * @param musica
 * Adiciona musica a playlist sendo gerenciado por esse controler. Associado a um user logado.
 */
void PlayListController::adicionarMusicaAPlaylist(const int playlistId, Musica *musica)
{
    MusicasDao musicaDao = MusicasDao(playlistId);
    if(musicaDao.add(musica)){
        emit on_playlistsChanged();
    }
}

/**
 * @brief PlayListController::playlists
 * @return playlists sendo gerenciada por esse controller.
 */
Playlists PlayListController::playlists() const
{
    return m_playlists;
}
