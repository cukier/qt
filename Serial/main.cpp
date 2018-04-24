#include "serialreader.h"

#include <QCoreApplication>
#include <QFile>
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication coreApplication(argc, argv);

    QSerialPort serialPort;

    serialPort.setPortName("COM5");
    serialPort.setBaudRate(QSerialPort::Baud9600);

    if (!serialPort.open(QIODevice::ReadOnly))
        return 1;

    SerialReader serialPortReader(&serialPort);

    return coreApplication.exec();
}
