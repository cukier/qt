#include "window.h"
#include "pizza.h"

#include <QGridLayout>

window::window(QWidget *parent) : QWidget(parent)
{
    Pizza *pizza = new Pizza;
    QGridLayout *mainLayout = new QGridLayout(this);

    pizza->setRaio(150);
    pizza->inserirSetor(40.0);
    pizza->inserirSetor(87.2);
    pizza->inserirSetor(35.7);
    pizza->inserirSetor(90.54);
    pizza->setAngulo(32.5);

    mainLayout->addWidget(pizza);
    setLayout(mainLayout);
}
