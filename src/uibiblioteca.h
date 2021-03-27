#pragma once

#include <QScrollArea>

namespace Ui {
class uiBiblioteca;
}

class uiBiblioteca : public QScrollArea
{
    Q_OBJECT

public:
    explicit uiBiblioteca(QWidget *parent = nullptr);
    ~uiBiblioteca();

private:
    Ui::uiBiblioteca *ui;
};

