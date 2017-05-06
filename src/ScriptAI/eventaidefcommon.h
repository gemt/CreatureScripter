#ifndef EVENTAIDEFCOMMON_H
#define EVENTAIDEFCOMMON_H

#include <QVector>
#include <QString>

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

struct TypeValue{
    int value;
    QString name;
    QString description;
};

struct EventAI_event {
    quint8 id;
    //QString name;
    QString shortName;
    QString description;
    //QString triggerNote;
    QVector<Parameter> params;

    static const Parameter phaseMask;
    static const Parameter eventFlags;
};

static const QString phase_mask_tooltip =
    "Phase mask is a bitmask of phases which shouldn't trigger this event. (ie. Phase mask of value 12 (binary 1100)<br>"
    " results in triggering this event in phases 0, 1 and all others with exception for phases 2 and 3 (counting from 0).<br>"
    " Phase 0 is default so this will occur in all phases unless specified. (1101 = Triggers in Phase 1 of 3, 1011 = Triggers<br>"
    " in Phase 2 of 3, 0111 = Triggers in Phase 3 of 3, 0011 = Triggers in Both Phase 2 and 3).<br>"
    " Take Desired Binary Configuration and convert into Decimal and this is your event_inverse_phase_mask to use in your script.<br>";

static const QString short_phasemask_tooltip =
        "<b>The phase mask decides in which phases this event will trigger."
        " In any phase which is checked, the event will be active. You do not"
        " need to uncheck phases which are not in use. In fact, it works as an"
        " inverse phase-mask in the core, meaning you need to uncheck phases where"
        " the event should NOT be active.";


}


#endif // EVENTAIDEFCOMMON_H
