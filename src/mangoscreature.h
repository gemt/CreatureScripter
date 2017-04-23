#ifndef MANGOSCREATURE_H
#define MANGOSCREATURE_H

#include "mangosrecord.h"

#include <QString>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlField>
#include <QVector>
#include <QVector>
// http://schemaspy.sourceforge.net/unifieddb/mangos/
namespace CreatureRecord{
/*
    creature_equip_template_raw
    creature_equip_template
    creature_model_info
creature_template_addon
    creature_template
    creature_addon
    creature
    creature_ai_scripts
    creature_ai_summons
    creature_ai_texts
    creature_battleground
    creature_groups
    creature_involved_relation
TODO: creature_loot_template
    creature_movement
    creature_movement_scripts
    creature_movement_template
    creature_onkill_reputation
creature_questrelation
creature_spells
*/
using Record = QSqlRecord;

class CreatureMovement{
    Record creature_movement;
    Record creature_movement_scripts;
};

class Creature{
    qint64 guid;
    QSqlRecord creature;
    QVector<Record> creature_groups;
    QVector<CreatureMovement> creature_movement; // One creature with given guid has 0-n records, each record is a waypoin, and can have a script

    QSqlRecord map;
};

class Loot{
    // todo. stupidly complicated
    //https://github.com/cmangos/issues/wiki/loot_template
};

class CreatureTemplate {
    Record creature_template;

    QMap<qint64,Creature> creature;

    QMap<qint64,Record> creature_addon;
    QMap<qint64,Record> creature_ai_scripts;
    QMap<qint64,Record> creature_ai_summons;
    QMap<qint64,Record> creature_ai_texts;
    QMap<qint64,Record> creature_battlegrounds;
    QSqlRecord creature_equip_template;
    QSqlRecord creature_equip_template_raw; // deprecated version of non creature_equip_template

    QSqlRecord creature_model_info[4]; // A creature can have up to 4 models

    QVector<Record> creature_movement_template; // not sure how this makes sense. Maybe only for bosses etc?

    Record creature_onkill_reputation;

    QMap<qint64,Record> creature_involvedrelation; // quests this creature finishes, indexed by quest id
    QMap<qint64,Record> creature_questrelation; // quests that the creature starts, indexed by quest id


};

}

#endif // MANGOSCREATURE_H
