#include "playlists.h"
#include "playlist.h"

#include <QVariantMap>
#include <algorithm>

#include <QJsonDocument>
#include <QDebug>
#include <QMutableListIterator>

/**
 * @brief Playlists::~Playlists
 * limpa playlists antes de destruir.
 */
Playlists::~Playlists()
{
    clear();
}

/**
 * @brief Playlists::getPlaylists
 * @return lista com playlists adicionadas.
 */
QList<PlayList *> Playlists::getPlaylists()
{
    return m_playlists;
}

/**
 * @brief Playlists::clear
 * percorre os itens da lista removendo-os e deixando a lista vazia.
 */
void Playlists::clear()
{
    //ToDo: Em c++ ou em Qt nativo???
    //    std::for_each(std::begin(m_playlists), std::end(m_playlists),
    //                  [&](PlayList *item) {
    //                        delete item;
    //    });
    //    if(!m_playlists.isEmpty()){
    //        //qDeleteAll(m_playlists);
    //        m_playlists.clear();
    //    }

    //    m_playlists.erase(std::remove(m_playlists.begin(), m_playlists.end(), m_playlists.end()));
    m_playlists.clear();
}

/**
 * @brief Playlists::getSize
 * @return tamanho da lista.
 */
int Playlists::getSize() const
{
    return m_playlists.size();
}

/**
 * @brief Playlists::addPlaylist
 * @param playlist
 * adiciona uma playlist a lista.
 */
void Playlists::addPlaylist(PlayList *playlist)
{
    m_playlists.append(playlist);
}

/**
 * @brief Playlists::removePlaylistByName
 * @param playlistName
 * remove uma playlist pelo nome caso exista.
 */
void Playlists::removePlaylistByName(const QString &playlistName)
{
    auto *playlist = getPlaylistByName(playlistName);
    if(playlist != nullptr)
        m_playlists.removeAll(playlist);
}

/**
 * @brief Playlists::removePlaylistById
 * @param id
 * remove uma playlist da lista pelo id caso exista.
 */
void Playlists::removePlaylistById(const int id)
{
    auto *playlist = getPlaylistById(id);
    if(playlist != nullptr)
        m_playlists.removeAll(playlist);
}

/**
 * @brief Playlists::getPlaylistById
 * @param id
 * @return uma playlist pelo id.
 */
PlayList *Playlists::getPlaylistById(const int id)
{
    auto itr = std::find_if(m_playlists.begin(), m_playlists.end(), [&](PlayList* playlist) { return playlist->getId() == id; });
    if(itr != m_playlists.end()) {
        return (*itr);
    }

    return nullptr;
}

/**
 * @brief Playlists::getPlaylistByName
 * @param playlistName
 * @return uma playlist pelo nome.
 */
PlayList *Playlists::getPlaylistByName(const QString &playlistName)
{
    auto itr = std::find_if(m_playlists.begin(), m_playlists.end(), [&](PlayList* playlist) { return playlist->nome() == playlistName; });
    if(itr != m_playlists.end()) {
        return (*itr);
    }
    return nullptr;
}

/**
 * @brief Playlists::getUsuarioid
 * @return o id do usuario dono das playlist.
 */
int Playlists::getUsuarioid() const
{
    return m_userid;
}

/**
 * @brief Playlists::setUsuarioid
 * @param userid
 * define o usuario da playlist.
 */
void Playlists::setUsuarioid(int userid)
{
    m_userid = userid;
}
