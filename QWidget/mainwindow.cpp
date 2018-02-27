#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pizza = new Pizza;
    pizza->setView(ui->graphicsView);

    ui->gridLayout->addWidget(pizza, 0, 0, 1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
