#ifndef ENCODER_H
#define ENCODER_H

//http://treyweaver.blogspot.com.br/2013/02/qt-console-application-template-tutorial.html

#include <QObject>
#include <QSerialPort>
#include <QCoreApplication>

class Encoder : public QObject
{
    Q_OBJECT

public:
    explicit Encoder(QObject *parent = 0);
    ~Encoder();

    void quit();
signals:
    void finished();
public slots:
    void simular();
private:
    QSerialPort *serialPort;
    QCoreApplication *app;

    bool conectar();
    bool fechar();
    void readReady();
    void writeReady();
};

#endif // ENCODER_H
