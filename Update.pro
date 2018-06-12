#-------------------------------------------------
#
# Project created by QtCreator 2018-05-24T19:33:15
#
#-------------------------------------------------

QT       += core gui
QT       += winextras
LIBS     += -lgdi32

VERSION  = 1.0.0

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
    destinationitem.cpp \
    settings.cpp \
    copyfiles.cpp \
    filecopyitem.cpp \
    checkbox.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    loadfilewidget.h \
    filelist.h \
    pushbutton.h \
    destinationwidget.h \
    destinationlist.h \
    popupnewdestination.h \
    destinationitem.h \
    settings.h \
    copyfiles.h \
    filecopyitem.h \
    define.h \
    checkbox.h \
    about.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
