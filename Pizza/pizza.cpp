#include "pizza.h"

#include <QPen>
#include <QPainter>
#include <QtCore/QtMath>
#include <QPaintEvent>
#include <QDebug>

Pizza::Pizza(QWidget *parent) :
    QWidget(parent)
{
    m_angulos.clear();
    setMinimumSize(MinimalSize, MinimalSize);
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

    QPainter painter(this);
    QPen pen;
    QBrush brush;

    int cor = Qt::darkRed;

    brush.setStyle(Qt::SolidPattern);

    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal m_size = width() < height() ? width() : height();
    qreal m_centroh = height() / 2;
    qreal m_centrow = width() / 2;
    qreal sum = 0;
    qreal angOffset = -90;
    QRect rec;

    rec.setWidth(m_size - 2 * PixelOffset);
    rec.setHeight(m_size - 2 * PixelOffset);
    rec.moveCenter(QPoint(m_centrow, m_centroh));

    for (const auto i : m_angulos)
    {
        pen.setColor((Qt::GlobalColor) cor);
        brush.setColor((Qt::GlobalColor) cor);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawPie(rec, (sum + angOffset) * -16, i * -16);
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
        painter.drawPie(rec, (sum + angOffset) * -16, (360 - sum) * -16);
    }

    qreal m_anguloAux = m_angulo - angOffset;
    qreal p_aux = m_centroh < m_centrow ? m_centroh : m_centrow;
    qreal co = qSin(qDegreesToRadians(m_anguloAux)) * p_aux;
    qreal ca = qCos(qDegreesToRadians(m_anguloAux)) * p_aux;
    qreal pos_x = m_centrow - ca;
    qreal pos_y = m_centroh - co;

    QPointF fim(pos_x, pos_y);
    QPointF centro(m_centrow, m_centroh);

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

void Pizza::inserirSetorCanhao(qreal angulo)
{
    m_angulosCanhao.push_back(angulo);
}

void Pizza::inserirSetores(QVector<qreal> angulos)
{
    m_angulos.clear();

    for (const auto i : angulos)
        m_angulos.push_back(i);
}

void Pizza::inserirSetoresCanhao(QVector<qreal> angulos)
{
    m_angulosCanhao.clear();

    for(const auto i : angulos)
        m_angulosCanhao.push_back(i);
}
