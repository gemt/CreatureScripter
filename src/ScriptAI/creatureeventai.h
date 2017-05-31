#ifndef CREATUREEVENTAI_H
#define CREATUREEVENTAI_H

#include "eventaidef.h"
#include "mangosrecord.h"

#include <QWidget>
#include <QSqlRecord>
#include <QTableWidget>
#include <memory>
#include <QVector>
#include <QScrollArea>
#include <QSqlField>

class QVBoxLayout;
class QGridLayout;
class QHBoxLayout;
class ChangesWidget;
namespace Tables{
struct creature_template;
}

namespace EventAI
{

class type_EventType;
class type_ActionType;

class EventEntry : public QWidget {
    Q_OBJECT
public:
    EventEntry(MangosRecord& record, QWidget* parent);

    MangosRecord& record;
    bool verbose = false;

public slots:
    void DoRemake();

private:
    void Remake();
    void AddConditionWidget(const EventAI_event& event, int& paramColOffset, int& i, int& event_param);
    QVector<QWidget*> widgets;

    QGridLayout* mainLayout;

    type_EventType* currentEventType;
    type_ActionType* currentActionTypes[3];

    struct hoverWidget{
        QWidget* w;
        bool pressed;
        bool clicked;
        bool doubleClicked;
    };
    hoverWidget* currHover = nullptr;

    void AddWidget(QWidget* w, int r, int c, int nr, int nc);
private slots:
    void onDoRemakeFromEvent(int i);
    void onDoRemakeFromAction1(int i);
    void onDoRemakeFromAction2(int i);
    void onDoRemakeFromAction3(int i);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};


class CreatureEventAI : public QScrollArea
{
Q_OBJECT
public:
    CreatureEventAI(std::shared_ptr<Tables::creature_template> creature, QWidget* parent);
    void SetChangeWidget(ChangesWidget* changWidg);
public slots:
    void NewEventAI();

private:
    std::shared_ptr<Tables::creature_template> _creature;
    QVector<EventEntry*> entryWidgets;
    QWidget* scrollAreaWidget;
    QVBoxLayout* vl;
    ChangesWidget* changes;
};


}


#endif // CREATUREEVENTAI_H
