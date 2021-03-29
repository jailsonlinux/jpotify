#pragma once
#include <QObject>
#include <QWidget>
#include <QTime>
#include <QString>
#include "Dao/usuario.h"

#include "Dao/playlist.h"

namespace Ui {
class UiPlaylist;
}

class UiPlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit UiPlaylist(QWidget *parent = nullptr);
    ~UiPlaylist();

    PlayList *getPlaylist() const;
    void setPlaylist(PlayList *value);
    int getQtdMusicas() const;
    void setQtdMusicas(int qtdMusicas);

    QString getDuracao() const;
    void setDuracao(const QTime &duracao);

    void setUsuario(Usuario *usuario);

signals:
    void on_cancelarPlaylist();
    void on_salvarPlayList();
    void on_excluirPlayList(PlayList *m_playlist);

private slots:
    void on_btnCancelar_clicked();


    void on_btnSalvar_clicked();

    void on_btnExcluir_clicked();

private:
    Ui::UiPlaylist *ui;

    PlayList *m_playlist;
    int m_qtdMusicas;

    QTime m_duracao;
    Usuario *m_usuario;
};

