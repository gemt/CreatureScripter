#include "creaturetemplateraw.h"

#include <QHeaderView>

CreatureTemplateRaw::CreatureTemplateRaw(CreatureTemplate &creature, QWidget *parent) :
    QTableWidget(parent)
{
    verticalHeader()->hide();
    setColumnCount(2);
    setHorizontalHeaderLabels(QStringList{"Field", "Value"});
    setRowCount(creature.names.size());

    for(int row = 0; row < creature.names.size(); row++){
        setItem(row, 0, new QTableWidgetItem(creature.names.at(row)));
        setItem(row, 1, new QTableWidgetItem(creature.table.at(row)));
    }
    resizeColumnsToContents();
}
