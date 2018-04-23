#include "server.h"
#include "ui_server.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server),
    server(nullptr),
    socket(nullptr)
{
    ui->setupUi(this);
    ui->spinPorta->setMaximum(9999);
    ui->spinPorta->setValue(6666);
    ui->btDis->setDisabled(true);
}

Server::~Server()
{
    delete ui;
}

void Server::on_btCon_clicked()
{
    if (server)
    {
        server->disconnect();
        server->close();
        delete server;
        server = nullptr;
    }

    server = new QTcpServer(this);

    if (!server)
    {
        QMessageBox::critical(this,
                              "Server Error",
                              "Erro ao criar servidor");
        return;
    }

    connect(server, &QTcpServer::acceptError,
            this, &Server::onError);
    connect(server, &QTcpServer::newConnection,
            this, &Server::onNewConnection);

    server->listen(
                QHostAddress::LocalHost,
                ui->spinPorta->value());

    if (server->isListening())
    {
        ui->btCon->setDisabled(true);
        ui->btDis->setDisabled(false);
    }
}

void Server::on_btDis_clicked()
{
    server->disconnect();
    server->close();
    delete server;
    server = nullptr;
    ui->btDis->setDisabled(true);
    ui->btCon->setDisabled(false);
}

void Server::onError(QAbstractSocket::SocketError socketError)
{
    QMessageBox::critical(this,
                          "Server Error",
                          server->errorString() + " " +
                          QString::number(socketError));
}

void Server::onNewConnection()
{
    socket = server->nextPendingConnection();

    connect(socket, &QTcpSocket::readyRead,
            this, &Server::onReadReady);
}

void Server::onReadReady()
{
    socket->write(socket->readAll());
}
