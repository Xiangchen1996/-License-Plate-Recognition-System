#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T21:55:28
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = new_send
TEMPLATE = app


SOURCES += main.cpp\
    maindialog.cpp \
    rotatedialog.cpp \
    addportdialog.cpp \
    logindialog.cpp \
    jsonwrapper.cpp \
    jsonparser.cpp \
    umethod.cpp \
    sendpicthread.cpp \
    messagebox.cpp \
    iconhelper.cpp

HEADERS  += \
    maindialog.h \
    rotatedialog.h \
    addportdialog.h \
    logindialog.h \
    jsonwrapper.h \
    jsonparser.h \
    umethod.h \
    sendpicthread.h \
    messagebox.h \
    iconhelper.h

FORMS    += \
    maindialog.ui \
    addportdialog.ui \
    logindialog.ui

RESOURCES += \
    resource.qrc \
    iconimg.qrc

DISTFILES += \
    resource/3.jpg
