#-------------------------------------------------
#
# Project created by QtCreator 2012-01-22T18:01:22
#
#-------------------------------------------------

QT       += core

QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

#QMAKE_CFLAGS+=-pg
#QMAKE_CXXFLAGS+=-pg
#QMAKE_LFLAGS+=-pg

TARGET = cooperation
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix:LIBS += -L/usr/lib -lboost_program_options

SOURCES += main.cpp \
    game.cpp \
    competitor.cpp \
    common.cpp

HEADERS += \
    game.h \
    competitor.h \
    common.h

CONFIG += debug_and_release

 CONFIG(debug, debug|release) {
     TARGET = debug_binary
 } else {
     TARGET = release_binary
 }
