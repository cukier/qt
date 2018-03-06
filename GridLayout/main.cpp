#include <QApplication>
#include "janelaprincipal.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    JanelaPrincipal w;

    w.show();

    return app.exec();
}
