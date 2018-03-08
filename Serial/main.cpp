#include <QCoreApplication>
//#include <QSerialPortInfo>
#include <QSerialPort>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    const auto infos = QSerialPortInfo::availablePorts();

//    for (const QSerialPortInfo &info : infos)
//    {
//        QString s = QObject::tr("Port: ") + info.portName() + "\n"
//                //                + QObject::tr("Location: ") + info.systemLocation() + "\n"
//                //                + QObject::tr("Description: ") + info.description() + "\n"
//                //                + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
//                //                + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
//                //                + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
//                //                + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
//                //                + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n"
//                ;

//        qDebug() << s;
//    }

    QSerialPort serialPort;

    //    QString str = "Hello\n";
    QByteArray writeData("Hello\n");

    serialPort.setPortName("COM3");
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    qDebug() << serialPort.open(QIODevice::WriteOnly);
    qDebug() << serialPort.write(writeData);
    serialPort.flush();
    serialPort.close();
    qDebug() << "Ok";

    return a.exec();
//    return 0;
}

//#include <QCoreApplication>
//#include <QSerialPort>


//int main(int argc, char *argv[])
//{
//    QCoreApplication coreApplication(argc, argv);

//    QSerialPort serialPort;
//    serialPort.setPortName("COM3");
//    serialPort.setBaudRate(QSerialPort::Baud9600);

//    if (!serialPort.open(QIODevice::WriteOnly))
//    {
//        return 1;
//    }

//    QByteArray writeData("Hello");

//    const qint64 bytesWritten = serialPort.write(writeData);

//    if (bytesWritten == -1) {
//        return 1;
//    } else if (bytesWritten != writeData.size()) {
//        return 1;
//    } else if (!serialPort.waitForBytesWritten(5000)) {
//        return 1;
//    }

//    return 0;
//}

