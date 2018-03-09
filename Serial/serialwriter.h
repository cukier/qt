#ifndef SERIALWRITER_H
#define SERIALWRITER_H

#include <QObject>
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>

class SerialWriter : public QObject
{
    Q_OBJECT
public:
    explicit SerialWriter(QSerialPort *serialPort, QObject *parent = nullptr);
    void write(const QByteArray &writeData);

private slots:
    void handleBytesWritten(qint64 bytes);
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

signals:

private:
    QSerialPort *m_serialPort = nullptr;
    QByteArray m_writeData;
    QTextStream m_standardOutput;
    qint64 m_bytesWritten = 0;
    QTimer m_timer;
};

#endif // SERIALWRITER_H
