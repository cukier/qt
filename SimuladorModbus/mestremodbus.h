#ifndef MESTREMODBUS_H
#define MESTREMODBUS_H

#include <QObject>
#include <QModbusDataUnit>
#include <QTimer>
#include <QModbusDevice>

class QModbusClient;

class MestreModbus : public QObject
{
    Q_OBJECT

    enum
    {
        TamanhoMapa = 250,
        Step = 40
    };
public:
    explicit MestreModbus(QUrl *addr, QObject *parent = nullptr);
    ~MestreModbus();

signals:
    void mapaChanged(QVector<quint16> data);

private slots:
    void onStateChanged(int state);
    void onErrorOccurred(QModbusDevice::Error error);
    void refresh();
    void readReady();

private:
    QModbusClient *modbusDevice;
    QTimer *timer;

    quint16 offset = 0;
    QVector<quint16> mapa;
};

#endif // MESTREMODBUS_H
