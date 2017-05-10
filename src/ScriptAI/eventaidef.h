#ifndef EVENTAIDEF_H
#define EVENTAIDEF_H

#ifdef ELYSIUM
#include "eventaidefelysium.h"
#else
#include "eventaidefcmangos.h"
#endif


#include <QVector>
#include <QMap>
namespace EventAI
{

class EventAIStorage
{
public:
    static EventAIStorage& Get(){
        static EventAIStorage* instance = nullptr;
        if(!instance)
            instance = new EventAIStorage();
        return *instance;
    }

    const QMap<int,EventAI_event>& Events();
    const QMap<int,EventAI_Action>& Actions();
private:
    EventAIStorage();
    QMap<QString,QString> keywords;
    QMap<int, EventAI_event> events;
    QMap<int, EventAI_Action> actions;

    void LoadEvents();
    void LoadActions();
};

}

#endif // EVENTAIDEF_H
