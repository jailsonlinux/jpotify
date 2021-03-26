#pragma once

#include <QList>

#include "user.h"

class UserList
{
public:
    explicit UserList() = default;
    ~UserList();
    void clear();
    int size() const;
    void addUser(User *user);
    void removeUser(User *user);
    User *getUserByName(const QString &nome);
    User *getUserById(const int id);
    User *getUserByClientId(const QString &clientid);

private:
    QList<User*> m_users;

};

