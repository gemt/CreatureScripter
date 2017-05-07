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
    QString MakeQuery(){

        QString ret = nameAndMapQ
                .arg(Tables::worldTable<Tables::creature_template>())   //1
                .arg(Tables::creature_template::entry)                  //2
                .arg(Tables::creature_template::name)                   //3
                .arg(Tables::worldTable<Tables::map_template>())        //4
                .arg(Tables::map_template::mapname)                     //5
                .arg(Tables::worldTable<Tables::creature>())            //6
                .arg(Tables::creature::id)                              //7
                .arg(Tables::map_template::entry)                       //8
                .arg(Tables::creature::map)                             //9
                .arg(Tables::map_template::entry)                       //10
                .arg(mapFilter)                                         //11
                .arg(Tables::creature_template::AIName)                 //12
                ;
        ret.replace("_@NAMEFILTER@_", nameFilter);
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
        setQuery(MakeQuery(), _db);
        baseQuery = QString("SELECT %1, %2 FROM %3")
                .arg(Tables::creature_template::entry,
                     Tables::creature_template::name,
                     Tables::worldTable<Tables::creature_template>());
        setQuery(baseQuery, _db);
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
        setQuery(MakeQuery(), _db);
    }
    void SetZoneFilter(const QString& s)
    {
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
        setQuery(MakeQuery(), _db);
    }
};
const QString CreatureSearcherModel::nameAndMapQ =
        "SELECT DISTINCT %1.%2, %1.%3, %4.%5, %1.%12 FROM %1"
        " INNER JOIN %6 ON %1.%2=%6.%7"
        " INNER JOIN %4 ON %6.%9=%4.%10"
        " WHERE (%1.%3 LIKE _@NAMEFILTER@_ OR %1.%2 LIKE _@NAMEFILTER@_) AND %4.%8 IN (%11)";

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




