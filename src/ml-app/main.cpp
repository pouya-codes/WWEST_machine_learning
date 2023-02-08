#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow wndw_main;
    wndw_main.show();

    return a.exec();
}
