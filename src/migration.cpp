#include "migration.h"
#include "cache.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlField>
#include <QDebug>

Migration::Migration(const char* table, const QString& field, const QString& fieldVal)
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

    QSqlQuery q = db.exec(qry);
    if(!q.next())
        throw std::runtime_error(QString("Migration ctor could not find %1").arg(qry).toStdString().c_str());

    record = q.record();
    if(q.next())
        throw std::runtime_error(QString("Migration query got more than 1 result: %1").arg(qry).toStdString().c_str());
}
