#ifndef CREATURECACHE_H
#define CREATURECACHE_H

#include <QMap>
#include <QVector>
#include <QString>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlRecord>

class Creature
{
public:

    Creature():entry(0),name("INVALID"){}
    Creature(const QString& name, unsigned int entry);

    unsigned int entry;
    QString name;
};

namespace Tables{
struct relation{
    const QString& table;
    const QString& myKey;
    const QString& relationKey;
    const QString& relationName;
};

template<typename T>
static QString dbtable(){
    return QString("%1.%2").arg(Cache::Get().settings.value("worldDB").toString(), T::t);
}
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
        return relation{T::t, myKey, otherKey, optName};
    }
};
}

class Cache
{
public:


public:
    static Cache& Get(){
        static Cache* instance = new Cache();
        return *instance;
    }
    QString Table(const QString& table) const;
    QSqlDatabase GetDB();

    bool Connect();
    bool isConnected();

    void LoadSchemas();
    void LoadMaps();

    QString MapName(unsigned int entry);
    QSettings settings;

private:
    Cache();
    QMap<unsigned int, QString> maps;
    QMap<QString,Tables::Table*> table_definitions;
    void LoadSchema(const QString& table, QStringList& names);
};

namespace Tables{

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

static const QString creature_addon              = "creature_addon";
static const QString creature_ai_summons         = "creature_ai_summons";
static const QString creature_ai_texts           = "creature_ai_texts";
static const QString creature_battleground       = "creature_battleground";
static const QString creature_groups             = "creature_groups";
static const QString creature_involved_relation  = "creature_involved_relation";
static const QString creature_loot_template      = "creature_loot_template";
static const QString creature_movement           = "creature_movement";
static const QString creature_movement_scripts   = "creature_movement_scripts";
static const QString creature_movement_template  = "creature_movement_template";
static const QString creature_onkill_reputation  = "creature_onkill_reputation";
static const QString creature_questrelation      = "creature_questrelation";
static const QString creature_spells             = "creature_spells";

namespace map_template{
static const QString t(){return Cache::Get().Table("map_template");}
static const QString entry = "Entry";
static const QString mapname = "MapName";
}
}
#endif // CREATURECACHE_H
