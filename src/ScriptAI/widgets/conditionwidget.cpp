#include "conditionwidget.h"
#include "widgetFactory.h"

#include <QGridLayout>
#include <QLabel>
ConditionWidget::ConditionWidget(MangosRecord &r, const QString &field, const QVector<QString> &condValKeys, QWidget *parent, bool verbose)
    : QWidget(parent),
      record(r),
      fieldName(field),
      condValKeys(condValKeys),
      verbose(verbose)
{
    using namespace EventAI;
    mainLayout = new QGridLayout(this);

    bool ok;
    int cond = r.value(field).toInt(&ok);
    Q_ASSERT(ok);

    // XXX: placeholder
    foreach(const Condition& c, Conditions){
        if(c.id != cond) continue;
        setToolTip(c.description);

        mainLayout->addWidget(new QLabel(c.name,this), 0, 0, 1, 1, Qt::AlignTop|Qt::AlignLeft);

        /*
        for(int i = 0; i < c.params.size(); i++){
            const Parameter& p = c.params.at(i);
            QWidget* condWidget = CreateParameterWidget(p, r, condValKeys.at(i), this, verbose);
            mainLayout->addWidget(condWidget, 0, 1+i, 1, 1, Qt::AlignLeft|Qt::AlignTop);
        }
        */
        break;
    }
}
