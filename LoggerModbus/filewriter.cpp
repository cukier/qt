#include "filewriter.h"

#include <QDate>
#include <QTime>
#include <QDebug>
#include <QDir>

FileWriter::FileWriter(QObject *parent) : QObject(parent)
{
//    file_path = "C:/Users/Mouses/Desktop/arquivo.txt";
    file_path = QDir::currentPath() + "logModbus.txt";
}

FileWriter::FileWriter(QString str, QObject *parent) :
    QObject(parent),
    file_path(str)
{
}

void FileWriter::salvar(quint16 addr, QVector<quint16> dado)
{
    QFile file(file_path);

    if (!file.open(QFile::WriteOnly | QFile::Text | QIODevice::Append))
    {
        qDebug() << "<FileWriter> Erro ao abrir arquivo " << file_path;
        return;
    }

    QTextStream txt(&file);

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    txt << tr("%1").arg(date.day(), 2, 10, QLatin1Char('0')) << '/'
        << tr("%1").arg(date.month(), 2, 10, QLatin1Char('0')) << ' '
        << tr("%1").arg(time.hour(), 2, 10, QLatin1Char('0')) << ':'
        << tr("%1").arg(time.minute(), 2, 10, QLatin1Char('0')) << ':'
        << tr("%1").arg(time.second(), 2, 10, QLatin1Char('0')) << ' ';

    for (int i = 0; i < dado.size(); ++i)
        txt << tr("%1 %2 ")
               .arg(i + addr, 5, 10, QLatin1Char('0'))
               .arg(dado.value(i), 5, 10, QLatin1Char('0'));

    txt << '\n';

    file.flush();
    file.close();
}
