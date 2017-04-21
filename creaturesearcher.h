#ifndef CREATURESEARCHER_H
#define CREATURESEARCHER_H

#include <QTableView>
#include <QSqlTableModel>

class CreatureSearcherModel;
class CreatureSearcher : public QTableView
{
public:
    CreatureSearcher(QWidget* parent, const QSqlDatabase& db);
    void Search(const QString& s);

private:
    CreatureSearcherModel* model;
};

#endif // CREATURESEARCHER_H
