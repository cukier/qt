#include<QTextStream>
#include<QFile>

int main()
{
    QFile file("C:/Users/Mouses/Desktop/leitura.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "Thomas M. Disch: " << 334 << endl;
    }

    return 0;
}

//#include <QtCore>

//class Task : public QObject
//{
//    Q_OBJECT
//public:
//    Task(QObject *parent = 0) : QObject(parent) {}

//public slots:
//    void run()
//    {
//        // Do processing here

//        emit finished();
//    }

//signals:
//    void finished();
//};

//int main(int argc, char *argv[])
//{
//    QCoreApplication app(argc, argv);

//    Task *task = new Task(&app);
//    QObject::connect(task, SIGNAL(finished()), &app, SLOT(quit()));
//    QTimer::singleShot(0, task, SLOT(run()));

//    return app.exec();
//}
