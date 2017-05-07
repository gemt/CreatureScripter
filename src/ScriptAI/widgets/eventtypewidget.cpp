#include "eventtypewidget.h"
#include "eventaidef.h"

EventTypeWidget::EventTypeWidget(MangosRecord &r, const QString &fieldName, QWidget *parent, bool verbose)
    : QComboBox(parent),
      record(r),
      fieldName(fieldName)
{
    using namespace EventAI;
    const QMap<int, EventAI_event>& events = EventAIStorage::Get().Events();
    foreach(const EventAI_event& p, events){
        addItem(p.shortName, p.id);
    }
    connect(this, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            [this](int){
        bool ok;
        int currentVal = currentData().toInt(&ok);
        Q_ASSERT(ok);
        record.setValue(this->fieldName, currentVal);
    });
}
