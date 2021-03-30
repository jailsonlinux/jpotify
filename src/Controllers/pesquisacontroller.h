#pragma once

#include <QObject>
#include <QJsonObject>
#include "Dao/musica.h"
#include "Dao/musicalist.h"
#include "Dao/musicasdao.h"
#include "Api/api.h"

class PesquisaController: public QObject
{
    Q_OBJECT
public:
    PesquisaController(Api *api);

    void pesquisarMusicas(const QString &termo);

    MusicaList *musicaList() const;

signals:
    void on_pesquisaConcluida();

private:

    Api *m_api;
    MusicaList *m_musicaList;

};

