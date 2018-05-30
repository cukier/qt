#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

class Settings;
class QModbusClient;
class QModbusReply;

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onStateChanged(int state);
    void onReplyFinished();
    void on_btConf_clicked();
    void on_btAbrir_clicked();

    void on_btLer_clicked();

    void on_btGravar_clicked();

private:
    enum Comando {
        NaoExitente,
        Leitura,
        Gravacao
    };

    Ui::MainWindow *ui;
    Settings *m_settings;
    QModbusClient *modbusDevice;
    int m_comando;
};

#endif // MAINWINDOW_H
