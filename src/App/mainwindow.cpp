#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * Telas do fluxo
 * Logar
 * Cadastrar credenciais
 * Buscas
 * Tocar playlists
**/

#include "./usuarios.h"
#include "./searchresult.h"
#include "./playlist.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , uiLogin( new Login(this))
{
    ui->setupUi(this);
    uiLogin.get()->resize(500, 640);
    uiLogin.get()->show();
    ui->stackedWidget->addWidget(uiLogin.get());

    //Chamar login
    ui->stackedWidget->setCurrentWidget(uiLogin.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}


/**
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QPainter>

#include "./loginweb.h"

//Todo: Optar por imagens em svg
void MainWindow::initIcons()
{
    QSvgRenderer renderer(QStringLiteral(":/resources/images/svg/logo.svg"));
    QPixmap pm(ui->lblLogo->width(), ui->lblLogo->height());
    pm.fill(Qt::transparent);
    QPainter painter(&pm);
    renderer.render(&painter, pm.rect());
    ui->lblLogo->setPixmap(pm);
}

void MainWindow::initLoginWeb()
{
    std::unique_ptr<LoginWeb>uiLogin = std::make_unique<LoginWeb>(this);
    uiLogin.get()->setUrl(QUrl(QStringLiteral("https://open.spotify.com/playlist/5uHljRIG4nQcxrBepa2nyA")));
    uiLogin.get()->resize(500, 640);
    uiLogin.get()->show();

    ui->stackedWidget->addWidget(uiLogin.get());
    //Chamar login
    ui->stackedWidget->setCurrentWidget(uiLogin.get());
}
**/
