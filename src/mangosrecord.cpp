#include "mangosrecord.h"
#include "cache.h"
#include "cache.h"

#include <QApplication>
#include <QClipboard>
#include <QSqlDriver>

MangosRecord::MangosRecord(const MangosRecord &other) :
    original(other.original),
    editable(other.editable),
    table(other.table),
    pk(other.pk)

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
    this->pk = other.pk;
}

void MangosRecord::InsertToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString str = QString("INSERT INTO %1\n(%2)\nVALUES\n(%3);");
    QString arg1, arg2;
    QSqlDatabase db = Cache::Get().GetDB();
    for(int i = 0; i < editable.count(); i++)
    {
        if(!arg1.isEmpty()){
            arg1+= ", ";
            arg2+= ", ";
        }

        arg1 += db.driver()->escapeIdentifier(editable.fieldName(i), QSqlDriver::FieldName);
        arg2 += db.driver()->formatValue(editable.field(i));
    }
    str = str.arg(db.driver()->escapeIdentifier(table, QSqlDriver::TableName),
                  arg1, arg2);
    clipboard->setText(str);
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
    //emit valueChanged(table, fieldName(index), val, pk, original.value(pk));
    emit valueChanged(*this);
}

void MangosRecord::setValue(const QString &name, const QVariant &val)
{
    editable.setValue(name, val);
    //emit valueChanged(table, name, val, pk, original.value(pk));
    emit valueChanged(*this);
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
