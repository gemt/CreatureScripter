#ifndef STATSTEMPLATE_H
#define STATSTEMPLATE_H

#include "tables.h"

#include <QWidget>
#include <memory>

class QTableWidget;
class StatsTemplate : public QWidget
{
    Q_OBJECT
public:
    StatsTemplate(std::shared_ptr<Tables::creature_template> creature, QWidget* parent);

private slots:
    void onFilterChanged(const QString& filt);
    void onCellClicked(int row, int column);

private:
    std::shared_ptr<Tables::creature_template> _creature;
    QTableWidget* table;
};

#endif // STATSTEMPLATE_H
