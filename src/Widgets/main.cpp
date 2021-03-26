#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /**
     * ToDo: Parametrizar estilos.
     */
    /**
    QFile file(QStringLiteral(":/darkstyle.qss"));
    if(file.open(QFile::ReadOnly)){
        qApp->setStyleSheet(QLatin1String(file.readAll()));
    }
    **/

    MainWindow w;
    w.show();
    return a.exec();
}
