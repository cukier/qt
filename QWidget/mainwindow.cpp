#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Pizza *pizza = new Pizza;
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(pizza);
    setLayout(mainLayout);
    pizza->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
