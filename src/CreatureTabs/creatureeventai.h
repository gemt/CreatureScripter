#ifndef CREATUREEVENTAI_H
#define CREATUREEVENTAI_H

#include "eventaidef.h"

#include <QWidget>
#include <QSqlRecord>
#include <QTableWidget>
#include <memory>

namespace Tables{
struct creature_template;
}
namespace EventAI{

class EventEntry : public QTableWidget {
private:
    QSqlRecord& record;
public:
    EventEntry(QSqlRecord& record, QWidget* parent);

private:
    void Remake();
};


class CreatureEventAI : public QWidget
{
public:
    CreatureEventAI(std::shared_ptr<Tables::creature_template> creature, QWidget* parent);

private:
    std::shared_ptr<Tables::creature_template> _creature;
    QVector<EventEntry*> entryWidgets;
};


}


#endif // CREATUREEVENTAI_H
