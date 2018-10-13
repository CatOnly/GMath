#include "MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include "SFLTest.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);

    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();

    testMain();

    return a.exec();
}
