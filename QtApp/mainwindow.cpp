#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    MainWindow.set

}
