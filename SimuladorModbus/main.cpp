#include <QCoreApplication>
#include <QUrl>
#include <QNetworkProxy>
#include <QSettings>

#include "mestremodbus.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUrl url;
    url.setPort(502);
    //    url.setHost("192.168.0.110");
    url.setHost("127.0.0.1");
    //    url.setUserName("USER");
    //    url.setPassword("USER");

    QNetworkProxyQuery npq(url);
    QList<QNetworkProxy> listOfProxies = QNetworkProxyFactory::systemProxyForQuery(npq);
    QNetworkProxy proxy;

    if (listOfProxies.size())
    {
        proxy.setHostName(listOfProxies[0].hostName());
        proxy.setPort(listOfProxies[0].port());
    }
    else
    {
        proxy.setHostName("192.168.0.1");
        proxy.setPort(3128);
    }

    proxy.setType(QNetworkProxy::HttpProxy);
    //    proxy.setUser("username");
    //    proxy.setPassword("password");
    QNetworkProxy::setApplicationProxy(proxy);

    MestreModbus m(&url);

    return a.exec();
}
