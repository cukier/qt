#include <QCoreApplication>
#include <QTimer>

#include "encoder.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Encoder e;

    QObject::connect(&e, SIGNAL(finished()), &app, SLOT(quit()));
    QTimer::singleShot(10, &e, SLOT(simular()));

    return app.exec();
}
