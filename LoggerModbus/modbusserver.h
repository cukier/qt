#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include <QObject>
#include <QSerialPort>
#include <QVector>

class ModbusServer : public QObject
{
    Q_OBJECT

public:
    enum ModbusCommands
    {
        NoCommand,
        ReadCoils,
        ReadDiscreteInputs,
        ReadHoldingRegisters,
        ReadInputRegisters,
        WriteSingleCoil,
        WriteSingelRegister,
        ReadExecptionStatus,
        Diagnostics,
        GetCommEventCounter = 0x0B,
        GetCommEventLog,
        WriteMultipleCoils = 0x0F,
        WriteMultipleRegisters,
        ReportSlaveId
    };

    enum ModbusErrors
    {
        NoError,
        FunctionNotSupported,
        IndexOutOfBoundsError,
        QuantityOfRegistersError,
        ReadError
    };

    explicit ModbusServer(QString porta, QObject *parent = nullptr);
    ~ModbusServer();

    void setAddr(const quint8 &addr);

private slots:
    void on_readReady();
    void on_bytesWritten(quint64 bytes);
    void on_errorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serialPort;
    static const quint16 wCRCTable[];
    QVector<quint16> mapaMemoria;
    quint8 m_addr = 1;
    static const quint16 mem_size = 1024;

    quint16 make16(quint8 h_b, quint8 l_b);
    quint16 swapW(quint16 i_w);
    quint16 ModRTU_CRC(quint8 *buf, quint16 len);
    quint16 ModRTU_CRC(QByteArray buf);
    void modbusWrite(QByteArray buf);
    void returnModbusError(quint8 eCommand, quint8 eCode);
};

#endif // MODBUSSERVER_H
