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

class NoEditTableModel : public QSqlTableModel
{
public:
    NoEditTableModel(QWidget* parent, QSqlDatabase db) :
        QSqlTableModel(parent, db)
    { }
    bool setData(const QModelIndex &, const QVariant &, int) override
    {
        //no editing!
        return false;
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
    tableModel = new NoEditTableModel(this, db);
    tableModel->setTable(table);
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QSqlField f;
    f.setType(QVariant::String);
    f.setValue(value);
    QString filt = QString("%1=%2").arg(key, db.driver()->formatValue(f));
    tableModel->setFilter(filt);
    tableModel->select();

    setModel(tableModel);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalHeader()->hide();
    horizontalHeader()->setStretchLastSection(true);
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
}



CreatureTables::CreatureTables(uint entry, QWidget* parent) :
    QTabWidget(parent)
{
    setContentsMargins(0,0,0,0);
    setContentsMargins(0,0,0,0);
    setMouseTracking(true);
    QString sEntry = QString("%1").arg(entry);
    //QTabWidget::tabBar()-
    AddTable<cCreatureTable>(Tables::creature, "id", sEntry);
    AddTable<CreatureTable>(Tables::creature_template,              "entry", sEntry);

    //AddTable<CreatureTable>(Tables::creature_addon,                 "entry", sEntry);
    AddTable<CreatureTable>(Tables::creature_ai_scripts,            "creature_id", sEntry);
    AddTable<CreatureTable>(Tables::creature_ai_summons,            "id", sEntry);
    //AddTable<CreatureTable>(Tables::creature_ai_texts,              "entry", sEntry);
    //AddTable<CreatureTable>(Tables::creature_battleground,          "entry", sEntry);
    //AddTable<CreatureTable>(Tables::creature_equip_template,        "entry", sEntry);
    AddTable<CreatureTable>(Tables::creature_equip_template_raw,    "entry", sEntry);
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
    AddTable<CreatureTable>(Tables::creature_template_addon,        "entry", sEntry);

    setTabShape(TabShape::Rounded);
    //setStyleSheet(QString("QTabBar::tab { width: %200px; } ").arg(size().width()/count()));

}




