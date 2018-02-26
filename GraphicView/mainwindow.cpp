#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QtMath>
#include <QTimer>
#include <QDebug>

#include "pizza.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(nullptr),
    timer(nullptr)
{
    ui->setupUi(this);

    QPen pen;

    //    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(3);
    //    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    scene = new Pizza(this);
    scene->config(Raio, 0, pen);
    scene->insertSector(120);
    scene->insertSector(60);
    scene->insertSector(144);
//    scene->insertSector(44);

    ui->graphicsView->setMinimumSize(Raio * 2.5, Raio * 2.5);
    ui->graphicsView->setScene(scene);

    timer = new QTimer();
    timer->start(10);

    angulo = 0;

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

MainWindow::~MainWindow()
{
    if(timer)
        timer->stop();

    delete timer;
    delete scene;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    angulo += 0.25;

    if (angulo == 360)
    {
        angulo = 0;
        timer->stop();
    }

    scene->setAngulo(angulo);
    scene->clear();
    scene->drawSec();
    //    scene->drawCircle();
//    scene->drawPosition();
}
