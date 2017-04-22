#include "cache.h"
#include "creaturesearcher.h"
#include "warnings.h"

#include <QHeaderView>
#include <Qdebug>
#include <QSqlQuery>
#include <QSettings>
#include <QSqlField>
#include <QSqlDriver>
#include <QModelIndex>

class CreatureSearcherModel : public QSqlTableModel
{
private:
    QSqlDatabase _db;
    QSettings settings;
public:
    CreatureSearcherModel(QObject* parent, const QSqlDatabase& db) :
        QSqlTableModel(parent, db),
        _db(db)
    {
        setTable(Tables::creature_template);
        setEditStrategy(QSqlTableModel::OnManualSubmit);
        setHeaderData(0, Qt::Horizontal, tr("Entry"));
        setHeaderData(1, Qt::Horizontal, tr("Name"));
        select();
    }

    void Search(const QString &s)
    {
        if(s.isEmpty())
            setFilter(s);
        else{
            QSqlField f;
            f.setType(QVariant::String);
            f.setValue(QString("%%1%").arg(s));
            QString filt = QString("name LIKE %1").arg(_db.driver()->formatValue(f));
            setFilter(filt);
        }
        //select();
    }

public:
    bool setData(const QModelIndex &, const QVariant &, int) override
    {
        // Absofuckinglutely no editing allowed
        return false;
    }
};

CreatureSearcher::CreatureSearcher(QWidget *parent, const QSqlDatabase &db) :
    QTableView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    model = new CreatureSearcherModel(this, db);
    setModel(model);
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->hide();

    // only showing entry and name columns
    for(int i = 0; i < model->columnCount(); i++)
        if(i != 0 && i != 7)
            hideColumn(i);

    connect(this, &QTableView::activated, this, &CreatureSearcher::onActivated);

}

void CreatureSearcher::Search(const QString &s)
{
    model->Search(s);
}

void CreatureSearcher::onActivated(const QModelIndex &idx)
{
    bool ok;
    int entry = idx.model()->index(idx.row(), 0).data().toUInt(&ok);
    QString name = idx.model()->index(idx.row(),7).data().toString();
    if(!ok){
        Warnings::Warning("Error occured when reading entry on selected line");
    }else{
        emit entrySelected(entry, name);
    }
}




