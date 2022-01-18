#include <QApplication>
#include <QWidget>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow window;

    window.setFixedSize(500,450);
    window.setWindowTitle("Timer Application");
    window.show();

    return a.exec();
}
