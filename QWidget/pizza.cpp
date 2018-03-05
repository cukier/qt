#include "pizza.h"

#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QtCore/QtMath>

Pizza::Pizza(QWidget *parent) :
    QWidget(parent)
{
    m_pen.setColor(Qt::black);
    m_pen.setWidth(3);
    m_pen.setCapStyle(Qt::RoundCap);
    m_pen.setJoinStyle(Qt::RoundJoin);

    m_brush.setStyle(Qt::NoBrush);
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

    painter.setPen(m_pen);
    painter.setBrush(m_brush);

    //    Pizza::drawA(&painter);
    //    Pizza::drawPos(&painter);
    Pizza::drawSec(&painter);
    qDebug() << "update";
}

void Pizza::drawPos(QPainter *painter)
{
    QLineF li;

    if (m_raio <= 0)
        m_raio = 200;

    if (m_angulo >= 360 || m_angulo < 0)
        m_angulo = 0;

    li.setP1(QPoint(m_raio, m_raio));
    li.setP2(QPoint(((qCos(qDegreesToRadians(m_angulo)) * m_raio) + m_raio),
                    ((qSin(qDegreesToRadians(m_angulo)) * m_raio)) + m_raio));

    m_pen.setBrush(Qt::red);

    painter->setPen(m_pen);
    painter->drawLine(li);
}

void Pizza::drawSec(QPainter *painter)
{
    qreal aux;

    if (m_raio <= 0)
        m_raio = 200;

    aux = m_raio + 10;

    QPointF c(aux, aux);
    painter->setBrush(m_brush);
    painter->drawEllipse(c, m_raio, m_raio);

    qreal sum;

    sum = 0;

    if (m_angulos.size() <= 0)
        return;

    QRect rect(10, 10, m_raio * 2, m_raio * 2);

    for (auto ang : m_angulos)
    {
        sum += ang;
        painter->drawPie(rect, (sum - ang) * 16, ang * 16);
    }
}

void Pizza::inSec(qreal angulo)
{
    m_angulos.push_back(angulo);
}

void Pizza::drawElip()
{
    QPainter painter;

    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();
    painter.drawPie(QRect(10, 10, 100, 100), 0, 160);
    painter.restore();
}

void Pizza::drawA(QPainter *painter)
{
    QRect rect(10, 20, 80, 60);
    int startAngle = 20 * 16;
    int arcLength = 120 * 16;


    painter->drawPie(rect, startAngle, arcLength);
}
