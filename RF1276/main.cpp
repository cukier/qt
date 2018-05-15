#include "rf1276.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RF1276 w;
    w.show();

    return a.exec();
}
