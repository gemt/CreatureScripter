#ifndef CREATURECACHE_H
#define CREATURECACHE_H

#include <QMap>
#include <QVector>
#include <QString>
#include <QSettings>
#include <QSqlDatabase>

class Creature
{
public:

    Creature():entry(0),name("INVALID"){}
    Creature(const QString& name, unsigned int entry);

    unsigned int entry;
    QString name;
};
namespace Tables{
static constexpr char creature[]                    = "creature";
static constexpr char creature_addon[]              = "creature_addon";
static constexpr char creature_ai_scripts[]         = "creature_ai_scripts";
static constexpr char creature_ai_summons[]         = "creature_ai_summons";
static constexpr char creature_ai_texts[]           = "creature_ai_texts";
static constexpr char creature_battleground[]       = "creature_battleground";
static constexpr char creature_equip_template[]     = "creature_equip_template";
static constexpr char creature_equip_template_raw[] = "creature_equip_template_raw";
static constexpr char creature_groups[]             = "creature_groups";
static constexpr char creature_involved_relation[]  = "creature_involved_relation";
static constexpr char creature_loot_template[]      = "creature_loot_template";
static constexpr char creature_model_info[]         = "creature_model_info";
static constexpr char creature_movement[]           = "creature_movement";
static constexpr char creature_movement_scripts[]   = "creature_movement_scripts";
static constexpr char creature_movement_template[]  = "creature_movement_template";
static constexpr char creature_onkill_reputation[]  = "creature_onkill_reputation";
static constexpr char creature_questrelation[]      = "creature_questrelation";
static constexpr char creature_spells[]             = "creature_spells";
static constexpr char creature_template[]           = "creature_template";
static constexpr char creature_template_addon[]     = "creature_template_addon";
}

class Cache
{
public:


public:
    static Cache& Get(){
        static Cache* instance = new Cache();
        return *instance;
    }
    QString Table(const char* table);
    QSqlDatabase GetDB();

    bool Connect();
    bool isConnected();

    void LoadSchemas();
    void LoadMaps();

    QString MapName(unsigned int entry);

private:
    Cache();
    QSettings settings;
    QMap<unsigned int, QString> maps;

    void LoadSchema(const QString& table, QStringList& names);
};


#endif // CREATURECACHE_H
