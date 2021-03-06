#include "pizza.h"

#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QtCore/QtMath>

Pizza::Pizza(QWidget *parent) :
    QWidget(parent)
{
    m_angulos.clear();
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
    setMinimumHeight((raio + PixelOffset) * 2);
    setMinimumWidth((raio + PixelOffset) * 2);
}

void Pizza::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    int cor = Qt::darkGreen;

    if (m_raio <= 0)
        m_raio = 200;

    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    brush.setStyle(Qt::SolidPattern);

    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_angulos.size())
    {
        qreal sum;

        sum = 0;

        qreal rectAux = m_raio * 2;
        QRectF rect(PixelOffset, PixelOffset, rectAux, rectAux);
        cor = Qt::blue;

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

        if (sum < 360)
        {
            pen.setColor(Qt::darkGreen);
            brush.setColor(Qt::darkGreen);
            painter.setBrush(brush);
            painter.setPen(pen);
            painter.drawPie(rect, sum * 16, (360 - sum) * 16);
        }
    }
    else
    {
        int aux = m_raio + PixelOffset;

        pen.setColor(Qt::darkGreen);
        brush.setColor(Qt::darkGreen);
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawEllipse(QPointF(aux, aux), m_raio, m_raio);
    }

    int aux = m_raio + PixelOffset;
    QPointF centro(aux, aux);
    qreal pos_y = (qCos(qDegreesToRadians(m_angulo)) * m_raio) + aux;
    qreal pos_x = (qSin(qDegreesToRadians(m_angulo)) * m_raio) + aux;
    QPointF fim(pos_x, pos_y);

    pen.setColor(Qt::red);
    brush.setColor(Qt::red);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawLine(centro, fim);
}

void Pizza::inserirSetor(qreal angulo)
{
    m_angulos.push_back(angulo);
}
