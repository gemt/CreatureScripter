#ifndef CREATURETABLES_H
#define CREATURETABLES_H

#include <QTabWidget>
#include <QPushButton>
#include <QMap>
#include <functional>
#include <QTableView>

class QSqlTableModel;
class QVBoxLayout;

class CreatureTable : public QTableView {
public:
    CreatureTable(const QString& table, QString key, QString value, QWidget* parent);

private:
    QPushButton* collapseBtn;
    QSqlTableModel* tableModel;
};


class CreatureTables : public QTabWidget
{
public:
    CreatureTables(uint entry, QWidget* parent);

private:
    template<typename T>
    void AddTable(const char* table, QString key, QString value){
        T* cTable;
        cTable = new T(table, key, QString("%1").arg(value), this);
        tables[table] = cTable;
        addTab(cTable, table);
    }

    QMap<const char*,CreatureTable*> tables;
    QWidget* contentWidget;
    QVBoxLayout* contentLayout;
};

#endif // CREATURETABLES_H
