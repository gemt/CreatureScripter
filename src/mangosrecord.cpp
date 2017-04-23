#include "mangosrecord.h"

MangosRecord::MangosRecord(const QSqlRecord& other, const QString& pk, const QString& pv) :
    QSqlRecord(other),
    pKey(pk),
    pVal(pv)
{
}

QString MangosRecord::key()
{
    return pKey;
}

QString MangosRecord::keyVal()
{
    return pVal;
}
