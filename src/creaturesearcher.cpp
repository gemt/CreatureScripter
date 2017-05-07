#include "cache.h"
#include "creaturesearcher.h"
#include "warnings.h"
#include "tables.h"
#include "timer.h"


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
#include <QMap>
#include <QStandardItemModel>
#include <QSet>
#include <QVector>

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

struct CreatureModelCreature{
    int entry;
    QString name;
    QSet<int> maps;
    QString aiType;
};

class CreatureSearchModel2 : public QStandardItemModel
{
public:
    CreatureSearchModel2(QWidget* parent)
        :QStandardItemModel(parent)
    {
    }
    void SetItem(CreatureModelCreature& c){

    }
    void Search(const QString &s){

    }
    void SetZoneFilter(const QString &s){

    }

private:

};

CreatureSearcher::CreatureSearcher(QWidget *parent, const QSqlDatabase &db, LoadingScreen& ls) :
    QTableView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    model = new CreatureSearchModel2(this);
    setModel(model);
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->hide();
    connect(this, &QTableView::clicked, this, &CreatureSearcher::onActivated);
    try{
        Load(ls);
    }catch(std::exception& e){
        Warnings::Warning(e.what());
    }
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

void CreatureSearcher::Load(LoadingScreen& ls){
    ls.SetMessage("Caching Creature information");
    QSqlDatabase db = Cache::Get().GetDB();
    QSqlQuery template_query(db);

    if(!template_query.exec(QString("SELECT %1,%2,%3 from %4")
                            .arg(Tables::creature_template::entry,
                                 Tables::creature_template::name,
                                 Tables::creature_template::AIName,
                                 Tables::worldTable<Tables::creature_template>()
                            ))){
        throw std::runtime_error("CreatureSearchModel::Load creature_template table failed:" + template_query.lastError().text().toStdString());
    }
    QSqlQuery creature_query(db);
    if(!creature_query.exec(QString("SELECT %1,%2 from %4")
                            .arg(Tables::creature::id,
                                 Tables::creature::map,
                                 Tables::worldTable<Tables::creature>()
                            ))){
        throw std::runtime_error("CreatureSearchModel::Load creature table failed:" + creature_query.lastError().text().toStdString());
    }
    ls.InitProgress(template_query.size() + creature_query.size());

    while(template_query.next()){
        ls.setProgress(ls.getProgress()+1);
        CreatureModelCreature creature;
        creature.entry = template_query.value(0).toInt();
        creature.name = template_query.value(1).toString();
        creature.aiType = template_query.value(2).toString();
        creatures.insert(creature.entry, std::move(creature));
    }

    if(creatures.empty())
        throw std::runtime_error("No creatures loaded");
    CreatureModelCreature* currCreature = &creatures.first();
    while(creature_query.next()){
        ls.setProgress(ls.getProgress()+1);
        int entry = creature_query.value(0).toInt();
        int map = creature_query.value(1).toInt();

        if(currCreature->entry != entry){
            auto it = creatures.find(entry);
            if(it == creatures.end()){
                qWarning() << "Loaded creature with entry: " << entry << ", but no creature_template loaded for this entry";
                continue;
            }
            currCreature = &(*it);
        }
        currCreature->maps.insert(map);
    }
}


