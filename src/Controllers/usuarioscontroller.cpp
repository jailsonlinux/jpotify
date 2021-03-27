#include "usuarioscontroller.h"

UsuariosController::UsuariosController():
  m_usuarioAtual(new Usuario)
  ,m_usuarios(new UsuarioList)
{
    loadAll();
}

Usuario *UsuariosController::getUsuarioAtual() const
{
    return m_usuarioAtual;
}

void UsuariosController::setUsuarioAtual(Usuario *value)
{
    m_usuarioAtual = value;
}

UsuarioList *UsuariosController::getUsuarios() const
{
    return m_usuarios;
}

void UsuariosController::setUsuarios(UsuarioList *value)
{
    m_usuarios->setUsuarios(value->getUsuarios());
}

void UsuariosController::loadAll()
{
    UsuariosDao usuariosDao;
    if(usuariosDao.loadAll(m_usuarios)){
        emit on_usuariosLoaded();
    }
}

void UsuariosController::addicionaUsuario(Usuario *usuario)
{
    UsuariosDao usuariosDao;
    if(usuariosDao.add(usuario)){
        m_usuarios->addUsuario(usuario);
        emit on_usuarioAdicionado();
    }
}

void UsuariosController::removerUsuario(Usuario *usuario)
{
    UsuariosDao usuariosDao;    
    if(usuariosDao.remove(usuario)){
        m_usuarios->removeUsuario(usuario);
        emit on_usuarioRemovido();
    }
}
