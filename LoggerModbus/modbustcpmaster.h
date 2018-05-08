#ifndef MODBUSTCPMASTER_H
#define MODBUSTCPMASTER_H

#include <QObject>
#include <QModbusDevice>
#include <QVector>

class QModbusClient;
class QTimer;

class ModbusTcpMaster : public QObject
{
    Q_OBJECT
public:
    explicit ModbusTcpMaster(QObject *parent = nullptr);
    ~ModbusTcpMaster();

    bool conectar();

signals:
    void mudouValor(quint16 endreco, QVector<quint16> valores);

private slots:
    void on_errorOccurred(QModbusDevice::Error error);
    void on_StateChanged(QModbusDevice::State state);
    void on_timeout();
    void on_finished();

private:
    QModbusClient *modbusDevice;
    QTimer *timer;

    const static quint16 tamanhoMapa = 250;
    const static quint16 delayFrame = 5;
    quint16 index = 0;
    QVector<quint16> mapa;
    QVector<quint16> mudados;
};

#endif // MODBUSTCPMASTER_H
