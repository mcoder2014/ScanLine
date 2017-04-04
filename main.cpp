#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./glutdlls37beta");      // 搜寻dll路径

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
