#include "modbustcpmaster.h"

#include <QDebug>
#include <QModbusTcpClient>
#include <QTimer>

ModbusTcpMaster::ModbusTcpMaster(QObject *parent)
    : QObject(parent)
    , modbusDevice(nullptr)
    , timer(new QTimer(this))
    , mapa(QVector<quint16>(tamanhoMapa))
{
    connect(timer, &QTimer::timeout,
            this, &ModbusTcpMaster::on_timeout);
}

ModbusTcpMaster::~ModbusTcpMaster()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();
}

bool ModbusTcpMaster::conectar()
{
    if (modbusDevice)
    {
        modbusDevice->disconnect();
        modbusDevice->disconnectDevice();
        delete modbusDevice;
        modbusDevice = nullptr;
    }

    modbusDevice = new QModbusTcpClient(this);

    modbusDevice->setConnectionParameter(
                QModbusDevice::NetworkPortParameter,
                502);
    modbusDevice->setConnectionParameter(
                QModbusDevice::NetworkAddressParameter,
                "192.168.0.1");
    modbusDevice->setTimeout(3000);
    modbusDevice->setNumberOfRetries(3);

    connect(modbusDevice, &QModbusClient::errorOccurred,
            this, &ModbusTcpMaster::on_errorOccurred);
    connect(modbusDevice, &QModbusClient::stateChanged,
            this, &ModbusTcpMaster::on_StateChanged);

    return modbusDevice->connectDevice();
}

void ModbusTcpMaster::on_errorOccurred(QModbusDevice::Error error)
{
    qDebug() << "<ModbusTcpMaster> Erro ocorrido "
             << QString::number(error);
}

void ModbusTcpMaster::on_StateChanged(QModbusDevice::State state)
{
    if (timer && timer->isActive())
        timer->stop();

    if (state == QModbusDevice::UnconnectedState)
    {
        qDebug() << "<ModbusTcpMaster> Desconectado";
        index = 0;
    }
    else if (state == QModbusDevice::ConnectingState)
    {
        qDebug() << "<ModbusTcpMaster> Conectando";
    }
    else if (state == QModbusDevice::ConnectedState)
    {
        qDebug() << "<ModbusTcpMaster> Conectado";

        if (timer)
            timer->start(delayFrame);
    }
    else if (state == QModbusDevice::ClosingState)
    {
        qDebug() << "<ModbusTcpMaster> Desconectando";
    }
}

void ModbusTcpMaster::on_timeout()
{
    if (timer && timer->isActive())
        timer->stop();

    if (!modbusDevice)
        return;

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters,
                         index, 1);

    if (auto *reply = modbusDevice->sendReadRequest(unit,1))
    {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished,
                    this, &ModbusTcpMaster::on_finished);
        else
            delete reply;
    }
    else
    {
        qDebug() << "<ModbusTcpMaster> Erro ao emitir request "
                 << modbusDevice->errorString();
    }
}

void ModbusTcpMaster::on_finished()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();

        if (unit.valueCount() == 1)
        {
            if (mapa[index] != unit.value(0))
            {
                mapa[index] = unit.value(0);
                emit mudouValor(index, unit.values());
            }

            ++index;

            if (index >= tamanhoMapa)
            {
                index = 0;
            }
        }
        else if (reply->error() == QModbusDevice::ProtocolError)
        {
            qDebug() << tr("<ModbusTcpMaster> Read response error: %1 (Mobus exception: 0x%2)").
                        arg(reply->errorString()).
                        arg(reply->rawResult().exceptionCode(), -1, 16);
        }
        else
        {
            qDebug() << tr("<ModbusTcpMaster> Read response error: %1 (code: 0x%2)").
                        arg(reply->errorString()).
                        arg(reply->error(), -1, 16);
        }
    }

    reply->deleteLater();

    if (timer && !timer->isActive())
        timer->start(delayFrame);
}
