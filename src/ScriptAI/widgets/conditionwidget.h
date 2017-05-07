#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H
#include "eventaidef.h"
#include "mangosrecord.h"

#include <QWidget>
class QGridLayout;
class ConditionWidget : public QWidget
{
public:
    ConditionWidget(MangosRecord& r, const QString& field,const QVector<QString>& condValKeys,QWidget* parent, bool verbose);
private:
    QGridLayout* mainLayout;
    MangosRecord& record;
    const QString fieldName;
    const QVector<QString> condValKeys;
    bool verbose;
};

#endif // CONDITIONWIDGET_H
