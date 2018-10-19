#-------------------------------------------------
#
# Project created by QtCreator 2018-05-24T19:33:15
#
#-------------------------------------------------

QT       += core gui
QT       += winextras
QT       += concurrent
LIBS     += -lgdi32

VERSION  = 1.5.0

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
    about.cpp \
    threadcopy.cpp \
    missingfiles.cpp \
    missingfileitem.cpp \
    copyinfomation.cpp \
    preferences.cpp \
    preferencetab.cpp \
    listviewpreference.cpp \
    logs.cpp \
    pingpc.cpp

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
    about.h \
    threadcopy.h \
    missingfiles.h \
    missingfileitem.h \
    copyinfomation.h \
    preferences.h \
    preferencetab.h \
    listviewpreference.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc

RC_FILE = myapp.rc
