#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGuiApplication::setQuitOnLastWindowClosed(false);
    MainWindow w;
    w.show();
    return a.exec();
}
