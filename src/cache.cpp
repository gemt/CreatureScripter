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

}


QString Cache::Table(const char *table){
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
    bool ret = q.exec(QString("SELECT Entry, MapName FROM %1.map_template")
                 .arg(settings.value("worldDB").toString()));
    int entryField = q.record().indexOf("Entry");
    int nameField = q.record().indexOf("MapName");
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
