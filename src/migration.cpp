#include "migration.h"
#include "cache.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlField>
#include <QDebug>

#if 0
Migrations::Migration::Migration(const QString& table, const QString& pKey, const QString pVal)
    : _key(pKey)
{

    QSqlDatabase db = Cache::Get().GetDB();

    QSqlField fv;
    fv.setName(pKey);
    fv.setValue(pVal);
    fv.setType(QVariant::String);
    QString qry = QString("SELECT * from %1 WHERE %2=%3")
            .arg(db.driver()->escapeIdentifier(table, QSqlDriver::TableName),
                 db.driver()->escapeIdentifier(pKey, QSqlDriver::FieldName),
                 db.driver()->formatValue(fv));

    QSqlQuery q = db.exec(qry);
    if(!q.next())
        throw std::runtime_error(QString("Migration ctor could not find %1").arg(qry).toStdString().c_str());

    record = q.record();
    origRecord = record;
    if(q.next())
        throw std::runtime_error(QString("Migration query got more than 1 result: %1").arg(qry).toStdString().c_str());
}

void Migrations::Migration::Update(const QString &field, const QString &fieldVal)
{
    Q_ASSERT(field != _key);
    if(!record.contains(field))
        throw std::logic_error(QString("Migration::Update: field: %1 does not exist in record.").arg(field).toStdString().c_str());
    record.setValue(field, fieldVal);
}

QString Migrations::Migration::ToString()
{
    QString ret;
    for(int i = 0; i < record.count(); i++){
        //ret += QString("DELETE FROM %1 WHERE %2=%3")
        //        .arg()
    }
    return ret;
}

void Migrations::AddMigration(const QString& table, const QString &field, const QString &fieldVal,
                              const QString& pKey, const QString pVal)
{
    QString key = pKey.isEmpty() ? field : pKey;
    auto iter = _migrations.find(key);
    if(iter != _migrations.end()){
        iter->Update(field, fieldVal);
    }else{
        //_migrations.insert(key, Migration(table, field, fieldVal, pKey, pVal));
    }
}

QString Migrations::toString()
{
    QString ret;
    for(auto it = _migrations.begin(); it != _migrations.end(); it++){
        //it.value().record;
    }
    return ret;
}
#endif

UpdateMigration::UpdateMigration(const QString &table,  const MangosRecord& newRecord, const MangosRecord& oldRecord)
    : table(table),
      newRecord(newRecord),
      oldRecord(oldRecord)
{
    Q_ASSERT(newRecord.count() == oldRecord.count());
}

QString UpdateMigration::toString()
{
    QString str;
    QSqlDatabase db = Cache::Get().GetDB();
    for(int i = 0; i < oldRecord.count(); i++){
        if(oldRecord.value(i) != newRecord.value(i)){
            if(!str.isEmpty())
                str += ", ";
            QString fieldName = db.driver()->escapeIdentifier(oldRecord.fieldName(i), QSqlDriver::FieldName);
            QSqlField field(newRecord.field(i));
            QString val = db.driver()->formatValue(field);
            str += fieldName + "=" + val;
        }
    }
    str.prepend(QString("UPDATE %1 SET ").arg(table));
    str += ";";
    return str;
}
