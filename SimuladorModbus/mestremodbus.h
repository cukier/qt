#ifndef MESTREMODBUS_H
#define MESTREMODBUS_H

#include <QObject>
#include <QModbusDataUnit>
#include <QTimer>

class QModbusClient;

class MestreModbus : public QObject
{
    Q_OBJECT
public:
    explicit MestreModbus(QUrl *addr, QObject *parent = nullptr);
    ~MestreModbus();

private slots:
    void onStateChanged(int state);
//    void connectDev();
//    void readReady();

private:
    QModbusClient *modbusDevice;
};

#endif // MESTREMODBUS_H
