#pragma once

#include <QMainWindow>
#include <memory>

#include "login.h"
#include "searchresult.h"
#include "Dao/user.h"
#include "MouseButtomSignaler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Login *m_uiLogin;
    User *m_user;
    SearchResult *m_uiSearch;
    MouseButtonSignaler signaler;
};

