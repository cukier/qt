#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include <QObject>
#include <QModbusServer>
#include <QModbusResponse>

class ModbusServer : public QObject
{
    Q_OBJECT

public:
    explicit ModbusServer(QString porta, QObject *parent = nullptr);
    ~ModbusServer();

    bool conectar();
    QString porta() const;
    void setPorta(const QString &porta);
    uint16_t endereco() const;
    void setEndereco(const uint16_t &endereco);

signals:
    void novaEscrita(quint16 addr, QVector<quint16> dado);

private slots:
    void on_error(QModbusDevice::Error newError);
    void on_stateChanged(QModbusDevice::State newState);
    void on_dataWritten(QModbusDataUnit::RegisterType i_register,
                        int address, int size);

private:
    QModbusServer *m_device;
    QString m_porta;
    uint16_t m_endereco;
    bool conectado;
};

#endif // MODBUSSERVER_H
