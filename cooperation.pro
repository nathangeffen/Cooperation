#-------------------------------------------------
#
# Project created by QtCreator 2012-01-22T18:01:22
#
#-------------------------------------------------

QT       += core

QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

TARGET = cooperation
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    competitor.cpp

HEADERS += \
    game.h \
    competitor.h
