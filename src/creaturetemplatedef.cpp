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

    foreach(const QJsonValue& objV, arr){
        QJsonObject obj = objV.toObject();
        TableTypeValue v;

        v._field = obj["field"].toString();
        v.name = (obj.contains("name") ? obj["name"].toString() : v._field);
        v.tooltip = obj["desc"].toString();
        v._type = (WidgetType)obj["type"].toInt();
        bool useAltVal = v._type == STRING_VALUE_DROPDOWN;
        QJsonArray params = obj["params"].toArray();
        foreach(const QJsonValue& val, params){
            QJsonObject p = val.toObject();
            EventAI::TypeValue t;
            t.description = p.contains("d") ? p["d"].toString() : "";
            t.name = p["n"].toString();
            if(useAltVal)
                t.altValue = p["v"].toString();
            else
                t.value = p["v"].toInt();
            v.values.push_back(std::move(t));
        }
        _fieldTypes.push_back(std::move(v));
    }
}
