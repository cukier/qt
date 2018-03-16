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
    url.setHost("192.168.0.110");
    //    url.setHost("127.0.0.1");
    //    url.setUserName("USER");
    //    url.setPassword("USER");

    QNetworkProxyQuery npq(url);
    QList<QNetworkProxy> listOfProxies = QNetworkProxyFactory::systemProxyForQuery(npq);
    QNetworkProxy proxy;

    if (listOfProxies.size())
    {
        proxy.setHostName(listOfProxies[0].hostName());
        proxy.setPort(listOfProxies[0].port());
        //        proxy.setUser("username");
        //        proxy.setPassword("password");
    }

    if (!proxy.hostName().isEmpty())
    {
        qDebug() << "Encontrado proxy "
                 << proxy.hostName()
                 << " @ " << proxy.port();
    }
    proxy.setType(QNetworkProxy::NoProxy);
    QNetworkProxy::setApplicationProxy(proxy);
    //        QNetworkProxyFactory::setUseSystemConfiguration(true);

    MestreModbus m(&url);

    m.setObjectName("Mestre Modbus");

    QObject::connect(&m, &MestreModbus::mapaChanged, [&m](){
       qDebug() << "O mapa mudou" << m.objectName();
    });

    return a.exec();
}

