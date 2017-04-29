#ifndef TABLES_H
#define TABLES_H

#include <QSqlRecord>
#include <QString>
#include <QVector>

namespace Tables
{

template<typename T>
static QString dbtable(){
    return QString("%1.%2").arg(Cache::Get().settings.value("worldDB").toString(), T::t);
}

struct Table;
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

    QString Query(const QString& k, const QString& v) const;

    QString dbTable();

    virtual QVector<relation> Relations() {return QVector<relation>();}

    template<typename T>
    relation makeRelation(const QString& myKey, const QString& otherKey, const QString& optName = QString()){
        return relation{new T(), myKey, otherKey, optName};
    }
    QVector<QSqlRecord> records;
};

struct creature : public Table{
    static const QString t;
    static const QString id;
    creature():Table(t){}
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
    creature_template():Table(t){}
    QVector<relation> Relations() override;
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
    creature_equip_template():Table(t){}
    QVector<relation> Relations() override;
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
    static const QString creature_id;
    creature_ai_scripts():Table(t){}
};

struct item_template : public Table{
    static const QString t;
    item_template():Table(t){}
};


}

#endif // TABLES_H
