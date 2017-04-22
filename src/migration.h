#ifndef PATCH_H
#define PATCH_H

#include <QString>
#include <QSqlRecord>
#include <QMap>

class Migration
{
public:
    Migration(const char* table, const QString& field, const QString& fieldVal);

private:
    QSqlRecord record;

};

class Migrations
{
public:
    void AddMigration(const QString& table, const QString& row, const QString& value);

private:
    QMap<QString, Migration> _migrations;
};

#endif // PATCH_H
