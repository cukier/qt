#ifndef ATV312_H
#define ATV312_H

#include "atv312metaobject.h"

#include <QObject>
#include <QModbusDataUnit>
#include <QModbusClient>

class Atv312 : public QObject
{
    Q_OBJECT

public:

    enum
    {
        ControlWord = 8601,
        SpeedReferenceViaTheBus,
        StatusWord,
        OutputSpeed,
        SpeedReference,
        FaultCode,
        MinSpeed,
        MinSpeed1,
        MaxSpeed,
        MaxSpeed1,
        AccelerationSpeedDelta,
        AccelerationSpeedDelta1,
        AccelerationTimeDelta,
        DecelerationSpeedDelta,
        DecelerationSpeedDelta1,
        DecelerationTimeDelta
    };

    explicit Atv312(QObject *parent = nullptr);
    ~Atv312();

    bool conectar(QString porta);
    void fechar();
    void ler();
    void ler(quint16 word);
    void ler(quint16 word, quint16 size);

    quint16 getEndereco() const;
    void setEndereco(const quint16 &value);

public slots:
    void onStateChanged(int state);
    void readReady();

private:
    QModbusClient *modbusDevice = nullptr;
    Atv312MetaObject *atv312 = nullptr;

    bool conectado = false;
    quint16 endereco = 0;
    quint16 enderecoLeitura = 0;
    quint16 wordAux = 0;
};

#endif // ATV312_H
