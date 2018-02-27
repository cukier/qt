#ifndef PIZZA_H
#define PIZZA_H

#include <QObject>
#include <QGraphicsScene>

class Pizza : public QGraphicsScene
{
public:
    Pizza(QObject *parent = Q_NULLPTR);

    void config(int raio, qreal angulo, QPen pen);
    void setAngulo(qreal angulo);
    void setRaio(int raio);
    void setPen(QPen pen);
    void drawPosition();
    void drawSec();
    void drawCircle();
    void insertSector(qreal angulo);
    void drawElip();

private:
    QPen pen;
    qreal angulo;
    int raio;
    QVector<qreal> angulos;
};

#endif // PIZZA_H
