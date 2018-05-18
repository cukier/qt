#include "radiodialog.h"
#include "ui_radiodialog.h"

RadioDialog::RadioDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadioDialog)
{
    ui->setupUi(this);
}

RadioDialog::~RadioDialog()
{
    delete ui;
}

RadioDialog::RadioSettings RadioDialog::settings() const
{
    return m_settings;
}

void RadioDialog::setSettings(const RadioSettings &settings)
{
    m_settings = settings;
}
