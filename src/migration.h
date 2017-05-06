#ifndef PATCH_H
#define PATCH_H

#include "mangosrecord.h"

#include <QString>
#include <QSqlRecord>
#include <QMap>
#include <QDebug>

class UpdateMigration
{
public:
    UpdateMigration(const QString& table, const MangosRecord& newRecord, const MangosRecord& oldRecord);
    QString toString();
private:
    QString table;
    const MangosRecord& newRecord;
    const MangosRecord& oldRecord;
};
#if 0
class Migrations
{
private:
    class Migration
    {
    public:
        Migration(const QString& table, const QString& pKey, const QString pVal);

        void Update(const QString& field, const QString& fieldVal);
        QString ToString();

    private:
        QString _key;
        QSqlRecord record;
        QSqlRecord origRecord;
    };

public:
    void AddMigration(const QString& table, const QString& field, const QString& fieldVal,
                      const QString& pKey = QString(), const QString pVal = QString());
    QString toString();

private:
    QMap<QString, Migration> _migrations;


};
#endif
#endif // PATCH_H
