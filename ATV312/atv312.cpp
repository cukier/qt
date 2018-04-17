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

void Atv312::ler()
{
    enderecoLeitura = ControlWord;
    ler(ControlWord);
}

void Atv312::acinonarSentidoHorario()
{
    if (atv312)
    {
        delete atv312;
        atv312 = nullptr;
    }

    if (!atv312)
        atv312 = new Atv312MetaObject(this);

    comando = LigarSentidoHorario;
    connect(this, &Atv312::leituraTerminada,
            this, &Atv312::onLeituraCompleta);
    ler();
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

void Atv312::setValue(quint16 value)
{
    if (enderecoLeitura == ControlWord)
    {
        atv312->setControlWord(value);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == SpeedReferenceViaTheBus)
    {
        atv312->setSpeedReferenceViaTheBus(value);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == StatusWord)
    {
        atv312->setStatusWord(value);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == OutputSpeed)
    {
        atv312->setOutputSpeed(value);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == SpeedReference)
    {
        atv312->setSpeedReference(value);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == FaultCode)
    {
        atv312->setFaultCode(value);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == MinSpeed)
    {
        wordAux = 0;
        wordAux = value;
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == MinSpeed1)
    {
        quint32 aux = (value << 16) & 0xFFFF0000;
        aux |= wordAux;
        atv312->setMinSpeed(aux);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == MaxSpeed)
    {
        wordAux = 0;
        wordAux = value;
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == MaxSpeed1)
    {
        quint32 aux = (value << 16) & 0xFFFF0000;
        aux |= wordAux;
        atv312->setMaxSpeed(aux);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == AccelerationSpeedDelta)
    {
        wordAux = 0;
        wordAux = value;
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == AccelerationSpeedDelta1)
    {
        quint32 aux = (value << 16) & 0xFFFF0000;
        aux |= wordAux;
        atv312->setAccelerationSpeedDelta(aux);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == AccelerationTimeDelta)
    {
        atv312->setAccelerationTimeDelta(value);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == DecelerationSpeedDelta)
    {
        wordAux = 0;
        wordAux = value;
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == DecelerationSpeedDelta1)
    {
        quint32 aux = (value << 16) & 0xFFFF0000;
        aux |= wordAux;
        atv312->setDecelerationSpeedDelta(aux);
        ler(++enderecoLeitura);
    }
    else if (enderecoLeitura == DecelerationTimeDelta)
    {
        atv312->setDecelerationTimeDelta(value);
        enderecoLeitura = 0;
        emit leituraTerminada();
    }
}

quint16 Atv312::resetBit(quint16 word, quint16 bit)
{
    if (bit > 15)
        return 0;

    quint16 mask = 1 << bit;

    return word &= ~mask;
}

bool Atv312::getBit(quint16 word, quint16 bit)
{
    quint16 mask = 1 << bit;

    return bool(word & mask);
}

quint16 Atv312::setBit(quint16 word, quint16 bit)
{
    if (bit > 15)
        return 0;

    quint16 mask = 1 << bit;

    return word |= mask;
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
            setValue(unit.value(0));
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug() << QString(tr("<Atv312> Read response error: %1 (Mobus exception: 0x%2)").
                            arg(reply->errorString()).
                            arg(reply->rawResult().exceptionCode(), -1, 16));
        qApp->exit();
    }
    else
    {
        qDebug() << QString(tr("<Atv312> Read response error: %1 (code: 0x%2)").
                            arg(reply->errorString()).
                            arg(reply->error(), -1, 16));
        qApp->exit();
    }

    reply->deleteLater();
}

void Atv312::onLeituraCompleta()
{
    disconnect(this, SLOT(onLeituraCompleta()));

    if (comando == LigarSentidoHorario)
    {
        quint16 aux = setBit(atv312->getControlWord(), SwitchOn);
        aux = setBit(aux, DirectionCommand);
        qDebug() << tr("<Atv312> Enviando requisicao de acinamento no sentido horario 0x%1 0x%2")
                    .arg(atv312->getControlWord(), 4, 16, QLatin1Char('0'))
                    .arg(aux, 4, 16, QLatin1Char('0'));
        escrever(ControlWord, aux);
    }
}

void Atv312::escrever(quint16 address, quint16 word)
{
    if (!(modbusDevice && conectado))
        return;

    QVector<quint16> payload;

    payload.append(word);

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters,
                         address, payload);

    auto *reply = modbusDevice->sendWriteRequest(unit, endereco);

    if (reply)
    {
        if (reply->isFinished())
            reply->deleteLater();
        else
        {
            connect(reply, &QModbusReply::finished,
                    this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    qDebug() << QString(tr("<Atv312> Write response error: %1 (Mobus exception: 0x%2)")
                                        .arg(reply->errorString())
                                        .arg(reply->rawResult().exceptionCode(), -1, 16));
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    qDebug() << QString(tr("<Atv312> Write response error: %1 (code: 0x%2)")
                                        .arg(reply->errorString())
                                        .arg(reply->error(), -1, 16));
                }
                else
                {
                    qDebug() << "<Atv312> Enviado com sucesso";
                    qApp->exit();
                }
            });
        }
    }
    else
    {
        qDebug() << QString(tr("<Atv312> Write error: ") + modbusDevice->errorString());
    }
}

quint16 Atv312::getEndereco() const
{
    return endereco;
}

void Atv312::setEndereco(const quint16 &value)
{
    endereco = value;
}
