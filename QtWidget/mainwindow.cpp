#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDate>
#include <QUrl>
#include <QModbusTcpClient>

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
    isConn = false;

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

    QString addr = ui->textEdit->toPlainText();

    if (addr.isEmpty())
    {
        addr = "cuki-pc:502";
        ui->textEdit->setText(addr);
    }

    const QUrl url = QUrl::fromUserInput(addr);
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

    if (isConn)
    {
        modbusDevice->disconnectDevice();
        isConn = false;
        qDebug() << "Desconectando";
        ui->label->setText("Desconectado");
    }
    else
    {
        QString msg = "Conectando a " + url.host() + ":" + QString::number(url.port()) + '\n';
        qDebug() << "Conectando a" << url.host() << ":" << url.port();

        if (!modbusDevice->connectDevice())
        {
            qDebug() << "Falha na conexao";
            msg += "Falha na conexao";
        }
        else
        {
            qDebug() << "Conectado com sucesso";
            isConn = true;
            msg += "Conectado com sucesso";
        }

        ui->label->setText(msg);
    }
}

void MainWindow::on_readButton_clicked()
{
    if (!modbusDevice)
        return;

    QModbusDataUnit unit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 10);

    auto *reply = modbusDevice->sendReadRequest(unit, 1);

    QString str;

    if (!reply)
    {
        str = "Erro de resposta\n" + modbusDevice->errorString();
        qDebug() << str;
    }
    else
    {
        qDebug() << "Houve resposta";
        str = "Houve resposta\n";
    }

    ui->label->setText(str);
}
