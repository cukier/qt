#ifndef A_H
#define A_H

#include <QObject>
#include <QVector>

class A
{

public:
    A();

    void setNome(const QString nome);
    QString getNome(const int index) const;
    qint8 getId() const;
    void setId(const qint16 id);
    void addItem(const int item);
    int getItem(const int index) const;
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QString nome;
    qint16 id;
    QVector<int> tabela;
};

#endif // A_H
