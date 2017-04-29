#include "creature.h"
#include "warnings.h"

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlField>
#include <QSqlError>
#if 0
template<typename TableType>
LoadTable(TableType* t, const QString& k, const QString v)
{
    /*
    QString qs = t->Query(k, v);
    QSqlQuery q(qs, Cache::Get().GetDB());
    if(!q.exec()){
        throw std::runtime_error(QString("Error (%1) in LoadTable exec")
                                 .arg(q.lastError().text()).toStdString().c_str());
    }
    while(q.next()){
        q.record();
    }
    */
}
#endif
CreatureTable::CreatureTable(Tables::Table *t, const QString& k, const QString& v) : table(t)
{
    QString qs = t->Query(k, v);
    QSqlQuery q(qs, Cache::Get().GetDB());
    if(!q.exec()){
        throw std::runtime_error(QString("Error (%1) in query exec in CreatureTable")
                                 .arg(q.lastError().text()).toStdString().c_str());
    }
    while(q.next()){
        QSqlRecord* r = new QSqlRecord(q.record());

        //CreatureTable* child = new CreatureTable();
        //records[r] = child;
    }
    QVector<Tables::relation> relations = t->Relations();
    foreach(const Tables::relation& r, relations){

        //children.push_back(new CreatureTable(r.table, r.relationKey, r.));
    }
}

CreatureTable::~CreatureTable()
{
    qDeleteAll(children);
    delete table;
}

CreatureData::CreatureData(quint32 entry, const QString &name)
    : table(new Tables::creature_template, Tables::creature_template::entry, QString::number(entry)),
      entry(entry),name(name)
{

}
