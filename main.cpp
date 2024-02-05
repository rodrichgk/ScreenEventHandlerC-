#include "MainWindow.h"
#include "SignalManager.h"
#include <QApplication>
#include <QProcess>
#include <iostream>
#include <csignal>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    window.show();

    return app.exec();
}
