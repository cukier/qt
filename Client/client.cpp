#include "client.h"
#include "ui_client.h"

#include <QHostAddress>
#include <QMessageBox>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client),
    socket(nullptr)
{
    ui->setupUi(this);
    ui->spinPorta->setMaximum(9999);
    ui->spinPorta->setValue(6666);
    ui->btDes->setEnabled(false);
    ui->leArg->setEnabled(false);
    ui->btEnv->setEnabled(false);
    ui->leHost->setText("localhost");
}

Client::~Client()
{
    delete ui;
}

void Client::on_btCon_clicked()
{
    if (socket)
    {
        socket->disconnect();
        socket->close();
        delete socket;
        socket = nullptr;
    }

    socket = new QTcpSocket(this);

    if (!socket)
    {
        QMessageBox::critical(this,
                              "Client Error",
                              "Nao foi possivel criar cliente");
        return;
    }

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(socket, &QTcpSocket::connected,
            this, &Client::onSocketConnected);
    connect(socket, &QTcpSocket::disconnected,
            this, &Client::onSocketDisconnected);

    if (ui->leHost->text() == "localhost")
        socket->connectToHost(QHostAddress::LocalHost,
                              ui->spinPorta->value());
    else
        socket->connectToHost(ui->leHost->text(),
                              ui->spinPorta->value());
}

void Client::onError(QAbstractSocket::SocketError socketError)
{
    if (socket)
    {
        QMessageBox::critical(this,
                              "Client Error",
                              socket->errorString() +
                              QString::number(socketError));

        socket->disconnect();
        socket->close();
        delete socket;
        socket = nullptr;
    }
}

void Client::onSocketConnected()
{
    ui->leArg->setEnabled(true);
    ui->btEnv->setEnabled(true);
    ui->btCon->setEnabled(false);
    ui->btDes->setEnabled(true);
}

void Client::onSocketDisconnected()
{
    ui->leHost->setEnabled(false);
    ui->btEnv->setEnabled(false);
    ui->btCon->setEnabled(true);
    ui->btDes->setEnabled(false);

    QMessageBox::warning(this,
                         "Cliente",
                         "Conexao fechada");
}

void Client::on_btEnv_clicked()
{
    if (!socket)
        return;

    socket->write(ui->leArg->text().toLocal8Bit().constData());
}

void Client::on_btDes_clicked()
{
    if (socket)
    {
        socket->disconnect();
        socket->close();
        delete socket;
        socket = nullptr;

        ui->leArg->setEnabled(false);
        //        ui->btEnv->setEnabled(false);
        ui->btCon->setEnabled(true);
        ui->btDes->setEnabled(false);
    }
}
