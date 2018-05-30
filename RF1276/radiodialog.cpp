#include "radiodialog.h"
#include "ui_radiodialog.h"

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
}

void RadioDialog::on_btApply_clicked()
{
    m_settings.baudRate = ui->cbBaud->currentText().toInt();
    m_settings.freq = (float) ui->sbFreq->value();
    m_settings.id = ui->sbID->value();
    m_settings.mode = ui->cbMode->currentText().toInt();
    m_settings.NetId = ui->sbNet->value();
    m_settings.parity = ui->cbParity->currentText().toInt();
    m_settings.rfBw = ui->cbRfBw->currentText().toInt();
    m_settings.rfFactor = ui->cbRFactor->currentText().toInt();
    m_settings.rfPower = ui->cbPow->currentIndex() + 6;

    emit apply();
}
