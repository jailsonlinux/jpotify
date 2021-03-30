#pragma once

#include <QWidget>
#include "Dao/musica.h"
#include "Dao/musicalist.h"
#include "Dao/playlist.h"
#include "Dao/playlists.h"

namespace Ui {
class TocaPlaylist;
}

class TocaPlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit TocaPlaylist(QWidget *parent = nullptr);
    ~TocaPlaylist();

    void setMusicaList(MusicaList *musicaList);
    void setPlaylists(Playlists playlists);

protected:
    void resizeEvent(QResizeEvent *event)override;

private:
    void preencheGrid();

    Ui::TocaPlaylist *ui;

    enum ColunasTabela{
        Indice = 0,
        Nome = 1,
        Album = 2,
        Duracao = 3,
        Key = 4
    };

    Musica *m_musica;
    MusicaList *m_musicaList;
    Playlists m_playlists;
};

