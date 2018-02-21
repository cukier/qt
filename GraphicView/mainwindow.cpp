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

    scene = new Pizza(this);
    ui->graphicsView->setMinimumSize(Raio * 2.5, Raio * 2.5);
    ui->graphicsView->setScene(scene);

    timer = new QTimer();
    timer->start(10);

    angulo = 0;

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //    setMinimumSize(QSize(TamanhoMinimoH, TamanhoMinimoW));
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
    QPen pen;

    angulo += 0.25;

    if (angulo == 360)
    {
        angulo = 0;
        timer->stop();
    }


    //    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(3);
    //    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    scene->drawPosition(Raio, angulo, pen);
}
