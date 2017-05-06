#pragma once

#include <QWidget>
#include <QSqlRecord>
#include <QLineEdit>
#include <QDebug>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QFont>
#include "mangosrecord.h"
#include "eventaidef.h"
#include "spellidwidget.h"
#include "defaultlineedit.h"
#include "typevaluewidget.h"
#include "eventwidgetclasses.h"
#include "MillisecondsWidget.h"
#include "flagswidget.h"
#include "clickablewidget.h"
#include "inversephasemaskwidget.h"
#include "boolwidget.h"

static QWidget* CreateParameterWidget(const EventAI::Parameter& param, MangosRecord& record,
                                      const QString& field, QWidget* parent, bool verbose){
    QWidget* w = new QWidget(parent);
    w->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    w->setContentsMargins(0,0,0,0);
    QVBoxLayout* l = new QVBoxLayout(w);
    l->setContentsMargins(5,0,0,5);
    QLabel* lbl = new QLabel(param.name + ":");
    QFont f = lbl->font();
    f.setUnderline(true);
    lbl->setFont(f);
    lbl->setContentsMargins(0,0,0,0);
    l->addWidget(lbl);

    QWidget* rw = nullptr;
    switch(param.type){
    case EventAI::MILLISECONDS: rw = new MillisecondsWidget(record, field, param, w); break;
    case EventAI::PERCENTAGE: rw =  new DefaultLineEdit(record, field, param, w);break;
    case EventAI::SPELL_ID:
        rw = new SpellIDWidget(record, field, param, w);
        w->setProperty("hoverable", true);
        w->setMouseTracking(true);
        w->setProperty("clickWidget", QVariant::fromValue(rw));
        break;
    case EventAI::FACTION_ID_FLAGS:
        rw = new FlagsWidget(EventAI::factionFlags, record, field, w, verbose);
        break;
    case EventAI::TARGET:
        rw =new TypeValueWidget(EventAI::TargetTypes, record, field, w);
        break;
    case EventAI::CAST_FLAGS:
        rw = new FlagsWidget(EventAI::CastFlags, record, field, w, verbose); break;
        //rw = new TypeValueWidget(EventAI::CastFlags, record, field, w);break;
    case EventAI::SHEET:
        rw = new TypeValueWidget(EventAI::SheetState, record, field, w);
        break;
    case EventAI::EVENT_TYPE_MASK:
        rw = new FlagsWidget(EventAI::EventTypeMask, record, field, w, verbose);
        break;
    case EventAI::STAND_STATE:
        rw = new TypeValueWidget(EventAI::StandState, record, field, w);
        break;
    case EventAI::MOVEMENT_TYPE:
        rw = new TypeValueWidget(EventAI::MovementType, record, field, w);
        break;
    case EventAI::REACT_STATE:
        rw = new TypeValueWidget(EventAI::ReactState, record, field, w);
        break;
    case EventAI::SPAWN_EVENT_MODE:
        rw = new TypeValueWidget(EventAI::SpawnedEventMode, record, field, w);
        break;
    case EventAI::BOOL:
        rw = new boolWidget(record, field, param, w);
        break;
    case EventAI::MAP_AREA_ID: //map id or area id
    case EventAI::UNUSED:
    case EventAI::SPELL_SCHOOL:
    case EventAI::DISTANCE:
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
        break;
    ///////////////////
    case EventAI::EVENT_FLAGS:
        rw = new FlagsWidget(EventAI::EventFlags, record, field, w, verbose);
        break;
    case EventAI::EVENT_PHASE_MASK:
        rw = new InversePhaseMaskWidget(record, field, w, verbose);
        break;
    }
    Q_ASSERT(rw);
    l->addWidget(rw);
    return w;
}
