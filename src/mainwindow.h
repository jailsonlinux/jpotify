#pragma once

#include <QMainWindow>
#include <memory>

#include "uilogin.h"
#include "uiresultadopesquisa.h"
#include "uiplaylist.h"
#include "Dao/usuario.h"
#include "Api/api.h"
#include "Controllers/playlistcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void on_loginsucess();
    void on_loginErro();
    void on_loginCancel();

private slots:    

    void on_btnInicio_clicked();

    void on_btnBuscar_clicked();

    void on_btnCriarPlaylist_clicked();

private:

    void swapLoginToSearch();
    void reloadPlaylists();
    void habilitaSeLogado();

    Ui::MainWindow *ui;
    Login *m_uiLogin;
    UiPlaylist * m_uiPlayList;
    ResultadoPesquisa *m_uiSearch;

    Usuario *m_usuario;
    Api *api;

    PlayListController *playlistController;
    PlayList *currentPlaylist;
    Playlists *playlists;

};

