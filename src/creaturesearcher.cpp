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
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include <QTableWidget>

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

struct CreatureModelCreature {
    CreatureModelCreature()
    {
    }

    int entry;
    QString name;
    QSet<int> maps;
    QString aiType;
    bool eventAI;
    // QStandardItem interface
public:
    QVariant data(int role) const{
        //QStandardItem::data(role);
        return QString("%1 %2").arg(entry, -6, 10).arg(name);
    }
};


class ProxyModel : public QSortFilterProxyModel
{
public:
    QString nameFilt;
    QVector<int> maps;
    bool onlyEventAI;
    int numMaps;
    ProxyModel(QWidget* parent)
        :QSortFilterProxyModel(parent),
          onlyEventAI(false)
    {
        numMaps = Cache::Get().GetMapVec().size();
    }
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
    {
        QModelIndex index0 = sourceModel()->index(source_row, 0, source_parent);
        QSet<int> mapset = sourceModel()->data(index0, Qt::UserRole+2).value<QSet<int>>();


        if(!mapset.isEmpty()){
            bool inmap = false;
            for(int i = 0; i < maps.size(); i++){
                if(mapset.contains(maps[i])){
                    inmap = true;
                    break;
                }
            }
            if(!inmap){
                return false;
            }
        }else if(maps.size() != numMaps){
            // Gets arround creatures that does not exist in a map (summoned creatures, generally)
            return false;
        }

        if(onlyEventAI && !sourceModel()->data(index0, Qt::UserRole+3).toBool())
            return false;

        QString entry = sourceModel()->data(index0, Qt::UserRole+1).toString();
        QString nameLower = sourceModel()->data(sourceModel()->index(source_row, 1, source_parent), Qt::UserRole+1).toString();
        return entry.contains(nameFilt) || nameLower.contains(nameFilt);
    }
};

CreatureSearcher::CreatureSearcher(QWidget *parent, const QSqlDatabase &db, LoadingScreen& ls) :
    QTableView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    try{
        Load(ls);
    }catch(std::exception& e){
        Warnings::Warning(e.what());
    }
    model = new QStandardItemModel(creatures.size(), 2);
    qRegisterMetaType<QSet<int>>("QSet<int>");
    int rowc = 0;
    foreach(CreatureModelCreature* cmc, creatures){
        QStandardItem* entryItem = new QStandardItem(QString::number(cmc->entry));
        entryItem->setData(QString::number(cmc->entry));
        QVariant v;
        v.setValue(cmc->maps);
        entryItem->setData(v, Qt::UserRole+2);
        entryItem->setData(cmc->eventAI, Qt::UserRole+3);
        QStandardItem* nameItem = new QStandardItem(cmc->name);
        nameItem->setData(cmc->name.toLower());
        //QStandardItem* aiItem = new QStandardItem(cmc->aiType);
        model->setItem(rowc, 0, entryItem);
        model->setItem(rowc, 1, nameItem);
        //model->setItem(rowc, 2, aiItem);
        rowc++;
    }
    model->setHorizontalHeaderLabels(QStringList{"Entry", "Name"});
    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(model);
    setModel(proxyModel);
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->hide();
    connect(this, &QTableView::clicked, this, &CreatureSearcher::onActivated);
    SetZoneFilter("");
    resizeColumnsToContents();
}

void CreatureSearcher::Search(const QString &s)
{
    proxyModel->nameFilt = s.toLower();
    proxyModel->setFilterRegExp("");
}

void CreatureSearcher::SetZoneFilter(const QString &s)
{
    proxyModel->maps.clear();
    const QVector<std::pair<unsigned int, QString>>& maps = Cache::Get().GetMapVec();
    for(int i = 0; i < maps.size(); i++){
        if(maps.at(i).second.toLower().contains(s)){
            proxyModel->maps.push_back(maps.at(i).first);
        }
    }
    proxyModel->setFilterRegExp("");
}

void CreatureSearcher::OnlyEventAI(bool on)
{
    proxyModel->onlyEventAI = on;
    proxyModel->setFilterRegExp("");
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
    qDebug() << "Starting loading creatures";

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
        CreatureModelCreature* creature = new CreatureModelCreature();
        creature->entry = template_query.value(0).toInt();
        creature->name = template_query.value(1).toString();
        creature->aiType = template_query.value(2).toString();
        creature->eventAI = creature->aiType.contains("EventAI");
        creatures.insert(creature->entry, creature);
        creatureslst.push_back(creature);
    }

    if(creatures.empty())
        throw std::runtime_error("No creatures loaded");
    CreatureModelCreature* currCreature = creatures.first();
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
            currCreature = (*it);
        }
        currCreature->maps.insert(map);
    }
    qDebug() << "Finished loading " << QString::number(creatures.size()) << " creatures";
}


