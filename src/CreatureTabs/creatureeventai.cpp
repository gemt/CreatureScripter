#include "creatureeventai.h"
#include "tables.h"

#include <QSqlRecord>

CreatureEventAI::CreatureEventAI(Tables::creature_template *creature, QWidget *parent) :
    QWidget(parent),
    _creature(creature)
{
    foreach(QSqlRecord& r, _creature->scripts->records){
        EventEntry* ew = new EventEntry(r);
        entryWidgets.push_back(ew);
    }
}

EventEntry::EventEntry(QSqlRecord &record) :
    record(record)
{

}

QString EventEntry::EventName()
{
    bool ok;
    quint32 et = record.value(Tables::creature_ai_scripts::event_type).toUInt(&ok);
    if(!ok)
        throw std::runtime_error("EventEntry::EventName() could not parse event_type");

    switch(et){
        case 0: return "EVENT_T_TIMER_IN_COMBAT";
        case 1: return "EVENT_T_TIMER_OOC";
        case 2: return "";
        case 3: return "";
        case 4: return "";
        case 5: return "";
        case 6: return "";
        case 7: return "";
        case 8: return "";
        case 9: return "";
        case 10: return "";
        case 11: return "";
        case 12: return "";
        case 13: return "";
        case 14: return "";
        case 15: return "";
        case 16: return "";
        case 17: return "";
        case 18: return "";
        case 19: return "";
        case 20: return "";
        case 21: return "";
        case 22: return "";
        case 23: return "";
        case 24: return "";
        case 25: return "";
        case 26: return "";
        case 27: return "";
        case 28: return "";
        case 29: return "";
        case 30: return "";
        case 31: return "";
    default:
        throw std::runtime_error(QString("EventEntry::EventName() got unrecognized event_type: %1")
                                 .arg(et).toStdString());
    }
}

EventAI::EventAIJson::EventAIJson()
{

}
