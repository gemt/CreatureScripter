#ifndef CREATUREEVENTAI_H
#define CREATUREEVENTAI_H

#include "eventaidef.h"

#include <QWidget>
#include <QSqlRecord>
#include <QTableWidget>
#include <memory>
#include <QVector>
class QVBoxLayout;
class QHBoxLayout;
namespace Tables{
struct creature_template;
}

namespace EventAI
{

class EventEntry : public QFrame {
private:
    QSqlRecord& record;
public:
    EventEntry(QSqlRecord& record, QWidget* parent);

private:
    QVector<QWidget*> widgets;
    QVBoxLayout* mainLayout;
    QHBoxLayout* eventLayout;
    QHBoxLayout* action1Layout;
    QHBoxLayout* action2Layout;
    QHBoxLayout* action3Layout;
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
