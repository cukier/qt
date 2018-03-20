#ifndef MYLOGINFORM_H
#define MYLOGINFORM_H

#include <QWidget>

namespace Ui {
class MyLoginForm;
}

class MyLoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit MyLoginForm(QWidget *parent = 0);
    ~MyLoginForm();

private:
    Ui::MyLoginForm *ui;
};

#endif // MYLOGINFORM_H
