#include "musica.h"
#include <QTime>

/**
 * @brief Musica::Musica
 * representacao de um Track da api com sua relacao a uma playlist.
 */
Musica::Musica():
    m_key(""),
    m_playlistid{0},
    m_nome(""),
    m_artista(""),
    m_album(""),
    m_duracao{0},
    m_ordem{0},
    m_track(""),
    m_previewUrl(""),
    m_imagem("")
{

}

/**
 * @brief Musica::key
 * @return a chave capturada da api.
 * Faz chave composta com playlistid
 */
QString Musica::key() const
{
    return m_key;
}

/**
 * @brief Musica::setKey
 * @param key
 * define a chave capturada da api
 */
void Musica::setKey(const QString &key)
{
    m_key = key;
}

/**
 * @brief Musica::playlistid
 * @return id da playlist da qual a musica faz parte.
 * faz chave composta com a chave/key da musica da api.
 */
int Musica::playlistid() const
{
    return m_playlistid;
}

/**
 * @brief Musica::setPlaylistid
 * @param playlistid
 * define qual playlist a musica pertence.
 */
void Musica::setPlaylistid(int playlistid)
{
    m_playlistid = playlistid;
}

/**
 * @brief Musica::nome
 * @return o nome da musica.
 */
QString Musica::nome() const
{
    return m_nome;
}

/**
 * @brief Musica::setNome
 * @param nome
 * define o nome da musica.
 */
void Musica::setNome(const QString &nome)
{
    m_nome = nome;
}

/**
 * @brief Musica::artista
 * @return nome do artista
 */
QString Musica::artista() const
{
    return m_artista;
}

/**
 * @brief Musica::setArtista
 * @param artista
 * define o nome do artista.
 */
void Musica::setArtista(const QString &artista)
{
    m_artista = artista;
}

/**
 * @brief Musica::album
 * @return o nome do album/disco a qual pertence.
 */
QString Musica::album() const
{
    return m_album;
}

/**
 * @brief Musica::setAlbum
 * @param album
 * define o nome do album.
 */
void Musica::setAlbum(const QString &album)
{
    m_album = album;
}

/**
 * @brief Musica::duracao
 * @return em segundos a duracao da musica.
 */
int Musica::duracao() const
{
    return m_duracao;
}

/**
 * @brief Musica::setDuracao
 * @param duracao
 * define a duracao
*/
void Musica::setDuracao(int duracao)
{
    m_duracao = duracao;
}

/**
 * @brief Musica::ordem
 * @return a ordem de execucao na playlist.
 */
int Musica::ordem() const
{
    return m_ordem;
}

/**
 * @brief Musica::setOrdem
 * @param ordem
 * define a ordem de execucao na playlist;
 */
void Musica::setOrdem(int ordem)
{
    m_ordem = ordem;
}

/**
 * @brief Musica::track
 * @return identificador da musica na api.
 */
QString Musica::track() const
{
    return m_track;
}

/**
 * @brief Musica::setTrack
 * @param track
 * define identificador da musica.
 */
void Musica::setTrack(const QString &track)
{
    m_track = track;
}

/**
 * @brief Musica::previewUrl
 * @return url de amostra da musica.
 */
QString Musica::previewUrl() const
{
    return m_previewUrl;
}

/**
 * @brief Musica::setPreviewUrl
 * @param previewUrl
 * define url de amostra da musica.
 */
void Musica::setPreviewUrl(const QString &previewUrl)
{
    m_previewUrl = previewUrl;
}

/**
 * @brief Musica::imagem
 * @return url da imagem de exibicao album/musica.
 */
QString Musica::imagem() const
{
    return m_imagem;
}

/**
 * @brief Musica::setImagem
 * @param imagem
 * define uma url de exibicao de imagem do album/musica.
 */
void Musica::setImagem(const QString &imagem)
{
    m_imagem = imagem;
}

/**
 * @brief Musica::getDuracaoMinSec
 * @return duracao formatada para o grid.
 */
QString Musica::getDuracaoMinSec()
{
    QTime tempo(0,0,0,0);
    QTime t;
    t = tempo.addMSecs(m_duracao);    
    return t.toString("mm:ss");

}
