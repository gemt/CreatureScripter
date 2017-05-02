#ifndef CREATURECACHE_H
#define CREATURECACHE_H

#include <QMap>
#include <QVector>
#include <QString>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QByteArray>
#include <QProcess>
#include <QObject>

//class SpellInfoInterface;

class Cache : public QObject
{
Q_OBJECT
public:
    static Cache& Get(){
        static Cache* instance = new Cache();
        return *instance;
    }
    QString Table(const QString& table) const;
    QSqlDatabase GetDB();

    bool Connect();
    bool isConnected();

    void LoadMaps();

    QString MapName(unsigned int entry);
    QSettings settings;
    //SpellInfoInterface* spellInfo;
    QByteArray m_templateHtml;
    QByteArray m_styleCss;
private:
    Cache();
    QMap<unsigned int, QString> maps;
};

namespace Tables{

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
