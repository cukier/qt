#ifndef ATV312_H
#define ATV312_H

#include <QObject>
#include <QModbusDataUnit>
#include <QModbusClient>

class Atv312 : public QObject
{
    Q_OBJECT
public:
    explicit Atv312(QObject *parent = nullptr);
    ~Atv312();

    bool conectar(QString porta);
    void fechar();
    void ler(quint16 word);
    void ler(quint16 word, quint16 size);

    quint16 getEndereco() const;
    void setEndereco(const quint16 &value);

public slots:
    void onStateChanged(int state);
    void readReady();

private:
    QModbusClient *modbusDevice = nullptr;

    bool conectado = false;
    quint16 endereco = 0;
};

#endif // ATV312_H
