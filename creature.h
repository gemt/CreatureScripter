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


struct Table
{
    Table(){}
    Table(Table& t) : fields(std::move(t.fields)){}

    QMap<QString,QString> fields;
};


/*
 * The creature template is defines each creature type, uniquely indexed by 'entry'.
 */
class CreatureTemplate
{
public:
    CreatureTemplate(unsigned int entry);
    Table table;
};

/* The creature table contains spawn positions of a creature as it's defined in
 * creature_template. One entry from creature_template will potentially have many
 * entries in the creature table
 */
class CreatureTable
{
public:
    CreatureTable(unsigned int entry);
    QVector<Table> tables;
};

/*
 * Creature AI scripts contains ai scripts for creatures. There can be multiple ai scripts
 * for a single creature 'entry', thus they are uniquely indexed by the 'id' field
 */
class CreatureAIScripts
{
public:
    CreatureAIScripts(unsigned int entry);
    QVector<Table> tables;
};

class FullCreature
{
public:
    FullCreature(unsigned int entry);

    CreatureTemplate cTemplate;
    CreatureTable cCreatures;
    CreatureAIScripts cAIScripts;

private:
    void SelectStar(const QString& worldDB, const QString& tableName,
                    const QSqlDatabase& db, QVector<Table>& res,
                    unsigned int entry, const QString& entryFN);
};

#endif // TABLE_H

