#-------------------------------------------------
#
# Project created by QtCreator 2013-12-01T11:12:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dsp
TEMPLATE = app

CONFIG += qwt

LIBS += -lsfml-system -lsfml-audio -lOoura_fft -lAquila
QMAKE_CXXFLAGS = -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    ../aquila-src/lib/ooura/fft4g.c \
    signal.cpp \
    customwindow.cpp

HEADERS  += mainwindow.h \
    signal.hpp \
    customwindow.hpp

FORMS    += mainwindow.ui
