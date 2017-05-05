#ifndef EVENTAIDEF_H
#define EVENTAIDEF_H

#define ELYSIUM
#undef CMANGOS

#ifdef ELYSIUM
#include "eventaidefelysium.h"
#else
#include "eventaidefcmangos.h"
#endif

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
namespace EventAI
{
enum ParameterType{
    PT_MIN = -1,
    UNUSED = 0,
    // decides the returned widget-type
    MILLISECONDS = 1,
    PERCENTAGE = 2,
    SPELL_ID = 3,
    SPELL_SCHOOL = 4,
    DISTANCE = 5,
    BOOL = 6,
    HP = 7,
    NUMBER = 8,
    EMOTE_ID = 9,
    EVENT_TYPE = 10,
    DISPELL_TYPE = 11,
    CREATURE_ID = 12,
    CONDITION = 13,
    TEXT_ID = 14,
    FACTION_ID = 15,
    FACTION_ID_FLAGS = 16,
    MODEL_ID = 17,
    SOUND_ID = 18,
    TARGET = 19, // valid entries are in TargetTypes enum
    CAST_FLAGS = 20, // valid entries are in CastFlags enum
    QUEST_ID = 21,
    FLAGS_GENERIC = 22,
    PHASE = 23, // must validate to number between 0,31
    ANGLE = 24,
    SUMMON_ID = 25,
    TEAM = 26, // alliance/horde
    CREATURE_TEMPLATE_ID = 27,
    RADIUS = 28,
    SHEET = 29,
    CHANCE = 30,
    EVENT_TYPE_MASK = 31,
    STAND_STATE = 32,
    MOVEMENT_TYPE = 33,
    REACT_STATE = 34,
    SPAWN_EVENT_MODE = 35,
    MAP_AREA_ID = 36,

    //==============
    EVENT_PHASE_MASK = 50,
    EVENT_FLAGS = 51,
    PT_UNKNOWN
};

struct Parameter{
    ParameterType type;
    QString name;
    QString description;
};

struct EventAI_Action{
    int id;
    QString name;
    QString shortName;
    QString description;
    QVector<Parameter> params;
};

struct EventAI_event{
    EventAI_event(){
        params.push_back({ParameterType::EVENT_PHASE_MASK, "Phase Mask", phase_mask_tooltip});
        params.push_back({ParameterType::EVENT_FLAGS, "Event Flags", ""});
    }

    quint8 id;
    QString name;
    QString shortName;
    QString description;
    QString triggerNote;
    QVector<Parameter> params;
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
    const QMap<int,EventAI_Action>& Actions();
private:
    EventAIStorage();
    QMap<QString,QString> keywords;
    QMap<int, EventAI_event> events;
    QMap<int, EventAI_Action> actions;

    void LoadEvents();
    void LoadActions();
};

}

#endif // EVENTAIDEF_H
