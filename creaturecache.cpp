#include "creaturecache.h"

#include <QSqlDatabase>
#include <QSettings>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlRecord>

CreatureCache CreatureCache::instance;

Creature::Creature(const QString& name, unsigned int entry) :
    name(name),
    entry(entry)
{

}

std::vector<Creature*> CreatureCache::GetCreatures(const QString &name)
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

void CreatureCache::LoadCreatures()
{
    static bool loaded = false;
    if(loaded){
        throw std::logic_error("Creatures::LoadCreatures called twize");
    }else{
        loaded = true;
    }
    QSettings settings;
    QSqlDatabase db = QSqlDatabase::database(settings.value("connectionName").toString());
    bool ret = db.isOpen();
    if(!ret){
        throw std::logic_error("Unable to open database connection: " + db.connectionName().toStdString());
    }
    QSqlQuery q(db);
    ret = q.exec(QString("SELECT entry, name FROM %1.creature_template")
                 .arg(settings.value("worldDB").toString()));
    int entryField = q.record().indexOf("entry");
    int nameField = q.record().indexOf("name");
    if(!ret){
        throw std::logic_error("Query failed. Error: " + q.lastError().text().toStdString()
                               + ", Query:" + q.lastQuery().toStdString());
    }else{
        qDebug() << q.lastQuery();
    }
    if(!q.isValid()){
        //throw std::logic_error("Query is not valid");
    }
    while(q.next()){
        QString n = q.value(nameField).toString().toLower();
        unsigned int e = q.value(entryField).toUInt();
        _creatures.push_back(new Creature(n,e));
    }
}
