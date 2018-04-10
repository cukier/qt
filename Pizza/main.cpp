#include "pizza.h"

#include <QApplication>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pizza w;
    QTimer *timer = new QTimer(&w);
    qreal angulo = 0;

    w.setAngulo(0);
    w.inserirSetor(195);
    w.inserirSetor(38.47);
    w.inserirSetorCanhao(20);
    w.inserirSetorCanhao(68);
    w.show();

    QObject::connect(timer, &QTimer::timeout,
                     &a, [&w, &angulo](){
        w.setAngulo(angulo);
        angulo += 0.25;

        if (angulo >= 360.0)
            angulo = 0.0;

        w.repaint();
        qDebug() << "Angulo " << angulo;
    });

    timer->start(10);

    return a.exec();
}
