#pragma once

#include <QObject>

#include "musicalist.h"

class PlayList
{

public:
    explicit PlayList();
    ~PlayList() = default;

    int getId() const;
    void setId(int getId);

    int userid() const;
    void setUsuarioid(int userid);

    QString nome() const;
    void setNome(const QString &nome);

    QString descricao() const;
    void setDescricao(const QString &descricao);

    QString apiId() const;
    void setApiid(const QString &value);

    MusicaList* getMusicas();
    void setMusicas(MusicaList* &musicas);

private:
    int m_id;
    int m_userid;
    QString m_nome;
    QString m_descricao;
    QString m_apiid; //identificador de playlist da api.

    MusicaList m_musicas;

};

