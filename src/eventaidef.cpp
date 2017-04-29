#include "eventaidef.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
#include <QMap>

EventAIDef::EventAIDef()
{
    QString path("C:/Users/G3m7/Documents/git/CreatureScripter/CreatureScripter/EventAI.json");
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly)){
        qDebug() << f.errorString();
        return;
    }

    auto data = f.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    qDebug() << err.errorString();

    QJsonObject obj = doc.object();
    QMap<QString,QString> keywords;
    QJsonValue v = obj.value("keywords");
    qDebug() << v.isArray() << v.isObject() << v.isString();
    QJsonArray jKeyWords = obj.value("keywords").toArray();
    foreach(const QJsonValue& v, jKeyWords){
        qDebug() << v.isArray() << v.isObject() << v.isString();
    }

}

EventAI::EventAIDef::EventAIDef()
{

}
