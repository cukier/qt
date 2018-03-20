#include "myloginform.h"
#include "ui_myloginform.h"

MyLoginForm::MyLoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyLoginForm)
{
    ui->setupUi(this);
}

MyLoginForm::~MyLoginForm()
{
    delete ui;
}
