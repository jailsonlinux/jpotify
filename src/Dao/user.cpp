#include "user.h"

/**
 * @brief User::User
 * constroi instancia com valores default.
 */
User::User():
    m_id{0},
    m_nome{QStringLiteral("")},
    m_clientid{QStringLiteral("")},
    m_secret{QStringLiteral("")},
    m_access_token{QStringLiteral("")},
    m_autologin{false}
{

}

/**
 * @brief User::id
 * @return identificador unico do usuario.
 */
int User::id() const
{
    return m_id;
}

/**
 * @brief User::setId
 * @param id
 * define identificador unico de usuario.
 */
void User::setId(int id)
{
    m_id = id;
}

/**
 * @brief User::nome
 * @return nome do usuario.
 */
QString User::nome() const
{
    return m_nome;
}

/**
 * @brief User::setNome
 * @param nome
 * define um nome para o usuario.
 */
void User::setNome(const QString &nome)
{
    m_nome = nome;
}

/**
 * @brief User::clientid
 * @return clientid da api
 */
QString User::clientid() const
{
    return m_clientid;
}

/**
 * @brief User::setClientid
 * @param clientid
 * define clientid da api
 */
void User::setClientid(const QString &clientid)
{
    m_clientid = clientid;
}

/**
 * @brief User::secret
 * @return secret da api.
 */
QString User::secret() const
{
    return m_secret;
}

/**
 * @brief User::setSecret
 * @param secret
 * define secret da api.
 */
void User::setSecret(const QString &secret)
{
    m_secret = secret;
}

/**
 * @brief User::access_token
 * @return acess_token da api.
 */
QString User::access_token() const
{
    return m_access_token;
}

/**
 * @brief User::setAccess_token
 * @param access_token
 * define acess_token da api
 */
void User::setAccess_token(const QString &access_token)
{
    m_access_token = access_token;
}

/**
 * @brief User::autologin
 * @return se o usuario definiu tentar o autologin usando as credenciais persistidas.
 */
bool User::autologin() const
{
    return m_autologin;
}

/**
 * @brief User::setAutologin
 * @param autologin
 * define a opcao de autologin/preenchimento
 */
void User::setAutologin(bool autologin)
{
    m_autologin = autologin;
}
