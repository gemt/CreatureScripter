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

/*
 * The creature template is defines each creature type, uniquely indexed by 'entry'.
 */
class CreatureTemplate
{
public:
    CreatureTemplate(unsigned int entry);
    QStringList table;
    QString value(const QString& key);
    static QStringList names;
    static QString tableName;
};

/* The creature table contains spawn positions of a creature as it's defined in
 * creature_template. One entry from creature_template will potentially have many
 * entries in the creature table
 */
class CreatureTable
{
public:
    CreatureTable(unsigned int entry);
    QVector<QStringList> positions;

    static QStringList names;
    static QString tableName;
};

/*
 * Creature AI scripts contains ai scripts for creatures. There can be multiple rows
 * for a single creature 'entry', where each row defines an action/ability etc for the creature
 */
class CreatureAIScripts
{
public:
    CreatureAIScripts(unsigned int entry);
    QVector<QStringList> events;

    static QStringList names;
    static QString tableName;
};

class FullCreature
{
public:
    FullCreature(unsigned int entry);

    CreatureTemplate cTemplate;
    CreatureTable cCreatures;
    CreatureAIScripts cAIScripts;
};

#endif // TABLE_H

