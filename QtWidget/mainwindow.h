#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusDataUnit>

class QModbusClient;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool isConn;
    void readReady();
    void onStateChanged(int state);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_readButton_clicked();

    void on_connButton_clicked();

private:
    Ui::MainWindow *ui;
    QModbusClient *modbusDevice;
};

#endif // MAINWINDOW_H
