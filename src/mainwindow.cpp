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
    , m_uiResultadoPesquisa(new ResultadoPesquisa(this))
    , m_usuario(new Usuario)
    , api(new Api(this))
    , playlistController(new PlayListController())
    , pesquisaController(new PesquisaController(api))
    , currentPlaylist(new PlayList())
{
    ui->setupUi(this);

    //iniciar tela de login, e buscas
    ui->stackedWidget->addWidget(m_uiLogin);
    ui->stackedWidget->addWidget(m_uiResultadoPesquisa);
    ui->stackedWidget->addWidget(m_uiPlayList);
    m_uiResultadoPesquisa->hide();
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
        playlistController->setUsuario(m_usuario);
        playlistController->loadAll();

        //exibir tela de buscas
        ui->stackedWidget->setCurrentWidget(m_uiResultadoPesquisa);
    });

    //Confirma e tenta logar
    connect(m_uiLogin, &Login::on_escolheuUsuario, [&](Usuario *usuario) {
        m_usuario = usuario;
        ui->lblLoggedUser->setText(m_usuario->nome());

        api->setUsuario(m_usuario);
        api->abrirLogin(); // -> Api::on_acessToken
    });

    //Ao cancelar, volta para a tela de busca.
    connect(m_uiPlayList, &UiPlaylist::on_cancelarPlaylist, [&]() {
        ui->stackedWidget->setCurrentWidget(m_uiResultadoPesquisa);
    });

    //Ao salvar pede ao controler para persistir. E atualizar a lista de playlists.
    connect(m_uiPlayList, &UiPlaylist::on_salvarPlayList, [&](PlayList *playlist){
        playlistController->setUsuario(m_usuario);
        playlistController->addicionarPlaylist(playlist);
        ui->stackedWidget->setCurrentWidget(m_uiResultadoPesquisa);
    });

    //Ao salvar pede ao controler para persistir. E atualizar a lista de playlists.
    connect(m_uiPlayList, &UiPlaylist::on_excluirPlayList, [&](PlayList *playlist) {
        playlistController->setUsuario(m_usuario);
        playlistController->removerPlaylist(playlist);
        reloadPlaylists();
        ui->stackedWidget->setCurrentWidget(m_uiResultadoPesquisa);
    });


    //Ao remover, inserir, atualizar,  a lista de playlists da tela é atualizada.
    connect(playlistController, &PlayListController::on_playlistsChanged, [=](){
        playlistController->setUsuario(m_usuario);
        playlistController->loadAll();
    });

    //Atualiza lsitview e lista de playlists...
    connect(playlistController, &PlayListController::on_playlistsCarregado, [=](){
        reloadPlaylists();
    });



    //Ao pesquisar atualiza a lista de resultados...
    // A partir de la gerenciar quem entra na playlist ou tocar...
    connect(pesquisaController, &PesquisaController::on_pesquisaConcluida, [=](){
        ui->stackedWidget->setCurrentWidget(m_uiResultadoPesquisa);
        m_uiResultadoPesquisa->setMusicaList(pesquisaController->musicaList());
        m_uiResultadoPesquisa->setTermo(ui->edtSearch->text().trimmed());
        m_uiResultadoPesquisa->setPlaylists(playlistController->playlists());
        ui->edtSearch->clear();
    });

    //Ao adicionar uma musica escolhida da pesquisa numa playlist, o controler notifica atualizar as listas.
    connect(m_uiResultadoPesquisa, &ResultadoPesquisa::on_addMusicaNaPlaylist, [&](const int playlistId, Musica *musica){
        //qDebug() << "Musica para add na playlist: " << playlistId << " Musica: " << musica->nome();
        playlistController->adicionarMusicaAPlaylist(playlistId, musica);

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
    m_uiResultadoPesquisa->hide();
}

/**
 * @brief MainWindow::on_btnBuscar_clicked
 * exibe ultima tela de busca...
 */
void MainWindow::on_btnBuscar_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_uiResultadoPesquisa);
}

/**
 * @brief MainWindow::on_btnCriarPlaylist_clicked
 *adiciona uma playlist vazia a ser preenchida na view de edicao.
 */
void MainWindow::on_btnCriarPlaylist_clicked()
{
    PlayList *new_playlist = new PlayList();
    new_playlist->setUsuarioid(m_usuario->id());
    m_uiPlayList->setQtdMusicas(0);
    m_uiPlayList->setUsuario(m_usuario);
    m_uiPlayList->setPlaylist(new_playlist);
    ui->stackedWidget->setCurrentWidget(m_uiPlayList);
}

/**
 * @brief MainWindow::swapLoginToSearch
 * alterna ente login e pesquisa.
 */
void MainWindow::swapLoginToSearch()
{
    ui->stackedWidget->setCurrentWidget(m_uiResultadoPesquisa);
    m_uiLogin->hide();
    m_uiResultadoPesquisa->show();
}

/**
 * @brief MainWindow::reloadPlaylists
 * recarrega playlist e
 */
void MainWindow::reloadPlaylists()
{
    ui->lvPlaylists->clear();
    std::for_each(std::begin(playlistController->playlists().getPlaylists()), std::end(playlistController->playlists().getPlaylists()),
                  [=](PlayList *playlist){
        ui->lvPlaylists->addItem(playlist->nome());
    });
}

/**
 * @brief MainWindow::habilitaSeLogado
 * antes do login, icone e botoes desligados.
 */
void MainWindow::habilitaSeLogado()
{
    const bool logado  = api->getAcessTokenn().size() > 0;
    ui->btnCriarPlaylist->setEnabled(logado);
    ui->btnPlayPlaylist->setEnabled(logado);
    ui->btnBuscar->setEnabled(logado);
    ui->lvPlaylists->setEnabled(logado || ui->lvPlaylists->count() == 0);
}

/**
 * @brief MainWindow::showPlaylist
 * exibe playlists atualizadas no listview.
 */
void MainWindow::showPlaylist()
{
    if(!ui->lvPlaylists->selectedItems().empty()){
        currentPlaylist = playlistController->playlists().getPlaylistByName(ui->lvPlaylists->selectedItems().first()->text());
        if(currentPlaylist != nullptr){
            m_uiPlayList->setUsuario(m_usuario);
            m_uiPlayList->setPlaylist(currentPlaylist);
            ui->stackedWidget->setCurrentWidget(m_uiPlayList);
        }
    }
}

/**
 * @brief MainWindow::on_lvPlaylists_itemSelectionChanged
 *
 */
void MainWindow::on_lvPlaylists_itemSelectionChanged()
{
    showPlaylist();
}

/**
 * @brief MainWindow::on_btnPlayPlaylist_clicked
 */
void MainWindow::on_btnPlayPlaylist_clicked()
{
    //ui_tocarPlaylist
}

/**
 * @brief MainWindow::on_lvPlaylists_clicked
 * @param index
 */
void MainWindow::on_lvPlaylists_clicked(const QModelIndex &index)
{
    if(index.row() > 0)
        showPlaylist();
}

/**
 * @brief MainWindow::on_lvPlaylists_doubleClicked
 * @param index
 */
void MainWindow::on_lvPlaylists_doubleClicked(const QModelIndex &index)
{
    //ui_tocarPlaylist
}

/**
 * @brief MainWindow::on_edtSearch_returnPressed
 * Ao dar enter na pesquisa, executa no controler e atualiza a tabela de resultados.
 */
void MainWindow::on_edtSearch_returnPressed()
{
    pesquisaController->pesquisarMusicas(ui->edtSearch->text().trimmed());
}
