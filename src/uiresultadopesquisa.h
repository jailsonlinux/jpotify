#pragma once

#include <QWidget>

namespace Ui {
class ResultadoPesquisa;
}

class ResultadoPesquisa : public QWidget
{
    Q_OBJECT

public:
    explicit ResultadoPesquisa(QWidget *parent = nullptr);
    ~ResultadoPesquisa();

private:
    Ui::ResultadoPesquisa *ui;
};

