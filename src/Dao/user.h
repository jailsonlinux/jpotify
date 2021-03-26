#pragma once

#include <QObject>

class User
{
public:
    explicit User();
    ~User() = default;

    int id() const;
    void setId(int id);

    QString nome() const;
    void setNome(const QString &nome);

    QString clientid() const;
    void setClientid(const QString &clientid);

    QString secret() const;
    void setSecret(const QString &secret);

    QString access_token() const;
    void setAccess_token(const QString &access_token);

    bool autologin() const;
    void setAutologin(bool autologin);

private:
    int m_id;
    QString m_nome;
    QString m_clientid; // id da api
    QString m_secret;
    QString m_access_token;
    bool m_autologin;

};

