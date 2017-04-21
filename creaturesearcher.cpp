#include "tables.h"
#include "creaturesearcher.h"

#include <QHeaderView>
#include <Qdebug>
#include <QSqlQuery>
#include <QSettings>
#include <QSqlField>
#include <QSqlDriver>
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
            QString qry = QString("%%1%").arg(s);
            f.setValue(qry);
            QString filt = QString("name LIKE %1").arg(_db.driver()->formatValue(f));
            qDebug() << filt;
            setFilter(filt);
        }
        //select();
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

    //connect(this, QTableView::doubleClicked, )

}

void CreatureSearcher::Search(const QString &s)
{
    model->Search(s);
}




