#ifndef WORKTABS_H
#define WORKTABS_H

#include "creature.h"

#include <QTabWidget>
#include <QMap>

class Creature;
class CreatureSpawnLocations;
class CreatureTemplateRaw;
class CreatureAIScriptsRaw;
class ScriptAITab;

class WorkTab : public QTabWidget
{
public:
    WorkTab(Creature* pCreature, QWidget* parent);
    FullCreature fullCreature;
    unsigned int Entry();

private:
    Creature* pCreature;
    ScriptAITab* scriptAITab;
    CreatureSpawnLocations* locationsTab;
    CreatureTemplateRaw* rawTemplateTab;
    CreatureAIScriptsRaw* rawAITab;
};

class WorkTabs : public QTabWidget
{
public:
    WorkTabs(QWidget *parent);

public slots:
    void addTab(uint entry);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onTabCloseRequest(int);

private:
    QMap<unsigned int, QWidget*> tabMap;

};

#endif // WORKTABS_H
