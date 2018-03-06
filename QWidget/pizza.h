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
    void inserirSetor(qreal angulo);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    enum PixelsSize {
        PixelOffset = 10
    };

    qreal m_angulo = 0;
    int m_raio = 0;
    QVector<qreal> m_angulos;
};

#endif // PIZZA_H
