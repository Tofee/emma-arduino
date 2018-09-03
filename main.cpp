#include "mainwindow.h"
#include "arduino.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Arduino myArduino(&w);
    myArduino.setup();

    return a.exec();
}
