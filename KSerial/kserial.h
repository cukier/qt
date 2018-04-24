#ifndef KSERIAL_H
#define KSERIAL_H

#include "kserial_global.h"

#include <QObject>
#include <QSerialPort>
#include <QVector>

class KSERIALSHARED_EXPORT KSerial : public QObject
{
    Q_OBJECT

public:
    KSerial(QObject *parent);

private slots:
    void onErrorOccured(QSerialPort::SerialPortError error);
    void onReadyRead();

private:
    QSerialPort *m_serialPort;

    bool isOpened = false;
    QVector<quint16> mem;
    static const quint16 wCRCTable[];

    quint16 ModRTU_CRC(quint8 *buf, quint16 len);
};

#endif // KSERIAL_H
