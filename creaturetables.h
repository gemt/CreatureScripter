#ifndef CREATURETABLES_H
#define CREATURETABLES_H

#include <QScrollArea>
#include <QPushButton>
#include <QMap>

class QSqlTableModel;
class QTableView;


class CreatureTable : public QWidget {
public:
    CreatureTable(const QString& table, QString key, QString value, QWidget* parent);

    QTableView* tableView;
private slots:
    void OnCollapse();

private:
    QPushButton* collapseBtn;
    QSqlTableModel* tableModel;
};


class CreatureTables : public QScrollArea
{
public:
    CreatureTables(uint entry, QWidget* parent);

private:
    QMap<const char*,CreatureTable*> tables;
};

#endif // CREATURETABLES_H
