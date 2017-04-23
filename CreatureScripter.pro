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

INCLUDEPATH += src/ \
src/CreatureTabs/



HEADERS += $$files(src/*.h) \
    src/migration.h \
    src/CreatureTabs/templatetables.h \
    src/mangosrecord.h \
    src/mangoscreature.h
HEADERS += $$files(src/CreatureTabs/*.h)

SOURCES += $$files(src/*.cpp) \
    src/migration.cpp \
    src/CreatureTabs/templatetables.cpp \
    src/mangosrecord.cpp \
    src/mangoscreature.cpp
SOURCES += $$files(src/CreatureTabs/*.cpp)

RESOURCES += \
    icons.qrc \
    css.qrc

FORMS += $$files(src/CreatureTabs/*.ui)
