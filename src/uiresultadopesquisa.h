#pragma once

#include <QWidget>
#include "Dao/musica.h"
#include "Dao/musicalist.h"
#include "Dao/playlist.h"
#include "Dao/playlists.h"

namespace Ui {
class ResultadoPesquisa;
}

class ResultadoPesquisa : public QWidget
{
    Q_OBJECT

public:
    explicit ResultadoPesquisa(QWidget *parent = nullptr);
    ~ResultadoPesquisa();

    void setMusicaList(MusicaList *musicaList);
    void setTermo(const QString &termo);

    void setPlaylists(Playlists playlists);
signals:
    void on_addMusicaNaPlaylist(const int playlistId, Musica *musica);

protected:
    void resizeEvent(QResizeEvent *event)override;

private:    
    void preencheGrid();
    void addplaylistMenuRequested(QPoint pos);

    Ui::ResultadoPesquisa *ui;

    Musica *m_musica;
    MusicaList *m_musicaList;
    Playlists m_playlists;

    enum ColunasTabela{
        Indice = 0,
        Nome = 1,
        Album = 2,
        Duracao = 3,
        Key = 4
    };

private slots:
    void on_clickAddNaPlaylist(QAction *action);

};

