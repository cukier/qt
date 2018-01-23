#include "encoder.h"

#include <QCoreApplication>
#include <QSerialPort>
#include <QDebug>

Encoder::Encoder(int argc, char** argv)
    : QCoreApplication(argc, argv)
{
    serialPort = nullptr;
    connect(this, SIGNAL(aboutToQuit()), SLOT(endOfProgram()));
}

Encoder::~Encoder()
{
    delete serialPort;
}

void Encoder::simular()
{
    qDebug() << "Simulacao...";
    qDebug() << Encoder::conectar();
    qDebug() << Encoder::fechar();
    QCoreApplication::exec();
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

void Encoder::endOfProgram()
{

}
