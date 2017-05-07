#include "conditionwidget.h"
#include "widgetFactory.h"

#include <QVBoxLayout>
#include <QLabel>

ConditionWidget::ConditionWidget(MangosRecord &r, const QString &field, QWidget *parent, bool verbose)
    : QWidget(parent),
      record(r),
      fieldName(field),
      verbose(verbose)
{
    using namespace EventAI;

    QVBoxLayout* l = new QVBoxLayout(this);
    bool ok;
    int currVal = record.value(fieldName).toInt(&ok);
    Q_ASSERT(ok);

    l->addWidget(new QLabel("Condition"));

    QComboBox* comboBox = new QComboBox(this);
    l->addWidget(comboBox);
    int vIdx = 0;
    foreach(const Condition& c, Conditions){
        comboBox->addItem(c.name, c.id);
        if(c.id == currVal){
            comboBox->setCurrentIndex(vIdx);
            comboBox->setToolTip(c.description);
        }
        vIdx++;
    }

    connect(comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            [this, comboBox](int){
        bool ok;
        int currentVal = comboBox->currentData().toInt(&ok);
        Q_ASSERT(ok);
        record.setValue(fieldName, currentVal);
        emit ConditionChanged();
    });
}
