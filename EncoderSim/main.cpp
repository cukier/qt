#include <QCoreApplication>
#include "encoder.h"

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
    Encoder e(argc, argv);

//    QObject::connect(&e, SIGNAL(finished()), &a, SLOT(QCoreApplication::quit()));

    e.simular();
//    QCoreApplication::quit();
//    return a.exec();
    return e.exec();
}
