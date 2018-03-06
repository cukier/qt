#include "window.h"

#include <QGridLayout>

window::window(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer)
{
    pizza = new Pizza;
    QGridLayout *mainLayout = new QGridLayout(this);

    pizza->setRaio(150);
    pizza->inserirSetor(40.0);
//    pizza->inserirSetor(87.2);
//    pizza->inserirSetor(35.7);
//    pizza->inserirSetor(90.54);
    pizza->setAngulo(32.5);

    mainLayout->addWidget(pizza);
    setLayout(mainLayout);

    connect(timer, &QTimer::timeout, this, &window::setAngulo);
    timer->start(10);
}

window::~window()
{
    if (timer)
        timer->stop();

    delete timer;
    delete pizza;
}

void window::setAngulo()
{
    angulo += 0.25;
    pizza->setAngulo(angulo);
    update();
}
