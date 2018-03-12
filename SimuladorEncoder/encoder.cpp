#include "encoder.h"

#include <QDebug>

const char Encoder::enc_init[3] = {
    (char) 0x40, (char) 0x9a, (char) 0xda
};

Encoder::Encoder(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_port(serialPort)
{
    connect(m_port, &QSerialPort::readyRead,
            this, &Encoder::handleReadyRead);
    connect(m_port, &QSerialPort::errorOccurred,
            this, &Encoder::handleError);
}

void Encoder::handleReadyRead()
{
    const QByteArray data = m_port->readAll();

    if (data.contains(enc_init))
    {
        qDebug() << "Ok";
    }
}

void Encoder::handleError(QSerialPort::SerialPortError error)
{
    Q_UNUSED(error);
    qDebug() << m_port->errorString();
}
