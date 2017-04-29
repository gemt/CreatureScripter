#include "mangoscreature.h"
#include "cache.h"

#include <QSqlQuery>
#include <QSqlDriver>

namespace CreatureRecord
{
QSqlRecord LoadSingleRecord(QSqlDatabase& db, const QString& table, const QString& key, const QVariant& value)
{
    QSqlQuery q(db);
    QSqlField f;
    f.setValue(value);
    QString query = QString("SELECT * FROM %1 WHERE %2 = %3")
            .arg(db.driver()->escapeIdentifier(table, QSqlDriver::TableName),
                 db.driver()->escapeIdentifier(key, QSqlDriver::FieldName),
                 db.driver()->formatValue(f));
    if(!q.exec(query)){
        throw std::runtime_error(QString("Query failed: %1").arg(query).toStdString());
    }

}

CreatureTemplate::CreatureTemplate(quint32 entry)
{
    QSqlDatabase db = Cache::Get().GetDB();
    QSqlQuery q;
    //creature_template = LoadSingleRecord(db, Tables::creature_template::dbTable(), );
}

}
