#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QtCore/QtMath>
#include <QTimer>
#include <QDebug>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(nullptr)
{
    ui->setupUi(this);

    timer = new QTimer();
    timer->start(200);

    angulo = 0;

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    setMinimumSize(QSize(TamanhoMinimoH, TamanhoMinimoW));
}

MainWindow::~MainWindow()
{
    if(timer)
        timer->stop();

    delete timer;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPoint centro(Centro, Centro);
    QPoint fim(0, 0);
    QPen pen;

    angulo += 0.25;

    if (angulo == 360)
        angulo = 0;

    fim.setX((int) ((qCos(qDegreesToRadians(angulo)) * Raio) + Centro));
    fim.setY((int) ((qSin(qDegreesToRadians(angulo)) * Raio) + Centro));

    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(3);
    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    painter.setPen(pen);
    painter.drawEllipse(centro, (int) Raio, (int) Raio);
    painter.drawLine(centro, fim);
    qDebug() << angulo;
}
