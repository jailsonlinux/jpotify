#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
/**
 * Telas do fluxo
 * Logar
 * Cadastrar credenciais
 * Buscas
 * Tocar playlists
**/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_uiLogin(new Login(this))
    , m_usuario(new Usuario)
    , m_uiSearch(new ResultadoPesquisa(this))
{
    ui->setupUi(this);

    //iniciar tela de login, e buscas
    ui->stackedWidget->addWidget(m_uiLogin);
    ui->stackedWidget->addWidget(m_uiSearch);
    //Chamar login
    ui->stackedWidget->setCurrentWidget(m_uiLogin);
    //Cancelar exibe busca
    connect(m_uiLogin, &Login::on_loginCancel, [&]() {
        ui->stackedWidget->setCurrentWidget(m_uiSearch);
        m_uiSearch->show();
        ui->stackedWidget->removeWidget(m_uiLogin);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnBliblioteca_clicked()
{

}

/**
 * @brief MainWindow::on_btnInicio_clicked
 * faz um novo login
 */
void MainWindow::on_btnInicio_clicked()
{
    ui->stackedWidget->addWidget(m_uiLogin);
    ui->stackedWidget->setCurrentWidget(m_uiLogin);
}

/**
 * @brief MainWindow::on_btnBuscar_clicked
 * exibe ultima tela de busca...
 */
void MainWindow::on_btnBuscar_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_uiSearch);
}

/**
 * @brief MainWindow::on_btnCriarPlaylist_clicked
 *
 */
void MainWindow::on_btnCriarPlaylist_clicked()
{

}
