#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    struct SettingsSTR
    {
        QString portName = "COM2";
        int baud = 19200;
        int data = 8;
        int parity = 0;
        int stop = 1;
    };

    explicit Settings(QWidget *parent = 0);
    ~Settings();

    SettingsSTR settings() const;

private slots:
    void on_btApply_clicked();

private:
    Ui::Settings *ui;
    SettingsSTR m_settings;
};

#endif // SETTINGS_H
