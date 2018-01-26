#include <QCoreApplication>
#include <QJsonObject>
#include "a.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    A a;
    QJsonObject ob;

    a.setNome("Nome");
    a.write(ob);

    return app.exec();
}
