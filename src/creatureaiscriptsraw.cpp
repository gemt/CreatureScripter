#include "creatureaiscriptsraw.h"
#include <QHeaderView>

CreatureAIScriptsRaw::CreatureAIScriptsRaw(CreatureAIScripts &creature, QWidget *parent) :
    QTableWidget(parent)
{
    verticalHeader()->hide();
    setColumnCount(creature.names.size());
    setHorizontalHeaderLabels(creature.names);
    setRowCount(creature.events.size());

    int row = 0;
    foreach(const QStringList& t, creature.events)
    {
        int col = 0;
        foreach(const QString& s, t){
            setItem(row, col, new QTableWidgetItem(s));
            ++col;
        }
        ++row;
    }
    resizeColumnsToContents();
}
