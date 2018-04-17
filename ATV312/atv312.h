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

    enum CONTROL_WORD_BITS
    {
        SwitchOn,
        DisableVoltage,
        QuickStop,
        EnableOperation,
        Reserved0,
        Reserved1,
        Reserved2,
        FaultStateReset,
        Reserved3,
        Reserved4,
        Reserved5,
        DirectionCommand, //0: Foward, 1: Reverse
        StopCommand, //0: No Action, 1: Stop
        InjectionCommand, //0: No Action, 1: Injection
        FastStopCommand, //0: No Action, 1: Fast Stop
        Reserved6
    };

    enum IEC_VARIABLES
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

    enum COMANDOS
    {
        SemComando,
        LigarSentidoHorario
    };

    explicit Atv312(QObject *parent = nullptr);
    ~Atv312();

    bool conectar(QString porta);
    void fechar();
    void ler();
    void acinonarSentidoHorario();

    quint16 getEndereco() const;
    void setEndereco(const quint16 &value);

signals:
    void leituraTerminada();

public slots:
    void onStateChanged(int state);
    void readReady();

private slots:
    void onLeituraCompleta();

private:
    QModbusClient *modbusDevice = nullptr;
    Atv312MetaObject *atv312 = nullptr;

    bool conectado = false;
    quint16 endereco = 0;
    quint16 enderecoLeitura = 0;
    quint16 wordAux = 0;
    quint16 comando = 0;

    void escrever(quint16 address, quint16 word);
    void ler(quint16 word);
    void ler(quint16 word, quint16 size);
    void setValue(quint16 value);
    quint16 setBit(quint16 word, quint16 bit);
    quint16 resetBit(quint16 word, quint16 bit);
    bool getBit(quint16 word, quint16 bit);
};

#endif // ATV312_H
