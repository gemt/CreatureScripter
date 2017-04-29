#ifndef TABLE_H
#define TABLE_H

#include "cache.h"
#include "tables.h"

#include <QSqlRecord>

class CreatureTable{
public:
    CreatureTable(Tables::Table* t, const QString& k, const QString& v);
    ~CreatureTable();

    QMap<QSqlRecord*, CreatureTable*> records;
    QVector<CreatureTable*> children;
    Tables::Table* table;
};

class CreatureData{
public:
    CreatureData(quint32 entry, const QString& name);

private:
    CreatureTable table;
    quint32 entry;
    QString name;
};

#endif // TABLE_H

