#include "rf1276.h"
#include "ui_rf1276.h"

#include "settingsdialog.h"

RF1276::RF1276(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RF1276),
    dialog(new SettingsDialog()),
    m_serialPort(nullptr)
{
    ui->setupUi(this);
    ui->btDesc->setEnabled(false);
}

RF1276::~RF1276()
{
    delete dialog;
    delete ui;
}

void RF1276::on_btConfig_clicked()
{
    dialog->show();
}

void RF1276::on_btConectar_clicked()
{
    if (m_serialPort) {
        delete m_serialPort;
        m_serialPort = nullptr;
    }

    m_serialPort = new QSerialPort(this);

    connect(m_serialPort, &QSerialPort::errorOccurred,
            this, &RF1276::handleError);
    connect(m_serialPort, &QSerialPort::readyRead,
            this, &RF1276::handleReadyRead);

    m_serialPort->setPortName(dialog->settings().portName);
    m_serialPort->setBaudRate(dialog->settings().baud);
    m_serialPort->setDataBits(QSerialPort::DataBits(dialog->settings().dataBits));
    m_serialPort->setParity(QSerialPort::Parity(dialog->settings().parity));
    m_serialPort->setStopBits(QSerialPort::StopBits(dialog->settings().stopBits));

    isConnected = m_serialPort->open(QIODevice::ReadWrite);

    if (isConnected) {
        ui->label->setText(tr("Conectado %1@%2%3%4%5")
                           .arg(dialog->settings().portName)
                           .arg(dialog->settings().baud)
                           .arg(dialog->settings().dataBits)
                           .arg(dialog->settings().parity)
                           .arg(dialog->settings().stopBits));
        ui->btConectar->setEnabled(false);
        ui->btDesc->setEnabled(true);
    }
}

void RF1276::handleError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        ui->textBrowser->append(QObject::tr("An I/O error occurred while writing"
                                            " the data to port %1, error: %2")
                                .arg(m_serialPort->portName())
                                .arg(m_serialPort->errorString()));
    }
}

void RF1276::handleReadyRead()
{
    QByteArray buff = m_serialPort->readAll();

    if (ui->checkBox->isChecked())
        ui->textBrowser->append(buff.toHex());
    else
        ui->textBrowser->append(buff);
}

void RF1276::on_btDesc_clicked()
{
    if (isConnected) {
        m_serialPort->close();
        isConnected = false;
        ui->label->setText("Desconectado");
        ui->btConectar->setEnabled(true);
        ui->btDesc->setEnabled(false);
    }
}
