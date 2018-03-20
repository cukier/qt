#include "myloginform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyLoginForm w;
    w.show();

    return a.exec();
}
