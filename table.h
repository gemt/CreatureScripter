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
    static QVector<std::shared_ptr<Creature>> GetCreatures(const QString& name);

    Creature():entry(0){}
    Creature(QString&& name, unsigned int entry);

    unsigned int entry;
    QString name;

};

#endif // TABLE_H

