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


private:
    Cache();
    QSettings settings;
    QMap<unsigned int, QString> maps;

    void LoadSchema(const QString& table, QStringList& names);
};

namespace Tables{
namespace creature_template{
static const QString t(){return Cache::Get().Table("creature_template");}
static const QString entry   = "entry";
static const QString name    = "name";
}
namespace creature_template_addon{
static const QString t(){return Cache::Get().Table("creature_template_addon");}
static const QString entry   = "entry";
}
namespace creature_model_info{
static const QString t(){return Cache::Get().Table("creature_model_info");}
static const QString modelid = "modelid";
}
namespace creature{
static const QString t(){return Cache::Get().Table("creature");}
}
static const QString creature_addon              = "creature_addon";
static const QString creature_ai_scripts         = "creature_ai_scripts";
static const QString creature_ai_summons         = "creature_ai_summons";
static const QString creature_ai_texts           = "creature_ai_texts";
static const QString creature_battleground       = "creature_battleground";
static const QString creature_equip_template     = "creature_equip_template";
static const QString creature_equip_template_raw = "creature_equip_template_raw";
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
