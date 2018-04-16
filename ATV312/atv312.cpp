#include "atv312.h"

#include <QModbusRtuSerialMaster>
#include <QSerialPort>
#include <QDebug>
#include <QCoreApplication>

Atv312::Atv312(QObject *parent) : QObject(parent)
{
}

Atv312::~Atv312()
{
    fechar();
}

bool Atv312::conectar(QString porta)
{
    if (modbusDevice)
    {
        delete modbusDevice;
        modbusDevice = nullptr;
    }

    if (porta.isEmpty() || porta.isNull())
        porta = "COM2";

    modbusDevice = new QModbusRtuSerialMaster(this);

    if (!modbusDevice)
        return false;

    connect(modbusDevice, &QModbusClient::stateChanged,
            this, &Atv312::onStateChanged);
    connect(modbusDevice, &QModbusClient::errorOccurred,
            this, [this](){
        qDebug()  << modbusDevice->errorString();
    });

    modbusDevice->setConnectionParameter(
                QModbusDevice::SerialPortNameParameter,
                porta);
    modbusDevice->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter,
                QSerialPort::Baud19200);
    modbusDevice->setConnectionParameter(
                QModbusDevice::SerialDataBitsParameter,
                QSerialPort::Data8);
    modbusDevice->setConnectionParameter(
                QModbusDevice::SerialParityParameter,
                QSerialPort::EvenParity);
    modbusDevice->setConnectionParameter(
                QModbusDevice::SerialStopBitsParameter,
                QSerialPort::OneStop);
    modbusDevice->setTimeout(3000);
    modbusDevice->setNumberOfRetries(3);

    return modbusDevice->connectDevice();
}

void Atv312::fechar()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();

    delete modbusDevice;
    modbusDevice = nullptr;
}

void Atv312::ler(quint16 word)
{
    ler(word, 1);
}

void Atv312::ler(quint16 word, quint16 size)
{
    if (!(modbusDevice && conectado))
        return;

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters,
                         word, size);

    auto *reply = modbusDevice->
            sendReadRequest(unit, endereco);

    if (reply)
    {
        if (reply->isFinished())
            delete reply;
        else
            connect(reply, &QModbusReply::finished,
                    this, &Atv312::readReady);
    }
}

void Atv312::onStateChanged(int state)
{
    conectado = false;

    if (state == QModbusDevice::UnconnectedState)
    {
        qDebug() << "<Atv312> Nao conectado";
    }
    else if (state == QModbusDevice::ConnectingState)
    {
        qDebug() << "<Atv312> Conectando";
    }
    else if (state == QModbusDevice::ConnectedState)
    {
        conectado = true;
        qDebug() << "<Atv312> Conectado";
    }
    else if (state == QModbusDevice::ClosingState)
    {
        qDebug() << "<Atv312> Fechando conexao";
    }
}

void Atv312::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();

        qDebug() << "Lido " << unit.valueCount();
        QString str;

        for (const auto i : unit.values())
            str += QString::number(i, 10) + ' ';

        qDebug() << str;
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug() << QString(tr("Read response error: %1 (Mobus exception: 0x%2)").
                            arg(reply->errorString()).
                            arg(reply->rawResult().exceptionCode(), -1, 16));
    }
    else
    {
        qDebug() << QString(tr("Read response error: %1 (code: 0x%2)").
                            arg(reply->errorString()).
                            arg(reply->error(), -1, 16));
    }

    reply->deleteLater();
    qApp->exit();
}

quint16 Atv312::getEndereco() const
{
    return endereco;
}

void Atv312::setEndereco(const quint16 &value)
{
    endereco = value;
}
