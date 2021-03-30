#include "musicalist.h"

/**
 * @brief MusicaList::~MusicaList
 * limpa a lista antes de destruir.
 */
MusicaList::~MusicaList()
{
    clear();
}

/**
 * @brief MusicaList::clear
 * efetiva uma limpeza na lista de musicas.
 */
void MusicaList::clear()
{
    m_musicas.clear();
}

/**
 * @brief MusicaList::size
 * @return quantidade de itens na lista.
 */
int MusicaList::size() const
{
    return m_musicas.size();
}

/**
 * @brief MusicaList::addMusica
 * @param musica
 * adiciona musica a lista.
 */
void MusicaList::addMusica(Musica *musica)
{
    m_musicas.append(musica);
}

/**
 * @brief MusicaList::removeUsuario
 * @param musica
 */
void MusicaList::removeMusica(Musica *musica)
{
    m_musicas.removeOne(musica);
}

/**
 * @brief MusicaList::addMusicas
 * @param musicas
 * adiciona musicas a lista atual.
 */
void MusicaList::addMusicas(MusicaList *musicas)
{
    m_musicas.append(musicas->getMusicas());
}

/**
 * @brief MusicaList::getMusicaByName
 * @param nome
 * @return
 */
Musica *MusicaList::getMusicaByName(const QString &nome)
{
    auto u = std::find_if(std::begin(m_musicas), std::end(m_musicas),
                  [&](Musica *musica){
        return musica->nome() == nome;
    });

    if(u != m_musicas.end()) {
        return u.i->t();
    }

    return nullptr;
}

/**
 * @brief MusicaList::getMusicaByKey
 * @param key
 * @return musica pela chave unica que identifica o recurso na api.
 */
Musica *MusicaList::getMusicaByKey(const QString key)
{
    auto u = std::find_if(std::begin(m_musicas), std::end(m_musicas),
                  [&](Musica *musica){
        return musica->key() == key;
    });

    if(u != m_musicas.end()) {
        return u.i->t();
    }

    return nullptr;
}

/**
 * @brief MusicaList::getMusicas
 * @return
 */
QList<Musica *> MusicaList::getMusicas() const
{
    return m_musicas;
}

/**
 * @brief MusicaList::setMusicas
 * @param musicas
 */
void MusicaList::setMusicas(const QList<Musica *> &musicas)
{
    m_musicas = musicas;
}
