#ifndef ATV312METAOBJECT_H
#define ATV312METAOBJECT_H

#include <QObject>

class Atv312MetaObject : public QObject
{
    Q_OBJECT
public:
    explicit Atv312MetaObject(QObject *parent = nullptr);

    quint16 getControlWord() const;
    void setControlWord(const quint16 &value);
    quint16 getSpeedReferenceViaTheBus() const;
    void setSpeedReferenceViaTheBus(const quint16 &value);
    quint16 getStatusWord() const;
    void setStatusWord(const quint16 &value);
    quint16 getOutputSpeed() const;
    void setOutputSpeed(const quint16 &value);
    quint16 getSpeedReference() const;
    void setSpeedReference(const quint16 &value);
    quint16 getFaultCode() const;
    void setFaultCode(const quint16 &value);
    quint16 getAccelerationTimeDelta() const;
    void setAccelerationTimeDelta(const quint16 &value);
    quint16 getDecelerationTimeDelta() const;
    void setDecelerationTimeDelta(const quint16 &value);
    quint32 getMinSpeed() const;
    void setMinSpeed(const quint32 &value);
    quint32 getMaxSpeed() const;
    void setMaxSpeed(const quint32 &value);
    quint32 getAccelerationSpeedDelta() const;
    void setAccelerationSpeedDelta(const quint32 &value);
    quint32 getDecelerationSpeedDelta() const;
    void setDecelerationSpeedDelta(const quint32 &value);

private:
    quint16 controlWord = 0;
    quint16 speedReferenceViaTheBus = 0;
    quint16 statusWord = 0;
    quint16 outputSpeed = 0;
    quint16 speedReference = 0;
    quint16 faultCode = 0;
    quint16 accelerationTimeDelta = 0;
    quint16 decelerationTimeDelta = 0;
    quint32 minSpeed = 0;
    quint32 maxSpeed = 0;
    quint32 accelerationSpeedDelta = 0;
    quint32 decelerationSpeedDelta = 0;
};

#endif // ATV312METAOBJECT_H
