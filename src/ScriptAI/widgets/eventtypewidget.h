#ifndef EVENTTYPEWIDGET_H
#define EVENTTYPEWIDGET_H

#include "mangosrecord.h"
#include <QComboBox>

class EventTypeWidget : public QComboBox
{
public:
    EventTypeWidget(MangosRecord& r,const QString& fieldName, QWidget* parent, bool verbose);
private:
    MangosRecord& record;
    const QString fieldName;
};

#endif // EVENTTYPEWIDGET_H
