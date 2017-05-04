#ifndef CREATUREEVENTAI_H
#define CREATUREEVENTAI_H

#include "eventaidef.h"

#include <QWidget>
#include <QSqlRecord>
#include <QTableWidget>
#include <memory>
#include <QVector>
#include <QScrollArea>

class QVBoxLayout;
class QGridLayout;
class QHBoxLayout;
namespace Tables{
struct creature_template;
}

namespace EventAI
{

class type_EventType;
class type_ActionType;

class EventEntry : public QWidget {
private:
    QSqlRecord& record;
public:
    EventEntry(QSqlRecord& record, QWidget* parent);

private:
    QVector<QWidget*> widgets;
    QVector<QWidget*> eWidgets;
    QVector<QWidget*> spellWidgets;

    QGridLayout* mainLayout;
    void Remake();

    type_EventType* currentEventType;
    type_ActionType* currentActionTypes[3];
    QVector<QWidget*> hovering;
private slots:
    void onDoRemakeFromEvent(int i);
    void onDoRemakeFromAction1(int i);
    void onDoRemakeFromAction2(int i);
    void onDoRemakeFromAction3(int i);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};


class CreatureEventAI : public QScrollArea
{
public:
    CreatureEventAI(std::shared_ptr<Tables::creature_template> creature, QWidget* parent);

private:
    std::shared_ptr<Tables::creature_template> _creature;
    QVector<EventEntry*> entryWidgets;
};


}


#endif // CREATUREEVENTAI_H
