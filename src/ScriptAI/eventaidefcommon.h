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
    ITEM_ID = 37, // Make sure whatever widget this gets allows value 0
    LEVEL = 38,
    HOLLYDAY_ID = 39,
    GENDER = 40,
    DEAD_GRP = 41,
    WAYPOINT_ID = 42,
    ELG = 43, // exact, <= or >
    EFFECT_INDEX = 44, //DBCEnums.h SpellEffectIndex
    REPUTATION_RANK = 45,
    SKILL = 46,
    SKILL_LEVEL = 47,
    RACE_MASK = 48, // XXX: Not sure if this is  an enum in core somewhere
    CLASS_MASK = 49, // ^
    AREA_FLAG = 50, // not sure what is
    ZONE_OR_MAP_ID = 51,
    COND_VAL1 = 52,
    COND_VAL2 = 53,

    //==============
    EVENT_PHASE_MASK = 100,
    EVENT_FLAGS = 101,
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

static const QVector<TypeValue> Team =
{
    TypeValue{469, "Alliance", ""},
    TypeValue{67,  "Horde", ""}
};

static const QVector<TypeValue> ReputationRank =
{
    TypeValue{0, "HATED",       ""},
    TypeValue{1, "HOSTILE",     ""},
    TypeValue{2, "UNFRIENDLY",  ""},
    TypeValue{3, "NETURAL",     ""},
    TypeValue{4, "FRIENDLY",    ""},
    TypeValue{5, "HONORED",     ""},
    TypeValue{6, "REVERED",     ""},
    TypeValue{7, "EXALTED",     ""}
};

static const QVector<TypeValue> EffectIndex =
{
    TypeValue{0, "EFFECT_INDEX_0", ""},
    TypeValue{1, "EFFECT_INDEX_1", ""},
    TypeValue{2, "EFFECT_INDEX_2", ""}
};

static const QVector<TypeValue> ExactLesserEqualGreater =
{
    TypeValue{0, "Exact", ""},
    TypeValue{1, "<=",    "Lesser or equal"},
    TypeValue{2, ">",     "Greater"}
};

static const QVector<TypeValue> DeadState =
{
    TypeValue{0, "Player dead",  "True when the player is dead"},
    TypeValue{1, "Group Dead",   "True when the player is dead. If in group, only true when entire group is dead."}
};

static const QVector<TypeValue> Genders =
{
    TypeValue{0, "Male",  ""},
    TypeValue{1, "Female",""},
    TypeValue{2, "None",  ""}
};
static const QVector<TypeValue> SpellSchoolMask =
{
    TypeValue{1,  "PHYSICAL", "Referred to as SPELL_SCHOOL_NORMAL in the core"},
    TypeValue{2,  "HOLY",   ""},
    TypeValue{4,  "FIRE",   ""},
    TypeValue{8,  "NATURE", ""},
    TypeValue{16, "FROST",  ""},
    TypeValue{32, "SHADOW", ""},
    TypeValue{64, "ARCANE", ""},
};

struct Condition{
    qint8 id;
    QString name;
    QVector<Parameter> params;
    QString description;
};

// NOTE: This is based on Elysium core. Might be different for CMangos.
static const QVector<Condition> Conditions = {
    /*
    Condition{-3,  "NOT"                            ,{{CONDITION,   "cond-id-1", ""}}, "returns !cond-id-1"},
    Condition{-2,  "OR"                             ,{{CONDITION,   "cond-id-1", ""},{CONDITION, "cond-id-2", ""},  "returns cond-id-1 OR cond-id-2"},
    Condition{-1,  "AND"                            ,{{CONDITION,   "cond-id-1", ""},{CONDITION, "cond-id-2", ""},  "returns cond-id-1 AND cond-id-2"},
   */
    Condition{ 0,  "NONE"                           ,{},
               "Always true"},
    Condition{ 1,  "AURA"                           ,{{SPELL_ID,    "spell_id", ""}, {EFFECT_INDEX, "effindex", ""}},
               "True when player has aura (spell_id) on effect_index"},
    Condition{ 2,  "ITEM"                           ,{{ITEM_ID,     "item_id", ""}, {NUMBER, "count", ""}},
               "check present req. amount items in inventory"},
    Condition{ 3,  "ITEM_EQUIPPED"                  ,{{ITEM_ID,     "item_id", ""}},
               "True when item_id is equipped"},
    Condition{ 4,  "AREAID"                         ,{{ZONE_OR_MAP_ID, "area_id", "Zone or Map ID"}, {BOOL, "bool", ""}},
               "false: in (sub)area, 1: not in (sub)area)"},
    Condition{ 5,  "REPUTATION_RANK_MIN"            ,{{FACTION_ID,  "faction_id", ""}, {REPUTATION_RANK, "min_rank", ""}},
               "True when factio_id reputation rank is minimum min_rank"},
    Condition{ 6,  "TEAM"                           ,{{TEAM,        "player_team", ""}},
               "(469 - Alliance 67 - Horde)"},
    Condition{ 7,  "SKILL"                          ,{{SKILL, "skill_id", ""}, {SKILL_LEVEL, "skill_value", ""}},
               "True when skill_id is at least skill_value"},
    Condition{ 8,  "QUESTREWARDED"                  ,{{QUEST_ID,    "quest_id", ""}},
               "True when quest_id is rewarded"},
    Condition{ 9,  "QUESTTAKEN"                     ,{{QUEST_ID,    "quest_id", ""}, {NUMBER,"0,1,2", ""}},
               "for condition true while quest active (0 any state, 1 if quest incomplete, 2 if quest completed)."},
    Condition{ 12, "ACTIVE_GAME_EVENT"              ,{{EVENT_TYPE,  "event_id", ""}},
               "True when event_id is active"}

    /*
    Condition{ 10, "AD_COMMISSION_AURA"             ,{{NUMBER, "0", ""}, {NUMBER, "0", ""}}, "for condition true while one from AD commission aura active"},
    Condition{ 11, "NO_AURA"                        ,{{SPELL_ID,    "spell_id", ""},{EFFECT_INDEX, "effindex", ""}}, "True when player does not have the given aura"},
    Condition{ 13, "AREA_FLAG"                      ,{{AREA_FLAG, "area_flag", ""},{AREA_FLAG, "area_flag_not", ""}}, ""},
    Condition{ 14, "RACE_CLASS"                     ,{{RACE_MASK, "race_mask", ""}, {CLASS_MASK, "class_mask", ""}}, ""},
    Condition{ 15, "LEVEL"                          ,{{LEVEL,       "player_level", ""}, {ELG, "Condition", "0, 1 or 2 (0: equal to, 1: equal or higher than, 2: equal or less than)"}}, ""},
    Condition{ 16, "NOITEM"                         ,{{ITEM_ID,     "item_id", ""}, {NUMBER, "Count", ""},"check not present req. amount items in inventory"},
    Condition{ 17, "SPELL"                          ,{{SPELL_ID,    "spell_id", ""}, {BOOL, "Have Spell", "True: Have spell, false: Don't have spell"}}, "Returns true when event-caller have or don't have the provided spell"},
    Condition{ 18, "INSTANCE_SCRIPT"                ,{{MAP_AREA_ID, "map_id", ""}, {NUMBER, "instance_condition_id", "(instance script specific enum)"}}, ""},
    Condition{ 19, "QUESTAVAILABLE"                 ,{{QUEST_ID,    "quest_id", ""}}, "for case when loot/gossip possible only if player can start quest"},
    Condition{ 22, "QUEST_NONE"                     ,{{QUEST_ID,    "quest_id", ""}}, "quest did not take and not rewarded"},
    Condition{ 23, "ITEM_WITH_BANK"                 ,{{ITEM_ID,     "item_id", ""}, {NUMBER, "count", ""}}, "check present req. amount items in inventory or bank"},
    Condition{ 24, "NOITEM_WITH_BANK"               ,{{ITEM_ID,     "item_id", ""}, {NUMBER, "count", ""}}, "check not present req. amount items in inventory or bank"},
    Condition{ 25, "NOT_ACTIVE_GAME_EVENT"          ,{{EVENT_TYPE,  "event_id", ""}}, ""},
    Condition{ 26, "ACTIVE_HOLIDAY"                 ,{{HOLLYDAY_ID, "holiday_id", ""}}, "preferred use instead CONDITION_ACTIVE_GAME_EVENT when possible"},
    Condition{ 27, "NOT_ACTIVE_HOLIDAY"             ,{{HOLLYDAY_ID, "holiday_id", ""}}, "preferred use instead CONDITION_NOT_ACTIVE_GAME_EVENT when possible"},
    Condition{ 28, "LEARNABLE_ABILITY"              ,{{SKILL,    "skell_id", ""}, {ITEM_ID, "item_id", ""}}, "True when player can learn ability (using min skill value from SkillLineAbility). Item_id can be defined in addition (can also be 0), to check if player has one (1) item in inventory or bank. When player has spell or has item (when defined), condition return false."},
    Condition{ 29, "CONDITION_SKILL_BELOW"          ,{{SKILL,    "skill_id", ""}, {SKILL_LEVEL, "skill_value", ""}}, "True if player has skill skill_id and skill less than (and not equal) skill_value (for skill_value > 1). If skill_value == 1, then true if player has not skill skill_id"},
    Condition{ 30, "CONDITION_REPUTATION_RANK_MAX"  ,{{FACTION_ID,  "faction_id", ""}, {REPUTATION_RANK, "max_rank", ""}}, "Returns true if the specified faction has a lower or equal reputation rank to max_rank"},
    Condition{ 32, "CONDITION_SOURCE_AURA"          ,{{SPELL_ID,    "spell_id", ""}, {EFFECT_INDEX,"effindex", ""}}, "(returns true if the source of the condition check has aura of spell_id, effIndex)"},
    Condition{ 33, "CONDITION_LAST_WAYPOINT"        ,{{WAYPOINT_ID, "waypointId" ""}, {ELG, "Condition","0 = exact, 1: wp <= waypointId, 2: wp > waypointId  Use to check what waypoint was last reached"}}, "0 = exact, 1: wp <= waypointId, 2: wp > waypointId  Use to check what waypoint was last reached"},
    Condition{ 35, "CONDITION_GENDER"               ,{{GENDER, "Gender" "enum Gender"}}},
    Condition{ 36, "CONDITION_DEAD_OR_AWAY"         ,{{DEAD_GRP,    "Dead-state", ""}, {RADIUS, "Range", ""}}, "value1: 0=player dead, 1=player is dead (with group dead), 2=player in instance are dead, 3=creature is dead value2: if != 0 only consider players in range of this value"}
*/
    };
        //Condition{ 20, "RESERVED_1"                     ,{{"reserved for        3.x and later
        //Condition{ 21, "RESERVED_2"                     ,{{"reserved for        3.x and later
        //Condition{ 31, "CONDITION_RESERVED_3"           ,{{"reserved for"        3.x and later
        //Condition{ 34, "CONDITION_RESERVED_4"           ,{{"reserved for"        3.x and later

static const Condition& GetCondition(int num){
    // Will be the case for all except num==12 atm
    if(Conditions.size() >= num && Conditions.at(num).id == num)
        return Conditions.at(num);

    // sucks, but quickfix for num==12
    for(int i = 0; i < Conditions.size(); i++){
        if(Conditions.at(i).id == num)
            return Conditions.at(i);
    }
}
} // EventAI

#endif // EVENTAIDEFCOMMON_H
