#ifndef TABLE_H
#define TABLE_H

#include "cache.h"
#include "tables.h"

#include <QSqlRecord>
#include <memory>

namespace Tables{
struct creature_template;
}

class CreatureData{
public:
    CreatureData(quint32 entry, const QString& name);

    std::shared_ptr<Tables::creature_template> creature;
    quint32 entry;
    QString name;
};

#endif // TABLE_H

