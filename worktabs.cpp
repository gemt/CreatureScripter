#include "creaturespawnlocations.h"
#include "worktabs.h"
#include "warnings.h"
#include "creature.h"
#include "cache.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QKeyEvent>

#include <QTableWidget>

WorkTab::WorkTab(Creature* pCreature, QWidget *parent) :
    QTabWidget(parent),
    fullCreature(pCreature->entry)
{
    locationsTab = new CreatureSpawnLocations(fullCreature.cCreatures, this);
    addTab(locationsTab, "Spawn Locations");
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

void WorkTabs::addTab(unsigned int entry)
{
    std::vector<Creature*> ret = Cache::Get().GetCreatures(QString("%1").arg(entry));
    if(ret.size() != 1){
        Warnings::Warning("WorkTabs::addTab got entry that returned more than 1 creature. Skipping");
        return;
    }
    Creature* pCreature = ret.at(0);
    try{
        WorkTab* wt = new WorkTab(pCreature, this);
        QTabWidget::addTab(wt, pCreature->name);
        setCurrentWidget(wt);
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
        QWidget* t = QTabWidget::widget(idx);
        removeTab(idx);
        t->deleteLater();
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
