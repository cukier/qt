//#include <QCoreApplication>
#include <QVector>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    //    QCoreApplication a(argc, argv);

    QVector<quint16> vector;

    vector.push_back(0x8579);
    vector.push_back(0x6571);
    vector.push_back(0x2238);
    vector.push_back(0x9475);

    QString str;

    for (const auto i : vector)
    {
        char s1 = (char) (((i & 0xFF00) >> 8) & 0xFF);
        char s2 = (char) (i & 0xFF);

        str.append(s2);
        str.append(s1);
    }

    cout << qPrintable(str) << endl;

    str = "Mauricio";
    QVector<quint16> vt;

    for (int i = 0; i < str.size(); i += 2)
    {
        quint16 s1 = ((quint16) str.at(i).unicode() << 8) & 0xFF00;
        //        quint16 s1 = str.at(i).unicode();

        if ((i + 1) < str.size())
        {
            s1 |= str.at(i + 1).unicode() & 0xFF;
        }

        vt.append(s1);
    }

    //    return a.exec();
    return 0;
}
