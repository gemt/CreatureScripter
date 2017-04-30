#ifndef MILLISECONDSWIDGET_H
#define MILLISECONDSWIDGET_H
#include "eventaidef.h"

#include <QSqlRecord>
#include <QSpinBox>

class MillisecondsWidget : public QSpinBox
{
public:
    MillisecondsWidget(QSqlRecord& r, const QString fieldName, const EventAI::Parameter& param,  QWidget* parent = nullptr);

private:
    QSqlRecord& record;
    const EventAI::Parameter& parameter;
    int rIdx;
};

#endif // MILLISECONDSWIDGET_H
