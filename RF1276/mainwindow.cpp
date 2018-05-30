#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "radiodialog.h"
#include "settings.h"
#include "rf1276.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_settings(new Settings()),
    m_serialPort(nullptr),
    m_radio(nullptr),
    m_radioDialog(nullptr)
{
    ui->setupUi(this);
    ui->btDesc->setEnabled(false);
    ui->btSniff->setEnabled(false);
    ui->btProc->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete m_radioDialog;
    delete m_settings;
    delete ui;
}

void MainWindow::appendText(QString text)
{
    ui->textBrowser->append(text);
}

void MainWindow::on_btCon_clicked()
{
    createSerial();
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

void MainWindow::handleRadioEncontrado(QByteArray radio)
{
    if (m_radio) {
        m_radio->disconnect();
        delete m_radio;
        m_radio = nullptr;
    }

    if (radio.size() == 23) {
        ui->btSniff->setVisible(true);

        if (!m_radioDialog) {
            m_radioDialog = new RadioDialog();
        }

        m_radioDialog->setSettings(RF1276::getRadio(radio));

        if (m_radioDialog) {
            ui->textBrowser->append(QString("Baudrate %1")
                                    .arg(m_radioDialog->settings().baudRate));
            ui->textBrowser->append(QString("Parity %1")
                                    .arg(m_radioDialog->settings().parity));
            ui->textBrowser->append(QString("Frequencie %1 MHz")
                                    .arg(m_radioDialog->settings().freq / 10e5));
            ui->textBrowser->append(QString("RF Factor %1")
                                    .arg(m_radioDialog->settings().rfFactor));
            ui->textBrowser->append(QString("Mode %1")
                                    .arg(m_radioDialog->settings().mode));
            ui->textBrowser->append(QString("RF BW %1")
                                    .arg(m_radioDialog->settings().rfBw));
            ui->textBrowser->append(QString("ID %1")
                                    .arg(m_radioDialog->settings().id));
            ui->textBrowser->append(QString("NetID %1")
                                    .arg(m_radioDialog->settings().NetId));
            ui->textBrowser->append(QString("Power %1")
                                    .arg(m_radioDialog->settings().rfPower));
            ui->btSniff->setEnabled(true);
        } else {
            ui->textBrowser->append("Radio nao encontrado");
        }
    } else {
        ui->textBrowser->append("Radio nao encontrado");
    }

    createSerial();
}

void MainWindow::createSerial()
{
    if (m_serialPort) {
        m_serialPort->close();
        m_serialPort->disconnect();
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
        ui->btProc->setEnabled(true);
        ui->btSettings->setEnabled(false);
    }
}

void MainWindow::on_btDesc_clicked()
{
    if (isConnected) {
        m_serialPort->disconnect();
        m_serialPort->close();
        isConnected = false;
        ui->label->setText("Desconectado");
        ui->btCon->setEnabled(true);
        ui->btDesc->setEnabled(false);
        ui->btSniff->setEnabled(false);
        ui->btProc->setEnabled(false);
        ui->btSettings->setEnabled(true);
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
    ui->textBrowser->append(QString::number(m_radioDialog->settings().freq));

    RadioDialog::RadioSettings settings = m_radioDialog->settings();

    settings.freq = 9.16e+8;

    QByteArray req = RF1276::MaeRadioWriteCommand(settings);

    m_serialPort->write(req);
}

void MainWindow::on_btProc_clicked()
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

    connect(m_radio, &RF1276::debugMsg,
            this, &MainWindow::appendText);
    connect(m_radio, &RF1276::radioEncontrado,
            this, &MainWindow::handleRadioEncontrado);

    ui->textBrowser->append("Chamando radio");
    m_radio->searchRadio();
}
