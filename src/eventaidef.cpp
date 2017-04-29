#include "eventaidef.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
#include <QMap>

namespace EventAI{

EventAIStorage::EventAIStorage()
{
    QString path(":/eventai/json/EventAI.json");
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly)){
        throw std::runtime_error(QString("Unable to open file: %1").arg(path).toStdString());
    }

    auto data = f.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if(err.error != QJsonParseError::NoError){
        throw std::runtime_error(QString("Error (%1) when parsing json from file: %2")
                                 .arg(err.errorString(), path).toStdString());
    }
    QJsonObject obj = doc.object();
    QMap<QString,QString> keywords;
    QJsonValue v = obj.value("keywords");
    qDebug() << v.isArray() << v.isObject() << v.isString();
    QJsonArray jKeyWords = obj.value("keywords").toArray();
    foreach(const QJsonValue& v, jKeyWords){
        qDebug() << v.isArray() << v.isObject() << v.isString();
    }

}

}
