#include <QCoreApplication>
#include <atv312.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Atv312 *atv = new Atv312(&a);

    atv->setEndereco(1);
    atv->conectar("COM2");
    atv->acinonarSentidoHorario();

    return a.exec();
}
