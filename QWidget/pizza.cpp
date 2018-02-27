#include "pizza.h"

#include <QPen>
#include <QPainter>
#include <QDebug>

Pizza::Pizza(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(200);

    angulo = 0;
}

Pizza::~Pizza()
{
    if (timer)
        timer->stop();

    delete timer;
}

void Pizza::paintEvent(QPaintEvent */*event*/)
{
    QPen pen;
    pen.setWidth(3);
    //    pen.setBrush(Qt::green);
    //    pen.setStyle(Qt::DashDotLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    QBrush brush;
    brush = Qt::NoBrush;

    QRect rect(10, 20, 200, 200);
//    QRect rect(10, 20, 80, 60);

    int startAngle = 20 * 16;
    int arcLength = (20 + angulo) * 16;

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();
    painter.translate(0, 0);
    painter.drawPie(rect, startAngle, arcLength);
    painter.restore();

    angulo++;

    qDebug() << "Paint";
}
