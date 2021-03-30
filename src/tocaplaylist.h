#pragma once

#include <QWidget>
#include "Dao/musica.h"
#include "Dao/musicalist.h"
#include "Dao/playlist.h"
#include "Dao/playlists.h"
#include "Dao/usuario.h"

namespace Ui {
class TocaPlaylist;
}

class TocaPlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit TocaPlaylist(QWidget *parent = nullptr);
    ~TocaPlaylist();

    void setPlaylist(PlayList *playlist);

    void setUsuario(Usuario *usuario);

signals:
    void on_playCurrentMusica(const int playlistid, Musica *musica, const int rowIdx);
protected:
    void resizeEvent(QResizeEvent *event)override;

private slots:
    void on_tabelaResultados_doubleClicked(const QModelIndex &index);

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
    PlayList *m_playlist;

    QTime m_duracao;
    Usuario *m_usuario;
};

