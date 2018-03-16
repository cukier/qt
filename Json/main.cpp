//#include <QCoreApplication>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "a.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    //    QCoreApplication app(argc, argv);

    A a;
    a.setNome("Nome");
    a.setId(1985);

    A b;
    b.setNome("Outro");
    b.setId(392);

    QFile file(QDir::homePath() + "/Desktop/teste.json");

    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Erro ao abrir aquivo";
        return EXIT_FAILURE;
    }

    QJsonObject obj;
    a.write(obj);
//    b.write(obj);

//    QByteArray saveData = file.readAll();

    QJsonDocument doc(obj);
    file.write(doc.toJson());

    b.write(obj);
    doc.setObject(obj);
    file.write(doc.toJson());



    return EXIT_SUCCESS;
}
