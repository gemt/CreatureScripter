#ifndef PATCH_H
#define PATCH_H

#include <QString>
#include <QSqlRecord>
#include <QMap>

class Migrations
{
private:
    class Migration
    {
    public:
        Migration(const char* table, const QString& field, const QString& fieldVal,
                  const QString& pKey, const QString pVal);

        void Update(const QString& field, const QString& fieldVal);

    private:
        QSqlRecord record;

    };
public:
    void AddMigration(const char* table, const QString& field, const QString& fieldVal,
                      const QString& pKey = QString(), const QString pVal = QString());

private:
    QMap<QString, Migration> _migrations;


};

#endif // PATCH_H
