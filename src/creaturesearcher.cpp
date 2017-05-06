#include "cache.h"
#include "creaturesearcher.h"
#include "warnings.h"
#include "tables.h"

#include <QHeaderView>
#include <QDebug>
#include <QSqlQuery>
#include <QSettings>
#include <QSqlField>
#include <QSqlDriver>
#include <QModelIndex>
#include <QSqlQueryModel>
#include <utility>
#include <QSqlError>
/*
"SELECT DISTINCT %1.%2, %1.%3, %4.%5 FROM %1"
" INNER JOIN %6 ON %1.%2=%6.%7"
" INNER JOIN map_template ON creature.map=map_template.Entry"
" WHERE %1.%3 LIKE %8 AND %4.%9 IN (%10)";
*/
class CreatureSearcherModel : public QSqlQueryModel
{
private:
    QSqlDatabase _db;
    QSettings settings;
    QString baseQuery;
    QString filter;
    QVector<int> entryZoneFilter;
    QString nameFilter;
    QString mapFilter;
    static const QString nameAndMapQ;
    static const QString nameQ;
    static const QString mapQ;
    QString MakeQuery(){

        QString ret = nameAndMapQ
                .arg(Tables::worldTable<Tables::creature_template>())   //1
                .arg(Tables::creature_template::entry)                  //2
                .arg(Tables::creature_template::name)                   //3
                .arg(Tables::worldTable<Tables::map_template>())        //4
                .arg(Tables::map_template::mapname)                     //5
                .arg(Tables::worldTable<Tables::creature>())            //6
                .arg(Tables::creature::id)                              //7
                .arg(nameFilter)                                        //8
                .arg(Tables::map_template::entry)                       //9
                .arg(mapFilter);                                        //10
        if(mapFilter.isEmpty()){
            int idx = ret.indexOf(" AND ");
            ret.remove(idx, ret.size()-idx);
        }
        return ret;
    }

public:
    CreatureSearcherModel(QObject* parent, const QSqlDatabase& db) :
        QSqlQueryModel(parent),
        _db(db)
    {
        /*
        QString sel = QString("SELECT DISTINCT %1.%2, %3.%4, %5.%6")
                .arg(Tables::worldTable<Tables::creature_template>())
                .arg(Tables::creature_template::entry)
                .arg(Tables::worldTable<Tables::creature_template>())
                .arg(Tables::creature_template::name)
                .arg(Tables::worldTable<Tables::map_template>())
                .arg(Tables::map_template::mapname);

        QString mapName ="a", nameName = "b";
        QString nameAndMap = QString(
        "SELECT DISTINCT %1.%2, %1.%3, %4.%5 FROM %1"
        " INNER JOIN %6 ON %1.%2=%6.%7"
        " INNER JOIN map_template ON creature.map=map_template.Entry"
        " WHERE %1.%3 LIKE %8 AND %4.%5 LIKE %9")
                .arg(Tables::worldTable<Tables::creature_template>())   //1
                .arg(Tables::creature_template::entry)                  //2
                .arg(Tables::creature_template::name)                   //3
                .arg(Tables::worldTable<Tables::map_template>())        //4
                .arg(Tables::map_template::mapname)                     //5
                .arg(Tables::worldTable<Tables::creature>())            //6
                .arg(Tables::creature::id)                              //7
                .arg(Tables::EscapedVal(nameName))
                .arg(Tables::EscapedVal(mapName));
        */
        //Search("");
        //SetZoneFilter("");
        qDebug() << MakeQuery();
        setQuery(MakeQuery(), _db);
        //QString fin = baseQuery.arg()

        //"%tiger%" AND map_template.MapName LIKE "%%"")

        baseQuery = QString("SELECT %1, %2 FROM %3")
                .arg(Tables::creature_template::entry,
                     Tables::creature_template::name,
                     Tables::worldTable<Tables::creature_template>());
                     //Tables::creature_template::t);
                     //Cache::Get().Table(Tables::creature_template::t));
        setQuery(baseQuery, _db);

        //setHeaderData(0, Qt::Horizontal, tr("Entry"));
        //setHeaderData(1, Qt::Horizontal, tr("Name"));
    }

    void Search(const QString &s)
    {
        if(s.isEmpty()){
            nameFilter = "\"%%\"";
        }else{
            QSqlField m;
            m.setType(QVariant::String);
            m.setValue(QString("%%1%").arg(s));
            nameFilter = _db.driver()->formatValue(m);
        }
        qDebug() << "Search: " << MakeQuery();
        setQuery(MakeQuery(), _db);
        /*
        if(s.isEmpty() && !filter.isEmpty())
            setQuery(baseQuery, _db);
        else if(s != filter){
            QSqlField f;
            f.setType(QVariant::String);
            f.setValue(QString("%%1%").arg(s));
            QString filt = QString("WHERE name LIKE %1 OR entry LIKE %1")
                    .arg(_db.driver()->formatValue(f));
            setQuery(baseQuery + " " + filt, _db);
        }
        filter = s;
        */
    }
    void SetZoneFilter(const QString& s)
    {
        /*
        if(s.isEmpty()){
            mapFilter = "%%";
        }else{
            QSqlField m;
            m.setType(QVariant::String);
            m.setValue(QString("%%1%").arg(s));
            mapFilter = _db.driver()->formatValue(m);
        }
        qDebug() << "Zone: " << MakeQuery();
        */

        QVector<int> mapMatches;
        const QVector<std::pair<unsigned int, QString>>& maps = Cache::Get().GetMapVec();
        for(int i = 0; i < maps.size(); i++){
            if(maps.at(i).second.toLower().contains(s)){
                mapMatches.push_back(maps.at(i).first);
            }

        }

        QString inQ;
        if(mapMatches.isEmpty()){
            inQ += "-1";
        }else{
            foreach(int i, mapMatches){
                if(!inQ.isEmpty())
                    inQ += ", ";
                inQ += QString::number(i);
            }
        }
        if(mapFilter == inQ)
            return;

        mapFilter = inQ;
        qDebug() << "Zone: " << MakeQuery();
        setQuery(MakeQuery(), _db);
    }
};
const QString CreatureSearcherModel::nameAndMapQ =
        "SELECT DISTINCT %1.%2, %1.%3, %4.%5 FROM %1"
        " INNER JOIN %6 ON %1.%2=%6.%7"
        " INNER JOIN map_template ON creature.map=map_template.Entry"
        " WHERE (%1.%3 LIKE %8 OR %1.%2 LIKE %8) AND %4.%9 IN (%10)";

const QString CreatureSearcherModel::nameQ =
        "SELECT %1, %2 FROM %3.%4";

const QString CreatureSearcherModel::mapQ =
        "SELECT DISTINCT %1.%2, %1.%3, %4.%5 FROM %1"
        " INNER JOIN %6 ON %1.%2=%6.%7"
        " INNER JOIN map_template ON creature.map=map_template.Entry"
        " WHERE %4.%5 LIKE %8";

CreatureSearcher::CreatureSearcher(QWidget *parent, const QSqlDatabase &db) :
    QTableView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    model = new CreatureSearcherModel(this, db);
    setModel(model);
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->hide();
    connect(this, &QTableView::clicked, this, &CreatureSearcher::onActivated);

}

void CreatureSearcher::Search(const QString &s)
{
    model->Search(s);
}

void CreatureSearcher::SetZoneFilter(const QString &s)
{
    model->SetZoneFilter(s);
}

void CreatureSearcher::onActivated(const QModelIndex &idx)
{
    bool ok;
    int entry = idx.model()->index(idx.row(), 0).data().toUInt(&ok);
    QString name = idx.model()->index(idx.row(),1).data().toString();
    if(!ok){
        Warnings::Warning("Error occured when reading entry on selected line");
    }else{
        emit entrySelected(entry, name);
    }
}




