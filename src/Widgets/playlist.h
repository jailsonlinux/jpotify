#pragma once

#include <QWidget>

namespace Ui {
class PlayList;
}

class PlayList : public QWidget
{
    Q_OBJECT

public:
    explicit PlayList(QWidget *parent = nullptr);
    ~PlayList();

private:
    Ui::PlayList *ui;
};

