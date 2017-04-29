#ifndef CREATURETABLES_H
#define CREATURETABLES_H

#include <QTabWidget>
#include <QPushButton>
#include <map>
#include <functional>
#include <QTableView>
#include <QSqlRecord>

class QSqlQueryModel;
class QVBoxLayout;
#if 0
class CreatureTable : public QTableView {
public:
    CreatureTable(const QString& table, QString key, QString value, QWidget* parent);

    QSqlQueryModel* tableModel;
private:
    QPushButton* collapseBtn;
};


class CreatureTables : public QTabWidget
{
public:
    CreatureTables(uint entry, QWidget* parent);

    std::pair<QString,QSqlRecord> GetSingleRecord(const QString& table);

private:
    template<typename T>
    void AddTable(const QString& table, QString key, QString value){
        T* cTable;
        cTable = new T(table, key, QString("%1").arg(value), this);
        tables[table] = cTable;
        addTab(cTable, table);
    }

    std::map<QString,CreatureTable*> tables;
    QWidget* contentWidget;
    QVBoxLayout* contentLayout;
};
#endif
#endif // CREATURETABLES_H
