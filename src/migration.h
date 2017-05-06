#ifndef PATCH_H
#define PATCH_H

#include <QString>
#include <QSqlRecord>
#include <QMap>
#include <QDebug>

class UpdateMigration
{
public:
    UpdateMigration(const QString& table, const QSqlRecord& newRecord, const QSqlRecord& oldRecord);
    QString toString();
private:
    QString table;
    const QSqlRecord& newRecord;
    const QSqlRecord& oldRecord;
};

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

#endif // PATCH_H
