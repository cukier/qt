#ifndef PIZZA_H
#define PIZZA_H

#include <QObject>
#include <QWidget>
#include <QTimer>

class Pizza : public QWidget
{
    Q_OBJECT

public:
    Pizza(QWidget *parent = Q_NULLPTR);
    ~Pizza();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *timer;

    int angulo;
};

#endif // PIZZA_H
