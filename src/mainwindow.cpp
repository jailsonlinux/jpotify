#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QString>
/**
 * Telas do fluxo
 * Logar
 * Cadastrar credenciais
 * Buscas
 * Tocar playlists
**/

#include "usuarios.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_uiLogin(new Login(this))
    , m_user(new User)
    , m_uiSearch(new SearchResult(this))
    , signaler(new MouseButtonSignaler(this))
{
    ui->setupUi(this);

    //Filtro de clique no label
    signaler.installOn(ui->lblInicio);
    signaler.installOn(ui->lblImgInicio);

    signaler.installOn(ui->lblBuscar);
    signaler.installOn(ui->lblImgBusca);

    signaler.installOn(ui->lblBiblioteca);
    signaler.installOn(ui->lblImgBiblioteca);

    connect(&signaler, &MouseButtonSignaler::mouseButtonEvent, [&](QWidget* widget, QMouseEvent * event) {
        if (event->type() == QEvent::MouseButtonPress){
            QString widgetName = widget->objectName();
            qDebug() << widgetName;
            if(widgetName == "lblInicio" || widgetName == "lblImgInicio"){
                ui->stackedWidget->addWidget(m_uiLogin);
                ui->stackedWidget->setCurrentWidget(m_uiLogin);
            } else if(widgetName == "lblBuscar" || widgetName == "lblImgBusca"){
                ui->stackedWidget->addWidget(m_uiSearch);
                ui->stackedWidget->setCurrentWidget(m_uiSearch);
            } else if (widgetName == "lblBiblioteca" || widgetName == "lblImgBiblioteca"){
//                ui->stackedWidget->addWidget(m_uiLogin);
//                ui->stackedWidget->setCurrentWidget(m_uiLogin);
            }
        }
    });

    m_uiLogin->resize(500, 640);
    m_uiLogin->show();
    ui->stackedWidget->addWidget(m_uiLogin);
    ui->stackedWidget->addWidget(m_uiSearch);

    //Chamar login
    ui->stackedWidget->setCurrentWidget(m_uiLogin);

    connect(m_uiLogin, &Login::on_loginCancel, [=]() {
        ui->stackedWidget->addWidget(m_uiSearch);
        ui->stackedWidget->setCurrentWidget(m_uiSearch);
        ui->stackedWidget->removeWidget(m_uiLogin);
    });

    //    QMessageBox msgBox;
    //    msgBox.setText(QStringLiteral(""));
    //    msgBox.exec();

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
