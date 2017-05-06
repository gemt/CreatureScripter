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

const QMap<int, EventAI_Action> &EventAIStorage::Actions()
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
#ifdef ELYSIUM
QFile f(":/eventai/json/EventAI_elysium.json");
#else
QFile f(":/eventai/json/EventAI_cmangos.json");
#endif

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

    QMap<QString,Parameter> eventParameters;
    {
        QJsonArray eParams = obj["paramTypes"].toArray();
        foreach(const QJsonValue& v, eParams){
            QJsonObject o = v.toObject();
            ParameterType t = (ParameterType)o["type"].toInt();
            if(t <=PT_MIN || t >= PT_UNKNOWN){
                throw std::runtime_error(QString("Parsed unknown paramTypes with id: %1").arg(t).toStdString());
            }
            QString n = o["name"].toString();
            QString d = o["desc"].toString();
            eventParameters[n] = Parameter{t, n, d};
        }
    }

    QJsonArray eEvents = obj["events"].toArray();
    foreach(const QJsonValue& v, eEvents){
        QJsonObject o = v.toObject();

        EventAI_event event;
        QString name = o["name"].toString();

        event.id = o["id"].toInt();
        //event.name = name;
        event.shortName = name.remove("EVENT_T_");
        event.description = o["d1"].toString();
        //event.triggerNote = o["t"].toString();
        QJsonArray params = o["params"].toArray();
        foreach(const QJsonValue& v, params){
            qDebug() << v.toString();
            auto it = eventParameters.find(v.toString());
            if(it == eventParameters.end()){
                event.params.push_back(Parameter{PT_UNKNOWN, "UNKNOWN", ""});
                Q_ASSERT(0);
            }else{
                event.params.push_back(*it);
            }
        }
        events.insert(event.id, std::move(event));
    }

}

void EventAIStorage::LoadActions()
{
#ifdef ELYSIUM
QFile f(":/eventai/json/Actions_elysium.json");
#else
QFile f(":/eventai/json/Actions_cmangos.json");
#endif

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

    QJsonArray paramInfo = obj["paramInfo"].toArray();
    QMap<int,QStringList> loadedParamDescs;
    QMap<int,QStringList> loadedParamNames;
    foreach(const QJsonValue& v, paramInfo){
        QJsonObject paramInfoObj = v.toObject();
        int id = paramInfoObj["actionId"].toInt();
        Q_ASSERT(!loadedParamDescs.contains(id));
        Q_ASSERT(!loadedParamNames.contains(id));
        QJsonArray names = paramInfoObj["names"].toArray();
        foreach(const QJsonValue& d, names){
            loadedParamNames[id].push_back(d.toString());
        }
        Q_ASSERT(loadedParamNames[id].size() == 4);

        QJsonArray descs = paramInfoObj["descs"].toArray();
        foreach(const QJsonValue& d, descs){
            loadedParamDescs[id].push_back(d.toString());
        }
        Q_ASSERT(loadedParamDescs[id].size() == 4);
    }

    QJsonArray eActions = obj["actions"].toArray();
    qDebug() << eActions.count() << paramInfo.count();
    Q_ASSERT(eActions.count() == paramInfo.count());

    foreach(const QJsonValue& v, eActions){
        QJsonObject o = v.toObject();
        EventAI_Action action;
        QString name = o["Name"].toString();
        action.id = o["id"].toInt();
        action.name = name;
        action.shortName = name.remove("ACTION_T_");
        action.description = o["desc"].toString();

        QJsonArray params = o["params"].toArray();
        int paramNum = 0;
        foreach(const QJsonValue& v, params){
            qDebug() << v.toString();
            ParameterType type = (ParameterType)v.toInt(PT_UNKNOWN);
            action.params.push_back(
                        Parameter{type,
                                  loadedParamNames[action.id][paramNum],
                                  loadedParamDescs[action.id][paramNum]});

            paramNum++;
        }
        actions.insert(action.id, std::move(action));
    }

}

}
