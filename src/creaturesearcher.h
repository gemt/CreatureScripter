#ifndef CREATURESEARCHER_H
#define CREATURESEARCHER_H

#include <QTableView>
#include <QSqlTableModel>
#include <QMap>

#include "loadingscreen.h"

class CreatureSearchModel2;
class Creature;
class CreatureModelCreature;
class QSqlDatabase;

class CreatureSearcher : public QTableView
{
    Q_OBJECT
public:
    CreatureSearcher(QWidget* parent, const QSqlDatabase& db, LoadingScreen& ls);
public slots:
    void Search(const QString& s);
    void SetZoneFilter( const QString& s);
signals:
    void entrySelected(uint entry, QString name);

private slots:
    void onActivated(const QModelIndex& idx);

private:
    CreatureSearchModel2* model;
    QMap<int,CreatureModelCreature> creatures;
    void Load(LoadingScreen& ls);
};

#endif // CREATURESEARCHER_H
