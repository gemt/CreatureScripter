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

    bool verbose = false;
    void Remake();
private:
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
public:
    CreatureEventAI(std::shared_ptr<Tables::creature_template> creature, QWidget* parent);

private:
    std::shared_ptr<Tables::creature_template> _creature;
    QVector<EventEntry*> entryWidgets;
};


}


#endif // CREATUREEVENTAI_H
