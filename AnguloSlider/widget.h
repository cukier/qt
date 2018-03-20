#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QModbusTcpClient>
#include <QUrl>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_stateChanged(int state);
    void on_valueChanged(int value);
    void on_readReady();

private:
    Ui::Widget *ui;
    QModbusClient *modbusDevice;
};

#endif // WIDGET_H
