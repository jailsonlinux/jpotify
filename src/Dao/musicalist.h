#pragma once

#include <QList>

#include "musica.h"


class MusicaList
{    
public:
    explicit MusicaList() = default;
    ~MusicaList();
    void clear();
    int size() const;
    void addMusica(Musica *musica);
    void removeMusica(Musica *musica);
    void addMusicas(MusicaList * musicas);
    Musica *getMusicaByName(const QString &nome);
    Musica *getMusicaByKey(const QString key);

    QList<Musica *> getMusicas() const;
    void setMusicas(const QList<Musica *> &musicas);

private:
    QList<Musica*> m_musicas;

};

