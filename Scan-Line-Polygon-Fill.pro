#-------------------------------------------------
#
# Project created by QtCreator 2017-04-03T18:45:57
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scan_Line_Polygon_Fill_Algorithm
TEMPLATE = app

CONFIG += warn_on qt        # warn_on 尽可能多的显示编译信息


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    customwidget.cpp \
    Figure\Point.cpp \
    Figure\Edge.cpp \
    Figure\Polygon.cpp

HEADERS  += mainwindow.h \
    customwidget.h \
    Figure\Point.h \
    Figure\Edge.h \
    Figure\Polygon.h

INCLUDEPATH += $$PWD/glutdlls37beta
# $$PWD 当前工作路径 代表.pro 所在文件夹

LIBS += $$PWD/glutdlls37beta/glut.lib \
        $$PWD/glutdlls37beta/glut32.lib

DESTDIR = ./bin     # 生成文件在这
MOC_DIR = ./moc     # Q_OBJECT 类转换后的文件
RCC_DIR = ./rcc     # .qrc 文件转换后存放路径
OBJECTS_DIR += ./tmp   # .obj 文件存放路径

RESOURCES += \
    icon.qrc

RC_ICONS = $$PWD/source/icon.ico
