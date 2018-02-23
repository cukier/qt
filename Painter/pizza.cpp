#include "pizza.h"

#include <QtCore/QtMath>

Pizza::Pizza(QPaintDevice *device) : QPainter(device)
{
    this->m_angulos.clear();
    this->m_anguloAtual = 0;
    this->m_raio = 0;
    this->pen.setWidth(3);
    this->pen.setCapStyle(Qt::RoundCap);
    this->pen.setJoinStyle(Qt::RoundJoin);
}

void Pizza::setaAngulo(qreal angulo)
{
    this->m_anguloAtual = angulo;
}

qreal Pizza::anguloAtual()
{
    return this->m_anguloAtual;
}

void Pizza::setaRaio(qreal raio)
{
    this->m_raio = raio;
}

qreal Pizza::raio()
{
    return this->m_raio;
}

void Pizza::desenhaPosicao()
{
    QLineF li;

    if (m_raio <= 0)
        m_raio = 400.0;

    if (m_anguloAtual >= 360 || m_anguloAtual < 0)
        m_anguloAtual = 0;

    li.setP1(QPoint(m_raio, m_raio));
    li.setP2(QPoint(((qCos(qDegreesToRadians(m_anguloAtual)) * m_raio) + m_raio),
                    ((qSin(qDegreesToRadians(m_anguloAtual)) * m_raio)) + m_raio));

    pen.setBrush(Qt::red);
    drawLine(li);
}
