#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include <QObject>
#include <QSerialPort>
#include <QVector>

class ModbusServer : public QObject
{
    Q_OBJECT

public:
    explicit ModbusServer(QString porta, QObject *parent = nullptr);
    ~ModbusServer();

private slots:
    void on_readReady();
    void on_bytesWritten(quint64 bytes);
    void on_errorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serialPort;
    static const quint16 wCRCTable[];
    QVector<quint16> mapaMemoria;

    quint16 make16(quint8 h_b, quint8 l_b);
    quint16 swapW(quint16 i_w);
    quint16 ModRTU_CRC(quint8 *buf, quint16 len);
    quint16 ModRTU_CRC(QByteArray buf);
};

#endif // MODBUSSERVER_H
