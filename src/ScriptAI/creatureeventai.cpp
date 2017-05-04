#include "creatureeventai.h"
#include "tables.h"
#include "eventaidef.h"
#include "eventwidgetclasses.h"
#include "widgetFactory.h"
#include "collapsableframe.h"
#include "flagswidget.h"

#include <QSqlRecord>
#include <QFormLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QLineEdit>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QCursor>

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
    QWidget(parent),
    record(record),
    mainLayout(nullptr)
{
    setMouseTracking(true);
    setContentsMargins(0,0,0,0);
    Q_ASSERT(record.count() == Tables::creature_ai_scripts::num_cols);
    Remake();
}

void EventEntry::Remake()
{
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
    {
        // Adding the event combobox
        {
            currentEventType = new type_EventType(record.value(Tables::creature_ai_scripts::event_type).toInt(&ok), this/*eventFrame*/);
            widgets.push_back(currentEventType);
            eWidgets.push_back(currentEventType);
            Q_ASSERT(ok);
            connect(currentEventType, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EventEntry::onDoRemakeFromEvent, Qt::DirectConnection);

            QLabel* eventLabel = new QLabel("Event:");
            eventLabel->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum);
            eventLabel->setContentsMargins(0,0,0,0);
            mainLayout->addWidget(currentEventType,mainLayout->rowCount()-1,0,1,1,Qt::AlignLeft|Qt::AlignTop);
        }

        // phase mask
        int paramColOffset = 1;
        QWidget* w = CreateParameterWidget(event.params.at(0), record, Tables::creature_ai_scripts::event_inverse_phase_mask, this/*eventFrame*/);
        widgets.push_back(w);
        eWidgets.push_back(w);
        mainLayout->addWidget(w,mainLayout->rowCount()-1,paramColOffset++, 1,1,Qt::AlignLeft|Qt::AlignTop);

        // event flags
        w = CreateParameterWidget(event.params.at(1), record, Tables::creature_ai_scripts::event_flags, this/*eventFrame*/);
        widgets.push_back(w);
        eWidgets.push_back(w);
        mainLayout->addWidget(w,mainLayout->rowCount()-1,paramColOffset++, 1,1,Qt::AlignLeft|Qt::AlignTop);

        // Adding event parameters
        int eventParamNum = 1;
        for(int i = 2; i < 6; i++){
            if(i >= event.params.size()){
                w = new QWidget(this);
            }else{
                w = CreateParameterWidget(event.params.at(i), record, Tables::creature_ai_scripts::event_paramN(eventParamNum++), this/*eventFrame*/);
            }
            widgets.push_back(w);
            mainLayout->addWidget(w,mainLayout->rowCount()-1,paramColOffset++, 1,1, Qt::AlignLeft|Qt::AlignTop);
            eWidgets.push_back(w);
        }
    }

    // Adding action
    for(int i = 0; i < 3; i++){

        // Adding the action type
        int actionId = record.value(Tables::creature_ai_scripts::actionN_type(i+1)).toInt(&ok);
        Q_ASSERT(ok);
        const EventAI_Action& eventAction = GetEventAction(actionId);
        currentActionTypes[i] = new type_ActionType(eventAction.id, this/*actionFrame*/);
        widgets.push_back(currentActionTypes[i]);
        switch(i){
        case 0:
            connect(currentActionTypes[i], static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EventEntry::onDoRemakeFromAction1, Qt::DirectConnection);
            break;
        case 1:
            connect(currentActionTypes[i], static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EventEntry::onDoRemakeFromAction2, Qt::DirectConnection);
            break;
        case 2:
            connect(currentActionTypes[i], static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EventEntry::onDoRemakeFromAction3, Qt::DirectConnection);
            break;
        default:
        Q_ASSERT(0);
        }

        mainLayout->addWidget(currentActionTypes[i], mainLayout->rowCount(),0,1,1,Qt::AlignTop|Qt::AlignLeft);
        // Adding the action parameters
        for(int p = 0; p < 3; p++){
            QWidget* w;
            if(p >= eventAction.params.size()){
                w = new QWidget(this);
            }else{
                const Parameter& actParam = eventAction.params.at(p);
                w = CreateParameterWidget(actParam, record, Tables::creature_ai_scripts::actionX_paramY(i+1,p+1), this/*actionFrame*/);
            }
            widgets.push_back(w);
            mainLayout->addWidget(w, mainLayout->rowCount()-1, p*2+1, 1, 2, Qt::AlignTop|Qt::AlignLeft);
        }
    }
    adjustSize();
    updateGeometry();
    setMask(frameGeometry());
}

void EventEntry::onDoRemakeFromEvent(int i)
{
    bool ok;
    record.setValue(Tables::creature_ai_scripts::event_type, currentEventType->itemData(i).toInt(&ok));
    Q_ASSERT(ok);
    Remake();
}

void EventEntry::onDoRemakeFromAction1(int i)
{
    bool ok;
    record.setValue(Tables::creature_ai_scripts::action1_type, currentActionTypes[0]->itemData(i).toInt(&ok));
    Q_ASSERT(ok);
    Remake();
}

void EventEntry::onDoRemakeFromAction2(int i)
{
    bool ok;
    record.setValue(Tables::creature_ai_scripts::action2_type, currentActionTypes[1]->itemData(i).toInt(&ok));
    Q_ASSERT(ok);
    Remake();
}

void EventEntry::onDoRemakeFromAction3(int i)
{
    bool ok;
    record.setValue(Tables::creature_ai_scripts::action3_type, currentActionTypes[2]->itemData(i).toInt(&ok));
    Q_ASSERT(ok);
    Remake();
}

void EventEntry::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.save();

    painter.setPen(Qt::blue);
    //painter.rotate(270.0f);
    QRect eRect = mainLayout->cellRect(0,0);
    QRect pr = QRect(eRect.left()-10, eRect.top(), 10, eRect.height());
    painter.rotate(90.0f);
    painter.drawText(0,25, "Event");

    painter.setPen(Qt::red);
    QRect aREctTop = mainLayout->cellRect(1,0);
    QRect aREctBot = mainLayout->cellRect(mainLayout->rowCount()-1,0);

    painter.restore();
    painter.setPen(Qt::black);
    //drawing vertical lines for event
    {
        for(int i = 0; i < mainLayout->columnCount()-1; i++){
            QRect a = mainLayout->cellRect(0, i);
            QRect b = mainLayout->cellRect(0, i+1);
            float p = (a.right() + b.left()) / 2.0f;
            painter.drawLine(QPointF(p, (float)a.top()), QPoint(p, a.bottom()));

        }
    }
    //drawing vertical for actions
    {
        QRect a = mainLayout->cellRect(1, 0);
        QRect b = mainLayout->cellRect(mainLayout->rowCount()-1, 1);
        float p = (a.right() + b.left()) / 2.0f;
        painter.drawLine(QPointF(p, (float)a.top()), QPoint(p, b.bottom()));

        for(int i = 2; i < mainLayout->columnCount()-1; i+=2){
            a = mainLayout->cellRect(1, i);
            b = mainLayout->cellRect(mainLayout->rowCount()-1, i+1);
            p = (a.right() + b.left()) / 2.0f;
            painter.drawLine(QPointF(p, (float)a.top()), QPoint(p, b.bottom()));
        }
    }

    float top = mainLayout->cellRect(0, mainLayout->columnCount()-1).top()-5.0f;
    float bottom = 5.0f + mainLayout->cellRect(mainLayout->rowCount()-1, mainLayout->columnCount()-1).bottom();

    // drawing horizontal lines
    float left = (float)mainLayout->cellRect(0,0).left();
    float right = (float)mainLayout->cellRect(0, mainLayout->columnCount()-1).right();
    float p;
    QRect a, b;
    painter.drawLine(QPointF(left, top), QPoint(right, top));
    for(int i = 0; i < mainLayout->rowCount()-1; i++){
        a = mainLayout->cellRect(i, 0);
        b = mainLayout->cellRect(i+1,0);

        p = (a.bottom() + b.top())/ 2.0f;
        painter.drawLine(QPointF(left, p), QPoint(right, p));
    }
    // final horizontal line
    painter.drawLine(QPointF(left, bottom), QPoint(right, bottom));

    // event row background color
    {
        //QRect rightRect = mainLayout->cellRect(1, mainLayout->columnCount()-1);
        QRect eventRect(mainLayout->cellRect(0,0).topLeft(),
                        mainLayout->cellRect(0, mainLayout->columnCount()-1).bottomRight());
                        //mainLayout->cellRect(1, mainLayout->columnCount()-1).topRight());
        //QPointF leftP = QPointF(leftRect.left(), leftRect.center().y());
        //QPointF rightP = QPointF(rightRect.right(), rightRect.center().y());
        //QLinearGradient gradient(leftP, rightP);
        //gradient.setColorAt(0, QColor(255,0,0, 50));
        //gradient.setColorAt(1, QColor(255,0,0,0));
        //painter.fillRect(eventRect, gradient);
        painter.fillRect(eventRect, QColor(0,0,255, 25));
    }

    // Action rows background color
    {
        QRect leftRect = mainLayout->cellRect(1,0);
        QRect rightRect = mainLayout->cellRect(mainLayout->rowCount()-1, mainLayout->columnCount()-1);
        rightRect.setBottom(bottom);
        QRect eventRect(leftRect.topLeft(), rightRect.bottomRight());
        //QPointF leftP = QPointF(leftRect.left(), leftRect.center().y());
        //QPointF rightP = QPointF(rightRect.right(), rightRect.center().y());
        //QLinearGradient gradient(leftP, rightP);
        //gradient.setColorAt(0, QColor(0,0,255, 50));
        //gradient.setColorAt(1, QColor(0,0,255,0));
        painter.fillRect(eventRect, QColor(255,0,0, 25));
    }


    QPoint mp = mapFromGlobal(QCursor::pos());
    for(int i = 1; i < mainLayout->rowCount(); i++){
        for(int j = 1; j < mainLayout->columnCount(); j += 2){
            QWidget* w = mainLayout->itemAtPosition(i, j)->widget();
            if(!w) continue;

            if(hovering.contains(w)){
                QRect r1 = mainLayout->cellRect(i,j);
                QRect r2 = mainLayout->cellRect(i,j+1);
                QRect r3(r1.topLeft(),r2.bottomRight());
                painter.fillRect(r3, QBrush(QColor(0,0,0,50)));
            }
        }
    }
}

void EventEntry::mouseMoveEvent(QMouseEvent *event)
{
    for(int i = 1; i < mainLayout->rowCount(); i++){
        for(int j = 1; j < mainLayout->columnCount(); j += 2){
            QWidget* w = mainLayout->itemAtPosition(i, j)->widget();
            if(!w)
                continue;
            if(!w->property("hoverable").toBool())
                continue;
            QRect r1 = mainLayout->cellRect(i,j);
            QRect r2 = mainLayout->cellRect(i,j+1);
            QRect r3(r1.topLeft(),r2.bottomRight());
            if(r3.contains(event->pos())){
                if(!hovering.contains(w)){
                    hovering.push_back(w);
                    repaint();
                }
            }else{
                if(hovering.removeAll(w))
                    repaint();
            }
        }
    }
}

CreatureEventAI::CreatureEventAI(std::shared_ptr<Tables::creature_template> creature, QWidget *parent) :
    QScrollArea(parent),
    _creature(creature)
{
    setWidgetResizable(true);
    setContentsMargins(0,0,0,0);

    QWidget* scrollAreaWidget = new QWidget(this);
    scrollAreaWidget->setContentsMargins(0,0,0,0);
    //scrollAreaWidget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    scrollAreaWidget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    QVBoxLayout* vl = new QVBoxLayout(scrollAreaWidget);
    vl->setContentsMargins(0,0,0,0);
    scrollAreaWidget->setLayout(vl);

    setWidget(scrollAreaWidget);

    QVector<QSqlRecord>& records = _creature->scripts->records;

    for(QVector<QSqlRecord>::iterator it = records.begin(); it != records.end(); it++){
        QSqlRecord& r = *it;


        CollapsibleFrame* frame = new CollapsibleFrame(
                    "Event entry " +r.value(Tables::creature_ai_scripts::id).toString(),
                    r.value(Tables::creature_ai_scripts::comment).toString(),
                    scrollAreaWidget);
        EventEntry* ew = new EventEntry(r, frame);
        frame->SetWidget(ew);
        vl->addWidget(frame, 0, Qt::AlignTop|Qt::AlignLeft);
        entryWidgets.push_back(ew);
        //vl->setAlignment(frame, Qt::AlignTop);
    }
    adjustSize();
}



}

