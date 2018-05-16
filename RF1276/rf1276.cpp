#include "rf1276.h"

#include "settings.h"

#include <QSerialPort>
#include <QDebug>
#include <QTimer>

RF1276::RF1276(QSerialPort *serialPort, QObject *parent)
    : QObject(parent),
      m_serialPort(serialPort),
      m_timer(new QTimer(this)),
      m_settings(nullptr)
{
    connect(serialPort, &QSerialPort::readyRead,
            this, &RF1276::handleReadyRead);
    connect(m_timer, &QTimer::timeout,
            this, &RF1276::handleTimeOut);
}

void RF1276::searchRadio(QString porta)
{
    if (!m_serialPort) {
        m_serialPort = new QSerialPort(this);
    }

    m_serialPort->close();
    m_serialPort->setPortName(porta);
    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);

    if (m_serialPort->open(QIODevice::ReadWrite)) {
        currentTransaction = Sniffing;
        m_timer->start(500);
        m_serialPort->write(discover);
    } else {
        qDebug() << "Problemas para abrir a porta";
    }
}

char RF1276::crc(const QByteArray &data)
{
    quint16 acumulo = 0;

    for(const auto i : data) {
        acumulo += i;
    }

    return char(acumulo % 256);
}

void RF1276::MakeRadioRequest(const int commnadYY, QByteArray &data)
{
    char m_size = char(data.size());

    data.push_front(m_size);
    data.push_front(commnadYY);
    data.push_front(SendingXXCommand);
    data.push_front(0xAF);
    data.push_front(char(0x00));
    data.push_front(char(0x00));
    data.push_front(0xAF);
    data.push_front(0xAF);
    data.push_back(crc(data));
    data.push_back(0x0D);
    data.push_back(0x0A);
}

QByteArray RF1276::MakeRadioReadCommand(const int size)
{
    QByteArray arr(size, 0);

    MakeRadioRequest(ReadYYCommand, arr);

    return arr;
}

void RF1276::MakeRadioReadTransaction()
{
    QByteArray request = MakeRadioReadCommand(DataSize);

    currentTransaction = ReadTransaction;
    m_serialPort->write(request);
}

void RF1276::handleReadyRead()
{
    QByteArray response = m_serialPort->readAll();

    qDebug() << "RF1276 " << response.size();

    if (currentTransaction == Sniffing) {
        if (m_timer->isActive())
            m_timer->stop();

        qDebug() << "Radio encotrado "
                 << "Porta " << m_serialPort->portName()
                 << " baud " << m_serialPort->baudRate()
                 << " data " << m_serialPort->dataBits()
                 << " parity " << m_serialPort->parity()
                 << " stop " << m_serialPort->stopBits();
    }

    for (const auto i : response)
        qDebug() << QString::number(i, 16) << ' ';

    currentTransaction = NoTransaction;
}

void RF1276::handleTimeOut()
{
    qDebug() << "Timeout";

    if (currentTransaction == Sniffing) {
        bool repeate = true;

        m_timer->stop();
        m_serialPort->close();

        if (m_serialPort->parity() == QSerialPort::NoParity) {
            m_serialPort->setParity(QSerialPort::EvenParity);
        } else if (m_serialPort->parity() == QSerialPort::EvenParity) {
            m_serialPort->setParity(QSerialPort::OddParity);
        } else {
            m_serialPort->setParity(QSerialPort::NoParity);

            if (m_serialPort->baudRate() == QSerialPort::Baud1200)
                m_serialPort->setBaudRate(QSerialPort::Baud2400);
            else if (m_serialPort->baudRate() == QSerialPort::Baud2400)
                m_serialPort->setBaudRate(QSerialPort::Baud4800);
            else if (m_serialPort->baudRate() == QSerialPort::Baud4800)
                m_serialPort->setBaudRate(QSerialPort::Baud9600);
            else if (m_serialPort->baudRate() == QSerialPort::Baud9600)
                m_serialPort->setBaudRate(QSerialPort::Baud19200);
            else if (m_serialPort->baudRate() == QSerialPort::Baud19200)
                m_serialPort->setBaudRate(QSerialPort::Baud38400);
            else if (m_serialPort->baudRate() == QSerialPort::Baud38400)
                m_serialPort->setBaudRate(QSerialPort::Baud57600);
            else if (m_serialPort->baudRate() == QSerialPort::Baud57600)
                m_serialPort->setBaudRate(QSerialPort::Baud115200);
            else if (m_serialPort->baudRate() == QSerialPort::Baud115200)
                repeate = false;
        }

        if (repeate) {
            if (m_serialPort->open(QIODevice::ReadWrite)){
                qDebug() << "Testando " << m_serialPort->portName()
                         << " baud " << m_serialPort->baudRate()
                         << " data " << m_serialPort->dataBits()
                         << " parity " << m_serialPort->parity()
                         << " stop " << m_serialPort->stopBits();

                m_timer->start(500);
                m_serialPort->write(discover);
            }
        }
    }
}
