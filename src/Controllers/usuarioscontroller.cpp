#include "usuarioscontroller.h"

/**
 * @brief UsuariosController::UsuariosController
 * inicia listas de usuarios do banco, e um usuario em branco.
 */
UsuariosController::UsuariosController():
    m_usuarioAtual(new Usuario)
  ,m_usuarios(*new UsuarioList)
{
    loadAll();


}

/**
 * @brief UsuariosController::getUsuarioAtual
 * @return o usuario atualmente no controle.
 */

Usuario *UsuariosController::getUsuarioAtual() const
{
    return m_usuarioAtual;
}

/**
 * @brief UsuariosController::setUsuarioAtual
 * @param value
 * força um usuario no controle.
 */
void UsuariosController::setUsuarioAtual(Usuario *value)
{
    m_usuarioAtual = value;
}

/**
 * @brief UsuariosController::getUsuarioByName
 * @param nome
 * @return um usuario encontrado pelo nome de cadastro de login.
 */
Usuario *UsuariosController::getUsuarioByName(const QString &nome)
{
    return m_usuarios.getUsuarioByName(nome);
}

/**
 * @brief UsuariosController::getUsuarios
 * @return a ultima lista de usuarios pesquisada no banco de dados,
 */
UsuarioList UsuariosController::getUsuarios()
{
    return m_usuarios;
}

/**
 * @brief UsuariosController::setUsuarios
 * @param value
 * define uma lista de usuarios.
 */
void UsuariosController::setUsuarios(UsuarioList *value)
{
    m_usuarios.setUsuarios(value->getUsuarios());
}

/**
 * @brief UsuariosController::loadAll
 * pesquisa todos usuarios do bd, e atualiza a lista interna.
 * emit que usuarios foram atualizados da lista.
 */
void UsuariosController::loadAll()
{
    UsuariosDao usuariosDao;
    m_usuarios.clear();
    if(usuariosDao.loadAll(&m_usuarios)){
        emit on_usuariosLoaded();
    }
}

/**
 * @brief UsuariosController::clearAll
 * limpar lista de users
 */
void UsuariosController::clearAll()
{
    m_usuarios.clear();
}

/**
 * @brief UsuariosController::addicionaUsuario
 * @param usuario
 * insere usuario no bd e notifica.
 */
void UsuariosController::adicionaUsuario(Usuario *usuario)
{
    UsuariosDao usuariosDao;

    if(usuariosDao.add(usuario)){        
        emit on_usuarioAdicionado();
        loadAll();
    }
}

/**
 * @brief UsuariosController::removerUsuario
 * @param usuario
 * remove usuario no banco e notifica.
 */
void UsuariosController::removerUsuario(Usuario *usuario)
{
    UsuariosDao usuariosDao;
    if(usuariosDao.remove(usuario)){
        m_usuarios.removeUsuario(usuario);
        emit on_usuarioRemovido();
    }
}
