#pragma once

#include <QMainWindow>
#include <memory>

#include "uilogin.h"
#include "uiresultadopesquisa.h"
#include "uiplaylist.h"
#include "tocaplaylist.h"
#include "Dao/usuario.h"
#include "Api/api.h"
#include "Controllers/playlistcontroller.h"
#include "Controllers/pesquisacontroller.h"
#include "Dao/musica.h"
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>

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

    void on_lvPlaylists_itemSelectionChanged();

    void on_btnPlayPlaylist_clicked();

    void on_lvPlaylists_clicked(const QModelIndex &index);

    void on_lvPlaylists_doubleClicked(const QModelIndex &index);

    void on_edtSearch_returnPressed();

    void on_btnPlayPause_clicked();

    void on_btnBack_clicked();

    void on_btnNext_clicked();

private:

    void swapLoginToSearch();
    void reloadPlaylists();
    void habilitaSeLogado();
    void showPlaylist();
    void showTocaPlaylist();
    void preencheMusicaAtual(Musica *musica);

    Ui::MainWindow *ui;
    Login *m_uiLogin;
    UiPlaylist * m_uiPlayList;
    ResultadoPesquisa *m_uiResultadoPesquisa;
    TocaPlaylist *m_uiTocaPlaylist;

    Usuario *m_usuario;
    Api *api;

    PlayListController *playlistController;
    PesquisaController *pesquisaController;
    PlayList *currentPlaylist;
    Musica *m_musicaAtualTocando;


    QMediaPlaylist *mediaPlaylist;
    QMediaPlayer *mediaPlayer;

};

