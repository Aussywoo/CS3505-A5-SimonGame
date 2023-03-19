#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimonModel m;
    MainWindow w(nullptr, &m);
    w.show();
    return a.exec();
}
