#include "calculadora.h"
#include "ui_calculadora.h"

Calculadora::Calculadora(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculadora)
{
    ui->setupUi(this);
}

Calculadora::~Calculadora()
{
    delete ui;
}

void Calculadora::on_pushButtonMais_clicked()
{

}

void Calculadora::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{

}
