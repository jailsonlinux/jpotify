#pragma once

#include <QMainWindow>
#include <memory>

#include "uilogin.h"
#include "uiresultadopesquisa.h"
#include "Dao/usuario.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnBliblioteca_clicked();

    void on_btnInicio_clicked();

    void on_btnBuscar_clicked();

    void on_btnCriarPlaylist_clicked();

private:
    Ui::MainWindow *ui;
    Login *m_uiLogin;
    Usuario *m_usuario;
    ResultadoPesquisa *m_uiSearch;
};

