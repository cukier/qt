//http://doc.qt.io/qt-5/qtcore-json-savegame-example.html

#include "a.h"

#include <QDebug>
#include <QJsonObject>

A::A()
{
}

void A::setNome(const QString nome)
{
    this->nome = nome;
}

qint8 A::getId() const
{
    return this->id;
}

void A::setId(const qint16 id)
{
    this->id = id;
}

void A::addItem(const int item)
{
    this->tabela.push_back(item);
}

int A::getItem(const int index) const
{
    if (this->tabela.isEmpty())
        return -1;
    else
        return this->tabela[index];
}

void A::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        this->nome = json["name"].toString();

    if (json.contains("id") && json["id"].isString())
        this->id = json["id"].toInt();
}

void A::write(QJsonObject &json) const
{
    json["name"] = this->nome;
    json["id"] = this->id;
}
