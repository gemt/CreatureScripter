#include "cache.h"
#include "creaturesearcher.h"
#include "warnings.h"
#include "tables.h"

#include <QHeaderView>
#include <Qdebug>
#include <QSqlQuery>
#include <QSettings>
#include <QSqlField>
#include <QSqlDriver>
#include <QModelIndex>
#include <QSqlQueryModel>
class CreatureSearcherModel : public QSqlQueryModel
{
private:
    QSqlDatabase _db;
    QSettings settings;
    QString baseQuery;
    QString filter;
public:
    CreatureSearcherModel(QObject* parent, const QSqlDatabase& db) :
        QSqlQueryModel(parent),
        _db(db)
    {
        baseQuery = QString("SELECT %1, %2 FROM %3")
                .arg(Tables::creature_template::entry,
                     Tables::creature_template::name,
                     Tables::dbtable<Tables::creature_template>());
                     //Tables::creature_template::t);
                     //Cache::Get().Table(Tables::creature_template::t));
        setQuery(baseQuery, _db);
        //setHeaderData(0, Qt::Horizontal, tr("Entry"));
        //setHeaderData(1, Qt::Horizontal, tr("Name"));
    }

    void Search(const QString &s)
    {
        if(s.isEmpty() && !filter.isEmpty())
            setQuery(baseQuery, _db);
        else if(s != filter){
            QSqlField f;
            f.setType(QVariant::String);
            f.setValue(QString("%%1%").arg(s));
            QString filt = QString("WHERE name LIKE %1 OR entry LIKE %1").arg(_db.driver()->formatValue(f));
            setQuery(baseQuery + " " + filt, _db);
        }
        filter = s;
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
    QString name = idx.model()->index(idx.row(),1).data().toString();
    if(!ok){
        Warnings::Warning("Error occured when reading entry on selected line");
    }else{
        emit entrySelected(entry, name);
    }
}




