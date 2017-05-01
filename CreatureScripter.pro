#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T15:03:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql gui xml

TARGET = CreatureScripter
TEMPLATE = app
DEFINES += __STORMLIB_SELF__ QSW_LIB
CONFIG += c++14

RESOURCES += \
    icons.qrc \
    css.qrc \
    json.qrc

INCLUDEPATH += src/ \
src/CreatureTabs/ \
src/ScriptAI/ \
src/ScriptAI/widgets/ \
QSpellWork/QSW/ \

HEADERS += $$files(src/*.h)
HEADERS += $$files(src/CreatureTabs/*.h)
HEADERS += $$files(src/ScriptAI/*.h)
HEADERS += $$files(src/ScriptAI/widgets/*.h)

SOURCES += $$files(src/*.cpp)
SOURCES += $$files(src/CreatureTabs/*.cpp)
SOURCES += $$files(src/ScriptAI/*.cpp)
SOURCES += $$files(src/ScriptAI/widgets/*.cpp)



HEADERS += QSpellWork/QSW/qsw.h \
           QSpellWork/QSW/qsw_export.h \
           QSpellWork/QSW/blp/blp.h \
           QSpellWork/QSW/dbc/DBC.h \
           QSpellWork/QSW/mpq/MPQ.h \
           QSpellWork/QSW/wov/texture.h \
           QSpellWork/QSW/plugins/spellinfo/pre-tbc/spellinfo.h \
           QSpellWork/QSW/plugins/spellinfo/pre-tbc/structure.h

SOURCES += QSpellWork/QSW/qsw.cpp \
           QSpellWork/QSW/blp/blp.cpp \
           QSpellWork/QSW/dbc/DBC.cpp \
           QSpellWork/QSW/mpq/MPQ.cpp \
           QSpellWork/QSW/wov/texture.cpp \
           QSpellWork/QSW/plugins/spellinfo/pre-tbc/spellinfo.cpp \
           QSpellWork/QSW/plugins/spellinfo/pre-tbc/structure.cpp \


#CONFIG += debug_and_release

#QSW:

INCLUDEPATH += $$PWD/QSpellWork/QSW/mpq/StormLib
DEPENDPATH += $$PWD/QSpellWork/QSW/mpq/StormLib
#====

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/QSpellWork/QSW/mpq/StormLib/x64/Release/ -lStormLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/QSpellWork/QSW/mpq/StormLib/x64/Debug/ -lStormLib
message($$LIBS)
#INCLUDEPATH += $$PWD/QSpellWork/QSW/mpq/StormLib/x64/Debug
#DEPENDPATH += $$PWD/QSpellWork/QSW/mpq/StormLib/x64/Debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/QSpellWork/QSW/blp/squish/x64/Release/ -lsquish
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/QSpellWork/QSW/blp/squish/x64/Debug/ -lsquish

INCLUDEPATH += $$PWD/QSpellWork/QSW/blp/squish/x64/Debug
DEPENDPATH += $$PWD/QSpellWork/QSW/blp/squish/x64/Debug
