#include "creatureeventai.h"
#include "tables.h"
#include "eventaidef.h"
#include "eventwidgetclasses.h"
#include "widgetFactory.h"

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

QTableWidgetItem* HeaderItem(const Parameter& type){
    QTableWidgetItem* itm = new QTableWidgetItem(type.name);
    itm->setToolTip(type.description);
    return itm;
}

static QWidget* ActionWidget(const Parameter& type, QSqlRecord& r, const QString& f){
    int idx = r.indexOf(f);
    return new QLineEdit(r.value(idx).toString());
}

static const EventAI_Action& GetEventAction(int actionId)
{
    auto aIt = EventAIStorage::Get().Actions().find(actionId);
    if(aIt == EventAIStorage::Get().Actions().end())
        throw std::runtime_error(QString("EventEntry::Remake() action1Id %1 is unknown").arg(actionId).toStdString());
    return *aIt;
}

void EventEntry::Remake()
{
    //TODO: missing columns/info: event_flags, event_chance, event_inverse_phase_mask, comment
    // and alternatively some creature id/event id

    clear();
    setRowCount(1);
    EventAIStorage& s = EventAIStorage::Get();
    s.Events();
    bool ok;
    quint32 eventId = record.value(Tables::creature_ai_scripts::event_type).toUInt(&ok);Q_ASSERT(ok);
    quint32 action1Id = record.value(Tables::creature_ai_scripts::action1_type).toUInt(&ok);Q_ASSERT(ok);
    quint32 action2Id = record.value(Tables::creature_ai_scripts::action2_type).toUInt(&ok);Q_ASSERT(ok);
    quint32 action3Id = record.value(Tables::creature_ai_scripts::action3_type).toUInt(&ok);Q_ASSERT(ok);

    int col_count = 1;
    auto eIt = s.Events().find(eventId);
    if(eIt == EventAIStorage::Get().Events().end())
        throw std::runtime_error(QString("EventEntry::Remake() eventID %1 is unknown").arg(eventId).toStdString());
    const EventAI_event& event = *eIt;
    col_count += event.params.size();

    // todo: row_count += actions.size() etc
    col_count += 3; // 3 actions
    col_count += GetEventAction(action1Id).params.size();
    col_count += GetEventAction(action2Id).params.size();
    col_count += GetEventAction(action3Id).params.size();

    setColumnCount(col_count);
    int cur_col = 0;
    setHorizontalHeaderItem(cur_col, new QTableWidgetItem("Event Name"));
    type_EventType* et = new type_EventType(record.value(Tables::creature_ai_scripts::event_type).toInt(&ok));
    Q_ASSERT(ok);
    connect(et, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, et](int i){
        bool ok;
        record.setValue(Tables::creature_ai_scripts::event_type,et->itemData(i).toInt(&ok));
        Q_ASSERT(ok);
        Remake();
    });
    setCellWidget(0, cur_col, et);
    cur_col++;

    //adding event params
    for(int i = 0; i < event.params.size(); i++){
        setHorizontalHeaderItem(cur_col, HeaderItem(event.params.at(i)));
        setCellWidget(0, cur_col, GetParameterWidget(event.params.at(i), record, Tables::creature_ai_scripts::event_paramN(i+1)));
                      //EventWidget(event.params.at(i), record, Tables::creature_ai_scripts::event_paramN(i+1)));
        cur_col++;
    }

    // adding actions
    for(int i = 0; i < 3; i++){
        setHorizontalHeaderItem(cur_col, new QTableWidgetItem(QString("Action %1").arg(i+1)));
        int actionId = record.value(Tables::creature_ai_scripts::actionN_type(i+1)).toInt(&ok);
        Q_ASSERT(ok);
        const EventAI_Action& eventAction = GetEventAction(actionId);
        type_ActionType* at = new type_ActionType(eventAction.id);
        connect(at, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this, at, i](int isig){
            bool ok;
            record.setValue(Tables::creature_ai_scripts::actionN_type(i+1),at->itemData(isig).toInt(&ok));
            Q_ASSERT(ok);
            Remake();
        });
        setCellWidget(0, cur_col, at);
        cur_col++;
        for(int p = 0; p < eventAction.params.size(); p++){
            const Parameter& actParam = eventAction.params.at(p);
            setHorizontalHeaderItem(cur_col, HeaderItem(actParam));
            setCellWidget(0, cur_col, GetParameterWidget(actParam, record, Tables::creature_ai_scripts::actionX_paramY(i+1,p+1)));
            cur_col++;
        }
    }






    resizeColumnsToContents();
    resizeRowsToContents();
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

