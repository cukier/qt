#include "pizza.h"

#include <QtCore/QtMath>
#include <QGraphicsEllipseItem>

Pizza::Pizza(QObject *parent) : QGraphicsScene(parent)
{
    angulo = 0;
    raio = 0;
    angulos.clear();
}

void Pizza::config(int raio, qreal angulo, QPen pen)
{
    this->angulo = angulo;
    this->pen = pen;
    this->raio = raio;
}

void Pizza::setAngulo(qreal angulo)
{
    this->angulo = angulo;
}

void Pizza::setRaio(int raio)
{
    this->raio = raio;
}

void Pizza::setPen(QPen pen)
{
    this->pen = pen;
}

void Pizza::drawPosition()
{
    QLineF li;

    if (raio <= 0)
        raio = 200;

    if (angulo >= 360 || angulo < 0)
        angulo = 0;

    li.setP1(QPoint(raio, raio));
    li.setP2(QPoint(((qCos(qDegreesToRadians(angulo)) * raio) + raio),
                    ((qSin(qDegreesToRadians(angulo)) * raio)) + raio));

    pen.setBrush(Qt::red);

    addLine(li, pen);
}

void Pizza::drawSec()
{
    QLineF li;
    qreal sum;

    if (angulos.size() <= 0)
        return;

    pen.setBrush(Qt::blue);

    sum = 0;
    li.setP1(QPoint(raio, raio));
    li.setP2(QPoint(((qCos(qDegreesToRadians(0.0)) * raio) + raio),
                    ((qSin(qDegreesToRadians(0.0)) * raio)) + raio));
    addLine(li, pen);

    for(qreal ang : angulos)
    {
        sum += ang;

        while (sum >= 360)
            sum -= 360;

        li.setP2(QPoint(((qCos(qDegreesToRadians(sum)) * raio) + raio),
                        ((qSin(qDegreesToRadians(sum)) * raio)) + raio));
        addLine(li, pen);
    }
}

void Pizza::drawCircle()
{
    qreal diam;

    if (raio <= 0)
        raio = 200;

    pen.setBrush(Qt::green);
    diam = raio << 1;
    QRect elip(0, 0, diam, diam);
    addEllipse(elip, pen, Qt::NoBrush);
}

void Pizza::insertSector(qreal angulo)
{
    angulos.push_back(angulo);
}
