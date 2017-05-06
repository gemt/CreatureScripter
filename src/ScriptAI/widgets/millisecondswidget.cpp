#include "millisecondswidget.h"



MillisecondsWidget::MillisecondsWidget(MangosRecord &r, const QString fieldName, const EventAI::Parameter &param, QWidget *parent)
    : QSpinBox(parent),
      record(r),
      parameter(param)
{
    setMaximum(std::numeric_limits<int>::max());
    setMinimum(0);
    setSuffix("ms");
    rIdx = record.indexOf(fieldName);
    bool ok;
    setValue(record.value(rIdx).toInt(&ok));
    Q_ASSERT(ok);

    connect(this, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int v){
        record.setValue(this->rIdx, v);
    });
}
