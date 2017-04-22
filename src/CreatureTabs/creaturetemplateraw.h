#ifndef CREATURETEMPLATERAW_H
#define CREATURETEMPLATERAW_H

#include "creature.h"
#include <QTableWidget>

class CreatureTemplateRaw : public QTableWidget
{
public:
    CreatureTemplateRaw(CreatureTemplate& cTemplate, QWidget* parent);
};

#endif // CREATURETEMPLATERAW_H
