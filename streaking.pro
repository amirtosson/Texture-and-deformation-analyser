#-------------------------------------------------
#
# Project created by QtCreator 2018-11-17T20:07:09
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = streaking
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    my_q.cpp \
    qcustomplot.cpp \
    baseclass.cpp \
    rings.cpp

HEADERS  += dialog.h \
    my_q.h \
    qcustomplot.h \
    pixel.h \
    baseclass.h \
    rings.h

FORMS    += dialog.ui
