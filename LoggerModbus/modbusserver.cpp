#include "modbusserver.h"

#include <QDebug>
#include <QCoreApplication>

//#define make16(x,y)     ((((quint16)x<<8)&0xFF00)|y)
//#define make16(x,y)     ((quint16(x)<<8)|y)

const quint16 ModbusServer::wCRCTable[] = {
    0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
    0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
    0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
    0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
    0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
    0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
    0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
    0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
    0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
    0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
    0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
    0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
    0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
    0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
    0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
    0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
    0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
    0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
    0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
    0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
    0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
    0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
    0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
    0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
    0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
    0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
    0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
    0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
    0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
    0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
    0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
    0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

ModbusServer::ModbusServer(QString porta, QObject *parent) :
    QObject(parent),
    m_serialPort(nullptr),
    mapaMemoria(QVector<quint16>(mem_size))
{
    m_serialPort = new QSerialPort(this);

    if (!m_serialPort)
    {
        qDebug() << "<ModbusServer> Erro ao criar porta serial";
        qApp->exit(EXIT_FAILURE);
    }

    if (porta.isEmpty() || porta.isNull())
        porta = "COM1";

    m_serialPort->setPortName(porta);
    m_serialPort->setBaudRate(QSerialPort::Baud19200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);

    connect(m_serialPort, &QSerialPort::readyRead,
            this, &ModbusServer::on_readReady);
    connect(m_serialPort, &QSerialPort::bytesWritten,
            this, &ModbusServer::on_bytesWritten);
    connect(m_serialPort, &QSerialPort::errorOccurred,
            this, &ModbusServer::on_errorOccurred);
}

ModbusServer::~ModbusServer()
{
}

void ModbusServer::on_readReady()
{
    quint64 n = m_serialPort->bytesAvailable();

    qDebug() << "<ModbusServer> " << n << " bytes diponiveis";
    const auto adu = m_serialPort->readAll();
    quint8 addr = adu.at(0);

    if (addr == m_addr)
    {
        quint8 cmd = adu.at(1);

        if (cmd == ReadHoldingRegisters)
        {
            if (adu.size() == 8)
            {
                quint16 rSize = make16(adu.at(4), adu.at(5));

                if (rSize >= 1 && rSize <= 0x7D)
                {
                    quint16 sAddr = make16(adu.at(2), adu.at(3));

                    if (sAddr + rSize < mem_size)
                    {
                        quint16 crc = make16(adu.at(6), adu.at(7));
                        quint16 dataCrc;
                        QByteArray arr = adu.mid(0, 6);

                        dataCrc = swapW(ModRTU_CRC(arr));

                        if (dataCrc == crc)
                        {
                            qDebug() << "<ModbusServer> Requisicao de leitura (0x03) do endereco"
                                     << sAddr << " por " << rSize << " registradores";

                            QByteArray pdu;

                            pdu.append(m_addr);
                            pdu.append(ReadHoldingRegisters);
                            pdu.append(rSize * 2);

                            for (int i = 0; i < rSize; ++i)
                            {
                                pdu.append(make8(mapaMemoria.at(i + sAddr), 1));
                                pdu.append(make8(mapaMemoria.at(i + sAddr), 0));
                            }

                            modbusWrite(pdu);
                        }
                        else
                        {
                            qDebug() << "<ModbusServer> Erro de crc. Ignorando";
                        }
                    }
                    else
                    {
                        qDebug() << "<ModbusServer> Quantidade de registradores + endereco inicial maior que tamanho da memoria";
                        returnModbusError(ReadHoldingRegisters, IndexOutOfBoundsError);
                    }
                }
                else
                {
                    qDebug() << "<ModbusServer> Quantidade de registradores fora do padrao";
                    returnModbusError(ReadHoldingRegisters, QuantityOfRegistersError);
                }
            }
            else
            {
                qDebug() << "<ModbusServer> Adu tamanho errado";
                returnModbusError(ReadHoldingRegisters, FunctionNotSupported);
            }
        }
        else if (cmd == WriteSingleRegister)
        {
            if (adu.size() == 8)
            {
                quint16 rValue = make16(adu.at(4), adu.at(5));

                if (rValue <= 0xFFFE)
                {
                    quint16 sAddr = make16(adu.at(2), adu.at(3));

                    if (sAddr < mem_size)
                    {
                        quint16 crc = make16(adu.at(6), adu.at(7));
                        quint16 dataCrc;
                        QByteArray arr = adu.mid(0, 6);

                        dataCrc = swapW(ModRTU_CRC(arr));

                        if (dataCrc == crc)
                        {
                            qDebug() << "<ModbusServer> Requisicao de escrita (0x06) no endereco"
                                     << sAddr << " por " << rValue << " registradores";

                            mapaMemoria[sAddr] = rValue;
                            modbusWrite(adu.mid(0, 6));
                            emit novaEscrita(sAddr, mapaMemoria.mid(sAddr, 1));
                        }
                        else
                        {
                            qDebug() << "<ModbusServer> Erro de crc. Ignorando";
                        }
                    }
                    else
                    {
                        qDebug() << "<ModbusServer> Quantidade de registradores + endereco inicial maior que tamanho da memoria";
                        returnModbusError(WriteSingleRegister, IndexOutOfBoundsError);
                    }
                }
                else
                {
                    qDebug() << "<ModbusServer> Quantidade de registradores fora do padrao";
                    returnModbusError(WriteSingleRegister, QuantityOfRegistersError);
                }
            }
            else
            {
                qDebug() << "<ModbusServer> Adu tamanho errado";
                returnModbusError(WriteSingleRegister, FunctionNotSupported);
            }
        }
        else if (cmd == WriteMultipleRegisters)
        {
            quint16 rSize = make16(adu.at(4), adu.at(5));

            if (rSize >= 1 && rSize <= 0x7B)
            {
                quint16 sAddr = make16(adu.at(2), adu.at(3));

                if (sAddr + rSize < mem_size)
                {
                    quint8 rQtd = adu.at(6);

                    if (quint8(n) == 9 + rQtd)
                    {
                        quint16 crc = make16(adu.at(n - 2), adu.at(n - 1));
                        quint16 dataCrc;
                        QByteArray arr = adu.mid(0, n - 2);

                        dataCrc = swapW(ModRTU_CRC(arr));

                        if (dataCrc == crc)
                        {
                            qDebug() << "<ModbusServer> Requisicao de escrita (0x10) do endereco"
                                     << sAddr << " por " << rSize << " registradores";

                            for (int i = 0; i < rSize; ++i)
                            {
                                mapaMemoria[i + sAddr] = make16(adu.at(7 + (2 * i)), adu.at(7 + ((2 * i) + 1)));
                            }

                            QByteArray pdu = adu.mid(0, 6);
                            modbusWrite(pdu);
                            emit novaEscrita(sAddr, mapaMemoria.mid(sAddr, rSize));
                        }
                        else
                        {
                            qDebug() << "<ModbusServer> Erro de crc. Ignorando";
                        }
                    }
                    else
                    {
                        qDebug() << "<ModbusServer> Quantidade de bytes fora do padrao";
                        returnModbusError(WriteMultipleRegisters, FunctionNotSupported);
                    }
                }
                else
                {
                    qDebug() << "<ModbusServer> Quantidade de registradores + endereco inicial maior que tamanho da memoria";
                    returnModbusError(WriteMultipleRegisters, IndexOutOfBoundsError);
                }
            }
            else
            {
                qDebug() << "<ModbusServer> Quantidade de registradores fora do padrao";
                returnModbusError(WriteMultipleRegisters, QuantityOfRegistersError);
            }
        }
        else
        {
            //            qDebug() << "<ModbusServer> Comando nao suportado 0x" << QString::number(cmd, 16);
            qDebug() << tr("<ModbusServer> Comando nao suportado 0x%0").arg(ushort(cmd), 2, 16, QLatin1Char('0'));
            returnModbusError(cmd, FunctionNotSupported);
        }
    }
    else
    {
        qDebug() << "<ModbusServer> Endereco diferente, ignorando";
    }
}

void ModbusServer::on_bytesWritten(quint64 bytes)
{
    qDebug() << "<ModbusServer> " << bytes << " bytes para escrever";
}

void ModbusServer::on_errorOccurred(QSerialPort::SerialPortError error)
{
    qDebug() << "<ModbusServer> Erro " << QString::number(error);
}

quint8 ModbusServer::make8(quint32 dword, quint8 index)
{
    return quint8(dword >> (8 * index));
}

void ModbusServer::setEndereco(const quint8 &addr)
{
    m_addr = addr;
}

bool ModbusServer::conectar()
{
    if (m_serialPort)
        return m_serialPort->open(QIODevice::ReadWrite);
    else
        return false;
}

QString ModbusServer::getPortName()
{
    if (m_serialPort)
        return m_serialPort->portName();
    else
        return "Nenhuma porta";
}

quint16 ModbusServer::make16(quint8 h_b, quint8 l_b)
{
    quint16 ret = 0;

    ret = h_b << 8 & 0xFF00;
    ret |= l_b;

    return ret;
}

quint16 ModbusServer::swapW(quint16 i_w)
{
    quint8 l = quint8(i_w);
    quint8 h = quint8((i_w & 0xFF00) >> 8);

    return make16(l, h);
}

quint16 ModbusServer::ModRTU_CRC(quint8 *buf, quint16 len)
{
    quint8 nTemp;
    quint16 wCRCWord = 0xFFFF;

    while (len--) {
        nTemp = *buf++ ^ wCRCWord;
        wCRCWord >>= 8;
        wCRCWord ^= wCRCTable[nTemp];
    }

    return wCRCWord;
}

quint16 ModbusServer::ModRTU_CRC(QByteArray buf)
{
    quint8 nTemp;
    quint16 wCRCWord = 0xFFFF;

    for (const auto i : buf)
    {
        nTemp = quint8(i) ^ wCRCWord;
        wCRCWord >>= quint16(8);
        wCRCWord ^= wCRCTable[nTemp];
    }

    return wCRCWord;
}

void ModbusServer::modbusWrite(QByteArray buf)
{
    quint16 respCrc = swapW(ModRTU_CRC(buf));

    buf.append(quint8((respCrc & 0xFF00) >> 8));
    buf.append(quint8(respCrc));

    m_serialPort->write(buf, buf.size());
}

void ModbusServer::returnModbusError(quint8 eCommand, quint8 eCode)
{
    QByteArray errorPdu;

    errorPdu.append(m_addr);
    errorPdu.append(eCommand | 0x80);
    errorPdu.append(eCode);
    modbusWrite(errorPdu);
}

