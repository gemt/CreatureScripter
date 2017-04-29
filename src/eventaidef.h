#ifndef EVENTAIDEF_H
#define EVENTAIDEF_H

/*
 * Remember:
 * on using spellID, set spellSchool to 0
 * on using spellSchoo, set spellId to -1
 *
 * Pickup spell schools directly from file, cba putting in json
 * (Name ==> School ==> School Bitmask Values)
    -------------------------------------------
    SPELL_SCHOOL_NORMAL = 0 ==> 1
    SPELL_SCHOOL_HOLY   = 1 ==> 2
    SPELL_SCHOOL_FIRE   = 2 ==> 4
    SPELL_SCHOOL_NATURE = 3 ==> 8
    SPELL_SCHOOL_FROST  = 4 ==> 16
    SPELL_SCHOOL_SHADOW = 5 ==> 32
    SPELL_SCHOOL_ARCANE = 6 ==> 64
    Use These Bitmask Values For Schoolmask (Param2) or Any Combinations Of These School Bitmasks for Multiple Schools.
 *
 *
 * DispellType requires some bitmask thing
 *
 * an event can be without 't'
 *
 * EVENT_T_RECEIVE_EMOTE needs customizing
 *
 * EVENT_T_TARGET_BUFFED defines some enum stuff, look at it.
 *
 */

#include <QVector>
#include <QMap>
namespace EventAI{

struct event_param{
    QString identifier;
    QString name;
    QString description;
    QString triggerNote;
};

struct EventAI_event{
    quint8 id;
    QString name;
    QString description;
    QVector<event_param> params;
};

class EventAIStorage
{
public:
    static EventAIStorage& Get(){
        static EventAIStorage* instance = nullptr;
        if(!instance)
            instance = new EventAIStorage();
        return *instance;
    }


private:
    EventAIStorage();
    QVector<event_param> event_paramTypes;
    QMap<QString,QString> keywords;
};

}

#endif // EVENTAIDEF_H
