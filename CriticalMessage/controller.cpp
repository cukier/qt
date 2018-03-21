#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent),
    m_timer(new QTimer(this))
{
//    m_timer->singleShot(1000,
//                        this,
//                        [](){

//    });
}
