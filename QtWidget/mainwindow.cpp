#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDate>
#include <QUrl>
#include <QModbusTcpClient>

#define _BV(x)      (1<<x)
#define SET(x,y)    (x |= _BV(y))
#define RESET(x,y)  (x &= ~(_BV(y)))
#define IS(x,y)     ((x) & (_BV(y)))

#define INICIO_I    9
#define INICIO_AUX  6
#define PARAR_I     14

void MainWindow::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();

        ui->label->text().clear();

        for (uint i = 0; i < unit.valueCount(); i++)
        {
            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress() + i)
                    .arg(QString::number(unit.value(i),
                                         unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16)) + '\n';
            ui->label->setText(ui->label->text() + entry);
            qDebug() << entry;
        }

        w0 = unit.value(0);
    }

    reply->deleteLater();
}

void MainWindow::onStateChanged(int state)
{
    if (state == QModbusDevice::UnconnectedState)
        ui->label->setText("Desconectado");
    else if (state == QModbusDevice::ConnectedState)
        ui->label->setText("Conectado");

    qDebug() << "Estado " << state;
}

void MainWindow::inicio() const
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (!reply)
        return;

    if (reply->error() == QModbusDevice::ProtocolError)
    {
        ui->label->setText("Erro na escrita" +
                           reply->errorString() +
                           reply->rawResult().exceptionCode());
    }
    else if (reply->error() != QModbusDevice::NoError)
    {
        ui->label->setText("Erro na escrita" +
                           reply->errorString() +
                           reply->error());
    }

    reply->deleteLater();
}

void MainWindow::readModbus(unsigned short addr_slv,
                            unsigned short start_addr,
                            unsigned short qtd)
{
    if (!modbusDevice)
        return;

    auto *reply = modbusDevice->sendReadRequest(
                QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                start_addr, qtd), addr_slv);

    QString str;

    if (!reply)
    {
        str = "Erro de resposta\n" + modbusDevice->errorString();
        qDebug() << str;
    }
    else
    {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &MainWindow::readReady);
        else
            delete reply;
    }

    ui->label->setText(str);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    modbusDevice(nullptr)
{
    ui->setupUi(this);

    if (modbusDevice) {
        modbusDevice->disconnectDevice();
        delete modbusDevice;
        modbusDevice = nullptr;
    }

    modbusDevice = new QModbusTcpClient(this);
    modbusDevice->setTimeout(1000);
    modbusDevice->setNumberOfRetries(3);

    ui->label->setText("Desconectado");
}

MainWindow::~MainWindow()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();

    delete modbusDevice;
    delete ui;
}

void MainWindow::on_connButton_clicked()
{
    if (!modbusDevice)
        return;

    if (modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        modbusDevice->disconnectDevice();
        qDebug() << "Desconectando";
        ui->label->setText("Desconectado");
    }
    else
    {
        QString addr = ui->textEdit->toPlainText();

        if (addr.isEmpty())
        {
            addr = "127.0.0.1:502";
            ui->textEdit->setText(addr);
        }

        const QUrl url = QUrl::fromUserInput(addr);

        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

        qDebug() << "Conectando a" << url.host() << ":" << url.port();
        ui->label->setText("Conectando a " + url.host() + ":" + QString::number(url.port()));
        modbusDevice->connectDevice();
        connect(modbusDevice, &QModbusClient::stateChanged, this, &MainWindow::onStateChanged);
    }
}

void MainWindow::on_readButton_clicked()
{
    MainWindow::readModbus(1, 0, 10);
}

void MainWindow::on_irrigaButton_clicked()
{
    if (!modbusDevice)
        return;

    MainWindow::readModbus(1, 0, 10);

    QModbusDataUnit writeUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 1);

    if(IS(w0, INICIO_I))
    {
        SET(w0, PARAR_I);
    }
    else
    {
        SET(w0, INICIO_I);
        SET(w0, INICIO_AUX);
    }

    writeUnit.setValue(0, w0);

    auto *reply = modbusDevice->sendWriteRequest(writeUnit, 1);

    if (reply)
    {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, this, &MainWindow::inicio);
        }
        else
        {
            reply->deleteLater();
        }
    }
    else
    {
        ui->label->setText("Erro de escrita" + modbusDevice->errorString());
    }
}
