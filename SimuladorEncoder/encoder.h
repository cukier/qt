#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>

class Encoder : public QObject
{
    Q_OBJECT
public:
    explicit Encoder(QSerialPort *serialPort, QObject *parent = nullptr);

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
    void response();

private:
    QSerialPort *m_port = nullptr;
    QTimer *m_timer;
    QByteArray m_data;

    quint8 crc(QByteArray data) const;

    enum Sick
    {
        EncoderAddress = 0x40
    };

    enum SickCommands
    {
        Reset = 0x53,
        ReadSerialNumber = 0x56,
        ReadPosition = 0x92,
        SetNumberOfLines = 0x96,
        SetElectricalInterface,
        SetZeroPulseWidthElectrical,
        ZeroSet,
        ReadEncoderType,
        SetZeroPulseWidthMechanical,
        ReadZeroPulseWidthElctricalMecahnical,
        ReadElectricalInterface
    };
};

#endif // ENCODER_H
