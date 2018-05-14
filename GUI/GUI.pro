#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T10:30:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    DendogramView.cpp

HEADERS += \
        MainWindow.h \
    DendogramView.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DivisiveClusteringLib/release/ -lDivisiveClusteringLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DivisiveClusteringLib/debug/ -lDivisiveClusteringLib
else:unix: LIBS += -L$$OUT_PWD/../DivisiveClusteringLib/ -lDivisiveClusteringLib

INCLUDEPATH += $$PWD/../DivisiveClusteringLib
DEPENDPATH += $$PWD/../DivisiveClusteringLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DivisiveClusteringLib/release/libDivisiveClusteringLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DivisiveClusteringLib/debug/libDivisiveClusteringLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DivisiveClusteringLib/release/DivisiveClusteringLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DivisiveClusteringLib/debug/DivisiveClusteringLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../DivisiveClusteringLib/libDivisiveClusteringLib.a
