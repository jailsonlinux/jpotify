#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>


/**
 * Telas do fluxo
 * Logar
 * Cadastrar credenciais
 * Cadastrar playlists
 * Buscas
 * Adicionar tracks à playlists
 * Tocar playlists
**/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_uiLogin(new Login(this))
    , m_uiPlayList(new UiPlaylist(this))
    , m_uiSearch(new ResultadoPesquisa(this))
    , m_usuario(new Usuario)
    , api(new Api(this))
    , playlistController(new PlayListController())
    , currentPlaylist(new PlayList())
    , playlists(new Playlists())
{
    ui->setupUi(this);

    //iniciar tela de login, e buscas
    ui->stackedWidget->addWidget(m_uiLogin);
    ui->stackedWidget->addWidget(m_uiSearch);
    ui->stackedWidget->addWidget(m_uiPlayList);
    m_uiSearch->hide();
    m_uiPlayList->hide();

    //Chamar login
    ui->stackedWidget->setCurrentWidget(m_uiLogin);
    m_uiLogin->show();

    //Cancelar login
    connect(m_uiLogin, &Login::on_loginCancel, [&]() {
        m_usuario = m_uiLogin->getUsuario();
        swapLoginToSearch();
    });

    //Sucesso de login, pega o token da api
    connect(api, &Api::on_acessToken, [&](bool capturouUserToken){
        //Com userToken podemos capturar a api token. Senao volta pra login..
        if(capturouUserToken){
            api->getApiToken(); // -> on_Conectado
        }else{
            ui->stackedWidget->setCurrentWidget(m_uiLogin);
            m_uiLogin->show();
        }
    });

    //Sucesso ao obter a chave de autenticacao da API.
    connect(api, &Api::on_Conectado, [=](){
        //ToDo: Colocar icone de logado.

        ui->lblIconUser->setPixmap(api->getAcessTokenn().size() > 0? QPixmap(QStringLiteral(":/resources/images/png/userlogado.png"))
                                                                   : QPixmap(QStringLiteral(":/resources/images/png/user.png")));
        habilitaSeLogado();

        //Atualizar playlists
        m_usuario = m_uiLogin->getUsuario();
        reloadPlaylists();

        //exibir tela de buscas
        ui->stackedWidget->setCurrentWidget(m_uiSearch);
    });

    //Confirma e tenta logar
    connect(m_uiLogin, &Login::on_escolheuUsuario, [&]() {
        m_usuario = m_uiLogin->getUsuario();
        ui->lblLoggedUser->setText(m_usuario->nome());

        api->setUsuario(m_usuario);
        api->abrirLogin(); // -> Api::on_acessToken
    });

    //Ao cancelar, volta para a tela de busca.
    connect(m_uiPlayList, &UiPlaylist::on_cancelarPlaylist, [&]() {
          ui->stackedWidget->setCurrentWidget(m_uiSearch);
    });

    //Ao salvar pede ao controler para persistir. E atualizar a lista de playlists.
    connect(m_uiPlayList, &UiPlaylist::on_salvarPlayList, [&](PlayList *playlist){
          playlistController->setUsuario(m_usuario);
          playlistController->addicionarPlaylist(playlist);
          ui->stackedWidget->setCurrentWidget(m_uiSearch);
    });

    //Ao salvar pede ao controler para persistir. E atualizar a lista de playlists.
    connect(m_uiPlayList, &UiPlaylist::on_excluirPlayList, [&](PlayList *playlist) {
          playlistController->setUsuario(m_usuario);
          playlistController->removerPlaylist(playlist);
          reloadPlaylists();
    });


    //Ao remover, inserir, atualizar,  a lista de playlists da tela é atualizada.
    connect(playlistController, &PlayListController::on_playlistsChanged, [=](){
       reloadPlaylists();
    });

    habilitaSeLogado();


}

MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * @brief MainWindow::on_btnInicio_clicked
 * faz um novo login
 */
void MainWindow::on_btnInicio_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_uiLogin);
    m_uiLogin->show();

    m_uiLogin->setUsuario(m_usuario);
    m_uiSearch->hide();
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
 *adiciona uma playlist vazia a ser preenchida na view de edicao.
 */
void MainWindow::on_btnCriarPlaylist_clicked()
{

    PlayList * new_playlist = nullptr;
    m_uiPlayList->setQtdMusicas(0);
    m_uiPlayList->setUsuario(m_usuario);
    m_uiPlayList->setPlaylist(new_playlist);
    ui->stackedWidget->setCurrentWidget(m_uiPlayList);
}

void MainWindow::swapLoginToSearch()
{
    ui->stackedWidget->setCurrentWidget(m_uiSearch);
    m_uiLogin->hide();
    m_uiSearch->show();
}

void MainWindow::reloadPlaylists()
{
    ui->lvPlaylists->clear();
    playlistController->setUsuario(m_usuario);
    playlistController->loadAll();
    std::for_each(std::begin(playlistController->playlists().getPlaylists()), std::end(playlistController->playlists().getPlaylists()),
                  [=](PlayList *playlist){
        ui->lvPlaylists->addItem(playlist->nome());
    });
}

void MainWindow::habilitaSeLogado()
{
    const bool logado  = api->getAcessTokenn().size() > 0;
    ui->btnCriarPlaylist->setEnabled(logado);
    ui->btnExcluirPlaylist->setEnabled(logado);
    ui->btnEditarPlaylist->setEnabled(logado);
    ui->btnBuscar->setEnabled(logado);
    ui->lvPlaylists->setEnabled(logado || ui->lvPlaylists->count() == 0);
}

void MainWindow::on_btnEditarPlaylist_clicked()
{
    if(ui->lvPlaylists->selectedItems().size()>0){
        currentPlaylist = playlistController->playlists().getPlaylistByName(ui->lvPlaylists->selectedItems().first()->text());
        if(currentPlaylist != nullptr){
            m_uiPlayList->setUsuario(m_usuario);
            m_uiPlayList->setPlaylist(currentPlaylist);
            ui->stackedWidget->setCurrentWidget(m_uiPlayList);
        }
    }
}

void MainWindow::on_lvPlaylists_itemSelectionChanged()
{
    if(ui->lvPlaylists->selectedItems().size()>0){
        currentPlaylist = playlistController->playlists().getPlaylistByName(ui->lvPlaylists->selectedItems().first()->text());
        if(currentPlaylist != nullptr){
            m_uiPlayList->setUsuario(m_usuario);
            m_uiPlayList->setPlaylist(currentPlaylist);
            ui->stackedWidget->setCurrentWidget(m_uiPlayList);
        }
    }
}
