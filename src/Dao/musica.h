#pragma once

#include <QObject>
#include <QString>

class Musica :public QObject
{    
    Q_OBJECT
public:
    explicit Musica();
    ~Musica() = default;
    QString key() const;
    void setKey(const QString &key);

    int playlistid() const;
    void setPlaylistid(int playlistid);

    QString nome() const;
    void setNome(const QString &nome);

    QString artista() const;
    void setArtista(const QString &artista);

    QString album() const;
    void setAlbum(const QString &album);

    int duracao() const;
    void setDuracao(int duracao);

    int ordem() const;
    void setOrdem(int ordem);

    QString track() const;
    void setTrack(const QString &track);

    QString previewUrl() const;
    void setPreviewUrl(const QString &previewUrl);

    QString imagem() const;
    void setImagem(const QString &imagem);

    QString getDuracaoMinSec();

private:
    QString m_key;
    int m_playlistid;
    QString m_nome;
    QString m_artista;
    QString m_album;
    int m_duracao;
    int m_ordem;
    QString m_track;
    QString m_previewUrl;
    QString m_imagem;
};

