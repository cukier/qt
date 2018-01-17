#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPushButton>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addButton(ui, 0);
    addButton(ui, 1);
    addButton(ui, 2);
    addButton(ui, 3);

    QSize availableSize = qApp->desktop()->availableGeometry().size();
    int width = availableSize.width();
    int height = availableSize.height();
    qDebug() << "Available dimensions " << width << "x" << height;
    width *= 0.9; // 90% of the screen size
    height *= 0.8; // 90% of the screen size
    qDebug() << "Computed dimensions " << width << "x" << height;

    QSize newSize( width, height );

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            newSize,
            qApp->desktop()->availableGeometry()
        )
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addButton(Ui::MainWindow *ui, int nr)
{
    QPushButton *pushButton = new QPushButton(ui->centralWidget);
    QString n_str = "pushButton" + QString::number(nr);
    pushButton->setObjectName(n_str);
//    pushButton->setMinimumSize(QSize(50, 50));
//    pushButton->setMaximumSize(QSize(50, 50));

    QIcon icon;

    if (nr == 0)
        icon.addFile(QStringLiteral(":/ico/t1.png"), QSize(), QIcon::Normal, QIcon::Off);
    else if (nr == 1)
        icon.addFile(QStringLiteral(":/ico/t2.png"), QSize(), QIcon::Normal, QIcon::Off);
    else if (nr == 2)
        icon.addFile(QStringLiteral(":/ico/t3.png"), QSize(), QIcon::Normal, QIcon::Off);
    else if (nr == 3)
        icon.addFile(QStringLiteral(":/ico/t4.png"), QSize(), QIcon::Normal, QIcon::Off);

    pushButton->setIcon(icon);
    pushButton->setIconSize(QSize(64, 64));

    if (nr == 0)
        ui->gridLayout->addWidget(pushButton, 0, 0, 1, 1);
    else if (nr == 1)
        ui->gridLayout->addWidget(pushButton, 0, 1, 1, 1);
    else if (nr == 2)
        ui->gridLayout->addWidget(pushButton, 1, 0, 1, 1);
    else if (nr == 3)
        ui->gridLayout->addWidget(pushButton, 1, 1, 1, 1);


}
