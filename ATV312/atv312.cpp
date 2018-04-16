#include "atv312.h"

#include <QModbusRtuSerialMaster>
#include <QSerialPort>
#include <QDebug>
#include <QCoreApplication>

Atv312::Atv312(QObject *parent) : QObject(parent)
{
    atv312 = new Atv312MetaObject(this);
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

void Atv312::ler()
{
    enderecoLeitura = ControlWord;
    ler(ControlWord);
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
        qDebug() << "<Atv312> Conexao fechada";
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
    disconnect(this, SLOT(readReady()));

    auto reply = qobject_cast<QModbusReply *>(sender());

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();

        if (unit.valueCount() == 1)
        {
            if (enderecoLeitura == ControlWord)
            {
                atv312->setControlWord(unit.value(0));
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == SpeedReferenceViaTheBus)
            {
                atv312->setSpeedReferenceViaTheBus(unit.value(0));
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == StatusWord)
            {
                atv312->setStatusWord(unit.value(0));
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == OutputSpeed)
            {
                atv312->setOutputSpeed(unit.value(0));
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == SpeedReference)
            {
                atv312->setSpeedReference(unit.value(0));
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == FaultCode)
            {
                atv312->setFaultCode(unit.value(0));
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == MinSpeed)
            {
                wordAux = 0;
                wordAux = unit.value(0);
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == MinSpeed1)
            {
                quint32 aux = (unit.value(0) << 16) & 0xFFFF0000;
                aux |= wordAux;
                atv312->setMinSpeed(aux);
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == MaxSpeed)
            {
                wordAux = 0;
                wordAux = unit.value(0);
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == MaxSpeed1)
            {
                quint32 aux = (unit.value(0) << 16) & 0xFFFF0000;
                aux |= wordAux;
                atv312->setMaxSpeed(aux);
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == AccelerationSpeedDelta)
            {
                wordAux = 0;
                wordAux = unit.value(0);
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == AccelerationSpeedDelta1)
            {
                quint32 aux = (unit.value(0) << 16) & 0xFFFF0000;
                aux |= wordAux;
                atv312->setAccelerationSpeedDelta(aux);
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == AccelerationTimeDelta)
            {
                atv312->setAccelerationTimeDelta(unit.value(0));
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == DecelerationSpeedDelta)
            {
                wordAux = 0;
                wordAux = unit.value(0);
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == DecelerationSpeedDelta1)
            {
                quint32 aux = (unit.value(0) << 16) & 0xFFFF0000;
                aux |= wordAux;
                atv312->setDecelerationSpeedDelta(aux);
                ler(++enderecoLeitura);
            }
            else if (enderecoLeitura == DecelerationTimeDelta)
            {
                atv312->setDecelerationTimeDelta(unit.value(0));
                enderecoLeitura = 0;
                qApp->exit();
            }
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug() << QString(tr("<Atv312> Read response error: %1 (Mobus exception: 0x%2)").
                            arg(reply->errorString()).
                            arg(reply->rawResult().exceptionCode(), -1, 16));
    }
    else
    {
        qDebug() << QString(tr("<Atv312> Read response error: %1 (code: 0x%2)").
                            arg(reply->errorString()).
                            arg(reply->error(), -1, 16));
    }

    reply->deleteLater();
    //    qApp->exit();
}

quint16 Atv312::getEndereco() const
{
    return endereco;
}

void Atv312::setEndereco(const quint16 &value)
{
    endereco = value;
}
