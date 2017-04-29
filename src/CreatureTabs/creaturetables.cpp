#include "creaturetables.h"
#include "cache.h"

#include <QSqlTableModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QSqlField>
#include <QSqlDriver>
#include <QPushButton>
#include <QHeaderView>
#include <QToolTip>
#include <QCursor>
#include <QMouseEvent>
#include <QSplitter>
#if 0
class NoEditTableModel : public QSqlQueryModel
{
public:
    NoEditTableModel(const QString &table, QString key, QString value, QWidget* parent) :
        QSqlQueryModel(parent)
    {
        QSqlDatabase db = Cache::Get().GetDB();
        QSqlField f;
        f.setType(QVariant::String);
        f.setValue(value);
        QString qry = QString("SELECT * FROM %1 WHERE %2=%3")
                .arg(db.driver()->escapeIdentifier(table, QSqlDriver::TableName),
                     db.driver()->escapeIdentifier(key, QSqlDriver::FieldName),
                     db.driver()->formatValue(f));
        setQuery(qry, db);
    }
};

class cCreatureTable : public CreatureTable
{
public:
   cCreatureTable(const QString &table, QString key, QString value, QWidget* parent) :
       CreatureTable(table,key,value,parent){
       setMouseTracking(true);
   }

   void mouseMoveEvent(QMouseEvent *event) override
   {
       QModelIndex i = QTableView::indexAt(event->pos());
       static int prevR=-1;
       if(i.row() == prevR) return;
       prevR = i.row();
       if(i.column() == 2){
           bool ok;
           int entry = i.data().toInt(&ok);
           if(!ok) return;
           //QToolTip::hideText();
           QToolTip::showText(mapToGlobal(visualRect(i).topRight()), Cache::Get().MapName(entry));
       }else {
           QToolTip::hideText();
       }
   }
};

CreatureTable::CreatureTable(const QString &table, QString key, QString value, QWidget* parent) :
    QTableView(parent)
{
    QSqlDatabase db = Cache::Get().GetDB();
    tableModel = new NoEditTableModel(table, key, value, this);
    setModel(tableModel);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setStretchLastSection(true);
}



CreatureTables::CreatureTables(uint entry, QWidget* parent) :
    QTabWidget(parent)
{
    setContentsMargins(0,0,0,0);
    setContentsMargins(0,0,0,0);
    setMouseTracking(true);
    QString sEntry = QString("%1").arg(entry);
    //AddTable<cCreatureTable>(Tables::creature::t(),                   Tables::creature::entry, sEntry);
    //AddTable<CreatureTable>(Tables::creature_template::t(),           Tables::creature_template::entry, sEntry);
    //AddTable<CreatureTable>(Tables::creature_equip_template::t(),     Tables::creature_equip_template::entry, sEntry);
    //AddTable<CreatureTable>(Tables::creature_equip_template_raw::t(), Tables::creature_equip_template_raw::entry, sEntry);

    //AddTable<CreatureTable>(Tables::creature_addon,                 "entry", sEntry);
    //AddTable<CreatureTable>(Tables::creature_ai_scripts,            "creature_id", sEntry);
    AddTable<CreatureTable>(Tables::creature_ai_summons,            "id", sEntry);
    //AddTable<CreatureTable>(Tables::creature_ai_texts,              "entry", sEntry);
    //AddTable<CreatureTable>(Tables::creature_battleground,          "entry", sEntry);
    //AddTable<CreatureTable>(Tables::creature_groups,                "entry", sEntry);
    AddTable<CreatureTable>(Tables::creature_involved_relation,     "id", sEntry); //not sure
    AddTable<CreatureTable>(Tables::creature_loot_template,         "entry", sEntry);
    //AddTable<CreatureTable>(Tables::creature_model_info,            "entry", sEntry);
    AddTable<CreatureTable>(Tables::creature_movement,              "id", sEntry);
    //AddTable<CreatureTable>(Tables::creature_movement_scripts,      "entry", sEntry);
    AddTable<CreatureTable>(Tables::creature_movement_template,     "entry", sEntry); // not sure
    AddTable<CreatureTable>(Tables::creature_onkill_reputation,     "creature_id", sEntry);
    AddTable<CreatureTable>(Tables::creature_questrelation,         "id", sEntry);
    //AddTable<CreatureTable>(Tables::creature_spells,                "entry", sEntry); //empty
    //AddTable<CreatureTable>(Tables::creature_template_addon::t(),        "entry", sEntry);

    setTabShape(TabShape::Rounded);
}

std::pair<QString, QSqlRecord> CreatureTables::GetSingleRecord(const QString& table)
{
    auto it = tables.find(table);
    if(it == tables.end())
        throw std::logic_error(QString("CreatureTables::GetSingleRecord - unable to find table %1")
                               .arg(table).toStdString().c_str());

    CreatureTable* t = it->second;
    if(t->tableModel->rowCount() > 1)
        throw std::logic_error(QString("CreatureTables::GetSingleRecord - requested table (%1) contains %2 records")
                               .arg(table, t->tableModel->rowCount()).toStdString().c_str());
    if(t->tableModel->rowCount())
        return std::make_pair(table,t->tableModel->record(0));
    else
        return std::make_pair(table,QSqlRecord());
}




#endif
