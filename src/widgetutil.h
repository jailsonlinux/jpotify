#pragma once
#include <QTableWidget>
#include "Dao/musica.h"
#include "Dao/musicalist.h"


class WidgetUtil
{
public:
    template <typename Enumeration>
    static auto as_integer(Enumeration const value)
        -> typename std::underlying_type<Enumeration>::type
    {
        return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    }

    enum class ColunasTabela{
        Indice = 0,
        Nome = 1,
        Album = 2,
        Duracao = 3,
        Key = 4
    };

    static void resizeGrid(int parentWidget, QTableWidget *tabelaResultados);
    static void preencheGrid( QTableWidget *tabelaResultados, MusicaList *musicaList);

};

