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
    void on_addMusicaNaPlaylist(const QString &nome);

protected:
    void resizeEvent(QResizeEvent *event)override;

private:    
    void preencheGrid();
    void addplaylistMenuRequested(QPoint pos);

    Ui::ResultadoPesquisa *ui;

    Musica *m_musica;
    MusicaList *m_musicaList;
    Playlists m_playlists;

private slots:
    void on_clickAddNaPlaylist(QAction *action);

};

