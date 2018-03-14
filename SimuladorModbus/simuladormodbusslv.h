#ifndef SIMULADORMODBUSSLV_H
#define SIMULADORMODBUSSLV_H

#include <QObject>
#include <QModbusServer>

class SimuladorModbusSLV : public QObject
{
    Q_OBJECT
public:
    explicit SimuladorModbusSLV(QObject *parent = nullptr);
    ~SimuladorModbusSLV();

signals:

private Q_SLOTS:
    void onStateChanged(int state);
    void setRegister(const QString &value);
    void handleDeviceError(QModbusDevice::Error newError);

private:
    QModbusServer *modbusDevice;

};

#endif // SIMULADORMODBUSSLV_H
