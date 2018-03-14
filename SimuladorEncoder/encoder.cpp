#include "encoder.h"

#include <QDebug>

Encoder::Encoder(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_port(serialPort),
    m_timer(new QTimer(this))
{
    m_data.clear();

    connect(m_port, &QSerialPort::readyRead,
            this, &Encoder::handleReadyRead);
    connect(m_port, &QSerialPort::errorOccurred,
            this, &Encoder::handleError);
    connect(m_timer, &QTimer::timeout, this, &Encoder::response);
}

void Encoder::handleReadyRead()
{
    m_data = m_port->readAll();
    //    QString str;

    //    for(const auto i : data)
    //    {
    //        str += "0x" + QString::number(i & 0xFF, 16) + ' ';
    //    }

    //    qDebug() << str;

    if (m_data.contains(EncoderAddress))
    {
        //        qDebug() << "Ok";
        m_timer->start(10);
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

    QByteArray resp;

    resp.clear();
    resp.append(EncoderAddress);

    if (m_data.contains(ReadSerialNumber))
    {
        resp.append(ReadSerialNumber);
        resp.append("SERIAL___");
        resp.append("FIRMWARE__");
        resp.append("26.11.10");
        resp.append(crc(resp));
        qDebug() << "Read Serial Number";
    }
    else if(m_data.contains(ReadPosition))
    {
        resp.append(ReadPosition);
        resp.append((char) 0);
        resp.append((char) 0);
        resp.append(1);
        resp.append((char) 0);
        qDebug() << "Read Position";
    }
    else if(m_data.contains(ReadEncoderType))
    {
        resp.append(ReadEncoderType);
        resp.append("PART_NUMBER_____");
        resp.append("ENCTYPE");
        resp.append("DATACODE");
        resp.append((char) 0x00);
        resp.append((char) 0x01);
        resp.append((char) 0x00);
        qDebug() << "Read Encoder Type";
    }

    if(resp.size())
    {
        resp.append(crc(resp));

        const qint64 bytesWritten = m_port->write(resp);

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
            //        qDebug() << "Enviado";
        }
    }
    else
    {
        qDebug() << "Resp vazio";
    }

    m_data.clear();
}

quint8 Encoder::crc(QByteArray data) const
{
    quint8 ret = 0;

    for (const auto i : data)
        ret ^= i;

    return ret;
}
