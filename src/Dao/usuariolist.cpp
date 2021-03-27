#include "usuariolist.h"

#include <QDebug>
#include <algorithm>

/**
 * @brief UsuarioList::~UsuarioList
 * limpa a lista antes de destruir.
 */
UsuarioList::~UsuarioList()
{
    clear();
}

/**
 * @brief UsuarioList::clear
 * efetiva uma limpeza na lista de usuarios.
 */
void UsuarioList::clear()
{
    m_usuario.clear();
}

/**
 * @brief UsuarioList::size
 * @return quantidade de itens na lista.
 */
int UsuarioList::size() const
{
    return m_usuario.size();
}

/**
 * @brief UsuarioList::addUsuario
 * @param Usuario
 * adiciona um usuario a lista.
 */
void UsuarioList::addUsuario(Usuario *Usuario)
{
    m_usuario.append(Usuario);
}

/**
 * @brief UsuarioList::removeUsuario
 * @param Usuario
 * remove um usuario da lista.
 */
void UsuarioList::removeUsuario(Usuario *Usuario)
{
    m_usuario.removeOne(Usuario);
}

/**
 * @brief UsuarioList::getUsuarioByName
 * @param nome
 * @return um Usuario pelo nome, caso exista na lista.
 */
Usuario *UsuarioList::getUsuarioByName(const QString &nome)
{
    auto u = std::find_if(std::begin(m_usuario), std::end(m_usuario),
                  [&](Usuario *Usuario){
        return Usuario->nome() == nome;
    });

    return u.i->t();
}

/**
 * @brief UsuarioList::getUsuarioById
 * @param id
 * @return um Usuario pelo id, caso exista na lista.
 */
Usuario *UsuarioList::getUsuarioById(const int id)
{
    auto u = std::find_if(std::begin(m_usuario), std::end(m_usuario),
                  [&](Usuario *Usuario){
        return Usuario->id() == id;
    });

    return u.i->t();
}

/**
 * @brief UsuarioList::getUsuarioByClientId
 * @param clientid
 * @return um Usuario pelo clientid da api, caso exista na lista.
 */
Usuario *UsuarioList::getUsuarioByClientId(const QString &clientid)
{
    auto u = std::find_if(std::begin(m_usuario), std::end(m_usuario),
                  [&](Usuario *Usuario){
        return Usuario->clientid() == clientid;
    });

    return u.i->t();
}
