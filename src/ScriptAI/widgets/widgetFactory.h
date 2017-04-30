#pragma once

#include <QWidget>
#include <QSqlRecord>
#include <QLineEdit>
#include <QDebug>

#include "eventaidef.h"
#include "spellidwidget.h"
#include "defaultlineedit.h"

static QWidget* GetParameterWidget(const EventAI::Parameter& param, QSqlRecord& record, const QString& field, QWidget* parent = nullptr){
    switch(param.type){
    case EventAI::SPELL_ID:
        return new SpellIDWidget(record, field, param, parent);
    default:
        qDebug() << "GetParameterWidget returned DefaultLineEdit as no case was defined for type: " << param.type;
        return new DefaultLineEdit(record, field, param, parent);
    }
}
