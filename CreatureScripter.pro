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

RESOURCES += \
    icons.qrc \
    css.qrc \
    json.qrc

INCLUDEPATH += src/ \
src/CreatureTabs/ \
src/ScriptAI/ \
src/ScriptAI/widgets/


HEADERS += $$files(src/*.h) \
    src/ScriptAI/widgets/defaultlineedit.h
HEADERS += $$files(src/CreatureTabs/*.h)
HEADERS += $$files(src/ScriptAI/*.h)
HEADERS += $$files(src/ScriptAI/widgets/*.h)

SOURCES += $$files(src/*.cpp) \
    src/ScriptAI/widgets/defaultlineedit.cpp
SOURCES += $$files(src/CreatureTabs/*.cpp)
SOURCES += $$files(src/ScriptAI/*.cpp)
SOURCES += $$files(src/ScriptAI/widgets/*.cpp)
