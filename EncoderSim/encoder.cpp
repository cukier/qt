#include "encoder.h"

#include <QCoreApplication>
#include <QSerialPort>
#include <QDebug>

Encoder::Encoder(QObject *parent)
    : QObject(parent)
{
    serialPort = nullptr;
    app = QCoreApplication::instance();
}

Encoder::~Encoder()
{
    delete serialPort;
}

void Encoder::quit()
{
    emit finished();
}

void Encoder::simular()
{
    qDebug() << "Simulacao...";
    qDebug() << Encoder::conectar();
    qDebug() << Encoder::fechar();
    quit();
}

bool Encoder::conectar()
{
    bool ret = false;

    if (!serialPort)
    {
        serialPort = new QSerialPort();
        serialPort->setPortName("COM5");
        serialPort->setBaudRate(19200);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->open(QIODevice::ReadOnly);
        ret = serialPort->isOpen();
    }

    return ret;
}

bool Encoder::fechar()
{
    serialPort->close();

    return serialPort->isOpen();
}
