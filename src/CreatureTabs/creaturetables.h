#ifndef CREATURETABLES_H
#define CREATURETABLES_H

#include <QTabWidget>
#include <QPushButton>
#include <map>
#include <functional>
#include <QTableView>
#include <QSqlRecord>

class QSqlTableModel;
class QVBoxLayout;

class CreatureTable : public QTableView {
public:
    CreatureTable(const QString& table, QString key, QString value, QWidget* parent);

    QSqlTableModel* tableModel;
private:
    QPushButton* collapseBtn;
};


class CreatureTables : public QTabWidget
{
public:
    CreatureTables(uint entry, QWidget* parent);

    std::pair<const char*,QSqlRecord> GetSingleRecord(const char* table);

private:
    template<typename T>
    void AddTable(const char* table, QString key, QString value){
        T* cTable;
        cTable = new T(table, key, QString("%1").arg(value), this);
        tables[table] = cTable;
        addTab(cTable, table);
    }
    struct cmp_str
    {
       bool operator()(char const *a, char const *b) const
       {
          return std::strcmp(a, b) < 0;
       }
    };
    std::map<const char*,CreatureTable*,cmp_str> tables;
    QWidget* contentWidget;
    QVBoxLayout* contentLayout;
};

#endif // CREATURETABLES_H
