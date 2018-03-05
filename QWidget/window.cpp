#include "window.h"
#include "pizza.h"

#include <QGridLayout>

window::window(QWidget *parent) : QWidget(parent)
{
    Pizza *pizza = new Pizza;
    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout->addWidget(pizza);
    setLayout(mainLayout);

    timer.start(1000);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}
