#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QPainter>
//#include <QPaintEvent>
#include <QtCore/QtMath>
//#include <QTimer>
#include <QDebug>
//#include <QPen>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(nullptr),
    timer(nullptr)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    timer = new QTimer();
    timer->start(100);

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
    //    QPainter painter(this);
    QPoint centro(Centro, Centro);
    QPoint fim(0, 0);
    QPen pen;
    QRect elip(0, 0, Raio << 1, Raio << 1);
    QLineF li(0, 0, Raio, Raio);

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

    //    painter.setPen(pen);
    //    painter.drawEllipse(centro, (int) Raio, (int) Raio);
    //    painter.drawLine(centro, fim);
    //    qDebug() << angulo;
    //    scene->addLine(0, 0, (int) angulo, (int) angulo, pen);
    //    scene->addEllipse(centro.x(), centro.y(), Raio, Raio, pen, Qt::NoBrush);
    scene->addEllipse(elip, pen, Qt::NoBrush);
    scene->addLine(li, pen);
//    scene->addLine((qreal) centro.x(),(qreal) centro.y(),(qreal) fim.x(),(qreal) fim.y(), pen);
    qDebug() << angulo;
}
