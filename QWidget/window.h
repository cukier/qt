#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTimer>

#include "pizza.h"

class window : public QWidget
{
    Q_OBJECT
public:
    explicit window(QWidget *parent = nullptr);
    ~window();

signals:

public slots:
    void setAngulo();

private:
    QTimer *timer;
    Pizza *pizza;
    qreal angulo = 0;
};

#endif // WINDOW_H
