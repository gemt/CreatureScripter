#include "eventaidef.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
#include <QMap>
#include <QStringList>
#include <QDebug>

namespace EventAI{
const QMap<int, EventAI_event> &EventAIStorage::Events()
{
    return events;
}

const QMap<int, event_action> &EventAIStorage::Actions()
{
    return actions;
}

EventAIStorage::EventAIStorage()
{
    LoadEvents();
    LoadActions();
}

void EventAIStorage::LoadEvents()
{
    QFile f(":/eventai/json/EventAI.json");
    if(!f.open(QIODevice::ReadOnly)){
        throw std::runtime_error(QString("Unable to open file: %1").arg(f.fileName()).toStdString());
    }

    auto data = f.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if(err.error != QJsonParseError::NoError){
        throw std::runtime_error(QString("Error (%1) when parsing json from file: %2")
                                 .arg(err.errorString(), f.fileName()).toStdString());
    }
    QJsonObject obj = doc.object();

    {
        QJsonObject kw = obj["keywords"].toObject();
        for(auto it = kw.constBegin(); it != kw.constEnd(); it++){
            keywords[it.key()] = it.value().toString();
        }
    }
    {
        QJsonArray eParams = obj["paramTypes"].toArray();
        foreach(const QJsonValue& v, eParams){
            QJsonObject o = v.toObject();
            int t = o["type"].toInt();
            if(t <=TYPE_MIN || t >= UNKNOWN){
                throw std::runtime_error(QString("Parsed unknown paramTypes with id: %1").arg(t).toStdString());
            }
            QString n = o["name"].toString();
            QString d = o["desc"].toString();
            event_paramTypes_map[n] = event_param{(EventAIParamType)t, n, d};
        }
    }

    QJsonArray eEvents = obj["events"].toArray();
    foreach(const QJsonValue& v, eEvents){
        QJsonObject o = v.toObject();

        EventAI_event event;

        event.id = o["id"].toInt();
        event.name = o["name"].toString();
        event.description = o["d1"].toString();
        event.triggerNote = o["t"].toString();
        QJsonArray params = o["params"].toArray();
        foreach(const QJsonValue& v, params){
            qDebug() << v.toString();
            auto it = EventAIStorage::event_paramTypes_map.find(v.toString());
            if(it == event_paramTypes_map.end()){
                throw std::runtime_error(QString("unknown event param type: %1").arg(v.toString()).toStdString());
            }else{
                event.params.push_back(*it);
            }
        }
        events.insert(event.id, std::move(event));
    }

}

void EventAIStorage::LoadActions()
{
    QFile f(":/eventai/json/Actions.json");
    if(!f.open(QIODevice::ReadOnly)){
        throw std::runtime_error(QString("Unable to open file: %1").arg(f.fileName()).toStdString());
    }

    auto data = f.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if(err.error != QJsonParseError::NoError){
        throw std::runtime_error(QString("Error (%1) when parsing json from file: %2")
                                 .arg(err.errorString(), f.fileName()).toStdString());
    }
    QJsonObject obj = doc.object();
    QJsonArray eActions = obj["actions"].toArray();
    foreach(const QJsonValue& v, eActions){
        QJsonObject o = v.toObject();
        event_action action;

        action.id = o["id"].toInt();
        action.name = o["Name"].toString();
        action.description = o["desc"].toString();

        QJsonArray params = o["params"].toArray();
        foreach(const QJsonValue& v, params){
            qDebug() << v.toString();
            action.params.push_back(action_param{A_UNKNOWN, v.toString(), "todo"});
            /*
            auto it = EventAIStorage::event_paramTypes_map.find(v.toString());
            if(it == event_paramTypes_map.end()){
                throw std::runtime_error(QString("unknown event param type: %1").arg(v.toString()).toStdString());
            }else{
                event.params.push_back(*it);
            }
            */
        }
        actions.insert(action.id, std::move(action));
    }

}

}
