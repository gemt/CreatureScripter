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
enum ParameterType{
    PT_MIN,
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
    PT_UNKNOWN
};
struct Parameter{
    ParameterType type;
};

enum ActionParamTypes{
    A_TYPE_MIN,
    TEXT_ID = 1,

    MODEL_ID = 1,
    QUEST_ID = 2,
    REACT_STATE = 3,
    MOVEMENT_TYPE = 4,
    A_TEXT_ID = 5,
    FACTION_FLAGS = 6,
    FACTION_ID = 7,
    A_UNKNOWN
};

struct FactionFlag{
    int num;
    QString name;
    QString description;
};

static QVector<FactionFlag> factionFlags = {
    FactionFlag{0x00, "TEMPFACTION_NONE", "A persistent faction change and will require manual change to default/another faction when changed once"},
    FactionFlag{0x01, "TEMPFACTION_RESTORE_RESPAWN", "Default faction will be restored at respawn"},
    FactionFlag{0x02, "TEMPFACTION_RESTORE_COMBAT_STOP", "... at CombatStop() (happens at creature death, at evade or custom scripte among others)"},
    FactionFlag{0x04, "TEMPFACTION_RESTORE_REACH_HOME", "... at reaching home in home movement (evade), if not already done at CombatStop()"}
};

struct action_param{
    ActionParamTypes type;
    QString name;
    QString description;
};

struct event_action{
    int id;
    QString name;
    QString description;
    QVector<action_param> params;
};

struct event_param {
    ParameterType type;
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
    const QMap<int,event_action>& Actions();
private:
    EventAIStorage();
    QMap<QString,QString> keywords;
    QMap<QString,event_param> event_paramTypes_map;
    QMap<int, EventAI_event> events;
    QMap<int, event_action> actions;

    void LoadEvents();
    void LoadActions();
};

}

#endif // EVENTAIDEF_H
