#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"
#include "rf1276.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_settings(new Settings()),
    m_serialPort(nullptr),
    m_radio(nullptr)
{
    ui->setupUi(this);
    ui->btDesc->setEnabled(false);
    ui->btSniff->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete m_settings;
    delete ui;
}

void MainWindow::on_btCon_clicked()
{
    createSerial();
    isConnected = m_serialPort->open(QIODevice::ReadWrite);

    if (isConnected) {
        ui->label->setText(tr("Conectado %1@%2%3%4%5")
                           .arg(m_settings->settings().portName)
                           .arg(m_settings->settings().baud)
                           .arg(m_settings->settings().data)
                           .arg(m_settings->settings().parity)
                           .arg(m_settings->settings().stop));
        ui->btCon->setEnabled(false);
        ui->btDesc->setEnabled(true);
        ui->btSniff->setEnabled(true);
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        ui->textBrowser->append(QObject::tr("An I/O error occurred while writing"
                                            " the data to port %1, error: %2")
                                .arg(m_serialPort->portName())
                                .arg(m_serialPort->errorString()));
    }
}

void MainWindow::handleReadyRead()
{
    QByteArray buff = m_serialPort->readAll();

    if (ui->checkBox->isChecked())
        ui->textBrowser->append(buff.toHex());
    else
        ui->textBrowser->append(buff);
}

void MainWindow::createSerial()
{
    if (m_serialPort) {
        delete m_serialPort;
        m_serialPort = nullptr;
    }

    m_serialPort = new QSerialPort(this);

    connect(m_serialPort, &QSerialPort::errorOccurred,
            this, &MainWindow::handleError);
    connect(m_serialPort, &QSerialPort::readyRead,
            this, &MainWindow::handleReadyRead);

    m_serialPort->setPortName(m_settings->settings().portName);
    m_serialPort->setBaudRate(m_settings->settings().baud);
    m_serialPort->setDataBits(QSerialPort::DataBits(m_settings->settings().data));
    m_serialPort->setParity(QSerialPort::Parity(m_settings->settings().parity));
    m_serialPort->setStopBits(QSerialPort::StopBits(m_settings->settings().stop));
}

void MainWindow::on_btDesc_clicked()
{
    if (isConnected) {
        m_serialPort->close();
        isConnected = false;
        ui->label->setText("Desconectado");
        ui->btCon->setEnabled(true);
        ui->btDesc->setEnabled(false);
        ui->btSniff->setEnabled(false);
    } else {
        emit closePort();
    }
}

void MainWindow::on_btSettings_clicked()
{
    m_settings->show();
}

void MainWindow::on_btSniff_clicked()
{
    if (m_radio) {
        m_radio->disconnect();
        delete m_radio;
        m_radio = nullptr;
    }

    if (m_serialPort) {
        m_serialPort->close();
        m_serialPort->disconnect();
        delete m_serialPort;
        m_serialPort = nullptr;
        isConnected = false;
    }

    m_radio = new RF1276(m_settings, this);
    ui->textBrowser->append("Chamando radio");
    m_radio->searchRadio();
}
