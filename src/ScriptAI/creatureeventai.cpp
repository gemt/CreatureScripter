#include "creatureeventai.h"
#include "tables.h"
#include "eventaidef.h"
#include "eventwidgetclasses.h"
#include "widgetFactory.h"
#include "collapsableframe.h"

#include <QSqlRecord>
#include <QFormLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QLineEdit>
#include <QGridLayout>
#include <QPainter>

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

static QWidget* getHLine(QVector<QWidget*>& widgets){
    QFrame* f = new QFrame();
    widgets.push_back(f);
    f->setLineWidth(10);
    f->setMidLineWidth(10);
    f->setFrameShape(QFrame::HLine);
    f->setFrameShadow(QFrame::Raised);
    f->setPalette(QPalette(QColor(0,0,0)));
    return f;
}

EventEntry::EventEntry(QSqlRecord &record, QWidget* parent) :
    QFrame(parent),
    record(record),
    mainLayout(nullptr)
{
    setContentsMargins(0,0,0,0);
    //setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
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

    mainLayout = new QGridLayout();
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
        //QFrame* eventFrame = new QFrame();
        //widgets.push_back(eventFrame);
        //eventFrame->setObjectName("paramWidget");
        //eventFrame->setStyleSheet("#paramWidget { border: 1px solid black; }");z
        //mainLayout->addWidget(eventFrame, 0, 0, 1, 1, Qt::AlignLeft|Qt::AlignTop);
        //QHBoxLayout* efl = new QHBoxLayout();
        //eventFrame->setLayout(efl);
        {
            //QVBoxLayout* el = new QVBoxLayout();
            //efl->addLayout(el);

            et = new type_EventType(record.value(Tables::creature_ai_scripts::event_type).toInt(&ok), this/*eventFrame*/);
            widgets.push_back(et);
            eWidgets.push_back(et);
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
            //el->addWidget(eventLabel, Qt::AlignTop|Qt::AlignLeft);
            //el->addWidget(et, 0, Qt::AlignLeft);
            mainLayout->addWidget(et,0,0,1,1,Qt::AlignLeft|Qt::AlignTop);
        }
        for(int i = 0; i < 3; i++){
            QWidget* w;
            if(i >= event.params.size()){
                w = new QWidget(this);
            }else{
                w = CreateParameterWidget(event.params.at(i), record, Tables::creature_ai_scripts::event_paramN(i+1), this/*eventFrame*/);
                //efl->addWidget(w);
            }
            widgets.push_back(w);
            mainLayout->addWidget(w,0,i+1,1,1,Qt::AlignLeft|Qt::AlignTop);
            eWidgets.push_back(w);
        }
    }


    mainLayout->addWidget(getHLine(widgets), 1, 0,1,4);
    type_ActionType* at;
    for(int i = 0; i < 3; i++){
        int actionId = record.value(Tables::creature_ai_scripts::actionN_type(i+1)).toInt(&ok);
        Q_ASSERT(ok);
        const EventAI_Action& eventAction = GetEventAction(actionId);
        at = new type_ActionType(eventAction.id, this/*actionFrame*/);
        widgets.push_back(at);
        connect(at, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, at, i](int isig){
            bool ok;
            record.setValue(Tables::creature_ai_scripts::actionN_type(i+1),at->itemData(isig).toInt(&ok));
            Q_ASSERT(ok);
            Remake();
        });
        mainLayout->addWidget(at, mainLayout->rowCount(),0,1,1,Qt::AlignTop|Qt::AlignLeft);
        for(int p = 0; p < 3; p++){
            QWidget* w;
            if(p >= eventAction.params.size()){
                w = new QWidget(this);
            }else{
                const Parameter& actParam = eventAction.params.at(p);
                w = CreateParameterWidget(actParam, record, Tables::creature_ai_scripts::actionX_paramY(i+1,p+1), this/*actionFrame*/);
            }
            widgets.push_back(w);
            //afl->addWidget(w, Qt::AlignLeft);
            mainLayout->addWidget(w, mainLayout->rowCount()-1,p+1,1,1,Qt::AlignTop|Qt::AlignLeft);
        }
        mainLayout->addWidget(getHLine(widgets), mainLayout->rowCount(), 0,1,4);
    }
    adjustSize();
}

CreatureEventAI::CreatureEventAI(std::shared_ptr<Tables::creature_template> creature, QWidget *parent) :
    QScrollArea(parent),
    _creature(creature)
{
    setContentsMargins(0,0,0,0);
    QWidget* scrollAreaWidget = new QWidget(this);
    scrollAreaWidget->setContentsMargins(0,0,0,0);
    scrollAreaWidget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    QVBoxLayout* vl = new QVBoxLayout(scrollAreaWidget);
    vl->setContentsMargins(0,0,0,0);
    scrollAreaWidget->setLayout(vl);
    setWidget(scrollAreaWidget);

    QVector<QSqlRecord>& records = _creature->scripts->records;
    int maxSize = 0;
    for(QVector<QSqlRecord>::iterator it = records.begin(); it != records.end(); it++){
        QSqlRecord& r = *it;

        CollapsibleFrame* frame = new CollapsibleFrame("Event entry " +r.value(Tables::creature_ai_scripts::id).toString(), scrollAreaWidget);
        EventEntry* ew = new EventEntry(r, frame);
        frame->SetWidget(ew);
        vl->addWidget(frame, Qt::AlignTop);
        entryWidgets.push_back(ew);
        //if(maxSize < frame)
    }
    adjustSize();
    scrollAreaWidget->adjustSize();
    //scrollAreaWidget->setSizePolicy(QSize);
    foreach(QWidget* w, entryWidgets){
        w->setFixedWidth(scrollAreaWidget->width());
    }
    adjustSize();
    scrollAreaWidget->adjustSize();
}



}

