#include "usuarioscontroller.h"

/**
 * @brief UsuariosController::UsuariosController
 * inicia listas de usuarios do banco, e um usuario em branco.
 */
UsuariosController::UsuariosController():
  m_usuarioAtual(new Usuario)
  ,m_usuarios(new UsuarioList)
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
 * @brief UsuariosController::getUsuarios
 * @return a ultima lista de usuarios pesquisada no banco de dados,
 */
UsuarioList *UsuariosController::getUsuarios() const
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
    m_usuarios->setUsuarios(value->getUsuarios());
}

/**
 * @brief UsuariosController::loadAll
 * pesquisa todos usuarios do bd, e atualiza a lista interna.
 * emit que usuarios foram atualizados da lista.
 */
void UsuariosController::loadAll()
{
    UsuariosDao usuariosDao;
    if(usuariosDao.loadAll(m_usuarios)){
        emit on_usuariosLoaded();
    }
}

/**
 * @brief UsuariosController::addicionaUsuario
 * @param usuario
 * insere usuario no bd e notifica.
 */
void UsuariosController::addicionaUsuario(Usuario *usuario)
{
    UsuariosDao usuariosDao;
    if(usuariosDao.add(usuario)){
        m_usuarios->addUsuario(usuario);
        emit on_usuarioAdicionado();
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
        m_usuarios->removeUsuario(usuario);
        emit on_usuarioRemovido();
    }
}
