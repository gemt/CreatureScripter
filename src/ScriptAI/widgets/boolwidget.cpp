#include "boolwidget.h"

boolWidget::boolWidget(MangosRecord& r, const QString fieldName, const EventAI::Parameter& param, QWidget* parent) :
    QComboBox(parent),
    record(r),
    fieldName(fieldName)
{
    setToolTip(param.description);
    addItem("False");
    addItem("True");
    setCurrentIndex(r.value(fieldName).toBool() ? 1 : 0);
    connect(this, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this, &boolWidget::onIndexChanged);
}

void boolWidget::onIndexChanged(int index)
{
    record.setValue(fieldName, index);
}
