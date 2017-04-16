#ifndef WORKTABS_H
#define WORKTABS_H

#include <QTabWidget>
#include "table.h"

class Creature;

class WorkTab : public QWidget
{
public:
    WorkTab(Creature* pCreature, QWidget* parent);
    FullCreature fullCreature;
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
