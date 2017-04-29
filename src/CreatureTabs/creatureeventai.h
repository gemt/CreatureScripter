#ifndef CREATUREEVENTAI_H
#define CREATUREEVENTAI_H

#include <QWidget>
#include <QSqlRecord>

namespace Tables{
struct creature_template;
}
namespace EventAI{

class EventEntry : public QWidget {
private:
    QSqlRecord& record;
public:
    EventEntry(QSqlRecord& record);
    QString EventName();
};

class CreatureEventAI : public QWidget
{
public:
    CreatureEventAI(Tables::creature_template* creature, QWidget* parent);

private:
    Tables::creature_template* _creature;
    QVector<EventEntry*> entryWidgets;
};

}


#endif // CREATUREEVENTAI_H
