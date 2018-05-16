#ifndef RF1276_H
#define RF1276_H

#include <QObject>

class QSerialPort;
class QTimer;
class Settings;

class RF1276 : public QObject
{
    Q_OBJECT
public:
    RF1276(QSerialPort *serialPort, QObject *parent = nullptr);

    void searchRadio(QString porta);
    static QByteArray MakeRadioReadCommand(const int size);

private slots:
    void handleReadyRead();
    void handleTimeOut();

private:
    enum Transactions {
        NoTransaction,
        ReadTransaction,
        WriteTransaction,
        RSSITransaction,
        Sniffing
    };

    enum Sizes {
        DataSize = 12,
        DataSizeRSSI = 2,
        CommandSize = 23,
        CommandSizeRSSI = 13,
        HeaderSize = 8
    };

    enum CommandYY {
        WriteYYCommand = 1,
        ReadYYCommand,
        StatndardYYCommand,
        CentralYYCommand,
        NodeYYCommand,
        RSSIYYCommand
    };

    enum CommandXX {
        ResponseXXCommand,
        SendingXXCommand = 0x80
    };

    enum RfFactor {
        RF128 = 7,
        RF256,
        RF512,
        RF1024,
        RF2048,
        RF4096
    };

    enum Mode {
        StandardMode,
        LowPowerMode,
        SleepMode
    };

    enum RfBw {
        BW62_5K = 6,
        BW125K,
        BW250K,
        BW500K
    };

    enum RfPower {
        P4DBM = 1,
        P7DBM,
        P10DBM,
        P13DBM,
        P14DBM,
        P17DBM,
        P20DBm
    };

    QSerialPort *m_serialPort;
    QTimer *m_timer;
    Settings *m_settings;

    int currentTransaction = NoTransaction;
    const QByteArray discover = QByteArray(
                "\xAF\xAF\x00\x00\xAF\x80\x02\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x9B\x0D\x0A", 23
                );

    static char crc(const QByteArray& data);
    static void MakeRadioRequest(const int commnadYY, QByteArray& data);
    void MakeRadioReadTransaction();
};

#endif // RF1276_H
