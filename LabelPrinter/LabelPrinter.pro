#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T14:47:46
#
#-------------------------------------------------

QT       += core gui    \
            printsupport \
            xml \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += C:\Qt\Tools\mingw530_32\i686-w64-mingw32\lib\libwinspool.a \

TARGET = ZebraPrinter
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
        mainwindow.cpp \
        View/worksheet.cpp \
        Component/Printer/printer.cpp \
        View/Dialog/correctiondialog.cpp \
        Component/Xml/xml.cpp \
        View/Dialog/verdialog.cpp \
        View/Dialog/successdialog.cpp

HEADERS += \
        mainwindow.h \
        stylesheet.h \
        global.h \
        View/worksheet.h \
        Component/Printer/printer.h \
        View/Dialog/correctiondialog.h \
        Component/Xml/xml.h \
        View/Dialog/verdialog.h \
        View/Dialog/successdialog.h

win32:RC_FILE += label.rc

RESOURCES += \
    resources.qrc
