#include "uilogin.h"
#include "ui_uilogin.h"
#include <algorithm>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    usuario(new Usuario),
    usuariosController(new UsuariosController()),
    api(new Api())
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
        usuario = usuariosController->getUsuarios()->getUsuarioByName(ui->edtNome->text().trimmed());

        if(usuario == nullptr) {
            usuario = new Usuario;
            usuario->setId(0);
            usuario->setNome(ui->edtNome->text().trimmed());
            usuario->setClientid(ui->edtUsuario->text().trimmed());
            usuario->setSecret(ui->edtSecret->text().trimmed());
            usuario->setAutologin((int)(ui->chkRegistrar->isChecked()));
        }

        if(ui->chkRegistrar->isChecked()){
            usuariosController->addicionaUsuario(usuario);
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
    usuario = usuariosController->getUsuarios()->getUsuarioByName(nome);
//    reloadComboUsuarios();

    if(usuario == nullptr) {
        usuario = new Usuario();
        usuariosController->loadAll();
    }
    ui->edtNome->setText(usuario->nome());
    ui->edtUsuario->setText(usuario->clientid());
    ui->edtSecret->setText(usuario->secret());
    ui->chkRegistrar->setChecked(true);
}

void Login::onLoginSucess()
{
    emit on_loginsucess();
}

void Login::on_btnLogin_clicked()
{
    api->acessToken();
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
    usuario = usuariosController->getUsuarios()->getUsuarioByName(ui->edtNome->text().trimmed());
    if(usuario != nullptr) {
        usuariosController->removerUsuario(usuario);
        ui->cmbUsuarios->removeItem(ui->cmbUsuarios->findText(usuario->nome()));
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

    ui->cmbUsuarios->setCurrentIndex(ui->cmbUsuarios->findText(usuario->nome().trimmed()));
}

Usuario *Login::getUsuario() const
{
    return usuario;
}

void Login::setUsuario(Usuario *value)
{
    usuario = value;
}
