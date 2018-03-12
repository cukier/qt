#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include <QSerialPort>
#include <serialreader.h>
#include <serialwriter.h>

class Encoder : public QObject
{
    Q_OBJECT
public:
    explicit Encoder(QSerialPort *serialPort, QObject *parent = nullptr);

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_port = nullptr;
    static const char enc_init[3];
};

#endif // ENCODER_H
