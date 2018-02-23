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
    qreal diam;
    qreal sum;
    int cor = Qt::blue;

    if (raio <= 0)
        raio = 200;

    diam = raio << 1;
    sum = 0;
    addEllipse(QRect(0, 0, diam, diam), pen,QBrush(Qt::green));

    if (angulos.size() <= 0)
        return;

    for (auto ang : angulos)
    {
        sum += ang;
        cor++;
        pen.setBrush((Qt::GlobalColor) cor);
        QGraphicsEllipseItem *elip =
                addEllipse(QRect(0, 0, diam, diam), pen,(Qt::GlobalColor) cor);
        elip->setStartAngle((int) (sum - ang));
        elip->setSpanAngle((int) ang);
    }
}

void Pizza::drawCircle()
{
    qreal diam;

    if (raio <= 0)
        raio = 200;

    pen.setBrush(Qt::darkGreen);
    //    pen.setColor(Qt::darkGreen);
    diam = raio << 1;
    addEllipse(QRect(0, 0, diam, diam),
               pen, Qt::NoBrush);
}

void Pizza::insertSector(qreal angulo)
{
    angulos.push_back(angulo);
}
