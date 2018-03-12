#include <QCoreApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>

#include <encoder.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (!QSerialPortInfo::availablePorts().size())
    {
        QTextStream tcout(stdout);

        tcout << "Nenhuma porta disponivel\n";

        return -1;
    }

    QSerialPort sl1;

    sl1.setPortName("COM1");
    sl1.setBaudRate(QSerialPort::Baud115200);
    sl1.setDataBits(QSerialPort::Data8);
    sl1.setParity(QSerialPort::EvenParity);
    sl1.setStopBits(QSerialPort::OneStop);

    if (!sl1.open(QSerialPort::ReadWrite))
        return -1;

//    SerialReader sr(&sl1);
//    SerialWriter sw(&sl1);
    Encoder en(&sl1);

    return app.exec();
}
