#pragma once

#include <QWidget>
#include <QSqlRecord>
#include <QLineEdit>
#include <QDebug>

#include "eventaidef.h"
#include "spellidwidget.h"
#include "defaultlineedit.h"
#include "typevaluewidget.h"
#include "eventwidgetclasses.h"

static QWidget* GetParameterWidget(const EventAI::Parameter& param, QSqlRecord& record, const QString& field, QWidget* parent = nullptr){
    switch(param.type){
    case EventAI::MILLISECONDS: return new EventAI::type_MS(r, idx);
    case EventAI::PERCENTAGE: return new DefaultLineEdit(record, field, param, parent);
    case EventAI::SPELL_ID: return new SpellIDWidget(record, field, param, parent);
    case EventAI::FACTION_ID_FLAGS: return new TypeValueWidget(EventAI::factionFlags, record, field, param, parent);
    case EventAI::TARGET: return new TypeValueWidget(EventAI::TargetTypes, record, field, param, parent);
    case EventAI::CAST_FLAGS: return new TypeValueWidget(EventAI::CastFlags, record, field, param, parent);
    case EventAI::SHEET: return new TypeValueWidget(EventAI::SheetState, record, field, param, parent);
    case EventAI::EVENT_TYPE_MASK: return new TypeValueWidget(EventAI::EventTypeMask, record, field, param, parent);
    case EventAI::STAND_STATE: return new TypeValueWidget(EventAI::StandState, record, field, param, parent);
    case EventAI::MOVEMENT_TYPE:return new TypeValueWidget(EventAI::MovementType, record, field, param, parent);
    case EventAI::REACT_STATE: return new TypeValueWidget(EventAI::ReactState, record, field, param, parent);
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
        return new DefaultLineEdit(record, field, param, parent);
    }
}
