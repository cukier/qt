#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <mapa_memoria.h>
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
    void on_readButton_clicked();

    void on_connButton_clicked();

    void on_irrigaButton_clicked();

private:
    Ui::MainWindow *ui;
    QModbusClient *modbusDevice;
    Mapa_Memoria *m;
    unsigned short w0;

    void readReady();
    void onStateChanged(int state);
    void inicio() const;
    void readModbus(unsigned short addr_slv, unsigned short start_addr, unsigned short qtd);
    void writeModbus(unsigned short addr_slv, unsigned short start_addr, unsigned short qtd, unsigned short *arr);
};

#endif // MAINWINDOW_H
