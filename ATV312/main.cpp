#include <QCoreApplication>
#include <atv312.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Atv312 atv;

    atv.setEndereco(1);
    atv.conectar("COM2");
    atv.ler(8601);
//    atv.fechar();

    return a.exec();
}
