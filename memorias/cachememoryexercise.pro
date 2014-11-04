#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T19:12:40
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
QMAKE_CXX = clang++
QMAKE_CXXFLAGS += -std=c++11

TARGET = cachememoryexercise
TEMPLATE = app


SOURCES += main.cpp\
        cachegui.cpp \
    qcustomplot.cpp

HEADERS  += cachegui.h \
    qcustomplot.h

FORMS    += cachegui.ui
