#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    bool begin = false;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
