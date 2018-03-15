#include "mestremodbus.h"

#include <QModbusTcpClient>
#include <QUrl>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>

MestreModbus::MestreModbus(QUrl *addr, QObject *parent) :
    QObject(parent),
    modbusDevice(nullptr),
    timer(nullptr)
{
    mapa.clear();

    timer = new QTimer;
    timer->stop();

    modbusDevice = new QModbusTcpClient(this);
    modbusDevice->setConnectionParameter(
                QModbusDevice::NetworkPortParameter, addr->port());
    modbusDevice->setConnectionParameter(
                QModbusDevice::NetworkAddressParameter, addr->host());
    modbusDevice->setTimeout(5000);
    modbusDevice->setNumberOfRetries(3);

    connect(modbusDevice, &QModbusClient::stateChanged,
            this, &MestreModbus::onStateChanged);
    connect(modbusDevice, &QModbusClient::errorOccurred,
            this, &MestreModbus::onErrorOccurred);
    connect(timer, &QTimer::timeout,
            this, &MestreModbus::refresh);

    qDebug() << "Host: " + addr->host();

    if (!modbusDevice->connectDevice())
    {
        qDebug() << "Erro ao conectar " + addr->url();
    }
}

MestreModbus::~MestreModbus()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();

    if (timer)
        timer->stop();

    delete modbusDevice;
    delete timer;
}

void MestreModbus::onStateChanged(int state)
{
    if (timer->isActive())
        timer->stop();

    if (state == QModbusDevice::UnconnectedState)
    {
        qDebug() << "Desconectado";
        QCoreApplication::quit();
    }
    else if (state == QModbusDevice::ConnectedState)
    {
        timer->start(500);
        qDebug() << "Conectado";
    }
    else if (state == QModbusClient::ClosingState)
    {
        qDebug() << "Fechando conexao";
    }
    else if (state == QModbusClient::ConnectingState)
    {
        qDebug() << "Conectando";
    }
}

void MestreModbus::onErrorOccurred(QModbusDevice::Error error)
{
    //    Q_UNUSED(error);
    qDebug() << error << modbusDevice->errorString();
}

void MestreModbus::refresh()
{
    if (!modbusDevice)
        return;

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, offset, Step);
    QModbusReply *reply = modbusDevice->sendReadRequest(unit, 1);

    if (reply)
    {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished,
                    this, &MestreModbus::readReady);
        }
        else
        {
            delete reply;
        }
    }
    else
    {
        qDebug() << "Read Error: " + modbusDevice->errorString();
    }
}

void MestreModbus::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();

        for (quint16 i = 0; i < unit.valueCount(); ++i)
            mapa.append(unit.value(i));

        if (mapa.size() < TamanhoMapa)
        {
            offset += Step;
        }
        else
        {
            //            QProcess::execute("cls");
            QString str;

            for (quint16 i = 0; i < mapa.size(); ++i)
            {
                if (i && !(i % 10))
                {
                    qDebug() << str;
                    str.clear();
                }

                str.append("0x" + QString("%1 ").arg(QString::number(mapa.value(i), 16), 5, QChar('0')));
            }

            qDebug() << str;

            offset = 0;
            mapa.clear();
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug() << "Read response error: "
                 << reply->errorString()
                 << "(Mobus exception: 0x"
                 << reply->rawResult().exceptionCode()
                 << ")";
    }
    else
    {
        qDebug() << "Read response error: "
                 << reply->errorString()
                 << "(code: 0x"
                 << reply->rawResult().exceptionCode()
                 << ")";
    }

    reply->deleteLater();
}
