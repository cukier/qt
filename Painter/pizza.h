#ifndef PIZZA_H
#define PIZZA_H

#include <QObject>
#include <QPainter>
#include <QVector>

class Pizza : QPainter
{
public:
    Pizza(QPaintDevice *device);

    void setaAngulo(qreal angulo);
    qreal anguloAtual();
    void setaRaio(qreal raio);
    qreal raio();

    void desenhaPosicao(void);

private:
    qreal m_anguloAtual;
    qreal m_raio;
    QVector<qreal> m_angulos;
    QPen pen;
};

#endif // PIZZA_H
