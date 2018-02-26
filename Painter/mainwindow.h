#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pizza.h"

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent */*event*/);

private:
    Ui::MainWindow *ui;
    Pizza *painter;
    QTimer *timer;

    qreal angulo;
};

#endif // MAINWINDOW_H
