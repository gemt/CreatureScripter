#include "cache.h"
#include "creature.h"
#include "warnings.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlRecord>
#include <QStandardItem>
#include <QSqlDriver>

namespace Tables {
const QString creature::t = "creature";
const QString creature::id = "id";

const QString creature_template::t = "creature_template";
const QString creature_template::entry = "entry";
const QString creature_template::name = "name";
const QString creature_template::modelid_1 = "modelid_1";
const QString creature_template::modelid_2 = "modelid_2";
const QString creature_template::modelid_3 = "modelid_3";
const QString creature_template::modelid_4 = "modelid_4";
const QString creature_template::equipment_id = "equipment_id";

const QString creature_template_addon::t = "creature_template_addon";
const QString creature_template_addon::entry = "entry";

const QString creature_model_info::t = "creature_model_info";
const QString creature_model_info::modelid = "modelid";

const QString creature_equip_template::t = "creature_equip_template";
const QString creature_equip_template::entry = "entry";

const QString creature_equip_template_raw::t = "creature_equip_template_raw";

const QString creature_addon::t = "creature_addon";

const QString creature_ai_scripts::t = "creature_ai_scripts";
const QString creature_ai_scripts::creature_id = "creature_id";

const QString item_template::t = "item_template";


}

namespace Tables{

QString Table::Query(const QString& k, const QString& v) const {
    return QString("SELECT * FROM %1 WHERE %2 = %3").arg(table(), k, v);
}

QString Table::dbTable() {
    return QString("%1.%2").arg(Cache::Get().settings.value("worldDB").toString(), table());
}

QVector<relation> creature_template::Relations()  {
    return QVector<relation>{
        makeRelation<creature>(entry, creature::id),
        makeRelation<creature_ai_scripts>(entry, creature_ai_scripts::creature_id),
        makeRelation<creature_template_addon>(entry, creature_template_addon::entry),
        makeRelation<creature_model_info>(modelid_1, creature_model_info::modelid),
        makeRelation<creature_model_info>(modelid_2, creature_model_info::modelid),
        makeRelation<creature_model_info>(modelid_3, creature_model_info::modelid),
        makeRelation<creature_model_info>(modelid_4, creature_model_info::modelid),
        makeRelation<creature_equip_template>(equipment_id, creature_equip_template::entry),
    };
}

QVector<relation> creature_equip_template::Relations()
{
    return QVector<relation>{
        makeRelation<creature>("equipentry1", "entry", "Main-hand"),
        makeRelation<creature>("equipentry2", "entry", "Off-hand"),
        makeRelation<creature>("equipentry3", "entry", "Ranged")

    };
}


}

Creature::Creature(const QString& name, unsigned int entry) :
    name(name),
    entry(entry)
{

}

QString Cache::MapName(unsigned int entry)
{
    return maps.value(entry, "Unknown map");
}

Cache::Cache(){
    using namespace Tables;

    table_definitions[creature::t] = new creature;
    table_definitions[creature_template::t] = new creature_template;
    table_definitions[creature_template_addon::t] = new creature_template_addon;
    table_definitions[creature_model_info::t] = new creature_model_info;
    table_definitions[creature_equip_template::t] = new creature_equip_template;
    table_definitions[creature_equip_template_raw::t] = new creature_equip_template_raw;

    table_definitions[creature_template::t] = new creature_template;
    table_definitions[creature_template::t] = new creature_template;
}


QString Cache::Table(const QString& table) const{
    QSettings settings;
    return QString("%1.%2").arg(settings.value("worldDB").toString(), table);
}

QSqlDatabase Cache::GetDB()
{
    return QSqlDatabase::database(settings.value("connectionName").toString(), false);
}

bool Cache::Connect()
{
    qDebug() << "Connecting to database:";
    qDebug() << "connectionName:" << settings.value("connectionName").toString();
    qDebug() << "Hostname: " << settings.value("hostName").toString();
    qDebug() << "port: "     << settings.value("port").toInt();
    qDebug() << "username: "  << settings.value("username").toString();
    qDebug() << "password: "  << settings.value("password").toString();
    qDebug() << "dbName: "      << settings.value("worldDB").toString();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", settings.value("connectionName").toString());
    db.setHostName(settings.value("hostName").toString());
    db.setPort(settings.value("port").toInt());
    db.setDatabaseName(settings.value("worldDB").toString());
    db.setUserName(settings.value("username").toString());
    db.setPassword(settings.value("password").toString());
    qDebug() << settings.value("password").toString();
    bool ok = db.open();
    if(!ok)
    {
        Warnings::Warning(db.lastError().text());
        return false;
    }
    try{
        Cache::Get();
        Cache::Get().LoadSchemas();
        Cache::Get().LoadMaps();

    }catch(std::exception& e){
        Warnings::Warning(e.what());
        return false;
    }
    return true;
}

bool Cache::isConnected()
{
    QSqlDatabase db = GetDB();
    return db.isOpen() && db.isValid();
}

void Cache::LoadSchema(const QString& table, QStringList& names)
{
    QSqlDatabase db = GetDB();
    if(!db.isOpen()){
        throw std::logic_error("Database connection not open");
    }

    QSqlQuery q(db);
    QString query = QString(
            "SELECT `COLUMN_NAME` "
            "FROM `INFORMATION_SCHEMA`.`COLUMNS`"
            "WHERE `TABLE_SCHEMA`='%1'"
            "AND `TABLE_NAME`='%2'"
            )
            .arg(settings.value("worldDB").toString())
            .arg(table);

    bool ret = q.exec(query);
    if(!ret){
        throw std::logic_error("Query failed. Error: " + q.lastError().text().toStdString()
                               + ", Query:" + q.lastQuery().toStdString());
    }

    while(q.next()){
        names.push_back(q.value("COLUMN_NAME").toString());
    }
}

void Cache::LoadSchemas()
{
    static bool loaded = false;
    if(loaded) throw std::logic_error("Cache::LoadSchemas called twize");
    else loaded = true;

    LoadSchema(CreatureTemplate::tableName, CreatureTemplate::names);
    LoadSchema(CreatureAIScripts::tableName, CreatureAIScripts::names);
}

void Cache::LoadMaps()
{
    static bool loaded = false;
    if(loaded) throw std::logic_error("Cache::LoadMaps called twize");
    else loaded = true;

    QSqlDatabase db = GetDB();
    if(!db.isOpen()){
        throw std::logic_error("Database connection not open");
    }
    QSqlQuery q(db);
    QString qry = QString("SELECT %1, %2 FROM %3").arg(
                db.driver()->escapeIdentifier(Tables::map_template::entry, QSqlDriver::FieldName),
                db.driver()->escapeIdentifier(Tables::map_template::mapname, QSqlDriver::FieldName),
                db.driver()->escapeIdentifier(Tables::map_template::t(),QSqlDriver::TableName));
    bool ret = q.exec(qry);
    int entryField = q.record().indexOf(Tables::map_template::entry);
    int nameField = q.record().indexOf(Tables::map_template::mapname);
    if(!ret){
        throw std::logic_error("Query failed. Error: " + q.lastError().text().toStdString()
                               + ", Query:" + q.lastQuery().toStdString());
    }

    while(q.next()){
        QString n = q.value(nameField).toString();//.toLower();
        unsigned int e = q.value(entryField).toUInt();
        maps[e] = n;
    }
}
