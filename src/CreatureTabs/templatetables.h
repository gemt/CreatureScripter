#ifndef TEMPLATETABLES_H
#define TEMPLATETABLES_H

#include "tables.h"

#include <QWidget>
#include <memory>

class QTableWidget;
class TemplateTables : public QWidget
{
    Q_OBJECT
public:
    TemplateTables(std::shared_ptr<Tables::creature_template> creature, QWidget* parent);

private slots:
    void onFilterChanged(const QString& filt);
private:
    std::shared_ptr<Tables::creature_template> _creature;
    QTableWidget* table;
    void InsertTable(MangosRecord& r);
};

#endif // TEMPLATETABLES_H
