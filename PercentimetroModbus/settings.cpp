#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->lePorta->setText(m_settings.portName);
    ui->coBaud->setCurrentText(QString::number(m_settings.baud));
    ui->coData->setCurrentText(QString::number(m_settings.data));
    ui->coParity->setCurrentIndex(m_settings.parity);
    ui->coStop->setCurrentText(QString::number(m_settings.stop));
}

Settings::~Settings()
{
    delete ui;
}

Settings::SettingsSTR Settings::settings() const
{
    return m_settings;
}

void Settings::on_btApply_clicked()
{
    m_settings.portName = ui->lePorta->text();
    m_settings.baud = ui->coBaud->currentText().toInt();
    m_settings.data = ui->coData->currentText().toInt();
    m_settings.parity = ui->coParity->currentText().toInt();
    m_settings.stop = ui->coStop->currentText().toInt();

    if (m_settings.parity > 0)
        m_settings.parity++;

    hide();
}
