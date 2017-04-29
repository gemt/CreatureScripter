#include "tables.h"
#include "cache.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlField>

namespace Tables {

QString Table::Query(const QString& k, const QString& v) const {
    QSqlDatabase db = Cache::Get().GetDB();
    QSqlField f;
    f.setValue(v);
    f.setType(QVariant::String);
    return QString("SELECT * FROM %1 WHERE %2 = %3").arg(
                db.driver()->escapeIdentifier(table(), QSqlDriver::TableName),
                db.driver()->escapeIdentifier(k, QSqlDriver::FieldName),
                db.driver()->formatValue(f));
}

QString Table::dbTable() {
    return QString("%1.%2").arg(Cache::Get().settings.value("worldDB").toString(), table());
}

QVector<relation> creature_template::Relations()  {
    return QVector<relation>{
        makeRelation<creature>(entry, creature::id),
        makeRelation<creature_ai_scripts>(entry, creature_ai_scripts::creature_id),
        makeRelation<creature_template_addon>(entry, creature_template_addon::entry),
        makeRelation<creature_model_info>(modelid_1, creature_model_info::modelid),
        makeRelation<creature_model_info>(modelid_2, creature_model_info::modelid),
        makeRelation<creature_model_info>(modelid_3, creature_model_info::modelid),
        makeRelation<creature_model_info>(modelid_4, creature_model_info::modelid),
        makeRelation<creature_equip_template>(equipment_id, creature_equip_template::entry),
    };
}

QVector<relation> creature_equip_template::Relations()
{
    return QVector<relation>{
        makeRelation<creature>("equipentry1", "entry", "Main-hand"),
        makeRelation<creature>("equipentry2", "entry", "Off-hand"),
        makeRelation<creature>("equipentry3", "entry", "Ranged")

    };
}


const QString creature::t = "creature";
const QString creature::id = "id";

const QString creature_template::t = "creature_template";
const QString creature_template::entry = "entry";
const QString creature_template::name = "name";
const QString creature_template::modelid_1 = "modelid_1";
const QString creature_template::modelid_2 = "modelid_2";
const QString creature_template::modelid_3 = "modelid_3";
const QString creature_template::modelid_4 = "modelid_4";
const QString creature_template::equipment_id = "equipment_id";

const QString creature_template_addon::t = "creature_template_addon";
const QString creature_template_addon::entry = "entry";

const QString creature_model_info::t = "creature_model_info";
const QString creature_model_info::modelid = "modelid";

const QString creature_equip_template::t = "creature_equip_template";
const QString creature_equip_template::entry = "entry";

const QString creature_equip_template_raw::t = "creature_equip_template_raw";

const QString creature_addon::t = "creature_addon";

const QString creature_ai_scripts::t = "creature_ai_scripts";
const QString creature_ai_scripts::creature_id = "creature_id";

const QString item_template::t = "item_template";


}
