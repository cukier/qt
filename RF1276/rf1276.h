#ifndef RF1276_H
#define RF1276_H

#include <QWidget>
#include <QSerialPort>

class SettingsDialog;

namespace Ui {
class RF1276;
}

class RF1276 : public QWidget
{
    Q_OBJECT

public:
    explicit RF1276(QWidget *parent = 0);
    ~RF1276();

private slots:
    void on_btConfig_clicked();
    void on_btConectar_clicked();
    void handleError(QSerialPort::SerialPortError error);
    void handleReadyRead();

    void on_btDesc_clicked();

private:
    Ui::RF1276 *ui;
    SettingsDialog *dialog;
    QSerialPort *m_serialPort;

    bool isConnected = false;
};

#endif // RF1276_H
