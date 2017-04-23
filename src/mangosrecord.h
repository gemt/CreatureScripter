#ifndef MANGOSRECORD_H
#define MANGOSRECORD_H

#include <QSqlRecord>
class MangosRecord : public QSqlRecord
{
public:
    MangosRecord(const QSqlRecord& other, const QString& pk, const QString& pv);
    QString key();
    QString keyVal();
private:
    QString pKey;
    QString pVal;
};

#endif // MANGOSRECORD_H
