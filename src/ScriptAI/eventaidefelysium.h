#ifndef EVENTAIDEFELYSIUM_H
#define EVENTAIDEFELYSIUM_H

#include <QVector>
#include <QMap>

#include "eventaidefcommon.h"

namespace EventAI
{

static const QVector<TypeValue> SheetState =
{
    TypeValue{0, "No Weapon", "Sheets the weapons of the creature"},
    TypeValue{1, "Melee Weapon", "Unsheets the melee weapons of the creature"},
    TypeValue{2, "Ranged Weapon", "Unsheets the ranged weapon of the creature"}
};

// used by ParameterType::TARGET (19)
static const QVector<TypeValue> TargetTypes =
{
TypeValue{0,  /*TARGET_T_*/"SELF",                                          "Self cast"},
TypeValue{1,  /*TARGET_T_*/"HOSTILE",                                       "Our current target (ie: highest aggro)"},
TypeValue{2,  /*TARGET_T_*/"HOSTILE_SECOND_AGGRO",                          "Second highest aggro (generaly used for cleaves and some special attacks)"},
TypeValue{3,  /*TARGET_T_*/"HOSTILE_LAST_AGGRO",                            "Dead last on aggro (no idea what this could be used for)"},
TypeValue{4,  /*TARGET_T_*/"HOSTILE_RANDOM",                                "Just any random target on our threat list"},
TypeValue{5,  /*TARGET_T_*/"HOSTILE_RANDOM_NOT_TOP",                        "Any random target except top threat"},
TypeValue{6,  /*TARGET_T_*/"ACTION_INVOKER",                                "Unit who caused this Event to occur (only works for EVENT_T_AGGRO, EVENT_T_KILL, EVENT_T_DEATH, EVENT_T_SPELLHIT, EVENT_T_OOC_LOS, EVENT_T_FRIENDLY_HP, EVENT_T_FRIENDLY_IS_CC, EVENT_T_FRIENDLY_MISSING_BUFF)"},
TypeValue{7,  /*TARGET_T_*/"HOSTILE_WPET",                                  "Current target (can be a pet)"},
TypeValue{8,  /*TARGET_T_*/"HOSTILE_WPET_SECOND_AGGRO",                     "Second highest aggro (generaly used for cleaves and some special attacks)"},
TypeValue{9,  /*TARGET_T_*/"HOSTILE_WPET_LAST_AGGRO",                       "Dead last on aggro (no idea what this could be used for)"},
TypeValue{10, /*TARGET_T_*/"HOSTILE_WPET_RANDOM",                           "Just any random target on our threat list"},
TypeValue{11, /*TARGET_T_*/"HOSTILE_WPET_RANDOM_NOT_TOP",                   "Any random target except top threat"},
TypeValue{12, /*TARGET_T_*/"ACTION_INVOKER_WPET",                           ""}

};

static const QVector<TypeValue> CastFlags =
{
TypeValue{1 , /*CAST_*/"INTURRUPT_PREVIOUS" , "Interrupts any previous spell casting (basicaly makes sure that this spell goes off)"},
TypeValue{2 , /*CAST_*/"TRIGGERED"          , "Forces the spell to be instant cast and require no mana/reagents."},
TypeValue{4 , /*CAST_*/"FORCE_CAST"         , "Forces spell to cast even if the target is possibly out of range or the creature is possibly out of mana"},
TypeValue{8 , /*CAST_*/"NO_MELEE_IF_OOM"    , "Prevents creature from entering melee if out of mana or out of range"},
TypeValue{16, /*CAST_*/"FORCE_TARGET_SELF"  , "Forces the target to cast this spell on itself"},
TypeValue{32, /*CAST_*/"AURA_NOT_PRESENT"   , "Only casts the spell on the target if the target does not have the aura from that spell on itself already."}
};

static const QVector<TypeValue> EventTypeMask =
{
TypeValue{0x01, /*AI_EVENT_*/"JUST_DIED",       "Sender = Killed Npc, Invoker = Killer - Sent when npc dies"},
TypeValue{0x02, /*AI_EVENT_*/"CRITICAL_HEALTH", "Sender = Hurt Npc, Invoker = DamageDealer - Sent when damaged below 10% health"},
TypeValue{0x04, /*AI_EVENT_*/"LOST_HEALTH",     "Sender = Hurt Npc, Invoker = DamageDealer - Sent when damaged below 50% health"},
TypeValue{0x08, /*AI_EVENT_*/"LOST_SOME_HEALTH","Sender = Hurt Npc, Invoker = DamageDealer - Sent when damaged below 90% health"},
TypeValue{0x10, /*AI_EVENT_*/"GOT_FULL_HEALTH", "Sender = Healed Npc, Invoker = Healer - Sent when healed to full health"},
};

static const QVector<TypeValue> EventFlags =
{
TypeValue{1         ,"REPEATABLE"           ,"Event repeats (Does not repeat if this flag is not set)"},
TypeValue{2         ,"EFLAG_RESERVED_1"     ,""},
TypeValue{4         ,"EFLAG_RESERVED_2"     ,""},
TypeValue{8         ,"EFLAG_RESERVED_3"     ,""},
TypeValue{16        ,"EFLAG_RESERVED_4"     ,""},
TypeValue{32        ,"RANDOM_ACTION"        ,"At event occur execute one random action from event actions instead all actions."},
TypeValue{64        ,"EFLAG_RESERVED_6"     ,""},
TypeValue{128       ,"DEBUG_ONLY"           ,"Prevents events from occuring on Release builds. Useful for testing new features."}

};

// referenced in description of 44   ACTION_T_CHANCED_TEXT, but cant see how it should be used. Not used yet
static const QVector<TypeValue> TextTypes =
{
TypeValue{0,    /*CHAT_TYPE_*/"SAY"                 ,"This type sets the text to be displayed as a Say (Speech Bubble)."},
TypeValue{1,    /*CHAT_TYPE_*/"YELL"                ,"This type sets the text to be displayed as a Yell (Red Speech Bubble) and usually has a matching Sound ID."},
TypeValue{2,    /*CHAT_TYPE_*/"TEX T_EMOTE"          ,"This type sets the text to be displayed as a text emote in orange in the chat log."},
TypeValue{3,    /*CHAT_TYPE_*/"BOSS_EMOTE"          ,"This type sets the text to be displayed as a text emote in orange in the chat log (Used only for specific Bosses)."},
TypeValue{4,    /*CHAT_TYPE_*/"WHISPER"             ,"This type sets the text to be displayed as a whisper to the player in the chat log."},
TypeValue{5,    /*CHAT_TYPE_*/"BOSS_WHISPER"        ,"This type sets the text to be displayed as a whisper to the player in the chat log (Used only for specific Bosses)."},
TypeValue{6,    /*CHAT_TYPE_*/"ZONE_YELL"           ,"Same as CHAT_TYPE_YELL but will display to all players in current zone."}
};


// Not used yet, not sure if it will be either
static const QVector<TypeValue> LanguageTypes =
{
TypeValue{0 ,   "UNIVERSAL"                    ,"Text in this language is understood by ALL Races."},
TypeValue{1 ,   "ORCISH"                       ,"Text in this language is understood ONLY by Horde Races."},
TypeValue{2 ,   "DARNASSIAN"                   ,"Text in this language is understood ONLY by the Night Elf Race."},
TypeValue{3 ,   "TAURAHE"                      ,"Text in this language is understood ONLY by the Tauren Race."},
TypeValue{6 ,   "DWARVISH"                     ,"Text in this language is understood ONLY by the Dwarf Race."},
TypeValue{7 ,   "COMMON"                       ,"Text in this language is understood ONLY by Alliance Races."},
TypeValue{8 ,   "DEMONIC"                      ,"Text in this language is understood ONLY by the Demon Race (Not Implimented)."},
TypeValue{9 ,   "TITAN"                        ,"This language was used by Sargeras to speak with other Titians (Not Implemented)."},
TypeValue{10,   "THALASSIAN"                   ,"Text in this language is understood ONLY by the Blood Elf Race."},
TypeValue{11,   "DRACONIC"                     ,"Text in this language is understood ONLY by the Dragon Race."},
TypeValue{12,   "KALIMAG"                      ,"Text will display as Kalimag (not readable by players, language of all elementals)"},
TypeValue{13,   "GNOMISH"                      ,"Text in this language is understood ONLY by the Gnome Race."},
TypeValue{14,   "TROLL"                        ,"Text in this language is understood ONLY by the Troll Race."},
TypeValue{33,   "GUTTERSPEAK"                  ,"Text in this language is understood ONLY by the Undead Race."},
TypeValue{35,   "DRAENEI"                      ,"Text in this language is understood ONLY by the Draenai Race."},
TypeValue{36,   "ZOMBIE"                       ,"(not currently used?)"},
TypeValue{37,   "GNOMISH BINARY"               ,"Binary language used by Alliance when drinking Binary Brew"},
TypeValue{38,   "GOBLIN BINARY"                ,"Binary language used by Horce when drinking Binary Brew"}
};

static const QVector<TypeValue> StandState =
{
TypeValue{0, /*UNIT_STAND_STATE_*/"STAND", ""},
TypeValue{1, /*UNIT_STAND_STATE_*/"SIT", ""},
TypeValue{2, /*UNIT_STAND_STATE_*/"SIT_CHAIR", ""},
TypeValue{3, /*UNIT_STAND_STATE_*/"SLEEP", ""},
TypeValue{4, /*UNIT_STAND_STATE_*/"SIT_LOW_CHAIR", ""},
TypeValue{5, /*UNIT_STAND_STATE_*/"SIT_MEDIUM_CHAIR", ""},
TypeValue{6, /*UNIT_STAND_STATE_*/"SIT_HIGH_CHAIR", ""},
TypeValue{7, /*UNIT_STAND_STATE_*/"DEAD", ""},
TypeValue{8, /*UNIT_STAND_STATE_*/"KNEEL", ""}
};

static const QVector<TypeValue> MovementType =
{
TypeValue{0, "Idle", ""},
TypeValue{1, "Random", ""},
TypeValue{2, "Waypoint", ""}
};

static const QVector<TypeValue> ReactState =
{
TypeValue{0, "Passive", ""},
TypeValue{1, "Defensive", ""},
TypeValue{2, "Aggressive", ""}
};

static const QVector<TypeValue> factionFlags = {
TypeValue{0x00, /*"TEMPFACTION_*/"NONE", "A persistent faction change and will require manual change to default/another faction when changed once"},
TypeValue{0x01, /*"TEMPFACTION_*/"RESTORE_RESPAWN", "Default faction will be restored at respawn"},
TypeValue{0x02, /*"TEMPFACTION_*/"RESTORE_COMBAT_STOP", "... at CombatStop() (happens at creature death, at evade or custom scripte among others)"},
TypeValue{0x04, /*"TEMPFACTION_*/"RESTORE_REACH_HOME", "... at reaching home in home movement (evade), if not already done at CombatStop()"}
};

static const QVector<TypeValue> SpawnedEventMode = {
TypeValue{0, /*SPAWNED_EVENT_*/  "ALWAYS", ""},
TypeValue{1, /*"SPAWNED_EVENT_*/ "MAP",    ""},
TypeValue{2, /*"SPAWNED_EVENT_*/ "ZONE",   ""}
};
/*
static const QMap<int,EventAI_event> event_map =
{
    {0,  "TIMER"                        ,"Expires at first between (Param1) and (Param2) and then will repeat between every (Param3) and (Param4),  EXPIRES ONLY IN COMBAT.",{ Parameter{MILLISECONDS, "InitialMin"  }, Parameter{ MILLISECONDS, "InitialMax"        }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {1,  "TIMER_OOC"                    ,"Expires at first between (Param1) and (Param2) and then will repeat between every (Param3) and (Param4),  EXPIRES ONLY OUT OF COMBAT BUT NOT DURING EVADE.",                            { Parameter{MILLISECONDS, "InitialMin"  }, Parameter{ MILLISECONDS, "InitialMax"        }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {2,  "HP"                           ,"Expires when the NPC's HP% is between (Param1) and (Param2). Will repeat between every (Param3) and (Param4) If Event Conditions Are Still Met",                            { Parameter{PERCENTAGE, "HPMax%"      }, Parameter{ PERCENTAGE, "HPMin%"            }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {3,  "MANA"                         ,"Expires when the NPC's Mana% is between (Param1) and (Param2). Will repeat between every (Param3) and (Param4) If Event Conditions Are Still Met",                            { Parameter{PERCENTAGE, "ManaMax%"    }, Parameter{ PERCENTAGE, "ManaMin%"          }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {4,  "AGGRO"                        ,"Expires ONLY upon the NPC's INITIAL Aggro at the Start of Combat (Does NOT Repeat) and Only Resets on Spawn or Evade",                            { }                                                                                                },
    {5,  "KILL"                         ,"Expires upon Killing a Player. Will Repeat Check between (Param1) and (Param2). This Event Will Not Trigger Again Until Repeat Timer Expires",                            { Parameter{MILLISECONDS, "RepeatMin"   }, Parameter{ MILLISECONDS, "RepeatMax" }}                                                                      },
    {6,  "DEATH"                        ,"Expires on the NPC's Death. (This Triggers At The Moment The NPC Dies",                            { }                                                                                                },
    {7,  "EVADE"                        ,"Expires at the moment the Creature EnterEvadeMode() and Exits Combat",                            { }                                                                                                },
    {8,  "SPELLHIT"                     ,"Expires upon Spell Hit of the NPC. When (param1) is set, it is the specific Spell ID used as the trigger. With (param2) specified, the expiration is limited to specific spell schools (-1 for all) and Spell ID value is ignored. Will repeat Event Conditions Check between every (Param3) and (Param4). Only A Spell ID or Spell School may be Specified but NOT both.",                            { Parameter{3, "SpellID"     }, Parameter{ 4, "School"            }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {9,  "RANGE"                        ,"Expires when the Highest Threat Target Distance is Greater than (Param1) and Less than (Param2). Will repeat between every (Param3) and (Param4) if Event Conditions Are Still Met",                            { Parameter{5, "MinDist"     }, Parameter{ 5, "MaxDist"           }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {10, "OOC_LOS"                      ,"Expires when a unit moves within distance (MaxAllowedRange) of the NPC. If (Param1) is 0 it will expire only when unit is hostile, If (Param1) is 1 it will expire only when unit is friendly. This depends generally on faction relations. Will repeat every (Param3) and (Param4). Does NOT expire when the NPC is in combat.",                            { Parameter{6, "NoHostile"   }, Parameter{ 5, "MaxRange"          }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {11, "SPAWNED"                      ,"Expires on initial spawn and respawn of the NPC (Useful for setting Ranged Movement/Summoning Pets/Applying Buffs)",                            { Parameter{"Condition"   }, Parameter{ "CondValue1"        }}                                                              },
    {12, "TARGET_HP"                    ,"Expires when current target's HP% is between (Param1) and (Param2). Will repeat every (Param3) and (Param4)If Event Conditions Are Still Met",                            { Parameter{PERCENTAGE, "HPMax%"      }, Parameter{ PERCENTAGE, "HPMin%"            }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {13, "TARGET_CASTING"               ,"Expires when the current target is casting a spell. Will repeat every (Param1) and (Param2) If Event Conditions Are Still Met",                            { Parameter{MILLISECONDS, "RepeatMin"   }, Parameter{ MILLISECONDS, "RepeatMax"         }},                                                             },
    {14, "FRIENDLY_HP"                  ,"Expires when a friendly unit in (Radius) has at least (Param1) HP points missing. Will repeat every (Param3) and (Param4) If Event Conditions Are Still Met",                            { Parameter{7, "HPDeficit"   }, Parameter{ 5, "Radius"            }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {15, "FRIENDLY_IS_CC"               ,"Expires when a friendly unit is crowd controlled within the given Radius (Param2). Will repeat every (Param3) and (Param4).",                            { Parameter{"DispelType"  }, Parameter{ 5, "Radius"            }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {16, "FRIENDLY_MISSING_BUFF"        ,"Expires when a friendly unit is missing aura(s) given by a spell (Param1) within Radius (Param2). Will repeat every (Param3) and (Param4) If Event Conditions Are Still Met.",                            { Parameter{3, "SpellID"     }, Parameter{ 5, "Radius"            }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {17, "SUMMONED_UNIT"                ,"Expires after creature with entry = (Param1) is spawned (Param1 = 0 means all spawns). Will repeat every (Param2) and (Param3).",                            { Parameter{12, "CreatureId"  }, Parameter{ MILLISECONDS, "RepeatMin"         }, Parameter{ MILLISECONDS, "RepeatMax" }}                                    },
    {18, "TARGET_MANA"                  ,"Expires when current target's Mana% is between (Param1) and (Param2). Will repeat every (Param3) and (Param4) If Event Conditions Are Still Met",                            { Parameter{PERCENTAGE, "ManaMax%"    }, Parameter{ PERCENTAGE, "ManaMin%"          }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},


    {19, "QUEST_ACCEPT"                 ,"",                            { Parameter{"QuestID"     }}                                                                                                },
    {20, "QUEST_COMPLETE"               ,"",                            { }                                                                                                },
    {21, "REACHED_HOME"                 ,"Expires when a creature reaches it's home (spawn) location after evade. This is commonly used for NPC's who Stealth once reaching their Spawn Location",                            { Parameter{"NONE"        }}                                                                                                },
    {22, "RECEIVE_EMOTE"                ,"Expires when a creature receives an emote with emote text id (enum TextEmotes from SharedDefines.h in Mangos Source) in (Param1). Conditions can be defined (Param2) with optional values (Param3,Param4), see (enum ConditionType) in ObjectMgr.h (Mangos Source).",                            { Parameter{"EmoteId"     }, Parameter{ "Condition"         }, Parameter{ "CondValue1"         }, Parameter{ "CondValue2" }}},
    {23, "AURA"                         ,"Expires when a creature has spell (Param1) auras applied in a stack greater or equal to value provided in (Param2). Will repeat every (Param3) and (Param4) If Event Conditions Are Still Met",                            { Parameter{3, "SpellID"     }, Parameter{ "Stack"             }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {24, "TARGET_AURA"                  ,"Expires when a target unit has spell (Param1) auras applied in a stack greater or equal to value provided in (Param2). Will repeat every (Param3) and (Param4) If Event Conditions Are Still Met",                            { Parameter{3, "SpellID"     }, Parameter{ "Stack"             }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {25, "SUMMONED_JUST_DIED"           ,"Expires after creature with entry = (Param1) is die (Param1 = 0 means all spawns). Will repeat every (Param2) and (Param3).",                            { Parameter{12, "CreatureId"  }, Parameter{ MILLISECONDS, "RepeatMin"         }, Parameter{ MILLISECONDS, "RepeatMax" }},                                   },
    {26, "SUMMONED_JUST_DESPAWN"        ,"Expires before creature with entry = (Param1) is despawn (Param1 = 0 means all spawns). Will repeat every (Param2) and (Param3).",                            { Parameter{12, "CreatureId"  }, Parameter{ MILLISECONDS, "RepeatMin"         }, Parameter{ MILLISECONDS, "RepeatMax" }},                                   },
    {27, "MISSING_AURA"                 ,"Expires when a creature not has aura (Param1) auras applied in a stack greater or equal to value provided in (Param2). Will repeat every (Param3) and (Param4).",                            { Parameter{3, "SpellID"     }, Parameter{ "Stack"             }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},
    {28, "TARGET_MISSING_AURA"          ,"Expires when a target unit not has spell (Param1) auras applied in a stack greater or equal to value provided in (Param2). Will repeat every (Param3) and (Param4).",                            { Parameter{3, "SpellID"     }, Parameter{ "Stack"             }, Parameter{ MILLISECONDS, "RepeatMin"          }, Parameter{ MILLISECONDS, "RepeatMax"  }}},


};
*/
}

#endif // EVENTAIDEFELYSIUM_H
