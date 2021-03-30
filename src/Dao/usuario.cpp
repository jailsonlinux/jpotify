#include "usuario.h"

/**
 * @brief Usuario::Usuario
 * constroi instancia com valores default.
 */
Usuario::Usuario():
    m_id{0},
    m_nome(QStringLiteral("")),
    m_clientid(QStringLiteral("")),
    m_secret(QStringLiteral("")),
    m_access_token(QStringLiteral("")),
    m_api_token(QStringLiteral("")),
    m_autologin{false}
{

}

/**
 * @brief Usuario::id
 * @return identificador unico do usuario.
 */
int Usuario::id() const
{
    return m_id;
}

/**
 * @brief Usuario::setId
 * @param id
 * define identificador unico de usuario.
 */
void Usuario::setId(int id)
{
    m_id = id;
}

/**
 * @brief Usuario::nome
 * @return nome do usuario.
 */
QString Usuario::nome() const
{
    return m_nome;
}

/**
 * @brief Usuario::setNome
 * @param nome
 * define um nome para o usuario.
 */
void Usuario::setNome(const QString &nome)
{
    m_nome = nome;
}

/**
 * @brief Usuario::clientid
 * @return clientid da api
 */
QString Usuario::clientid() const
{
    return m_clientid;
}

/**
 * @brief Usuario::setClientid
 * @param clientid
 * define clientid da api
 */
void Usuario::setClientid(const QString &clientid)
{
    m_clientid = clientid;
}

/**
 * @brief Usuario::secret
 * @return secret da api.
 */
QString Usuario::secret() const
{
    return m_secret;
}

/**
 * @brief Usuario::setSecret
 * @param secret
 * define secret da api.
 */
void Usuario::setSecret(const QString &secret)
{
    m_secret = secret;
}

/**
 * @brief Usuario::access_token
 * @return acess_token da api.
 */
QString Usuario::access_token() const
{
    return m_access_token;
}

/**
 * @brief Usuario::setAccess_token
 * @param access_token
 * define acess_token da api
 */
void Usuario::setAccess_token(const QString &access_token)
{
    m_access_token = access_token;
}

/**
 * @brief Usuario::autologin
 * @return se o usuario definiu tentar o autologin usando as credenciais persistidas.
 */
bool Usuario::autologin() const
{
    return m_autologin;
}

/**
 * @brief Usuario::setAutologin
 * @param autologin
 * define a opcao de autologin/preenchimento
 */
void Usuario::setAutologin(bool autologin)
{
    m_autologin = autologin;
}

/**
 * @brief Usuario::api_token
 * @return caso o usuario tenha obtido um token da api.
 */
QString Usuario::api_token() const
{
    return m_api_token;
}

/**
 * @brief Usuario::setApi_token
 * @param api_token
 * Define o token capturado da api autenticada.
 */
void Usuario::setApi_token(const QString &api_token)
{
    m_api_token = api_token;
}
