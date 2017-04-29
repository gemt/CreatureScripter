#include "creature.h"
#include "warnings.h"
#include "tables.h"

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlField>
#include <QSqlError>

CreatureData::CreatureData(quint32 entry, const QString &name) :
      entry(entry),name(name)
{
    creature = std::make_shared<Tables::creature_template>(entry);
}
