#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T15:03:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql gui

TARGET = CreatureScripter
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    warnings.cpp \
    worktabs.cpp \
    creaturecache.cpp \
    creature.cpp

HEADERS  += mainwindow.h \
    config.h \
    warnings.h \
    worktabs.h \
    creaturecache.h \
    creature.h
