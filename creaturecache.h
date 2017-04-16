#ifndef CREATURECACHE_H
#define CREATURECACHE_H

#include <vector>
#include <QString>

class Creature
{
public:

    Creature():entry(0),name("INVALID"){}
    Creature(const QString& name, unsigned int entry);

    unsigned int entry;
    QString name;
};

class CreatureCache
{
public:
    static CreatureCache& Get(){
        return instance;
    }

    void LoadCreatures();


    std::vector<Creature*> GetCreatures(const QString& name);

private:
    CreatureCache(){}
    static CreatureCache instance;
    std::vector<Creature*> _creatures;
};


#endif // CREATURECACHE_H
