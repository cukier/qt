#include <QCoreApplication>
#include <QUrl>
#include <QNetworkProxyQuery>

#include "mestremodbus.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUrl url;
    url.setPort(502);
    url.setHost("192.168.0.110");
    url.setUserName("USER");
    url.setPassword("USER");

    QNetworkProxyQuery npq(url);
    QList<QNetworkProxy> listOfProxies = QNetworkProxyFactory::systemProxyForQuery(npq);

    if (listOfProxies.count() !=0)
    {
        for(const auto i : listOfProxies)
            qDebug() << i.hostName();
    }

    MestreModbus m(&url);

    return a.exec();
}
