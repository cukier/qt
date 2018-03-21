#include "widget.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QMessageBox::critical(nullptr,
                          "Title",
                          "Message");

    return a.exec();
}
