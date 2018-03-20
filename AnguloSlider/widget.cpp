#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QApplication>
#include <QNetworkProxy>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    modbusDevice(new QModbusTcpClient(this))
{
    ui->setupUi(this);

    ui->horizontalSlider->setRange(0, 10000);

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::NoProxy);
    QNetworkProxy::setApplicationProxy(proxy);

    modbusDevice->setConnectionParameter(
                QModbusDevice::NetworkAddressParameter, "192.168.0.110");
    modbusDevice->setConnectionParameter(
                QModbusDevice::NetworkPortParameter, 502);
    modbusDevice->setTimeout(3000);
    modbusDevice->setNumberOfRetries(3);

    connect(modbusDevice, &QModbusClient::stateChanged,
            this, on_stateChanged);

    if (!modbusDevice->connectDevice())
    {
        qDebug() << "Connect falied!";
    }
}

Widget::~Widget()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();

    delete ui;
}

void Widget::on_stateChanged(int state)
{
    if (state == QModbusDevice::ConnectedState)
    {
        connect(ui->horizontalSlider, &QSlider::valueChanged,
                this, &Widget::on_valueChanged);
        qDebug() << "Connected";
    }
    else if (state == QModbusDevice::ConnectingState)
    {
        qDebug() << "Connecting to " + modbusDevice->
                    connectionParameter(
                        QModbusDevice::NetworkAddressParameter).toString();
    }
    else if (state == QModbusDevice::ClosingState)
    {
        qDebug() << "Closing connection";
    }
    else if (state == QModbusDevice::UnconnectedState)
    {
        qDebug() << "Disconnected";
        close();
    }
}

void Widget::on_valueChanged(int value)
{
    QVector<quint16> data;

    data.append(value);

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, 7, data);
    auto reply = modbusDevice->sendWriteRequest(unit, 1);

    if (reply)
    {
        if (reply->isFinished())
            delete reply;
        else
        {
            connect(reply, &QModbusReply::finished,
                    this, &Widget::on_readReady);
        }
    }
    else
    {
        qDebug() << "Read error!";
    }
}

void Widget::on_readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        qDebug() << "Write Ok";
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug() << tr("Read response error: %1 (Mobus exception: 0x%2)").
                    arg(reply->errorString()).
                    arg(reply->rawResult().exceptionCode(), -1, 16);
    }
    else
    {
        qDebug() << tr("Read response error: %1 (code: 0x%2)").
                    arg(reply->errorString()).
                    arg(reply->error(), -1, 16);
    }

    reply->deleteLater();
}
