#ifndef ENCODER_H
#define ENCODER_H

//http://treyweaver.blogspot.com.br/2013/02/qt-console-application-template-tutorial.html

#include <QObject>
#include <QSerialPort>
#include <QCoreApplication>

class Encoder : public QCoreApplication
{
    Q_OBJECT

public:
    Encoder(int argc, char **argv);
    ~Encoder();

    void simular();
private:
    QSerialPort *serialPort;

    bool conectar();
    bool fechar();
    void readReady();
    void writeReady();
//signals:
//    void finished();
private slots:
    void endOfProgram();
};

#endif // ENCODER_H
