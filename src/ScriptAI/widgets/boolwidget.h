#ifndef BOOLWIDGET_H
#define BOOLWIDGET_H

#include "mangosrecord.h"
#include "eventaidef.h"

#include <QComboBox>

class boolWidget : public QComboBox
{
public:
    boolWidget(MangosRecord& r, const QString fieldName, const EventAI::Parameter& param,  QWidget* parent = nullptr);

private slots:
    void onIndexChanged(int index);
private:
    MangosRecord& record;
    QString fieldName;
};

#endif // BOOLWIDGET_H
