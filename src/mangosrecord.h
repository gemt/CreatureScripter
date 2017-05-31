#ifndef MANGOSRECORD_H
#define MANGOSRECORD_H

#include <QObject>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlField>

class MangosRecord : public QObject
{
    Q_OBJECT
public:
    MangosRecord(){}
    MangosRecord(const MangosRecord& other);
    MangosRecord(const QSqlRecord& other, const QString& table);
    ~MangosRecord(){}
    void operator=(const MangosRecord& other);

    void InsertToClipboard();

    QVariant value(int index) const;
    QVariant value(const QString& name) const;
    QString fieldName(int index) const;
    QSqlField field(int index) const;
    QSqlField field(const QString& name) const;
    int indexOf(const QString& name) const;
    int count() const;

    void setValue(int index, const QVariant& val);
    void setValue(const QString& name, const QVariant& val);

    QString GetChanges() const;

    QString table;
    QString pk;
    QSqlRecord original;
    QSqlRecord editable;
signals:
    //void valueChanged(QString table, QString field, QVariant value, QString pk, QVariant pkVal);
    void valueChanged(MangosRecord rec);

private:
};

#endif // MANGOSRECORD_H
