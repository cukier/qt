#include <QCoreApplication>
#include <atv312.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Atv312 atv(&a);

    atv.setEndereco(1);
    atv.conectar("COM2");
    atv.ler(8601);

    return a.exec();
}
