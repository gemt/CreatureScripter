#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H
#include "eventaidef.h"
#include "mangosrecord.h"

#include <QComboBox>
class QGridLayout;
class ConditionWidget : public QWidget
{
    Q_OBJECT
public:
    ConditionWidget(MangosRecord& r, const QString& field, QWidget* parent, bool verbose);
signals:
    void ConditionChanged();

private:
    QGridLayout* mainLayout;
    MangosRecord& record;
    const QString fieldName;
    bool verbose;
};

#endif // CONDITIONWIDGET_H
