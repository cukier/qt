#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <QMainWindow>

namespace Ui {
class Calculadora;
}

class Calculadora : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculadora(QWidget *parent = 0);
    ~Calculadora();

private slots:
    void on_pushButtonMais_clicked();

    void on_label_linkActivated(const QString &link);

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::Calculadora *ui;
};

#endif // CALCULADORA_H
