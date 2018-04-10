#include "pizza.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pizza w;

    w.setAngulo(0);
    w.inserirSetor(195);
    w.inserirSetor(38.47);
    w.inserirSetorCanhao(20);
    w.inserirSetorCanhao(68);
    w.show();

    return a.exec();
}
