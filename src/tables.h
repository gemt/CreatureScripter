#ifndef TABLES_H
#define TABLES_H

#include "cache.h"

#include <QSqlRecord>
#include <QString>
#include <QVector>

namespace Tables
{
template <typename T>
QString worldTable(){
    return QString("%1.%2").arg(Cache::Get().settings.value("worldDB").toString(), T::t);
}

struct Table;
struct creature_ai_scripts;
struct creature_equip_template;

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

    QVector<QSqlRecord> Query(const QVariant& value, const QString tarKey, int expectSize = -1);
    QSqlRecord Query1(const QVariant& value, const QString tarKey, bool assert = true);

    QString dbTable();
};

struct creature : public Table{
    static const QString t;
    static const QString id;
    creature(quint32 entry);
    QVector<QSqlRecord> records;
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
    creature_template(quint32 entry);
    QSqlRecord record;

    creature* creatures;
    creature_ai_scripts* scripts;
    creature_equip_template* equipment;
};

struct creature_template_addon : public Table{
    static const QString t;
    static const QString entry;
    creature_template_addon():Table(t){}
};


struct creature_model_info : public Table{
    static const QString t;
    static const QString modelid;
    creature_model_info():Table(t){}
};


struct creature_equip_template : public Table{
    static const QString t;
    static const QString entry;
    creature_equip_template(const QVariant& v);
    QSqlRecord record;
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
    QVector<QSqlRecord> records;
    QVector<QSqlRecord> originalRecords;
private:
    static const QString event_param_n;
    static const QString action_n_type;
    static const QString action_x_param_y;
};

struct item_template : public Table{
    static const QString t;
    item_template():Table(t){}
};


}

#endif // TABLES_H
