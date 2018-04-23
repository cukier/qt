#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>


class Socket : public QTcpSocket
{
public:
    Socket(QObject *parent = Q_NULLPTR);
};

#endif // SOCKET_H
