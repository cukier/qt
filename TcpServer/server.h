#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private slots:
    void on_btCon_clicked();
    void on_btDis_clicked();
    void onError(QAbstractSocket::SocketError socketError);
    void onNewConnection();
    void onReadReady();

private:
    Ui::Server *ui;
    QTcpServer *server;
    QTcpSocket *socket;
};

#endif // SERVER_H
