#ifndef SCRIPTAITAB_H
#define SCRIPTAITAB_H

#include "creature.h"
#include <QWidget>

class ScriptAITab : public QWidget
{
    Q_OBJECT
public:
    ScriptAITab(FullCreature& creature, QWidget* parent);

private:
    FullCreature& creature;


};

#endif // SCRIPTAITAB_H
