#include "serialreader.h"

#include <QCoreApplication>
#include <QDebug>

SerialReader::SerialReader(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_timer(nullptr),
    m_standardOutput(stdout)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialReader::handleReadyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialReader::handleError);

    qDebug() << "<SerialReader> Porta aberta " << m_serialPort->portName();

    //    m_timer = new QTimer(this);
    //    connect(&m_timer, &QTimer::timeout, this, &SerialReader::handleTimeout);

    //    m_timer.start(5000);
}

void SerialReader::handleReadyRead()
{
    QByteArray buff = m_serialPort->readAll();
    m_readData.append(buff);

    qDebug() << "<SerialReader> Recebido " << buff;
    //    if (!m_timer.isActive())
    //        m_timer.start(5000);
}

//void SerialReader::handleTimeout()
//{
//    if (m_readData.isEmpty()) {
//        m_standardOutput << QObject::tr("No data was currently available "
//                                        "for reading from port %1")
//                            .arg(m_serialPort->portName())
//                         << endl;
//    } else {
//        m_standardOutput << QObject::tr("Data successfully received from port %1")
//                            .arg(m_serialPort->portName())
//                         << endl;
//        m_standardOutput << m_readData << endl;
//    }

//    QCoreApplication::quit();
//}

void SerialReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        m_standardOutput << QObject::tr("An I/O error occurred while reading "
                                        "the data from port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                         << endl;
        QCoreApplication::exit(1);
    }
}
