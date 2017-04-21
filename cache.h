#ifndef CREATURECACHE_H
#define CREATURECACHE_H

#include <QMap>
#include <vector>
#include <QString>
#include <QSettings>
#include <QSqlDatabase>

class Creature
{
public:

    Creature():entry(0),name("INVALID"){}
    Creature(const QString& name, unsigned int entry);

    unsigned int entry;
    QString name;
};

class Cache
{
public:
    static Cache& Get(){
        return instance;
    }

    bool Connect();
    bool isConnected();

    void LoadCreatures();
    void LoadSchemas();
    void LoadMaps();

    std::vector<Creature*> GetCreatures(const QString& name);
    QString MapName(unsigned int entry);

private:
    Cache();
    static Cache instance;

    std::vector<Creature*> _creatures;
    QMap<unsigned int, QString> maps;

};


#endif // CREATURECACHE_H
