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

void MainWindow::on_commandLinkButton_clicked()
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
        qDebug() << "Conectando a" << url.host() << ":" << url.port();

        if (!modbusDevice->connectDevice())
        {
            qDebug() << "Falha na conexao";
            ui->label->setText("Falha na conexao");
        }
        else
        {
            qDebug() << "Conectado com sucesso";
            isConn = true;
            ui->label->setText("Conectado com sucesso");
        }
    }
}

void MainWindow::on_readButton_clicked()
{
    if (!modbusDevice)
        return;

    QModbusDataUnit unit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 10);

    auto *reply = modbusDevice->sendReadRequest(unit, 1);

    if (!reply)
    {
        QString str = "Erro de resposta\n" + modbusDevice->errorString();
        qDebug() << str;
        ui->label->setText(str);
    }
    else
    {
        qDebug() << "Houve resposta";
        ui->label->setText("Houve resposta");
    }
}
