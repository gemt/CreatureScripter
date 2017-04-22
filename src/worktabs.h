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
    WorkTab(uint entry, QString name, QWidget* parent);
    //FullCreature fullCreature;
    unsigned int Entry();

private:
    uint entry;
    QString name;

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
    void addTab(uint entry, QString name);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onTabCloseRequest(int);

private:
    QMap<unsigned int, QWidget*> tabMap;

};

#endif // WORKTABS_H
