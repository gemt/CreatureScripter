#include "table.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSettings>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QTableWidgetItem>

Creatures Creatures::instance;

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

Creature::Creature(const QString& name, unsigned int entry) :
    name(name),
    entry(entry)
{

}

std::vector<Creature*> Creatures::GetCreatures(const QString &name)
{
    if(name.isEmpty())
        return _creatures;
    QString lName = name;
    bool isUInt;
    unsigned int intVal = lName.toUInt(&isUInt);
    std::vector<Creature*> ret;
    if(isUInt){
        for(auto it = _creatures.cbegin(); it != _creatures.cend(); it++){
            if((*it)->entry == intVal)
                ret.push_back(*it);
        }
        return ret;
    }else{
        QString sn = lName.toLower();
        std::vector<Creature*> ret;
        for(auto it = _creatures.cbegin(); it != _creatures.cend(); it++){
            if((*it)->name.contains(sn))
                ret.push_back(*it);
        }

        return ret;
    }

}

void Creatures::LoadCreatures()
{
    static bool loaded = false;
    if(loaded){
        throw std::logic_error("Creatures::LoadCreatures called twize");
    }else{
        loaded = true;
    }
    QSettings settings;
    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
    bool ret = db.isOpen();
    if(!ret){
        throw std::logic_error("Unable to open database connection: " + db.connectionName().toStdString());
    }
    QSqlQuery q(db);
    ret = q.exec(QString("SELECT entry, name FROM %1.creature_template")
                 .arg(settings.value("worldDB").toString()));
    int entryField = q.record().indexOf("entry");
    int nameField = q.record().indexOf("name");
    if(!ret){
        throw std::logic_error("Query failed. Error: " + q.lastError().text().toStdString()
                               + ", Query:" + q.lastQuery().toStdString());
    }else{
        qDebug() << q.lastQuery();
    }
    if(!q.isValid()){
        //throw std::logic_error("Query is not valid");
    }
    while(q.next()){
        QString n = q.value(nameField).toString().toLower();
        unsigned int e = q.value(entryField).toUInt();
        _creatures.push_back(new Creature(n,e));
    }
}
