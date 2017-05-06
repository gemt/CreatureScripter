#ifndef CREATURESEARCHER_H
#define CREATURESEARCHER_H

#include <QTableView>
#include <QSqlTableModel>

class CreatureSearcherModel;
class Creature;
class CreatureSearcher : public QTableView
{
    Q_OBJECT
public:
    CreatureSearcher(QWidget* parent, const QSqlDatabase& db);
public slots:
    void Search(const QString& s);
    void SetZoneFilter( const QString& s);
signals:
    void entrySelected(uint entry, QString name);

private slots:
    void onActivated(const QModelIndex& idx);

private:
    CreatureSearcherModel* model;
};

#endif // CREATURESEARCHER_H
