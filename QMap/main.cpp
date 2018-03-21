//#include <QCoreApplication>
#include <QMap>
#include <QMapIterator>
#include <iostream>

using namespace std;

int main(/*int argc, char *argv[]*/)
{
    //    QCoreApplication a(argc, argv);

    //    return a.exec();

    QMap<QString, int> map;

    map.insert("one", 1);
    map.insert("three", 3);
    map.insert("seven", 7);
    map.insert("twelve", 12);

//    int num1 = map["thirteen"];
    int num2 = map.value("thirteen");

    int timeout = 30;

    if (map.contains("TIMEOUT"))
        timeout = map.value("TIMEOUT");

    int timeout2 = map.value("TIMEOUT", 30);

//    Q_UNUSED(num1);
    Q_UNUSED(num2);
    Q_UNUSED(timeout2);
    Q_UNUSED(timeout);

    QMapIterator<QString, int> i(map);

    while (i.hasNext())
    {
        i.next();
        cout << qPrintable(i.key()) << ": " << i.value() << endl;
    }

    //    QMap<QString, int>::const_iterator i = map.constBegin();

    //    while (i != map.constEnd())
    //    {
    //        cout << i.key() << ": " << i.value() << endl;
    //        ++i;
    //    }


    //    QMap<QString, int>::iterator i = map.find("plenty");
    //    while (i != map.end() && i.key() == "plenty") {
    //        cout << i.value() << endl;
    //        ++i;
    //    }

    map.insert("plenty", 100);
    map.insert("plenty", 2000);
    // map.value("plenty") == 2000

    QList<int> values = map.values("plenty");
    for (int i = 0; i < values.size(); ++i)
        cout << values.at(i) << endl;

    foreach (int value, map)
        cout << value << endl;

    return 0;
}
