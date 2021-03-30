#include "playlist.h"
#include <QTime>

/**
 * @brief PlayList::PlayList
 * constroi instancia iniando com valores defaults.
 */
PlayList::PlayList():
    m_id{0},
    m_userid{0},
    m_nome(""),
    m_descricao(""),
    m_apiid("")
{

}

/**
 * @brief PlayList::getId
 * @return identificacao unica da playlist.
 */
int PlayList::getId() const
{
    return m_id;
}

/**
 * @brief PlayList::setId
 * @param id
 * definine identificador unico da playlist.
 */
void PlayList::setId(int id)
{
    m_id = id;
}

/**
 * @brief PlayList::userid
 * @return identificacao unica de usuário por playlist.
 */
int PlayList::userid() const
{
    return m_userid;
}

/**
 * @brief PlayList::setUsuarioid
 * @param userid
 * definine identificador unico de usuário da playlist.
 */
void PlayList::setUsuarioid(int userid)
{
    m_userid = userid;
}

/**
 * @brief PlayList::nome
 * @return nome que identifica a playlist.
 */
QString PlayList::nome() const
{
    return m_nome;
}

/**
 * @brief PlayList::setNome
 * @param nome
 * define um nome para playlist.
 */
void PlayList::setNome(const QString &nome)
{
    m_nome = nome;
}

/**
 * @brief PlayList::descricao
 * @return descritivo da playlist.
 */
QString PlayList::descricao() const
{
    return m_descricao;
}

/**
 * @brief PlayList::setDescricao
 * @param descricao
 * define uma descricao para playlist
 */
void PlayList::setDescricao(const QString &descricao)
{
    m_descricao = descricao;
}

/**
 * @brief PlayList::apiId
 * @return identificação de acesso ao recurso, caso playlist salva.
 */
QString PlayList::apiId() const
{
    return m_apiid;
}

/**
 * @brief PlayList::setApiid
 * @param value
 * define identificador do recurso pela api.
 */
void PlayList::setApiid(const QString &value)
{
    m_apiid = value;
}

/**
 * @brief PlayList::getMusicas
 * @return lista de objetos musicas/tracks relacionadas a esta playlist.
 */
MusicaList *PlayList::getMusicas()
{
    return &m_musicas;
}

/**
 * @brief PlayList::setMusicas
 * @param musicas
 * define lista de musicas para esta lista.
 */
void PlayList::setMusicas(MusicaList *&musicas)
{
    m_musicas.clear();
    m_musicas.addMusicas(musicas);
}

QString PlayList::getDuracaoToString()
{
    QTime inicio(0,0,0,0);
    QTime total;
    std::for_each(std::begin(m_musicas.getMusicas()), std::end(m_musicas.getMusicas()), [&](Musica *musica){
       total = inicio.addMSecs(musica->duracao());
    });

    return total.toString("mm:ss");
}

QTime PlayList::getDuracaoTotal()
{
    QTime inicio(0,0,0,0);
    std::for_each(std::begin(m_musicas.getMusicas()), std::end(m_musicas.getMusicas()), [&](Musica *musica){
       inicio = inicio.addMSecs(musica->duracao());
    });

    return inicio;
}
