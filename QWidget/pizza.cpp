#include "pizza.h"

#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QtCore/QtMath>

Pizza::Pizza(QWidget *parent) :
    QWidget(parent)
{
}

Pizza::~Pizza()
{
}

void Pizza::setAngulo(qreal angulo)
{
    m_angulo = angulo;
}

void Pizza::setRaio(int raio)
{
    m_raio = raio;
    setMinimumHeight(raio * 2 + 20);
    setMinimumWidth(raio * 2 + 20);
}

void Pizza::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);

    qreal aux;

    if (m_raio <= 0)
        m_raio = 200;

    aux = m_raio + 10;

    QPointF c(aux, aux);
    int cor = Qt::darkGreen;

    QPen pen;
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);



    if (m_angulos.size())
    {
        qreal sum;

        sum = 0;

        if (m_angulos.size() <= 0)
            return;

        QRect rect(10, 10, m_raio * 2, m_raio * 2);

        for (auto ang : m_angulos)
        {
            sum += ang;
            pen.setColor((Qt::GlobalColor) cor);
            brush.setColor((Qt::GlobalColor) cor);
            painter.setPen(pen);
            painter.setBrush(brush);
            painter.drawPie(rect, (sum - ang) * 16, ang * 16);
            ++cor;
        }

        pen.setColor(Qt::darkGreen);
        brush.setColor(Qt::darkGreen);
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawPie(rect, sum * 16, (360 - sum) * 16);
    }
    else
    {
        pen.setColor(Qt::darkGreen);
        brush.setColor(Qt::darkGreen);
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawEllipse(c, m_raio, m_raio);
    }
}

void Pizza::inserirSetor(qreal angulo)
{
    m_angulos.push_back(angulo);
}
