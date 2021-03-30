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
    m_usuarios.clear();
}

/**
 * @brief UsuarioList::size
 * @return quantidade de itens na lista.
 */
int UsuarioList::size() const
{
    return m_usuarios.size();
}

/**
 * @brief UsuarioList::addUsuario
 * @param Usuario
 * adiciona um usuario a lista.
 */
void UsuarioList::addUsuario(Usuario *usuario)
{
    m_usuarios.append(usuario);
}

/**
 * @brief UsuarioList::removeUsuario
 * @param Usuario
 * remove um usuario da lista.
 */
void UsuarioList::removeUsuario(Usuario *usuario)
{
    m_usuarios.removeOne(usuario);
}

/**
 * @brief UsuarioList::getUsuarioByName
 * @param nome
 * @return um Usuario pelo nome, caso exista na lista.
 */
Usuario *UsuarioList::getUsuarioByName(const QString &nome)
{
    auto u = std::find_if(std::begin(m_usuarios), std::end(m_usuarios),
                  [&](Usuario *usuario){
        return usuario->nome() == nome;
    });

    if(u != m_usuarios.end()) {
        return u.i->t();
    }

    return nullptr;
}

/**
 * @brief UsuarioList::getUsuarioById
 * @param id
 * @return um Usuario pelo id, caso exista na lista.
 */
Usuario *UsuarioList::getUsuarioById(const int id)
{
    auto u = std::find_if(std::begin(m_usuarios), std::end(m_usuarios),
                  [&](Usuario *usuario){
        return usuario->id() == id;
    });

    if(u != m_usuarios.end()) {
        return u.i->t();
    }

    return nullptr;
}

/**
 * @brief UsuarioList::getUsuarioByClientId
 * @param clientid
 * @return um Usuario pelo clientid da api, caso exista na lista.
 */
Usuario *UsuarioList::getUsuarioByClientId(const QString &clientid)
{
    auto u = std::find_if(std::begin(m_usuarios), std::end(m_usuarios),
                  [&](Usuario *usuario){
        return usuario->clientid() == clientid;
    });

    if(u != m_usuarios.end()) {
        return u.i->t();
    }

    return nullptr;
}

/**
 * @brief UsuarioList::getUsuarios
 * @return
 */
QList<Usuario *> UsuarioList::getUsuarios() const
{
    return m_usuarios;
}

/**
 * @brief UsuarioList::setUsuarios
 * @param usuarios
 */
void UsuarioList::setUsuarios(const QList<Usuario *> &usuarios)
{
    m_usuarios.clear();
    m_usuarios.append(usuarios);
}
