#include "creaturespawnlocations.h"
#include "cache.h"

#include <QHeaderView>
#include <QToolTip>
#include <QCursor>

CreatureSpawnLocations::CreatureSpawnLocations(CreatureTable& creature, QWidget* parent)
    : QTableWidget(parent)
{
    verticalHeader()->hide();
    setColumnCount(creature.names.size());
    setHorizontalHeaderLabels(creature.names);
    setRowCount(creature.positions.size());

    int row = 0;
    foreach(const QStringList& t, creature.positions)
    {
        int col = 0;
        foreach(const QString& s, t){
            setItem(row, col, new QTableWidgetItem(s));
            ++col;
        }
        ++row;
    }
    resizeColumnsToContents();
    QTableWidget::setMouseTracking(true);
    connect(this, &QTableWidget::cellEntered, [this](int r, int c){
        static int prevR=-1;
        if(r == prevR) return;
        prevR = r;
        if(c == 2){
            bool ok;
            int entry = item(r,c)->text().toInt(&ok);
            if(!ok) return;
            QToolTip::hideText();
            QToolTip::showText(QCursor::pos(), Cache::Get().MapName(entry));
        }
    });
}
