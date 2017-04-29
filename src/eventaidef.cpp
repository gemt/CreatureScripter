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

EventAIStorage::EventAIStorage()
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
            QString t = o["type"].toString();
            QString n = o["name"].toString();
            QString d = o["desc"].toString();
            event_paramTypes_map[n] = event_param{t, n, d};
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
            auto it = event_paramTypes_map.find(v.toString());
            if(it == event_paramTypes_map.end()){
                event.params.push_back(event_param::unimplemented(v.toString()));
            }else{
                event.params.push_back(*it);
            }
        }
        events.insert(event.id, std::move(event));
    }

}

}
