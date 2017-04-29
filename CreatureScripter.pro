#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T15:03:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql gui

TARGET = CreatureScripter
TEMPLATE = app

CONFIG += c++14

INCLUDEPATH += src/ \
src/CreatureTabs/



HEADERS += $$files(src/*.h) \
    src/migration.h \
    src/CreatureTabs/templatetables.h \
    src/mangosrecord.h \
    src/mangoscreature.h \
    src/tables.h \
    src/CreatureTabs/creatureeventai.h \
    src/eventwidgetclasses.h
HEADERS += $$files(src/CreatureTabs/*.h)

SOURCES += $$files(src/*.cpp) \
    src/migration.cpp \
    src/CreatureTabs/templatetables.cpp \
    src/mangosrecord.cpp \
    src/mangoscreature.cpp \
    src/tables.cpp \
    src/CreatureTabs/creatureeventai.cpp \
    src/eventwidgetclasses.cpp
SOURCES += $$files(src/CreatureTabs/*.cpp)

RESOURCES += \
    icons.qrc \
    css.qrc \
    json.qrc

FORMS += $$files(src/CreatureTabs/*.ui)
