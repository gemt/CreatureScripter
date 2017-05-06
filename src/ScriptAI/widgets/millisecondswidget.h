#ifndef MILLISECONDSWIDGET_H
#define MILLISECONDSWIDGET_H
#include "eventaidef.h"
#include "mangoscreature.h"

#include <QSqlRecord>
#include <QSpinBox>

class MillisecondsWidget : public QSpinBox
{
public:
    MillisecondsWidget(MangosRecord& r, const QString fieldName, const EventAI::Parameter& param,  QWidget* parent = nullptr);

private:
    MangosRecord& record;
    const EventAI::Parameter& parameter;
    int rIdx;
};

#endif // MILLISECONDSWIDGET_H
