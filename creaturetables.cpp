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

class TableView : public QTableView
{
public:

};

CreatureTable::CreatureTable(const QString &table, QString key, QString value, QWidget* parent) :
    QWidget(parent)
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

    tableView = new QTableView(this);
    tableView->setModel(tableModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->hide();

    collapseBtn = new QPushButton(table);
    connect(collapseBtn, &QPushButton::clicked, this, &CreatureTable::OnCollapse);

    QVBoxLayout* l = new QVBoxLayout(this);
    setLayout(l);
    l->addWidget(collapseBtn);
    l->addWidget(tableView);
}

void CreatureTable::OnCollapse()
{
    tableView->setHidden(!tableView->isHidden());
}


CreatureTables::CreatureTables(uint entry, QWidget* parent) :
    QScrollArea(parent)
{
    QVBoxLayout* l = new QVBoxLayout(this);
    setLayout(l);
    CreatureTable* table;
    table = new CreatureTable(Tables::creature, "id", QString("%1").arg(entry), this);
    table->tableView->setMouseTracking(true);
    connect(table->tableView, &QTableView::entered, [](const QModelIndex& i){
        static int prevR=-1;
        if(i.row() == prevR) return;
        prevR = i.row();
        if(i.column() == 2){
            bool ok;
            int entry = i.data().toInt(&ok);
            if(!ok) return;
            QToolTip::hideText();
            QToolTip::showText(QCursor::pos(), Cache::Get().MapName(entry));
        }
    });
    tables[Tables::creature] = table;
    l->addWidget(table);
}


