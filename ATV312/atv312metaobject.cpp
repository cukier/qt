#include "atv312metaobject.h"

Atv312MetaObject::Atv312MetaObject(QObject *parent) : QObject(parent)
{

}

quint16 Atv312MetaObject::getControlWord() const
{
    return controlWord;
}

void Atv312MetaObject::setControlWord(const quint16 &value)
{
    controlWord = value;
}

quint16 Atv312MetaObject::getSpeedReferenceViaTheBus() const
{
    return speedReferenceViaTheBus;
}

void Atv312MetaObject::setSpeedReferenceViaTheBus(const quint16 &value)
{
    speedReferenceViaTheBus = value;
}

quint16 Atv312MetaObject::getStatusWord() const
{
    return statusWord;
}

void Atv312MetaObject::setStatusWord(const quint16 &value)
{
    statusWord = value;
}

quint16 Atv312MetaObject::getOutputSpeed() const
{
    return outputSpeed;
}

void Atv312MetaObject::setOutputSpeed(const quint16 &value)
{
    outputSpeed = value;
}

quint16 Atv312MetaObject::getSpeedReference() const
{
    return speedReference;
}

void Atv312MetaObject::setSpeedReference(const quint16 &value)
{
    speedReference = value;
}

quint16 Atv312MetaObject::getFaultCode() const
{
    return faultCode;
}

void Atv312MetaObject::setFaultCode(const quint16 &value)
{
    faultCode = value;
}

quint16 Atv312MetaObject::getAccelerationTimeDelta() const
{
    return accelerationTimeDelta;
}

void Atv312MetaObject::setAccelerationTimeDelta(const quint16 &value)
{
    accelerationTimeDelta = value;
}

quint16 Atv312MetaObject::getDecelerationTimeDelta() const
{
    return decelerationTimeDelta;
}

void Atv312MetaObject::setDecelerationTimeDelta(const quint16 &value)
{
    decelerationTimeDelta = value;
}

quint32 Atv312MetaObject::getMinSpeed() const
{
    return minSpeed;
}

void Atv312MetaObject::setMinSpeed(const quint32 &value)
{
    minSpeed = value;
}

quint32 Atv312MetaObject::getMaxSpeed() const
{
    return maxSpeed;
}

void Atv312MetaObject::setMaxSpeed(const quint32 &value)
{
    maxSpeed = value;
}

quint32 Atv312MetaObject::getAccelerationSpeedDelta() const
{
    return accelerationSpeedDelta;
}

void Atv312MetaObject::setAccelerationSpeedDelta(const quint32 &value)
{
    accelerationSpeedDelta = value;
}

quint32 Atv312MetaObject::getDecelerationSpeedDelta() const
{
    return decelerationSpeedDelta;
}

void Atv312MetaObject::setDecelerationSpeedDelta(const quint32 &value)
{
    decelerationSpeedDelta = value;
}
