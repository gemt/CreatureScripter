#include "creaturetemplatedef.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

const QVector<TableTypeValue> &CreatureTemplateDef::FieldTypes()
{
    return _fieldTypes;
}

CreatureTemplateDef::CreatureTemplateDef()
{
    Load();
}

void CreatureTemplateDef::Load()
{
    QFile f(":/eventai/json/CreatureTemplate.json");
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
    QJsonArray arr = doc.array();

    foreach(const QJsonObject& obj, arr){
        TableTypeValue v;
        obj.value("");
        v.name = obj.contains("name") ? obj["name"].toString() : "";
        v.tooltip = obj["desc"].toString();
        v._type = (WidgetType)obj["type"].toInt();
        bool useAltVal = v._type == STRING_VALUE_DROPDOWN;
        QJsonArray params = obj["params"].toArray();
        foreach(const QJsonValue& v, params){
            QJsonObject p = v.toObject();
            EventAI::TypeValue t;
            t.description = p.contains("d") ? p["d"].toString() : "";
            t.name = p["n"].toString();
            if(useAltVal)
                t.altValue = p["v"].toString();
            else
                t.value = p["v"].toInt();

        }
        events.insert(event.id, std::move(event));
    }
}
