#pragma once

#include <QWidget>
#include <QSqlRecord>
#include <QLineEdit>
#include <QDebug>
#include <QVBoxLayout>

#include "eventaidef.h"
#include "spellidwidget.h"
#include "defaultlineedit.h"
#include "typevaluewidget.h"
#include "eventwidgetclasses.h"
#include "MillisecondsWidget.h"

static QWidget* CreateParameterWidget(const EventAI::Parameter& param, QSqlRecord& record, const QString& field, QWidget* parent = nullptr){
    //QFrame* w = new QFrame(parent);
    //w->setContentsMargins(0,0,0,0);
    //w->setObjectName("paramWidget");
    //w->setStyleSheet("#paramWidget { border: 1px solid black; }");
    //QVBoxLayout* l = new QVBoxLayout(w);
    //w->setLayout(l);
    //QLabel* lbl = new QLabel(param.name);
    //lbl->setAutoFillBackground(true);
    //QPalette p = lbl->palette();
    //p.setBrush(QPalette::ColorRole::Background, QBrush(QColor(150,150,150)));
    //p.setBrush(QPalette::ColorRole::Window, QBrush(QColor(150,150,150)));
    //p.setBrush(QPalette::ColorRole::AlternateBase, QBrush(QColor(150,150,150)));
    //p.setBrush(QPalette::ColorRole::ToolTipBase, QBrush(QColor(150,150,150)));
    //lbl->setPalette(p);
    //w->setFrameStyle(QFrame::Raised);
    //lbl->setToolTip(param.description);
    //l->addWidget(lbl, 0, Qt::AlignTop);
    QWidget* w = parent;
    QWidget* rw = nullptr;
    switch(param.type){
    case EventAI::MILLISECONDS: rw = new MillisecondsWidget(record, field, param, w); break;
    case EventAI::PERCENTAGE: rw =  new DefaultLineEdit(record, field, param, w);break;
    //case EventAI::SPELL_ID: rw = new SpellIDWidget(record, field, param, w);break;
    case EventAI::FACTION_ID_FLAGS: rw = new TypeValueWidget(EventAI::factionFlags, record, field, param, w);break;
    case EventAI::TARGET: rw = new TypeValueWidget(EventAI::TargetTypes, record, field, param, w);break;
    case EventAI::CAST_FLAGS: rw = new TypeValueWidget(EventAI::CastFlags, record, field, param, w);break;
    case EventAI::SHEET: rw = new TypeValueWidget(EventAI::SheetState, record, field, param, w);break;
    case EventAI::EVENT_TYPE_MASK: rw = new TypeValueWidget(EventAI::EventTypeMask, record, field, param, w);break;
    case EventAI::STAND_STATE: rw = new TypeValueWidget(EventAI::StandState, record, field, param, w);break;
    case EventAI::MOVEMENT_TYPE:rw = new TypeValueWidget(EventAI::MovementType, record, field, param, w);break;
    case EventAI::REACT_STATE: rw = new TypeValueWidget(EventAI::ReactState, record, field, param, w);break;
    case EventAI::UNUSED:
    case EventAI::SPELL_SCHOOL:
    case EventAI::DISTANCE:
    case EventAI::BOOL:
    case EventAI::HP:
    case EventAI::NUMBER:
    case EventAI::EMOTE_ID:
    case EventAI::EVENT_TYPE:
    case EventAI::DISPELL_TYPE:
    case EventAI::CREATURE_ID:
    case EventAI::CONDITION:
    case EventAI::TEXT_ID:
    case EventAI::FACTION_ID:
    case EventAI::MODEL_ID:
    case EventAI::SOUND_ID:
    case EventAI::QUEST_ID:
    case EventAI::FLAGS_GENERIC:
    case EventAI::PHASE:
    case EventAI::ANGLE:
    case EventAI::SUMMON_ID:
    case EventAI::TEAM:
    case EventAI::CREATURE_TEMPLATE_ID:
    case EventAI::RADIUS:
    case EventAI::CHANCE:
        rw = new DefaultLineEdit(record, field, param, w);
    }
    Q_ASSERT(rw);
    rw->setContentsMargins(0,0,0,0);
    //l->addWidget(rw, 0, Qt::AlignTop | Qt::AlignLeft);
    return rw;
}
