#include "pizza.h"

#include <QPen>
#include <QPainter>
#include <QtCore/QtMath>
#include <QPaintEvent>

Pizza::Pizza(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this))
{
    m_angulos.clear();

    connect(timer, &QTimer::timeout,
            this, [this](){
        m_angulo += 0.5;

        if (m_angulo >= 360)
            m_angulo = 0;
    });

    timer->start(50);
}

Pizza::~Pizza()
{
}

void Pizza::setAngulo(qreal angulo)
{
    m_angulo = angulo;
}

void Pizza::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //    const QRect & rect = event->rect();

    QPainter painter(this);
    QPen pen;
    QBrush brush;

    int cor = Qt::darkRed;

    brush.setStyle(Qt::SolidPattern);

    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal sum = 0;
    QRect rec(PixelOffset, PixelOffset, width() - 2 * PixelOffset, height() - 2 * PixelOffset);

    for (const auto i : m_angulos)
    {
        pen.setColor((Qt::GlobalColor) cor);
        brush.setColor((Qt::GlobalColor) cor);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawPie(rec, sum * 16, i * 16);
        sum += i;
        update();
        ++cor;
    }

    if (sum < 360)
    {
        pen.setColor(Qt::gray);
        brush.setColor(Qt::gray);
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawPie(rec, sum * 16, (360 - sum) * 16);
    }

    qreal m_anguloAux = m_angulo + 90;
    qreal raioh = height() / 2;
    qreal raiow = width() / 2;
    qreal co = qSin(qDegreesToRadians(m_anguloAux)) * raioh;
    qreal ca = qCos(qDegreesToRadians(m_anguloAux)) * raiow;
    qreal pos_x = raiow + ca;
    qreal pos_y = raioh - co;


    //    qreal pos_y = (qCos(qDegreesToRadians(m_angulo)) * width()) + auxw;
    //    qreal pos_x = (qSin(qDegreesToRadians(m_angulo)) * height()) + auxh;
    QPointF fim(pos_x, pos_y);
    QPointF centro(raiow, raioh);

    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(centro, fim);
}

void Pizza::inserirSetor(qreal angulo)
{
    m_angulos.push_back(angulo);
}

void Pizza::clearSetor()
{
    m_angulos.clear();
}
