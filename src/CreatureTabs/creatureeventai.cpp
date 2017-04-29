#include "creatureeventai.h"
#include "tables.h"
#include "eventaidef.h"
#include "eventwidgetclasses.h"

#include <QSqlRecord>
#include <QFormLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QLineEdit>

namespace EventAI{

EventEntry::EventEntry(QSqlRecord &record, QWidget* parent) :
    QTableWidget(parent),
    record(record)
{
    Q_ASSERT(record.count() == Tables::creature_ai_scripts::num_cols);
    //horizontalHeader()->setHidden(true);
    verticalHeader()->setHidden(true);
    Remake();
}

QTableWidgetItem* HeaderItem(const event_param& type){
    QTableWidgetItem* itm = new QTableWidgetItem(type.name);
    itm->setToolTip(type.description);
    return itm;
}

static QWidget* EventWidget(const event_param& type, QSqlRecord& r, const QString& f){
    int idx = r.indexOf(f);
    switch(type.type){
    case event_param::ms:
        return new type_MS(r, idx);
    case event_param::pct:
    case event_param::SpellId:
    case event_param::SpellSchool:
    case event_param::dist:
    case event_param::_bool:
    case event_param::hp:
    case event_param::num:
    case event_param::EmoteId:
    case event_param::EventEntry:
    case event_param::DispellType:
    case event_param::CreatureID:
    case event_param::Condition:
    case event_param::UNKNOWN:
        return new QLineEdit(r.value(idx).toString());
    }
}

void EventEntry::Remake()
{
    clear();
    setRowCount(1);
    EventAIStorage& s = EventAIStorage::Get();
    s.Events();
    bool ok;
    quint32 eventId = record.value(Tables::creature_ai_scripts::event_type).toUInt(&ok);
    Q_ASSERT(ok);
    quint32 action1Id = record.value(Tables::creature_ai_scripts::action1_type).toUInt(&ok);
    Q_ASSERT(ok);
    quint32 action2Id = record.value(Tables::creature_ai_scripts::action2_type).toUInt(&ok);
    Q_ASSERT(ok);
    quint32 action3Id = record.value(Tables::creature_ai_scripts::action3_type).toUInt(&ok);
    Q_ASSERT(ok);
    int col_count = 1;
    auto it = s.Events().find(eventId);
    if(it == EventAIStorage::Get().Events().end())
        throw std::runtime_error(QString("EventEntry::Remake() eventID %1 is unknown").arg(eventId).toStdString());
    const EventAI_event& event = *it;
    col_count += event.params.size();
    // todo: row_count += actions.size() etc
    setColumnCount(col_count);

    setHorizontalHeaderItem(0, new QTableWidgetItem("Event Name"));
    type_EventType* et = new type_EventType(record.value(Tables::creature_ai_scripts::event_type).toInt(&ok));
    Q_ASSERT(ok);
    connect(et, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, et](int i){
        bool ok;
        record.setValue(Tables::creature_ai_scripts::event_type,et->itemData(i).toInt(&ok));
        Q_ASSERT(ok);
        Remake();
    });

    setCellWidget(0, 0, et);
    for(int i = 0; i < event.params.size(); i++){
        setHorizontalHeaderItem(i+1, HeaderItem(event.params.at(i)));
        setCellWidget(0, i+1, EventWidget(event.params.at(i), record, Tables::creature_ai_scripts::event_paramN(i+1)));
    }
    resizeColumnsToContents();
}


CreatureEventAI::CreatureEventAI(std::shared_ptr<Tables::creature_template> creature, QWidget *parent) :
    QWidget(parent),
    _creature(creature)
{
    QFormLayout* l = new QFormLayout(this);
    setLayout(l);

    QVector<QSqlRecord>& records = _creature->scripts->records;
    for(QVector<QSqlRecord>::iterator it = records.begin(); it != records.end(); it++){
        QSqlRecord& r = *it;
        EventEntry* ew = new EventEntry(r, this);
        l->addRow(new QPushButton(), ew);
        entryWidgets.push_back(ew);
    }
}



}

