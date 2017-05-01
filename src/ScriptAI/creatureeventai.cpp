#include "creatureeventai.h"
#include "tables.h"
#include "eventaidef.h"
#include "eventwidgetclasses.h"
#include "widgetFactory.h"

#include <QSqlRecord>
#include <QFormLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QLineEdit>
#include <QGridLayout>
namespace EventAI{
QTableWidgetItem* HeaderItem(const Parameter& type){
    QTableWidgetItem* itm = new QTableWidgetItem(type.name);
    itm->setToolTip(type.description);
    return itm;
}

static QWidget* ActionWidget(const Parameter& type, QSqlRecord& r, const QString& f){
    int idx = r.indexOf(f);
    return new QLineEdit(r.value(idx).toString());
}

static const EventAI_Action& GetEventAction(int actionId)
{
    auto aIt = EventAIStorage::Get().Actions().find(actionId);
    if(aIt == EventAIStorage::Get().Actions().end())
        throw std::runtime_error(QString("EventEntry::Remake() action1Id %1 is unknown").arg(actionId).toStdString());
    return *aIt;
}


EventEntry::EventEntry(QSqlRecord &record, QWidget* parent) :
    QFrame(parent),
    record(record),
    mainLayout(nullptr)
{
    setObjectName("eventEntry");
    setStyleSheet("#eventEntry { border: 3px solid black; }");

    //setFrameStyle(QFrame::StyledPanel);
    Q_ASSERT(record.count() == Tables::creature_ai_scripts::num_cols);
    //horizontalHeader()->setHidden(true);
    //verticalHeader()->setHidden(true);
    Remake();
}
void EventEntry::Remake(){
    foreach(QWidget* w, widgets){
        w->deleteLater();
    }
    widgets.clear();
    delete mainLayout;

    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    EventAIStorage& s = EventAIStorage::Get();
    s.Events();
    bool ok;
    quint32 eventId = record.value(Tables::creature_ai_scripts::event_type).toUInt(&ok);Q_ASSERT(ok);
    auto eIt = s.Events().find(eventId);
    if(eIt == EventAIStorage::Get().Events().end())
        throw std::runtime_error(QString("EventEntry::Remake() eventID %1 is unknown").arg(eventId).toStdString());

    const EventAI_event& event = *eIt;
    type_EventType* et;
    {
        QFrame* eventFrame = new QFrame();
        widgets.push_back(eventFrame);
        eventFrame->setObjectName("paramWidget");
        eventFrame->setStyleSheet("#paramWidget { border: 1px solid black; }");
        mainLayout->addWidget(eventFrame, 0, Qt::AlignLeft|Qt::AlignTop);
        QHBoxLayout* efl = new QHBoxLayout();
        eventFrame->setLayout(efl);
        {
            QVBoxLayout* el = new QVBoxLayout();
            efl->addLayout(el);

            et = new type_EventType(record.value(Tables::creature_ai_scripts::event_type).toInt(&ok), eventFrame);
            Q_ASSERT(ok);
            connect(et, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, et](int i){
                bool ok;
                record.setValue(Tables::creature_ai_scripts::event_type,et->itemData(i).toInt(&ok));
                Q_ASSERT(ok);
                Remake();
            });
            QLabel* eventLabel = new QLabel("Event:");
            eventLabel->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum);
            //eventLabel->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 cyan, stop:1 blue);}");

            eventLabel->setContentsMargins(0,0,0,0);
            el->addWidget(eventLabel, Qt::AlignTop|Qt::AlignLeft);
            el->addWidget(et, 0, Qt::AlignLeft);
        }
        for(int i = 0; i < event.params.size(); i++){
            QWidget* w = CreateParameterWidget(event.params.at(i), record, Tables::creature_ai_scripts::event_paramN(i+1), eventFrame);
            efl->addWidget(w);
        }
    }
    type_ActionType* at;
    for(int i = 0; i < 3; i++){
        int actionId = record.value(Tables::creature_ai_scripts::actionN_type(i+1)).toInt(&ok);
        Q_ASSERT(ok);
        QFrame* actionFrame = new QFrame();
        actionFrame->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        widgets.push_back(actionFrame);
        actionFrame->setObjectName("paramWidget");
        actionFrame->setStyleSheet("#paramWidget { border: 1px solid black; }");
        mainLayout->addWidget(actionFrame, 0, Qt::AlignLeft|Qt::AlignTop);
        QHBoxLayout* afl = new QHBoxLayout();
        actionFrame->setLayout(afl);


        const EventAI_Action& eventAction = GetEventAction(actionId);
        at = new type_ActionType(eventAction.id, actionFrame);
        widgets.push_back(at);
        connect(at, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, at, i](int isig){
            bool ok;
            record.setValue(Tables::creature_ai_scripts::actionN_type(i+1),at->itemData(isig).toInt(&ok));
            Q_ASSERT(ok);
            Remake();
        });
        QVBoxLayout* el = new QVBoxLayout();
        afl->addLayout(el);

        el->addWidget(new QLabel(QString("Action %1:").arg(i+1)), Qt::AlignTop|Qt::AlignLeft);
        el->addWidget(at, Qt::AlignLeft);
        for(int p = 0; p < eventAction.params.size(); p++){
            const Parameter& actParam = eventAction.params.at(p);
            QWidget* w = CreateParameterWidget(actParam, record, Tables::creature_ai_scripts::actionX_paramY(i+1,p+1), actionFrame);
            afl->addWidget(w, Qt::AlignLeft);
        }
    }
    et->resize(at->width(),et->height());
}

CreatureEventAI::CreatureEventAI(std::shared_ptr<Tables::creature_template> creature, QWidget *parent) :
    QScrollArea(parent),
    _creature(creature)
{
    QWidget* scrollAreaWidget = new QWidget(this);
    scrollAreaWidget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    QVBoxLayout* vl = new QVBoxLayout(scrollAreaWidget);
    scrollAreaWidget->setLayout(vl);

    setWidget(scrollAreaWidget);

    QVector<QSqlRecord>& records = _creature->scripts->records;
    for(QVector<QSqlRecord>::iterator it = records.begin(); it != records.end(); it++){
        QSqlRecord& r = *it;

        CollapsibleFrame* frame = new CollapsibleFrame(r.value(Tables::creature_ai_scripts::id).toString(), scrollAreaWidget);
        EventEntry* ew = new EventEntry(r, frame);
        frame->SetWidget(ew);
        vl->addWidget(frame, Qt::AlignTop);
        //vl->addWidget(ew);
        //QPalette p = ew->palette();
        //p.setBrush(QPalette::Background, QBrush(p.background().color().lighter()));
        //ew->setContentsMargins(0,0,0,0);
        //vl->addWidget(ew);
        entryWidgets.push_back(ew);
        //frame->adjustSize();
        //frame->resize(500,500);
    }
    scrollAreaWidget->adjustSize();
}



}

