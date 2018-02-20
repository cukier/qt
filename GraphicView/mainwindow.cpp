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
    //    QPoint fim(0, 0);
    qreal diam = Raio << 1;
    QPen pen;
    QRect elip(0, 0, diam, diam);
    QLineF li;

    angulo += 0.25;

    if (angulo == 360)
    {
        angulo = 0;
        timer->stop();
    }

    //    li.setAngle(angulo);
    //    li.setLength(Raio);
    li.setP1(QPoint(Raio, Raio));
    li.setP2(QPoint(((qCos(qDegreesToRadians(angulo)) * Raio) + Raio),
                    ((qSin(qDegreesToRadians(angulo)) * Raio)) + Raio));

    //    fim.setX((int) (qCos(qDegreesToRadians(angulo)) * Raio));
    //    fim.setY((int) (qSin(qDegreesToRadians(angulo)) * Raio));
    //    li.setP1(QPoint(Raio, Raio));
    //    li.setLength(diam);
    //    li.setAngle(angulo);


    //    pen.setStyle(Qt::DashDotLine);
    pen.setWidth(3);
    //    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    //    painter.setPen(pen);
    //    painter.drawEllipse(centro, (int) Raio, (int) Raio);
    //    painter.drawLine(centro, fim);
    //    qDebug() << angulo;
    //    scene->addLine(0, 0, (int) angulo, (int) angulo, pen);
    //    scene->addEllipse(centro.x(), centro.y(), Raio, Raio, pen, Qt::NoBrush);
    scene->clear();
    scene->addEllipse(elip, pen, Qt::NoBrush);
    scene->addLine(li, pen);
    //    scene->addLine((qreal) centro.x(),(qreal) centro.y(),(qreal) fim.x(),(qreal) fim.y(), pen);
    qDebug() << angulo;
}
