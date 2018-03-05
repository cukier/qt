#include "window.h"
#include "pizza.h"

#include <QGridLayout>

window::window(QWidget *parent) : QWidget(parent)
{
    Pizza *pizza = new Pizza;
    QGridLayout *mainLayout = new QGridLayout(this);

    pizza->setRaio(150);
    pizza->inSec(40.0);
    pizza->inSec(87.2);
    pizza->setAngulo(32.5);

    mainLayout->addWidget(pizza);
    setLayout(mainLayout);
}
