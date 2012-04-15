#-------------------------------------------------
#
# Project created by QtCreator 2012-04-15T19:57:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app


SOURCES += main.cpp\
        mainform.cpp \
    exampletempateserrialization.cpp

HEADERS  += mainform.h \
    exampletempateserrialization.h

FORMS    += mainform.ui
include("../mt/mt.pri")
