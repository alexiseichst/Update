#-------------------------------------------------
#
# Project created by QtCreator 2018-05-24T19:33:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Update
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loadfilewidget.cpp \
    filelist.cpp \
    pushbutton.cpp \
    destinationwidget.cpp \
    destinationlist.cpp \
    popupnewdestination.cpp \
    destinationitem.cpp

HEADERS  += mainwindow.h \
    loadfilewidget.h \
    filelist.h \
    pushbutton.h \
    destinationwidget.h \
    destinationlist.h \
    popupnewdestination.h \
    destinationitem.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
