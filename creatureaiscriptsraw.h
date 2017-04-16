#ifndef CREATUREAISCRIPTSRAW_H
#define CREATUREAISCRIPTSRAW_H

#include "creature.h"
#include <QTableWidget>

class CreatureAIScriptsRaw : public QTableWidget
{
public:
    CreatureAIScriptsRaw(CreatureAIScripts& creature, QWidget* parent);
};

#endif // CREATUREAISCRIPTSRAW_H
