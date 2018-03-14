#include "mestremodbus.h"

#include <QModbusTcpClient>
#include <QUrl>
#include <QDebug>
#include <QCoreApplication>

MestreModbus::MestreModbus(QUrl *addr, QObject *parent) :
    QObject(parent),
    modbusDevice(nullptr)
{
    modbusDevice = new QModbusTcpClient(this);
    modbusDevice->setConnectionParameter(
                QModbusDevice::NetworkPortParameter, addr->port());
    modbusDevice->setConnectionParameter(
                QModbusDevice::NetworkAddressParameter, addr->host());
    modbusDevice->setTimeout(5000);
    modbusDevice->setNumberOfRetries(3);

    connect(modbusDevice, &QModbusClient::stateChanged,
            this, &MestreModbus::onStateChanged);

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

    delete modbusDevice;
}

void MestreModbus::onStateChanged(int state)
{
    if (state == QModbusDevice::UnconnectedState)
    {
        qDebug() << "Desconectado";
    }
    else if (state == QModbusDevice::ConnectedState)
    {
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

    QCoreApplication::quit();
}
