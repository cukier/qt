#include "pizza.h"

#include <QtCore/QtMath>
#include <QDebug>

void Pizza::drawPosition(int raio, qreal angulo, QPen pen)
{
    qreal diam = raio << 1;
    QRect elip(0, 0, diam, diam);
    QLineF li;

    if (raio <= 0)
        raio = 200;

//    angulo += 0.25;

    if (angulo >= 360 || angulo < 0)
    {
        angulo = 0;
    }

    li.setP1(QPoint(raio, raio));
    li.setP2(QPoint(((qCos(qDegreesToRadians(angulo)) * raio) + raio),
                    ((qSin(qDegreesToRadians(angulo)) * raio)) + raio));

    clear();
    addEllipse(elip, pen, Qt::NoBrush);
    addLine(li, pen);
    qDebug() << angulo;
}
