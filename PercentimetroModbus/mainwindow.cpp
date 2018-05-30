#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"

#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow),
    m_settings(new Settings),
    modbusDevice(nullptr),
    m_comando(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_settings;
    delete ui;
}

void MainWindow::onStateChanged(int state)
{
    //    bool connected = (state != QModbusDevice::UnconnectedState);

    //    ui->btLer->setEnabled(connected);
    //    ui->btGravar->setEnabled(connected);

    if (state == QModbusDevice::UnconnectedState)
        ui->lblEstado->setText("onStateChanged Connect");
    else if (state == QModbusDevice::ConnectedState)
        ui->lblEstado->setText("onStateChanged Disconnect");
}

void MainWindow::onReplyFinished()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();

        if (unit.valueCount() == 3 && m_comando == Leitura) {
            ui->cbCom->setCurrentIndex(unit.value(0));
            ui->sbPeriodo->setValue(unit.value(1));
            ui->sbDutty->setValue(unit.value(2));
            ui->lblEstado->setText("Lido com sucesso");
            m_comando = NaoExitente;
        }
    } else {
        ui->lblEstado->setText(QString("Read response error: %1 (code: 0x%2)")
                               .arg(reply->errorString())
                               .arg(reply->error()));
    }

    reply->deleteLater();
}

void MainWindow::on_btConf_clicked()
{
    if (m_settings) {
        m_settings->show();
    }
}

void MainWindow::on_btAbrir_clicked()
{
    if (modbusDevice) {
        modbusDevice->disconnectDevice();
        modbusDevice->disconnect();
        delete modbusDevice;
        modbusDevice = nullptr;
    }

    modbusDevice = new QModbusRtuSerialMaster(this);

    connect(modbusDevice, &QModbusClient::errorOccurred,
            this, [this](QModbusDevice::Error) {
        ui->lblEstado->setText(modbusDevice->errorString());
        ui->btLer->setEnabled(false);
        ui->btGravar->setEnabled(false);
    });

    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                         m_settings->settings().portName);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                         m_settings->settings().baud);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                         m_settings->settings().parity);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                         m_settings->settings().data);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                         m_settings->settings().stop);
    modbusDevice->setTimeout(10000);
    modbusDevice->setNumberOfRetries(3);

    //    qDebug() << "Porta " << m_settings->settings().portName;
    //    qDebug() << "Baud " << m_settings->settings().baud;
    //    qDebug() << "Parity " << m_settings->settings().parity;
    //    qDebug() << "DataBits " << m_settings->settings().data;
    //    qDebug() << "StopBits " << m_settings->settings().stop;

    if (modbusDevice->connectDevice()) {
        ui->lblEstado->setText("Conectado\nLeitura nao realizada");
        ui->btLer->setEnabled(true);
        ui->btGravar->setEnabled(true);
    } else {
        ui->lblEstado->setText("Erro ao conectar");
    }
}

void MainWindow::on_btLer_clicked()
{
    if (!modbusDevice)
        return;

    ui->lblEstado->setText("Iniciando leitura");
    auto *reply = modbusDevice->sendReadRequest(
                QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 3), 1);

    if (reply) {
        if (reply->isFinished()) {
            delete reply;
        } else {
            m_comando = Leitura;
            connect(reply, &QModbusReply::finished,
                    this, &MainWindow::onReplyFinished);
        }
    } else {
        ui->lblEstado->setText("Read error " + modbusDevice->errorString());
    }
}

void MainWindow::on_btGravar_clicked()
{
    if (!modbusDevice)
        return;

    QVector<quint16> payload;

    payload.append(ui->cbCom->currentIndex());
    payload.append(ui->sbPeriodo->value());
    payload.append(ui->sbDutty->value());

//    qDebug() << "Comando " << ui->cbCom->currentIndex();
//    qDebug() << "Periodo " << ui->sbPeriodo->value();
//    qDebug() << "Duty " << ui->sbDutty->value();

    QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, 0, payload);

    auto *reply = modbusDevice->sendWriteRequest(unit, 1);

    if (reply) {
        if (reply->isFinished()) {
            delete reply;
        } else {
            m_comando = Gravacao;
            connect(reply, &QModbusReply::finished,
                    this, &MainWindow::onReplyFinished);
        }
    } else {
        ui->lblEstado->setText("Read error " + modbusDevice->errorString());
    }
}
