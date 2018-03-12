#include "serialwriter.h"

#include <QCoreApplication>

SerialWriter::SerialWriter(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    m_timer.setSingleShot(true);

    connect(m_serialPort, &QSerialPort::bytesWritten,
            this, &SerialWriter::handleBytesWritten);
    connect(m_serialPort, &QSerialPort::errorOccurred,
            this, &SerialWriter::handleError);
    connect(&m_timer, &QTimer::timeout, this, &SerialWriter::handleTimeout);
}

void SerialWriter::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_writeData.size()) {
        m_bytesWritten = 0;
        m_standardOutput << QObject::tr("Data successfully sent to port %1")
                            .arg(m_serialPort->portName()) << endl;
        QCoreApplication::quit();
    }
}

void SerialWriter::handleTimeout()
{
    m_standardOutput << QObject::tr("Operation timed out for port %1, error: %2")
                        .arg(m_serialPort->portName())
                        .arg(m_serialPort->errorString())
                     << endl;
    QCoreApplication::exit(1);
}

void SerialWriter::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::WriteError) {
        m_standardOutput << QObject::tr("An I/O error occurred while writing"
                                        " the data to port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                         << endl;
        QCoreApplication::exit(1);
    }
}

void SerialWriter::write(const QByteArray &writeData)
{
    m_writeData = writeData;

    const qint64 bytesWritten = m_serialPort->write(writeData);

    if (bytesWritten == -1) {
        m_standardOutput << QObject::tr("Failed to write the data to port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                         << endl;
        QCoreApplication::exit(1);
    } else if (bytesWritten != m_writeData.size()) {
        m_standardOutput << QObject::tr("Failed to write all the data to port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                         << endl;
        QCoreApplication::exit(1);
    }

    m_timer.start(5000);
}
