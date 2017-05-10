#ifndef TABLES_H
#define TABLES_H

#include "cache.h"
#include "mangosrecord.h"
#include "eventaidefcommon.h"

#include <QSqlRecord>
#include <QString>
#include <QVector>
#include <QSqlField>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QVariant>
namespace Tables
{
template <typename T>
static QString worldTable(){
    return QString("%1.%2").arg(Cache::Get().settings.value("worldDB").toString(), T::t);
}

static QString EscapedVal(const QVariant& val){
    QSqlDatabase db = Cache::Get().GetDB();
    QSqlField f;
    f.setType(val.type());
    f.setValue(val);
    return db.driver()->formatValue(f);
}

struct Table;
struct creature_ai_scripts;
struct creature_equip_template;
struct creature_template_addon;
struct creature_model_info;

struct relation{
    Table* table;
    const QString& myKey;
    const QString& relationKey;
    const QString& relationName;
};

struct Table{
private:
    const QString _t;
public:
    Table(const QString& t) : _t(t){}

    QString table() const {return _t;}

    QVector<MangosRecord> Query(const QVariant& value, const QString tarKey, int expectSize = -1);
    MangosRecord Query1(const QVariant& value, const QString tarKey, bool assert = true);

    QString dbTable();
};

struct creature : public Table{
    static const QString t;
    static const QString id;

    static const QString map;

    creature(quint32 entry);
    QVector<MangosRecord> records;
};

struct creature_template : public Table{
    static const QString t;
    static const QString entry;
    static const QString name;
    static const QString modelid_1;
    static const QString modelid_2;
    static const QString modelid_3;
    static const QString modelid_4;
    static const QString equipment_id;
    static const QString Unit_flags;
    static const QString Dynamicflags;
    static const QString Family;
    static const QString KillCredit1;
    static const QString KillCredit2;
    static const QString subname;
    static const QString gossip_menu_id;
    static const QString minlevel;
    static const QString maxlevel;
    static const QString minhealth;
    static const QString maxhealth;
    static const QString minmana;
    static const QString maxmana;
    static const QString armor;
    static const QString faction_A;
    static const QString faction_H;
    static const QString npcflag;
    static const QString speed_walk;
    static const QString speed_run;
    static const QString scale;
    static const QString rank;
    static const QString mindmg;
    static const QString maxdmg;
    static const QString dmgschool;
    static const QString attackpower;
    static const QString dmg_multiplier;
    static const QString baseattacktime;
    static const QString rangeattacktime;
    static const QString unit_class;
    static const QString unit_flags;
    static const QString dynamicflags;
    static const QString family;
    static const QString trainer_type;
    static const QString trainer_spell;
    static const QString trainer_class;
    static const QString trainer_race;
    static const QString minrangedmg;
    static const QString maxrangedmg;
    static const QString rangedattackpower;
    static const QString type;
    static const QString type_flags;
    static const QString lootid;
    static const QString pickpocketloot;
    static const QString skinloot;
    static const QString resistance1;
    static const QString resistance2;
    static const QString resistance3;
    static const QString resistance4;
    static const QString resistance5;
    static const QString resistance6;
    static const QString spell1;
    static const QString spell2;
    static const QString spell3;
    static const QString spell4;
    static const QString PetSpellDataId;
    static const QString mingold;
    static const QString maxgold;
    static const QString MovementType;
    static const QString InhabitType;
    static const QString Civilian;
    static const QString RacialLeader;
    static const QString RegenHealth;
    static const QString trainer_id;
    static const QString vendor_id;
    static const QString MechanicImmuneMask;
    static const QString SchoolImmuneMask;
    static const QString flags_extra;
    static const QString AIName;
    static const QString ScriptName;

    creature_template(quint32 entry);
    MangosRecord record;

    // XXX: add a dtor and delete this stuff
    creature* creatures;
    creature_ai_scripts* scripts;
    creature_equip_template* equipment;
    creature_template_addon* template_addon;
    static constexpr int MAX_MODEL_INFO = 4;
    creature_model_info* model_info[MAX_MODEL_INFO];
};

struct creature_template_addon : public Table{
    static const QString t;
    static const QString entry;
    MangosRecord record;
    creature_template_addon(const QVariant &v);
};


struct creature_model_info : public Table{
    static const QString t;
    static const QString modelid;
    creature_model_info(QVariant v);
    MangosRecord record;
};


struct creature_equip_template : public Table{
    static const QString t;
    static const QString entry;
    creature_equip_template(const QVariant& v);
    MangosRecord record;
};


struct creature_equip_template_raw : public Table{
    static const QString t;
    creature_equip_template_raw():Table(t){}
};

struct creature_addon : public Table{
    static const QString t;
    creature_addon():Table(t){}
};

struct creature_ai_scripts : public Table{
    static const QString t;
    static const QString id;
    static const QString creature_id;

    static const QString event_type;
    static const QString event_inverse_phase_mask;
    static const QString event_chance;
    static const QString event_flags;
    static QString event_paramN(int n){return event_param_n.arg(n);}
    static const QString event_param1;
    static const QString event_param2;
    static const QString event_param3;
    static const QString event_param4;
    static QString actionN_type(int n){return action_n_type.arg(n);}
    static QString actionX_paramY(int x, int y){return action_x_param_y.arg(x).arg(y);}
    static const QString action1_type;
    static const QString action1_param1;
    static const QString action1_param2;
    static const QString action1_param3;
    static const QString action2_type;
    static const QString action2_param1;
    static const QString action2_param2;
    static const QString action2_param3;
    static const QString action3_type;
    static const QString action3_param1;
    static const QString action3_param2;
    static const QString action3_param3;
    static const QString comment;
    static const int num_cols = 23;

    creature_ai_scripts(quint32 entry);
    QVector<MangosRecord> records;
private:
    static const QString event_param_n;
    static const QString action_n_type;
    static const QString action_x_param_y;
};

struct item_template : public Table{
    static const QString t;
    item_template():Table(t){}
};

struct map_template : public Table{
    static const QString t;
    map_template() :Table(t){}
    static const QString entry;
    static const QString mapname;
};

}

#endif // TABLES_H
