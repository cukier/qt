#ifndef PIZZA_H
#define PIZZA_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QGraphicsView>

class Pizza : public QWidget
{
    Q_OBJECT

public:
    Pizza(QWidget *parent = Q_NULLPTR);
    ~Pizza();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int angulo = 0;
};

#endif // PIZZA_H
