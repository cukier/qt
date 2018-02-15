#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void MainWindow::on_pushButton_2_clicked()
{

}
