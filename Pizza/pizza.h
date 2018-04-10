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
    void inserirSetor(qreal angulo);
    void inserirSetores(QVector<qreal> angulos);
    void inserirSetorCanhao(qreal angulo);
    void inserirSetoresCanhao(QVector<qreal> angulos);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    enum PixelsSize {
        PixelOffset = 10,
        MinimalSize = 150
    };

    qreal m_angulo = 0;
    QVector<qreal> m_angulos = { 0 };
    QVector<qreal> m_angulosCanhao = { 0 };
    QTimer *timer;
};

#endif // PIZZA_H
