#include "userlist.h"

#include <QDebug>
#include <algorithm>

/**
 * @brief UserList::~UserList
 * limpa a lista antes de destruir.
 */
UserList::~UserList()
{
    clear();
}

/**
 * @brief UserList::clear
 * efetiva uma limpeza na lista de users.
 */
void UserList::clear()
{
    m_users.clear();
}

/**
 * @brief UserList::size
 * @return quantidade de itens na lista.
 */
int UserList::size() const
{
    return m_users.size();
}

/**
 * @brief UserList::addUser
 * @param user
 * adiciona um usuario a lista.
 */
void UserList::addUser(User *user)
{
    m_users.append(user);
}

/**
 * @brief UserList::removeUser
 * @param user
 * remove um usuario da lista.
 */
void UserList::removeUser(User *user)
{
    m_users.removeOne(user);
}

/**
 * @brief UserList::getUserByName
 * @param nome
 * @return um Usuario pelo nome, caso exista na lista.
 */
User *UserList::getUserByName(const QString &nome)
{
    auto u = std::find_if(std::begin(m_users), std::end(m_users),
                  [&](User *user){
        return user->nome() == nome;
    });

    return u.i->t();
}

/**
 * @brief UserList::getUserById
 * @param id
 * @return um Usuario pelo id, caso exista na lista.
 */
User *UserList::getUserById(const int id)
{
    auto u = std::find_if(std::begin(m_users), std::end(m_users),
                  [&](User *user){
        return user->id() == id;
    });

    return u.i->t();
}

/**
 * @brief UserList::getUserByClientId
 * @param clientid
 * @return um Usuario pelo clientid da api, caso exista na lista.
 */
User *UserList::getUserByClientId(const QString &clientid)
{
    auto u = std::find_if(std::begin(m_users), std::end(m_users),
                  [&](User *user){
        return user->clientid() == clientid;
    });

    return u.i->t();
}
