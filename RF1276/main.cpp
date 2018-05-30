//#include "mainwindow.h"
#include "radio.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    Radio w;

    w.show();

    return a.exec();
}
