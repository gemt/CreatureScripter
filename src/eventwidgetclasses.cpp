#include "eventwidgetclasses.h"
#include "eventaidef.h"

namespace EventAI{

type_EventType::type_EventType(int currType)
{
    EventAIStorage& s = EventAIStorage::Get();
    foreach(const EventAI_event& e, s.Events()){
        addItem(e.name, e.id);
    }
    bool ok;
    for(int i = 0; i <= count(); i++){
        if(i == count()){
            Q_ASSERT(0); //ugly hack to assert that we got a valid ID
        }
        int t = itemData(i).toInt(&ok);
        Q_ASSERT(ok);
        if(t == currType){
            setCurrentIndex(i);
            break;
        }
    }
}

type_MS::type_MS(QSqlRecord &r, int idx) : r(r),idx(idx)
{
    setMaximum(std::numeric_limits<int>::max());
    setMinimum(0);
    setSuffix("ms");

    bool ok;
    setValue(r.value(idx).toInt(&ok));
    Q_ASSERT(ok);
    connect(this, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int v){
        this->r.setValue(this->idx, v);
    });
}

}
