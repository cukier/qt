#ifndef PIZZA_H
#define PIZZA_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPen>
#include <QPainter>

class Pizza : public QWidget
{
    Q_OBJECT

public:
    Pizza(QWidget *parent = Q_NULLPTR);
    ~Pizza();

    void setAngulo(qreal angulo);
    void setRaio(int raio);
    void inSec(qreal angulo);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QBrush m_brush;
    QPen m_pen;

    qreal m_angulo = 0;
    int m_raio = 0;
    QVector<qreal> m_angulos;

    void drawPos(QPainter *painter);
    void drawSec(QPainter *painter);
    void drawElip();
    void drawA(QPainter *painter);
};

#endif // PIZZA_H
