#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QDebug>

class Sensor
{
public:
    QJsonObject request(const QString &url, bool *ok = nullptr) const
    {
        QEventLoop waitLoop;
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
        QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
        waitLoop.exec();

        //Caso tenha algum problema de conexão
        if(reply->error())
        {
            qDebug() << reply->errorString();
            if(ok)
            {
                *ok = false;
            }
            return QJsonObject();
        }

        if(ok)
        {
            *ok = true;
        }

        QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
        return doc.object();
    }

    //Essa função será responsável por processar os dados recebidos da requisição e pode, por exemplo, ligar a irrigação das plantas.
    void execute(const QJsonObject &json) const
    {
        qDebug() << "Temperatura: " << json["temperatura"].toInt();
        qDebug() << "Umidade    : " << json["umidade"].toInt();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Sensor sensor;
    bool ok;
    while(true)
    {
        //A plaquinha vai precisar de um IP fixo. Quando colocar o IP fixo, basta trocar o 127.0.0.1 pelo novo endereço.
        QJsonObject json(sensor.request("http://127.0.0.1:8080/sensor", &ok));
        if(ok)
        {
            sensor.execute(json);
        }
        //A cada X segundos será feita uma requisição.
        QThread::sleep(1);
    }

    return a.exec();
}
