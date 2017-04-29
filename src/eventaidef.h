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

struct event_param {
    enum Type{TYPE_MIN,
              ms = 1,
              pct = 2,
              SpellId = 3,
              SpellSchool = 4,
              dist = 5,
              _bool = 6,
              hp = 7,
              num = 8,
              EmoteId = 9,
              EventEntry = 10,
              DispellType = 11,
              CreatureID = 12,
              Condition = 13,
              UNKNOWN
             };
    Type type;
    QString name;
    QString description;
};

struct EventAI_event{
    quint8 id;
    QString name;
    QString description;
    QString triggerNote;
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

    const QMap<int,EventAI_event>& Events();

private:
    EventAIStorage();
    QMap<QString,QString> keywords;
    QMap<QString,event_param> event_paramTypes_map;
    QMap<int, EventAI_event> events;
};

}

#endif // EVENTAIDEF_H
