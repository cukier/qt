#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Pixels
    {
        Centro = 300,
        Raio = 200,
        TamanhoMinimoH = 600,
        TamanhoMinimoW = 600
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    qreal angulo;
};

#endif // MAINWINDOW_H
