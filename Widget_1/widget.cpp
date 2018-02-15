#include "widget.h"
#include "ui_widget.h"

#include <QPlainTextEdit>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->plainTextEdit,
            SIGNAL(textChanged()),
            this,
            SLOT(on_plainTextEdit_textChanged()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_plainTextEdit_textChanged()
{
    ui->label->setText(ui->plainTextEdit->toPlainText());
}
