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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::MainWindow *ui;
    QModbusClient *modbusDevice;
};

#endif // MAINWINDOW_H
