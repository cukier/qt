#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDate>
#include <QUrl>
#include <QModbusTcpClient>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_commandLinkButton_clicked()
{
    qDebug() << "Criando mestre modbus\n";

    QString addr = ui->textEdit->toPlainText();

    qDebug() << "Texto: " << ui->textEdit->toPlainText();

    if (addr.isEmpty())
    {
        addr = "192.168.0.100:502";
    }

    modbusDevice = new QModbusTcpClient(this);

    if (!modbusDevice)
    {
        qDebug() << "Could not create Modbus master.\n";
        return ;
    }

    const QUrl url = QUrl::fromUserInput(addr);
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
    modbusDevice->setTimeout(1000);
    modbusDevice->setNumberOfRetries(3);

    if (!modbusDevice->connectDevice())
    {
        qDebug() << "Impossivel conectar " << url.host() << " : " << url.port() << '\n';
        return ;
    }
    else
    {
        qDebug() << "Conectado\n";
    }

    QModbusDataUnit unit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 10);
    QModbusReply *r = modbusDevice->sendReadRequest(unit, 1);
    modbusDevice->disconnectDevice();

    if (!r)
        qDebug() << "Erro ao ler o dispositivo\n";
    else
        qDebug() << "Sucesso\n";

}
