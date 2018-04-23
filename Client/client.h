#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private slots:
    void on_btCon_clicked();
    void onError(QAbstractSocket::SocketError socketError);
    void onSocketConnected();
    void onSocketDisconnected();
    void onReadReady();

    void on_btEnv_clicked();

    void on_btDes_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *socket;
};

#endif // CLIENT_H
