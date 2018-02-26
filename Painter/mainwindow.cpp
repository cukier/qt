#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    painter(nullptr),
    timer(nullptr)
{
    ui->setupUi(this);

    angulo = 0;

    QPen pen;
    //    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(3);
    //    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    painter = new Pizza(this);
    painter->setaRaio(600);
    painter->setaAngulo(0);
    painter->setPen(pen);

    timer = new QTimer;
    timer->start(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete painter;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (!painter)
        return;

    painter->setaAngulo(angulo);
    painter->desenhaPosicao();

    angulo += 0.25;

    if (angulo >= 360.0)
        angulo = 0.0;

    qDebug() << "Paint";
}
