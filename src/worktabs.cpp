#include "worktabs.h"
#include "warnings.h"
#include "creature.h"
#include "cache.h"
#include "creaturetables.h"
#include "templatetables.h"
#include "creatureeventai.h"
#include "changeswidget.h"
#include "statstemplate.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QKeyEvent>

#include <QTableWidget>

WorkTab::WorkTab(uint entry, QString name, QWidget *parent) :
    QTabWidget(parent),
    entry(entry),
    name(name),
    data(new CreatureData(entry, name))
    //fullCreature(pCreature->entry)
{
    setMouseTracking(true);
    setContentsMargins(0,0,0,0);

    EventAI::CreatureEventAI* event_ai = new EventAI::CreatureEventAI(data->creature, this);
    addTab(event_ai, "EventAI");

    //CreatureModifier* cm = new CreatureModifier(this);
    //rawTables = new CreatureTables(entry,this);
    StatsTemplate* creatureTemplate = new StatsTemplate(data->creature, this);

    //templateRecords.push_back(std::move(rawTables->GetSingleRecord(Tables::creature_template::dbTable())));
    //templateRecords.push_back(std::move(rawTables->GetSingleRecord(Tables::creature_template_addon::t())));
    //templateRecords.push_back(std::move(rawTables->GetSingleRecord(Tables::creature_equip_template::t())));
    //templateRecords.push_back(std::move(rawTables->GetSingleRecord(Tables::creature_equip_template_raw::t())));
    //templateRecords.push_back(std::move(rawTables->GetSingleRecord(Tables::)));
    TemplateTables* templateTable = new TemplateTables(data->creature, this);
    addTab(templateTable, "Template Tables");

    addTab(creatureTemplate, "CreatureTemplate");
    //addTab(cm, "Modifier");
    //addTab(rawTables, "Raw Tables");

    changesTab = new ChangesWidget(this, data->creature);
    event_ai->SetChangeWidget(changesTab);
    addTab(changesTab, "Changes");

}

WorkTab::~WorkTab()
{
    delete data;
}

unsigned int WorkTab::Entry()
{
    return entry;
}

WorkTabs::WorkTabs(QWidget *parent) :
    QTabWidget(parent)
{
    setMouseTracking(true);
    setContentsMargins(0,0,0,0);
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
    try
    {
        WorkTab* wt = new WorkTab(entry,name,this);
        wt->setContentsMargins(0,0,0,0);
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
        tabMap.remove(wt->Entry());
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

