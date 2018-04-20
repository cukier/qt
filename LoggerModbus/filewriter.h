#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QObject>
#include <QFile>

class FileWriter : public QObject
{
    Q_OBJECT
public:
    explicit FileWriter(QObject *parent = nullptr);

public slots:
    void salvar(quint16 addr, QVector<quint16> dado);

signals:

public slots:

private:
    QFile *file;
    QString file_path;
};

#endif // FILEWRITER_H
