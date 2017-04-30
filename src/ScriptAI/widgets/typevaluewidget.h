#ifndef TYPEVALUEWIDGET_H
#define TYPEVALUEWIDGET_H

#include "eventaidef.h"

#include <QComboBox>
#include <QSqlRecord>

class TypeValueWidget : public QComboBox
{
public:
    TypeValueWidget(const QVector<EventAI::TypeValue>& values, QSqlRecord& r, const QString fieldName,
                    const EventAI::Parameter& param, QWidget* parent);

private:
    QSqlRecord& record;
    const EventAI::Parameter& parameter;
    int rIdx;
    const QVector<EventAI::TypeValue>& values;
};

#endif // TYPEVALUEWIDGET_H
