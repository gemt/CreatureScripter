#include "worktabs.h"
#include "warnings.h"
#include "creature.h"
#include "cache.h"
#include "creaturetemplateraw.h"
#include "creatureaiscriptsraw.h"
#include "scriptaitab.h"
#include "creaturetables.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QKeyEvent>

#include <QTableWidget>

WorkTab::WorkTab(uint entry, QString name, QWidget *parent) :
    QTabWidget(parent),
    entry(entry),
    name(name)
    //fullCreature(pCreature->entry)
{
    CreatureTables* rawTables = new CreatureTables(entry,this);
    addTab(rawTables, "Raw Tables");
/*
    scriptAITab = new ScriptAITab(fullCreature, this);
    addTab(scriptAITab, "Event Modifier");
    locationsTab = new CreatureSpawnLocations(fullCreature.cCreatures, this);
    addTab(locationsTab, "Spawn Locations");
    rawTemplateTab = new CreatureTemplateRaw(fullCreature.cTemplate, this);
    addTab(rawTemplateTab, "Creature Template");
    rawAITab = new CreatureAIScriptsRaw(fullCreature.cAIScripts, this);
    addTab(rawAITab, "AI events");
    */
}

unsigned int WorkTab::Entry()
{
    return entry;
}

WorkTabs::WorkTabs(QWidget *parent) :
    QTabWidget(parent)
{
    setTabsClosable(true);
    connect(this, &QTabWidget::tabBarClicked, [this](){
        currentWidget()->setFocus();
    });
    connect(this, &QTabWidget::tabCloseRequested, this, &WorkTabs::onTabCloseRequest);
}

void WorkTabs::addTab(uint entry, QString name)
{
    if(tabMap.contains(entry)){
        setCurrentWidget(tabMap[entry]);
        return;
    }
    /*
    QVector<Creature*> ret = Cache::Get().GetCreatures(QString("%1").arg(entry));
    if(ret.size() != 1){
        Warnings::Warning("WorkTabs::addTab got entry that returned more than 1 creature. Skipping");
        return;
    }
    Creature* pCreature = ret.at(0);
    */
    try{
        WorkTab* wt = new WorkTab(entry,name,this);
        QTabWidget::addTab(wt, name);
        tabMap[wt->Entry()] = wt;
        setCurrentWidget(wt);
        if(QWidget* cw = currentWidget()){
            cw->setFocus();
        }
    }catch(std::exception& e){
        Warnings::Warning(e.what());
    }
}

void WorkTabs::onTabCloseRequest(int idx)
{
    QString yes = "Yes";
    QString ret = Warnings::confirmBox(QString("Close %1?").arg(tabText(idx)),
                             QStringList{yes, "Cancel"}, this);
    if(ret == yes) {
        WorkTab* wt = static_cast<WorkTab*>(QTabWidget::widget(idx));
        removeTab(idx);
        wt->deleteLater();
        if(QWidget* cw = currentWidget()){
            cw->setFocus();
        }
    }

}

void WorkTabs::keyPressEvent(QKeyEvent *e)
{
    if(e->modifiers() & Qt::ControlModifier){
        if(e->key() == Qt::Key_W){
            onTabCloseRequest(QTabWidget::currentIndex());
            return;
        }
    }

    QTabWidget::keyPressEvent(e);
}

