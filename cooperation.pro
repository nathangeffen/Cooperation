#-------------------------------------------------
#
# Project created by QtCreator 2012-01-22T18:01:22
#
#-------------------------------------------------

QT       += core

QMAKE_CXXFLAGS += -std=c++0x

#QMAKE_CFLAGS+=-pg
#QMAKE_CXXFLAGS+=-pg
#QMAKE_LFLAGS+=-pg

TARGET = cooperation
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
RESOURCES = application.qrc

unix:LIBS += -L/usr/lib -lboost_program_options

SOURCES += main.cpp \
    game/game.cpp \
    game/competitor.cpp \
    game/common.cpp \
    gui.cpp \
    competitorwidget.cpp \
    guiplay.cpp \
    competitorshape.cpp \
    mainwindow.cpp \
    definegamedialog.cpp

HEADERS += \
    game/game.h \
    game/competitor.h \
    game/common.h \
    gui.h \
    competitorwidget.h \
    guiplay.h \
    competitorshape.h \
    mainwindow.h \
    definegamedialog.h \
    guicommon.h

CONFIG += debug_and_release

 CONFIG(debug, debug|release) {
     TARGET = cooperation_debug
 } else {
     TARGET = cooperation
 }
