#include "typevaluewidget.h"

TypeValueWidget::TypeValueWidget(const QVector<EventAI::TypeValue> &values, QSqlRecord &r,
                                 const QString fieldName, const EventAI::Parameter &param, QWidget *parent)
    :QComboBox(parent),
      record(r),
      parameter(param),
      values(values)
{
    rIdx = record.indexOf(fieldName);
    bool ok;
    int currVal = record.value(rIdx).toInt(&ok);
    Q_ASSERT(ok);
    int vIdx = 0;
    foreach(const EventAI::TypeValue& v, values){
        addItem(v.name, v.value);
        if(v.value == currVal){
            setCurrentIndex(vIdx);
            setToolTip(v.description);
        }
        vIdx++;
    }

    connect(this, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            [this](int i){
        bool ok;
        int currentVal = currentData().toInt(&ok);
        Q_ASSERT(ok);
        record.setValue(rIdx, currentVal);
    });
}
