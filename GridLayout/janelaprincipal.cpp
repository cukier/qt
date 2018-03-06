#include "janelaprincipal.h"

#include <QLabel>
#include <QGridLayout>

JanelaPrincipal::JanelaPrincipal(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);
    setLayout(mainLayout);

    QLabel *label_1 = new QLabel(this);
    label_1->setText("Label 1");
    label_1->setMinimumHeight(30);
    label_1->setMinimumHeight(70);
    mainLayout->addWidget(label_1, 0, 0, 1, 1);

    label_1 = new QLabel(this);
    label_1->setText("Label 2");
    label_1->setMinimumHeight(30);
    label_1->setMinimumHeight(70);
    mainLayout->addWidget(label_1, 1, 0, 1, 1);

    label_1 = new QLabel(this);
    label_1->setText("Label 3");
    label_1->setMinimumHeight(30);
    label_1->setMinimumHeight(70);
    mainLayout->addWidget(label_1, 2, 0, 1, 1);
}
