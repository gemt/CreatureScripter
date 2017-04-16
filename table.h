#ifndef TABLE_H
#define TABLE_H

/*
 * Needed tables:
 * creature_template    - entry mapped to name, lvl, movespeed, dmg, lots of stuff
 * creature_ai_scripts  - entry (creature_id) with ai scripts
 * creature             - entry (id) mapped to spawn location, respawntimer etc
 *
 */
#include <QVector>
#include <QString>
#include <memory>
#include <map>
#include <vector>
#include <QAbstractTableModel>
#include <QSqlResult>
#include <QSqlDatabase>
#include <QMap>

struct creature_template
{
    uint32_t entry_idx = 0;
    static const QVector<QString> rows;
};

struct creature
{
    uint32_t entry_idx = 1;
    uint32_t guid_idx  = 0;
    static const QVector<QString> rows;
};

struct creature_ai_scripts
{
    uint32_t entry_idx = 1;
    uint32_t id_idx  = 0;   // script id?
    static const QVector<QString> rows;
};

class Creature
{
public:

    Creature():entry(0),name("INVALID"){}
    Creature(const QString& name, unsigned int entry);

    unsigned int entry;
    QString name;
};

class Table
{
public:
    QMap<QString,QString> fields;
};

class FullCreature
{
public:
    FullCreature(unsigned int entry);

    QVector<Table> cTemplate;
    QVector<Table> cCreature;
    QVector<Table> cAIScripts;

private:
    void SelectStar(const QString& worldDB, const QString& tableName,
                    const QSqlDatabase& db, QVector<Table>& res,
                    unsigned int entry, const QString& entryFN);
};

class CreatureCache
{
public:
    static CreatureCache& Get(){
        return instance;
    }

    void LoadCreatures();


    std::vector<Creature*> GetCreatures(const QString& name);

private:
    CreatureCache(){}
    static CreatureCache instance;
    std::vector<Creature*> _creatures;
};




#endif // TABLE_H

