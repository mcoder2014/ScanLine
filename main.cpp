#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./glutdlls37beta");      // 搜寻dll路径
    QApplication a(argc, argv);

    QTextCodec * textCodec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(textCodec);

    QTranslator translator;                             // 翻译工具
    if(translator.load(":/translator/app_zh_CN.qm"))
    {
        a.installTranslator(&translator);
        qDebug("文件加载成功");
    }
    else
    {
            qDebug("文件加载失效");
    }


    QTranslator qtGloble;
    if(qtGloble.load(":/translator/qt_zh_CN.qm"))
    {
        a.installTranslator(&qtGloble);
        qDebug("文件加载成功");
    }
    else
    {
        qDebug("文件加载失败");
    }

    MainWindow w;
    w.show();

    return a.exec();
}
