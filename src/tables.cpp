#include "tables.h"
#include "cache.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>

namespace Tables {
const QString creature::t = "creature";
const QString creature::id = "id";
const QString creature::map = "Map";

const QString creature_template::t = "creature_template";
const QString creature_template::entry = "entry";
const QString creature_template::name = "name";
const QString creature_template::modelid_1 = "modelid_1";
const QString creature_template::modelid_2 = "modelid_2";
const QString creature_template::modelid_3 = "modelid_3";
const QString creature_template::modelid_4 = "modelid_4";
const QString creature_template::equipment_id = "equipment_id";
const QString creature_template::AIName = "AIName";

const QString creature_template_addon::t = "creature_template_addon";
const QString creature_template_addon::entry = "entry";

const QString creature_model_info::t = "creature_model_info";
const QString creature_model_info::modelid = "modelid";

const QString creature_equip_template::t = "creature_equip_template";
const QString creature_equip_template::entry = "entry";

const QString creature_equip_template_raw::t = "creature_equip_template_raw";

const QString creature_addon::t = "creature_addon";

const QString creature_ai_scripts::t = "creature_ai_scripts";
const QString creature_ai_scripts::id = "id";
const QString creature_ai_scripts::creature_id = "creature_id";
const QString creature_ai_scripts::event_type = "event_type";
const QString creature_ai_scripts::event_inverse_phase_mask = "event_inverse_phase_mask";
const QString creature_ai_scripts::event_chance = "event_chance";
const QString creature_ai_scripts::event_flags = "event_flags";
const QString creature_ai_scripts::event_param1 = "event_param1";
const QString creature_ai_scripts::event_param2 = "event_param2";
const QString creature_ai_scripts::event_param3 = "event_param3";
const QString creature_ai_scripts::event_param4 = "event_param4";
const QString creature_ai_scripts::action1_type = "action1_type";
const QString creature_ai_scripts::action1_param1 = "action1_param1";
const QString creature_ai_scripts::action1_param2 = "action1_param2";
const QString creature_ai_scripts::action1_param3 = "action1_param3";
const QString creature_ai_scripts::action2_type = "action2_type";
const QString creature_ai_scripts::action2_param1 = "action2_param1";
const QString creature_ai_scripts::action2_param2 = "action2_param2";
const QString creature_ai_scripts::action2_param3 = "action2_param3";
const QString creature_ai_scripts::action3_type = "action3_type";
const QString creature_ai_scripts::action3_param1 = "action3_param1";
const QString creature_ai_scripts::action3_param2 = "action3_param2";
const QString creature_ai_scripts::action3_param3 = "action3_param3";
const QString creature_ai_scripts::comment = "comment";
const QString creature_ai_scripts::event_param_n = "event_param%1";
const QString creature_ai_scripts::action_n_type = "action%1_type";
const QString creature_ai_scripts::action_x_param_y = "action%1_param%2";


const QString item_template::t = "item_template";

const QString map_template::t = "map_template";
const QString map_template::entry = "Entry";
const QString map_template::mapname = "MapName";

QVector<MangosRecord> Table::Query(const QVariant &value, const QString tarKey, int expectSize)
{
    if(!value.isValid()) {
        throw std::runtime_error("Query got invalid value");
    }else if(value.isNull()){
        throw std::runtime_error("Query got null-value");
    }

    QSqlDatabase db = Cache::Get().GetDB();
    QSqlField f;
    f.setValue(value);
    f.setType(value.type());
    QString qs = QString("SELECT * FROM %1 WHERE %2 = %3").arg(
                db.driver()->escapeIdentifier(dbTable(), QSqlDriver::TableName),
                db.driver()->escapeIdentifier(tarKey, QSqlDriver::FieldName),
                db.driver()->formatValue(f));

    QSqlQuery q(qs, db);
    if(!q.exec()){
        throw std::runtime_error(QString("Error (%1) during query exec in Query")
                                 .arg(q.lastError().text()).toStdString().c_str());
    }
    if(expectSize == 1 && q.size() != 1){
        throw std::runtime_error(QString("Query returned %1 result(s), expected 1")
                                 .arg(q.size()).toStdString().c_str());
    }
    QVector<MangosRecord> ret;
    while(q.next()){
        ret.push_back(MangosRecord(q.record(), _t));
    }

    return ret;
}

MangosRecord Table::Query1(const QVariant &value, const QString tarKey, bool assert)
{
    QVector<MangosRecord> records = Query(value, tarKey, assert ? 1 : -1);
    return records.empty() ? MangosRecord() : records.takeFirst();
}

QString Table::dbTable() {
    return QString("%1.%2").arg(Cache::Get().settings.value("worldDB").toString(), table());
}

creature_template::creature_template(quint32 entry) :
    Table(t)
{
    record = Query1(entry, creature_template::entry);
    record.table = t;
    record.pk = creature_template::entry;

    creatures = new creature(entry);
    scripts = new creature_ai_scripts(entry);
    equipment = new creature_equip_template(record.value(equipment_id));

    //makeRelation<creature_template_addon>(entry, creature_template_addon::entry),
    //makeRelation<creature_model_info>(modelid_1, creature_model_info::modelid),
    //makeRelation<creature_model_info>(modelid_2, creature_model_info::modelid),
    //makeRelation<creature_model_info>(modelid_3, creature_model_info::modelid),
    //makeRelation<creature_model_info>(modelid_4, creature_model_info::modelid),
}


creature::creature(quint32 entry)
    :Table(t)
{
    records = Query(entry, creature::id);
}

creature_equip_template::creature_equip_template(const QVariant &v) :
    Table(t),
    record(Query1(v, creature_equip_template::entry, false))
{
    //makeRelation<creature>("equipentry1", "entry", "Main-hand"),
    //makeRelation<creature>("equipentry2", "entry", "Off-hand"),
    //makeRelation<creature>("equipentry3", "entry", "Ranged")
}

creature_ai_scripts::creature_ai_scripts(quint32 entry) :
    Table(t)
{
    records = Query(entry, creature_ai_scripts::creature_id);
    for(auto it = records.begin(); it != records.end(); it++){
        (*it).table = t;
        (*it).pk = creature_ai_scripts::id;
    }
}



}
