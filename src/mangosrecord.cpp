#include "mangosrecord.h"
#include "cache.h"

MangosRecord::MangosRecord(const MangosRecord &other) :
    original(other.original),
    editable(other.editable),
    table(other.table)
{
}

MangosRecord::MangosRecord(const QSqlRecord& other, const QString& table) :
    original(other),
    editable(other),
    table(table)
{

}

void MangosRecord::operator=(const MangosRecord &other)
{
    this->editable = other.editable;
    this->original = other.original;
    this->table = other.table;
}

QVariant MangosRecord::value(int index) const
{
    return editable.value(index);
}

QVariant MangosRecord::value(const QString &name) const
{
    return editable.value(name);
}

QString MangosRecord::fieldName(int index) const
{
    return editable.fieldName(index);
}

QSqlField MangosRecord::field(int index) const
{
    return editable.field(index);
}

QSqlField MangosRecord::field(const QString &name) const
{
    return editable.field(name);
}

int MangosRecord::indexOf(const QString &name) const
{
    return editable.indexOf(name);
}

int MangosRecord::count() const
{
    return editable.count();
}

void MangosRecord::setValue(int index, const QVariant &val)
{
    editable.setValue(index, val);
    emit valueChanged(fieldName(index), val);
}

void MangosRecord::setValue(const QString &name, const QVariant &val)
{
    editable.setValue(name, val);
    emit valueChanged(name, val);
}

QString MangosRecord::GetChanges() const
{
    /*
    QString str;
    QSqlDatabase db = Cache::Get().GetDB();
    for(int i = 0; i < oldRecord.count(); i++){
        if(original.value(i) != editable.value(i)){
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
    */
    return "";
}
