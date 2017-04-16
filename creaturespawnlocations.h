#ifndef CREATURESPAWNLOCATIONS_H
#define CREATURESPAWNLOCATIONS_H

#include "creature.h"

#include <QTableWidget>

class CreatureSpawnLocations : public QTableWidget
{
public:
    CreatureSpawnLocations(CreatureTable& creature, QWidget* parent);
};

#endif // CREATURESPAWNLOCATIONS_H
