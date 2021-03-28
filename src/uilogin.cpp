#include "uilogin.h"
#include "ui_uilogin.h"
#include <algorithm>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    m_usuario(new Usuario),
    usuariosController(new UsuariosController()),
    api(new Api(this))
{
    ui->setupUi(this);

    //ToDo: SetValidator nos inputs para nao permitir espaços.

    //Prencher combo com usuarios previamente registrados quando a tela for ativada.
    connect(this, &Login::show, [&](){
        usuariosController->loadAll();
    });

    //Prencher combo com usuarios previamente registrados quando a base atualizar.
    connect(usuariosController, &UsuariosController::on_usuariosLoaded, [&](){
       reloadComboUsuarios();
    });

    //Sucesso de login, cadastrar caso opcao marcada, ou nao existir e for sucesso.

    connect(api, &Api::on_acessToken, [&](){
        m_usuario = usuariosController->getUsuarios()->getUsuarioByName(ui->edtNome->text().trimmed());

        if(m_usuario == nullptr) {
            m_usuario = new Usuario;
            m_usuario->setId(0);
            m_usuario->setNome(ui->edtNome->text().trimmed());
            m_usuario->setClientid(ui->edtUsuario->text().trimmed());
            m_usuario->setSecret(ui->edtSecret->text().trimmed());
            m_usuario->setAutologin((int)(ui->chkRegistrar->isChecked()));
        }

        if(ui->chkRegistrar->isChecked()){
            usuariosController->addicionaUsuario(m_usuario);
        }

        emit on_loginsucess();
    });

    usuariosController->loadAll();

    habilitaBotaoLogin();

}

Login::~Login()
{
    delete ui;
}

void Login::habilitaBotaoLogin()
{
    ui->btnLogin->setEnabled((!ui->edtNome->text().isEmpty() &&
                              !ui->edtUsuario->text().isEmpty() &&
                              !ui->edtSecret->text().isEmpty() ));
}

void Login::preencheUsuario(const QString &nome)
{
    m_usuario = usuariosController->getUsuarios()->getUsuarioByName(nome);
//    reloadComboUsuarios();

    if(m_usuario == nullptr) {
        m_usuario = new Usuario();
        usuariosController->loadAll();
    }
    ui->edtNome->setText(m_usuario->nome());
    ui->edtUsuario->setText(m_usuario->clientid());
    ui->edtSecret->setText(m_usuario->secret());
    ui->chkRegistrar->setChecked(true);
}

void Login::onLoginSucess()
{

    emit on_loginsucess();

}

void Login::on_btnLogin_clicked()
{
    api->setUsuario(m_usuario);
    api->iniciarAutenticador();
}

void Login::on_btnCancelar_clicked()
{
    emit on_loginCancel();
}

void Login::on_edtNome_textChanged(const QString &arg1)
{
    if(arg1.size() > 0)
        habilitaBotaoLogin();
}

void Login::on_edtUsuario_textChanged(const QString &arg1)
{
    if(arg1.size() > 0)
        habilitaBotaoLogin();
}

void Login::on_edtSecret_textChanged(const QString &arg1)
{
    if(arg1.size() > 0)
        habilitaBotaoLogin();
}

void Login::on_cmbUsuarios_currentIndexChanged(int index)
{
    if(index >= 0){
        preencheUsuario(ui->cmbUsuarios->currentText());
        habilitaBotaoLogin();
    }
}

void Login::on_btnRemove_clicked()
{
    m_usuario = usuariosController->getUsuarios()->getUsuarioByName(ui->edtNome->text().trimmed());
    if(m_usuario != nullptr) {
        usuariosController->removerUsuario(m_usuario);
        ui->cmbUsuarios->removeItem(ui->cmbUsuarios->findText(m_usuario->nome()));
        usuariosController->loadAll();
    }

    preencheUsuario("");

}

void Login::reloadComboUsuarios()
{
    ui->cmbUsuarios->clear();

    std::for_each(std::begin(usuariosController->getUsuarios()->getUsuarios()), std::end(usuariosController->getUsuarios()->getUsuarios()),
                  [&](Usuario *item){
        ui->cmbUsuarios->addItem(item->nome());
    });

    ui->cmbUsuarios->setCurrentIndex(ui->cmbUsuarios->findText(m_usuario->nome().trimmed()));
}

Usuario *Login::getUsuario() const
{
    return m_usuario;
}

void Login::setUsuario(Usuario *value)
{
    m_usuario = value;
}
