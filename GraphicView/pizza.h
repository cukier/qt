#ifndef PIZZA_H
#define PIZZA_H

#include <QObject>
#include <QGraphicsScene>

class Pizza : public QGraphicsScene
{
public:
    Pizza(QObject *parent = Q_NULLPTR) : QGraphicsScene(parent) {}
    void drawPosition(int radio, qreal angulo, QPen pen);
};

#endif // PIZZA_H
