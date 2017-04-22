#include "migration.h"
#include "cache.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlField>
#include <QDebug>

Migrations::Migration::Migration(const char* table, const QString& field, const QString& fieldVal,
                     const QString& pKey, const QString pVal)
{

    QSqlDatabase db = Cache::Get().GetDB();

    QSqlField fv;
    fv.setName(field);
    fv.setValue(fieldVal);
    fv.setType(QVariant::String);
    QString qry = QString("SELECT * from %1 WHERE %2=%3")
            .arg(db.driver()->escapeIdentifier(Cache::Get().Table(table), QSqlDriver::TableName),
                 db.driver()->escapeIdentifier(field, QSqlDriver::FieldName),
                 db.driver()->formatValue(fv));

    if(!pKey.isEmpty()) {
        fv.setName(pKey);
        fv.setValue(pVal);
        qry += QString(" and %1=%2")
                .arg(db.driver()->escapeIdentifier(pKey, QSqlDriver::FieldName),
                     db.driver()->formatValue(fv));
    }

    QSqlQuery q = db.exec(qry);
    if(!q.next())
        throw std::runtime_error(QString("Migration ctor could not find %1").arg(qry).toStdString().c_str());

    record = q.record();
    if(q.next())
        throw std::runtime_error(QString("Migration query got more than 1 result: %1").arg(qry).toStdString().c_str());
}

void Migrations::Migration::Update(const QString &field, const QString &fieldVal)
{
    if(!record.contains(field))
        throw std::logic_error(QString("Migration::Update: field: %1 does not exist in record.").arg(field).toStdString().c_str());
    record.setValue(field, fieldVal);
}

void Migrations::AddMigration(const char* table, const QString &field, const QString &fieldVal,
                              const QString& pKey, const QString pVal)
{
    QString key = pKey.isEmpty() ? field : pKey;
    auto iter = _migrations.find(key);
    if(iter != _migrations.end()){
        iter->Update(field, fieldVal);
    }else{
        _migrations.insert(key, Migration(table, field, fieldVal, pKey, pVal));
    }
}
