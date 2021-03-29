#include "uilogin.h"
#include "ui_uilogin.h"

#include <algorithm>
#include <QIcon>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    m_usuario(new Usuario),
    usuariosController(new UsuariosController()),
    api(new Api(this))
{
    ui->setupUi(this);
    ui->cmbUsuarios->setDuplicatesEnabled(false);

    //Prencher combo com usuarios previamente registrados quando a base atualizar.
    connect(usuariosController, &UsuariosController::on_usuariosLoaded, [&](){
        // Repreenche o combo com novos dados..
        reloadComboUsuarios();
        //Ao setar os dados do usuario atual, seta o combo, que seta os dados
        setUsuario(m_usuario);
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

void Login::preencheUsuario(Usuario *usuario)
{    
    m_usuario = usuario;

    if(m_usuario == nullptr) {
        m_usuario = new Usuario();
        usuariosController->loadAll();
    }

    ui->edtNome->setText(m_usuario->nome());
    ui->edtUsuario->setText(m_usuario->clientid());
    ui->edtSecret->setText(m_usuario->secret());
    ui->chkRegistrar->setChecked(true);
}

void Login::on_btnLogin_clicked()
{
    m_usuario = usuariosController->getUsuarioByName(ui->edtNome->text().trimmed());

    if(m_usuario == nullptr) {
        m_usuario = new Usuario;
        m_usuario->setId(0);
        m_usuario->setNome(ui->edtNome->text());
        m_usuario->setClientid(ui->edtUsuario->text());
        m_usuario->setSecret(ui->edtSecret->text());
        m_usuario->setAutologin((int)(ui->chkRegistrar->isChecked()));
    }

    m_usuario->setAccess_token(QStringLiteral(""));
    if(ui->chkRegistrar->isChecked()){
        usuariosController->adicionaUsuario(m_usuario);
    }

    emit on_escolheuUsuario(m_usuario);
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
    m_usuario = usuariosController->getUsuarioByName(ui->cmbUsuarios->itemText(index));

    if(index >= 0){
        preencheUsuario(m_usuario);
        habilitaBotaoLogin();
    }
}

void Login::on_btnRemove_clicked()
{
    m_usuario = usuariosController->getUsuarioByName(ui->edtNome->text().trimmed());
    if(m_usuario != nullptr) {
        usuariosController->removerUsuario(m_usuario);
        ui->cmbUsuarios->removeItem(ui->cmbUsuarios->findText(m_usuario->nome()));
        reloadComboUsuarios();
    }

    preencheUsuario(m_usuario);

}

void Login::reloadComboUsuarios()
{
    ui->cmbUsuarios->clear();

    std::for_each(std::begin(usuariosController->getUsuarios().getUsuarios()), std::end(usuariosController->getUsuarios().getUsuarios()), [&](Usuario *item){
        ui->cmbUsuarios->addItem(QIcon(QStringLiteral(":resources/images/png/user.png")), item->nome());
    });
}

Usuario *Login::getUsuario() const
{
    return m_usuario;
}

void Login::setUsuario(Usuario *value)
{
    m_usuario = value;
    if(m_usuario != nullptr){
        const int idx = ui->cmbUsuarios->findText(m_usuario->nome());
        ui->cmbUsuarios->setCurrentIndex(idx);
    }
}
