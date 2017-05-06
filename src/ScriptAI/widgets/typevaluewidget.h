#ifndef TYPEVALUEWIDGET_H
#define TYPEVALUEWIDGET_H

#include "mangosrecord.h"
#include "eventaidef.h"

#include <QComboBox>
#include <QSqlRecord>

class TypeValueWidget : public QComboBox
{
public:
    TypeValueWidget(const QVector<EventAI::TypeValue>& values, MangosRecord& r, const QString fieldName, QWidget* parent);

private:
    MangosRecord& record;
    int rIdx;
    const QVector<EventAI::TypeValue>& values;
};

#endif // TYPEVALUEWIDGET_H
