#include "creature.h"
#include "warnings.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSettings>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QTableWidgetItem>

/*
const QVector<QString> creature_template::rows =
{
    "entry",
    "KillCredit1",
    "KillCredit2",
    "modelid_1",
    "modelid_2",
    "modelid_3",
    "modelid_4",
    "name",
    "subname",
    "gossip_menu_id",
    "minlevel",
    "maxlevel",
    "minhealth",
    "maxhealth",
    "minmana",
    "maxmana",
    "armor",
    "faction_A",
    "faction_H",
    "npcflag",
    "speed_walk",
    "speed_run",
    "scale",
    "rank",
    "mindmg",
    "maxdmg",
    "dmgschool",
    "attackpower",
    "dmg_multiplier",
    "baseattacktime",
    "rangeattacktime",
    "unit_class"
    "unit_flags",
    "dynamicflags",
    "family",
    "trainer_type"
    "trainer_spell"
    "trainer_class",
    "trainer_race",
    "minrangedmg"
    "maxrangedmg",
    "rangedattackpower",
    "type",
    "type_flags",
    "lootid",
    "pickpocketloot",
    "skinloot",
    "resistance1",
    "resistance2",
    "resistance3",
    "resistance4",
    "resistance5",
    "resistance6",
    "spell1",
    "spell2",
    "spell3",
    "spell4",
    "PetSpellDataId",
    "mingold",
    "maxgold",
    "AIName",
    "MovementType",
    "InhabitType",
    "Civilian",
    "RacialLeader",
    "RegenHealth",
    "equipment_id",
    "trainer_id",
    "vendor_id",
    "MechanicImmuneMask",
    "SchoolImmuneMask",
    "flags_extra",
    "ScriptName",
};

const QVector<QString> creature_ai_scripts::rows =
{
    "id",
    "creature_id",
    "event_type",
    "event_inverse_phase_mask",
    "event_chance",
    "event_flags",
    "event_param1",
    "event_param2",
    "event_param3",
    "event_param4",
    "action1_type",
    "action1_param1",
    "action1_param2",
    "action1_param3",
    "action2_type",
    "action2_param1",
    "action2_param2",
    "action2_param3",
    "action3_type",
    "action3_param1",
    "action3_param2",
    "action3_param3",
    "comment"
};
*/

QString CreatureTable::tableName = "creature";
QString CreatureTemplate::tableName = "creature_template";
QString CreatureAIScripts::tableName = "creature_ai_scripts";

QStringList CreatureTable::names;
QStringList CreatureTemplate::names;
QStringList CreatureAIScripts::names;


static void SelectStar(const QString& tableName, QVector<QStringList>& res, const QStringList& names,
                       unsigned int entry, const QString& entryFN)
{
    QSettings settings;
    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
    bool ret = db.isOpen();
    if(!ret){
        throw std::logic_error("Unable to open database connection: " + db.connectionName().toStdString());
    }
    QString worldDB = settings.value("worldDB").toString();

    QSqlQuery q(db);
    ret = q.exec(QString("SELECT * FROM %1.%2 WHERE %3 = %4")
                      .arg(worldDB)
                      .arg(tableName)
                      .arg(entryFN)
                      .arg(entry));
    if(!ret){
        throw std::runtime_error("SelectStar failed. Query: " + q.lastQuery().toStdString()
                                 + ", Error: " + q.lastError().text().toStdString());
    }
    while(q.next()){
        QSqlRecord record = q.record();
        Q_ASSERT(!names.isEmpty());
        QStringList t;
        foreach(const QString& n, names){
            int idx = record.indexOf(n);
            t.push_back(idx == -1 ? "" : record.value(idx).toString());
        }
        res.push_back(t);
    }
}


CreatureTemplate::CreatureTemplate(unsigned int entry)
{
    QVector<QStringList> tmp;
    SelectStar(tableName, tmp, names, entry, "entry");
    Q_ASSERT(tmp.size() == 1);
    table = tmp.first();
}

QString CreatureTemplate::value(const QString &key)
{
    for(int i = 0; i < names.size(); i++){
        if(names.at(i) == key){
            return table.at(i);
        }
    }
    throw std::logic_error("CreatureTemplate::value no entry for key: " + key.toStdString());
}

CreatureTable::CreatureTable(unsigned int entry)
{
    SelectStar(tableName, positions, names, entry, "id");
}

CreatureAIScripts::CreatureAIScripts(unsigned int entry)
{
    SelectStar(tableName, events, names, entry, "creature_id");
}


FullCreature::FullCreature(unsigned int entry) :
    cTemplate(entry),
    cCreatures(entry),
    cAIScripts(entry)
{
}











