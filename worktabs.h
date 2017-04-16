#ifndef WORKTABS_H
#define WORKTABS_H

#include <QTabWidget>
#include "creature.h"

class Creature;
class CreatureSpawnLocations;
class WorkTab : public QTabWidget
{
public:
    WorkTab(Creature* pCreature, QWidget* parent);
    FullCreature fullCreature;

private:
    CreatureSpawnLocations* locationsTab;
};

class WorkTabs : public QTabWidget
{
public:
    WorkTabs(QWidget *parent);

    void addTab(unsigned int entry);

private slots:
    void onTabCloseRequest(int);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // WORKTABS_H
