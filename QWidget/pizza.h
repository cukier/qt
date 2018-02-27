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

    void setView(QGraphicsView *i_view);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *timer;
    QGraphicsView *view;

    int angulo;
};

#endif // PIZZA_H
