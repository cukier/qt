#include <QCoreApplication>

//#include "modbusserver.h"
#include "filewriter.h"
#include "modbustcpmaster.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ModbusTcpMaster *mstr = new ModbusTcpMaster(&a);
    FileWriter *fw = new FileWriter(&a);

    QObject::connect(mstr, &ModbusTcpMaster::mudouValor,
                     fw, &FileWriter::salvar);

    mstr->conectar();

    //    ModbusServer *srv = nullptr;

    //    if (argc == 2)
    //    {
    //        srv = new ModbusServer(argv[1], &a);
    //    }
    //    else
    //    {
    //        srv = new ModbusServer("COM3", &a);
    //    }

    //    FileWriter *fw = new FileWriter(&a);

    //    QObject::connect(srv, &ModbusServer::novaEscrita,
    //                     fw, &FileWriter::salvar);

    //    srv->setEndereco(1);
    //    qDebug() << "Abrindo a porta " << srv->getPortName()
    //             << ' ' << srv->conectar();

    return a.exec();
}
