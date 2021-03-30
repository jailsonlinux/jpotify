#pragma once

#include <QObject>

class Usuario
{
public:
    explicit Usuario();
    ~Usuario() = default;

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

    QString api_token() const;
    void setApi_token(const QString &api_token);

private:
    int m_id;
    QString m_nome;
    QString m_clientid; // id da api
    QString m_secret;
    QString m_access_token;

    QString m_api_token;

    bool m_autologin;

};

