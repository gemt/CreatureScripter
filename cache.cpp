#include "cache.h"
#include "creature.h"

#include <QSqlDatabase>
#include <QSettings>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlRecord>

Cache Cache::instance;

Creature::Creature(const QString& name, unsigned int entry) :
    name(name),
    entry(entry)
{

}

std::vector<Creature*> Cache::GetCreatures(const QString &name)
{
    if(name.isEmpty())
        return _creatures;
    QString lName = name;
    bool isUInt;
    unsigned int intVal = lName.toUInt(&isUInt);
    std::vector<Creature*> ret;
    if(isUInt){
        for(auto it = _creatures.cbegin(); it != _creatures.cend(); it++){
            if((*it)->entry == intVal)
                ret.push_back(*it);
        }
        return ret;
    }else{
        QString sn = lName.toLower();
        std::vector<Creature*> ret;
        for(auto it = _creatures.cbegin(); it != _creatures.cend(); it++){
            if((*it)->name.contains(sn))
                ret.push_back(*it);
        }

        return ret;
    }

}

QString Cache::MapName(unsigned int entry)
{
    return maps.value(entry, "Unknown map");
}

void Cache::LoadCreatures()
{
    static bool loaded = false;
    if(loaded) throw std::logic_error("Cache::LoadCreatures called twize");
    else loaded = true;

    QSettings settings;
    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
    if(!db.isOpen()){
        throw std::logic_error("Database connection not open");
    }
    QSqlQuery q(db);
    bool ret = q.exec(QString("SELECT entry, name FROM %1.creature_template")
                 .arg(settings.value("worldDB").toString()));
    int entryField = q.record().indexOf("entry");
    int nameField = q.record().indexOf("name");
    if(!ret){
        throw std::logic_error("Query failed. Error: " + q.lastError().text().toStdString()
                               + ", Query:" + q.lastQuery().toStdString());
    }

    while(q.next()){
        QString n = q.value(nameField).toString().toLower();
        unsigned int e = q.value(entryField).toUInt();
        _creatures.push_back(new Creature(n,e));
    }
}

static void LoadSchema(const QString& table, QStringList& names)
{
    QSettings settings;
    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
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

    LoadSchema(CreatureTable::tableName, CreatureTable::names);
    LoadSchema(CreatureTemplate::tableName, CreatureTemplate::names);
    LoadSchema(CreatureAIScripts::tableName, CreatureAIScripts::names);
}

void Cache::LoadMaps()
{
    static bool loaded = false;
    if(loaded) throw std::logic_error("Cache::LoadMaps called twize");
    else loaded = true;

    QSettings settings;
    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
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
        QString n = q.value(nameField).toString().toLower();
        unsigned int e = q.value(entryField).toUInt();
        maps[e] = n;
    }
}
