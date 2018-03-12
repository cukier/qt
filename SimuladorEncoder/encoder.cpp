#include "encoder.h"

#include <QDebug>

const char Encoder::enc_init[3] = {
    (char) 0x40, (char) 0x9a, (char) 0xda
};

Encoder::Encoder(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_port(serialPort),
    m_timer(new QTimer(this))
{
    connect(m_port, &QSerialPort::readyRead,
            this, &Encoder::handleReadyRead);
    connect(m_port, &QSerialPort::errorOccurred,
            this, &Encoder::handleError);
    connect(m_timer, &QTimer::timeout, this, &Encoder::response);
}

void Encoder::handleReadyRead()
{
    const QByteArray data = m_port->readAll();

    if (data.contains(enc_init))
    {
        qDebug() << "Ok";
        m_timer->start(100);
    }
}

void Encoder::handleError(QSerialPort::SerialPortError error)
{
    Q_UNUSED(error);
    qDebug() << m_port->errorString();
}

void Encoder::response()
{
    if (m_timer->isActive())
        m_timer->stop();

    QByteArray resp("Resposta encoder");

    const qint64 bytesWritten = m_port->write("Resposta encoder");

    if (bytesWritten == -1)
    {
        qDebug() << "Failed to write the data to port";
    }
    else if (bytesWritten != resp.size())
    {
        qDebug() << "Failed to write all the data to port";
    }
    else
    {
        m_port->flush();
        qDebug() << "Enviado";
    }
}
