#include "creatureeventai.h"
#include "tables.h"
#include "eventaidef.h"

#include <QSqlRecord>
#include <QFormLayout>
#include <QPushButton>
#include <QHeaderView>

namespace EventAI{

EventEntry::EventEntry(QSqlRecord &record, QWidget* parent) :
    QTableWidget(parent),
    record(record)
{
    Q_ASSERT(record.count() == Tables::creature_ai_scripts::num_cols);
    horizontalHeader()->setHidden(true);
    verticalHeader()->setHidden(true);
    setRowCount(1);
}

void EventEntry::Remake()
{
    clear();
    EventAIStorage& s = EventAIStorage::Get();
    s.Events();
    bool ok;
    quint32 eventId = record.value(Tables::creature_ai_scripts::event_type).toUInt(&ok); Q_ASSERT(ok);
    quint32 action1Id = record.value(Tables::creature_ai_scripts::action1_type).toUInt(&ok);Q_ASSERT(ok);
    quint32 action2Id = record.value(Tables::creature_ai_scripts::action1_type).toUInt(&ok);Q_ASSERT(ok);
    quint32 action3Id = record.value(Tables::creature_ai_scripts::action1_type).toUInt(&ok);Q_ASSERT(ok);

    auto it = s.Events().find(eventId);
    if(it == EventAIStorage::Get().Events().end())
        throw std::runtime_error(QString("EventEntry::Remake() eventID %1 is unknown").arg(eventId).toStdString());
    const EventAI_event& event = *it;
    for(const event_param& p : event.params){
        p;
    }

}

const EventAI_event &EventEntry::Event()
{
    bool ok;
    quint32 et = record.value(Tables::creature_ai_scripts::event_type).toUInt(&ok);
    if(!ok)
        throw std::runtime_error("EventEntry::EventName() could not parse event_type");

    auto it = EventAIStorage::Get().Events().find(et);
    if(it == EventAIStorage::Get().Events().end()){
        throw std::runtime_error(QString("EventEntry::EventName() eventID %1 is unknown").arg(et).toStdString());
    }else{
        return (*it);
    }
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

