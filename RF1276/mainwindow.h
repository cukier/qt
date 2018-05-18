#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSerialPort>

class Settings;
class RF1276;
class RadioDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void appendText(QString text);

signals:
    void closePort();

private slots:
    void on_btCon_clicked();
    void on_btDesc_clicked();
    void on_btSettings_clicked();
    void on_btSniff_clicked();
    void handleError(QSerialPort::SerialPortError error);
    void handleReadyRead();
    void handleRadioEncontrado(QByteArray radio);
    void on_btProc_clicked();

private:
    Ui::MainWindow *ui;
    Settings *m_settings;
    QSerialPort *m_serialPort;
    RF1276 *m_radio;
    RadioDialog *m_radioDialog;

    bool isConnected = false;

    void createSerial();
    float ByteToFreq(QByteArray data);
    void getRadio(QByteArray radio);
};

#endif // MAINWINDOW_H
