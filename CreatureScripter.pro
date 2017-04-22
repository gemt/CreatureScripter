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
    creature.cpp \
    cache.cpp \
    creaturetemplateraw.cpp \
    creatureaiscriptsraw.cpp \
    dbconnectionsettings.cpp \
    scriptaitab.cpp \
    eventaidef.cpp \
    creaturesearcher.cpp \
    creaturetables.cpp

HEADERS  += mainwindow.h \
    config.h \
    warnings.h \
    worktabs.h \
    creature.h \
    cache.h \
    creaturetemplateraw.h \
    creatureaiscriptsraw.h \
    dbconnectionsettings.h \
    scriptaitab.h \
    eventaidef.h \
    timer.h \
    creaturesearcher.h \
    creaturetables.h

RESOURCES += \
    icons.qrc
