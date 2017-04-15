#include "table.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSettings>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


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

QVector<std::shared_ptr<Creature>> Creature::GetCreatures(const QString &name)
{
    QVector<std::shared_ptr<Creature>> result;

    QSettings settings;
    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
    bool ret = db.isOpen();
    if(!ret){
        throw std::logic_error("Unable to open database connection: " + db.connectionName().toStdString());
    }
    QSqlQuery q(db);
    QString ns = "%"+name+"%";
    ns.replace("'", "''");
    q.prepare(QString("SELECT entry, name FROM %1.creature_template WHERE name LIKE '%2'")
              .arg(settings.value("worldDB").toString())
              .arg(ns));
    ret = q.exec();
    int entryField = q.record().indexOf("entry");
    int nameField = q.record().indexOf("name");
    if(!ret){
        throw std::logic_error("Query failed. Error: " + q.lastError().text().toStdString()
                               + ", Query:" + q.lastQuery().toStdString());
    }else{
        qDebug() << q.lastQuery();
    }
    if(!q.isValid()){
        // throw something
    }
    while(q.next()){
        result.push_back(std::make_shared<Creature>(q.value(nameField).toString(), q.value(entryField).toUInt()));
    }
    return result;
}


Creature::Creature(QString&& name, unsigned int entry) :
    name(std::move(name)),
    entry(entry)
{

}






