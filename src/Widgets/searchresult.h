#pragma once

#include <QWidget>

namespace Ui {
class SearchResult;
}

class SearchResult : public QWidget
{
    Q_OBJECT

public:
    explicit SearchResult(QWidget *parent = nullptr);
    ~SearchResult();

private:
    Ui::SearchResult *ui;
};

