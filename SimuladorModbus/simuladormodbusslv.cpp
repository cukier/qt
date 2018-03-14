#include "simuladormodbusslv.h"

SimuladorModbusSLV::SimuladorModbusSLV(QObject *parent) :
    QObject(parent),
    modbusDevice(nullptr)
{
    if (modbusDevice) {
        modbusDevice->disconnect();
        delete modbusDevice;
        modbusDevice = nullptr;
    }
}

SimuladorModbusSLV::~SimuladorModbusSLV()
{

}

void SimuladorModbusSLV::onStateChanged(int state)
{

}

void SimuladorModbusSLV::setRegister(const QString &value)
{

}

void SimuladorModbusSLV::handleDeviceError(QModbusDevice::Error newError)
{

}
