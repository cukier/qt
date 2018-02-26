#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer)
{
    ui->setupUi(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    angulo += 0.25;

    if (angulo >= 360.0 || angulo < 0.0)
        angulo = 0.0;

    QPen pen;
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    QLineF li;
    li.setP1(QPoint(150, 150));
    li.setP2(QPoint(0, 0));

    QPainter painter(ui->graphicsView->viewport());
    painter.setPen(pen);
    painter.drawLine(li);

    qDebug() << "Paint " << angulo;
}
