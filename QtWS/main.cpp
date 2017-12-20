#include <QApplication>
#include <QDesktopWidget>
#include <QDir>

#include "httpwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HttpWindow httpWin;
    const QRect availableSize = QApplication::desktop()->availableGeometry(&httpWin);
    httpWin.resize(availableSize.width() / 5, availableSize.height() / 5);
    httpWin.move((availableSize.width() - httpWin.width()) / 2, (availableSize.height() - httpWin.height()) / 2);

    httpWin.show();
    return app.exec();
}
