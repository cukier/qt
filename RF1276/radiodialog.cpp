#include "radiodialog.h"
#include "ui_radiodialog.h"

#include <QtMath>

RadioDialog::RadioDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadioDialog)
{
    ui->setupUi(this);
}

RadioDialog::~RadioDialog()
{
    delete ui;
}

RadioDialog::RadioSettings RadioDialog::settings() const
{
    return m_settings;
}

void RadioDialog::setSettings(const RadioSettings &settings)
{
    m_settings = settings;

//    ui->cbBaud->setCurrentText(QString::number(m_settings.baudRate));
    ui->sbFreq->setValue(m_settings.freq / 1e+6);
    ui->sbID->setValue(m_settings.id);
    ui->cbMode->setCurrentText(QString::number(m_settings.mode));
    ui->sbNet->setValue(m_settings.NetId);
    ui->cbParity->setCurrentText(QString::number(m_settings.mode));
    ui->cbRfBw->setCurrentText(QString::number(m_settings.rfBw));
    ui->cbRFactor->setCurrentText(QString::number(m_settings.rfFactor));
    ui->cbPow->setCurrentIndex(m_settings.rfPower - 6);

    ui->cbBaud->setCurrentText(QString::number(qPow(2, m_settings.baudRate) * 600));
}

void RadioDialog::on_btApply_clicked()
{
    m_settings.baudRate = ui->cbBaud->currentText().toInt();
    m_settings.freq = (float) ui->sbFreq->value() * 1e+6;
    m_settings.id = ui->sbID->value();
    m_settings.mode = ui->cbMode->currentText().toInt();
    m_settings.NetId = ui->sbNet->value();
    m_settings.parity = ui->cbParity->currentText().toInt();
    m_settings.rfBw = ui->cbRfBw->currentText().toInt();
    m_settings.rfFactor = ui->cbRFactor->currentText().toInt();
    m_settings.rfPower = ui->cbPow->currentIndex() + 6;

    hide();
    emit apply();
}
