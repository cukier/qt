#include "pizza.h"

#include <QPen>
#include <QPainter>
#include <QDebug>

Pizza::Pizza(QWidget *parent) :
    QWidget(parent)
{

}

Pizza::~Pizza()
{
}

void Pizza::paintEvent(QPaintEvent */*event*/)
{
    QRect rect(10, 20, 80, 60);
    int startAngle = 20 * 16;
    int arcLength = 120 * 16;

    QPen pen;
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    QBrush brush(Qt::NoBrush);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.save();
    painter.drawPie(rect, startAngle, arcLength);
//    painter.restore();
    qDebug() << "update";
}
