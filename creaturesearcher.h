#ifndef CREATURESEARCHER_H
#define CREATURESEARCHER_H

#include <QTableView>
#include <QSqlTableModel>

class CreatureSearcherModel;
class CreatureSearcher : public QTableView
{
    Q_OBJECT
public:
    CreatureSearcher(QWidget* parent, const QSqlDatabase& db);
    void Search(const QString& s);

signals:
    void entrySelected(uint entry);

private slots:
    void onActivated(const QModelIndex& idx);

private:
    CreatureSearcherModel* model;
};

#endif // CREATURESEARCHER_H
