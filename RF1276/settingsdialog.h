#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QString>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString portName = "COM1";
        int parity = QSerialPort::EvenParity;
        int baud = QSerialPort::Baud19200;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;
        int responseTime = 1000;
        int numberOfRetries = 3;
    };

    explicit SettingsDialog(QDialog *parent = 0);
    ~SettingsDialog();

    Settings settings() const;

private:
    Settings m_settings;
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
