#include "modbusserver.h"

#include <QSerialPort>
#include <QModbusRtuSerialSlave>
#include <QDebug>
#include <QModbusDataUnitMap>

ModbusServer::ModbusServer(QString porta, QObject *parent) :
    QObject(parent),
    m_device(nullptr),
    m_porta(porta),
    m_endereco(1),
    conectado(false)
{

}

ModbusServer::~ModbusServer()
{
    if (m_device)
        m_device->disconnectDevice();
}

QString ModbusServer::porta() const
{
    return m_porta;
}

void ModbusServer::setPorta(const QString &porta)
{
    m_porta = porta;
}

uint16_t ModbusServer::endereco() const
{
    return m_endereco;
}

void ModbusServer::setEndereco(const uint16_t &endereco)
{
    m_endereco = endereco;
}

void ModbusServer::on_error(QModbusDevice::Error newError)
{
    qDebug() << "<ModbusServer> Erro ocorrido " << newError
             << ' ' << m_device->errorString();
}

void ModbusServer::on_stateChanged(QModbusDevice::State newState)
{
    conectado = false;

    if (newState == QModbusDevice::ConnectedState)
    {
        conectado = true;
        qDebug() << "<ModbusServer> conectado";
    }
    else if (newState == QModbusDevice::ConnectingState)
    {
        qDebug() << "<ModbusServer> conectando a porta "
                 << m_porta;
    }
    else if (newState == QModbusDevice::ClosingState)
    {
        qDebug() << "<ModbusServer> fechando";
    }
    else if (newState == QModbusDevice::UnconnectedState)
    {
        qDebug() << "<ModbusServer> desconectado";
    }
}

void ModbusServer::on_dataWritten(QModbusDataUnit::RegisterType i_register,
                                  int address, int size)
{
    QVector<quint16> dado;

    qDebug() << "<ModbusServer> Solicitacao de escrita de " << size
             << " word no endereco " << address;

    for (int i = 0; i < size; ++i)
    {
        quint16 value;

        switch (i_register)
        {
        case QModbusDataUnit::Coils:
            break;
        case QModbusDataUnit::HoldingRegisters:
            m_device->data(QModbusDataUnit::HoldingRegisters, address + i, &value);
            dado.append(value);
            qDebug() << "<ModbusServer> " << value;
            m_device->blockSignals(true);
            m_device->setData(QModbusDataUnit::HoldingRegisters, address + i, 0xFFFF);
            m_device->blockSignals(false);
            break;
        default:
            break;
        }
    }

    if (dado.size())
        emit novaEscrita(address, dado);
}

bool ModbusServer::conectar()
{
    if (conectado || m_device)
    {
        conectado = false;

        if (m_device)
        {
            m_device->disconnectDevice();
            delete m_device;
            m_device = nullptr;
        }
    }

    m_device = new QModbusRtuSerialSlave(this);

    if (!m_device)
    {
        qDebug() << "<ModbusServer> erro ao criar servidor modbus";
    }

    m_device->setConnectionParameter(
                QModbusDevice::SerialPortNameParameter, m_porta);
    m_device->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter,
                QSerialPort::Baud19200);
    m_device->setConnectionParameter(
                QModbusDevice::SerialDataBitsParameter,
                QSerialPort::Data8);
    m_device->setConnectionParameter(
                QModbusDevice::SerialParityParameter,
                QSerialPort::NoParity);
    m_device->setConnectionParameter(
                QModbusDevice::SerialStopBitsParameter,
                QSerialPort::OneStop);
    m_device->setServerAddress(m_endereco);

    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::DiscreteInputs,
    { QModbusDataUnit::DiscreteInputs, 0, 10 });
    reg.insert(QModbusDataUnit::InputRegisters,
    { QModbusDataUnit::InputRegisters, 0, 10 });
    reg.insert(QModbusDataUnit::HoldingRegisters,
    { QModbusDataUnit::HoldingRegisters, 0, 1024 });

    m_device->setMap(reg);


    connect(m_device, &QModbusServer::stateChanged,
            this, &ModbusServer::on_stateChanged);
    connect(m_device, &QModbusServer::errorOccurred,
            this, &ModbusServer::on_error);
    connect(m_device, &QModbusServer::dataWritten,
            this, &ModbusServer::on_dataWritten);

    return m_device->connectDevice();
}
