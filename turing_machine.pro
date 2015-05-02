#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T22:35:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = turing_machine
TEMPLATE = app


SOURCES += main.cpp\
        cmainwindow.cpp \
    cmachine.cpp \
    qcodeedit.cpp \
    qlinenumberarea.cpp

HEADERS  += cmainwindow.h \
    cmachine.h \
    qcodeedit.h \
    qlinenumberarea.h

FORMS    += cmainwindow.ui
