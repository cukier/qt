#include <QCoreApplication>

#include "modbusserver.h"
#include "filewriter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ModbusServer *srv = new ModbusServer("COM3", &a);
//    FileWriter *fw = new FileWriter(&a);

//    QObject::connect(srv, &ModbusServer::novaEscrita,
//                     fw, &FileWriter::salvar);

//    srv->setEndereco(1);
//    srv->conectar();

    return a.exec();
}
