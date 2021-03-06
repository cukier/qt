#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QTextStream>
#include <QTimer>
#include <QSerialPort>

class SerialReader : public QObject
{
    Q_OBJECT
public:
    explicit SerialReader(QSerialPort *serialPort, QObject *parent = nullptr);

private slots:
    void handleReadyRead();
//    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serialPort = nullptr;
    QTimer *m_timer;
    QByteArray m_readData;
    QTextStream m_standardOutput;    
};

#endif // SERIALREADER_H
