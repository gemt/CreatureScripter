#ifndef COLLAPSABLEFRAME_H
#define COLLAPSABLEFRAME_H

#include <QWidget>
#include <QFrame>
class QVBoxLayout;
class QPushButton;

namespace EventAI
{

class EventEntry;
class CollapsibleFrame : public QFrame
{
    Q_OBJECT
private:
    QVBoxLayout* l;
    QPushButton* btn;
    EventEntry* _w;
public:
    CollapsibleFrame(const QString& buttonText, const QString& labelText, QWidget *parent);
    void SetWidget(EventEntry* w);

};

}
#endif // COLLAPSABLEFRAME_H
