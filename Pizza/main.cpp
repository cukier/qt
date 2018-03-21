#include "pizza.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pizza w;

    w.setAngulo(258.4);
    w.inserirSetor(40.87);
    w.inserirSetor(32.98);
    w.show();

    return a.exec();
}
