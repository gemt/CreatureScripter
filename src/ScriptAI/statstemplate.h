#ifndef STATSTEMPLATE_H
#define STATSTEMPLATE_H

#include "tables.h"

#include <QWidget>
#include <memory>

class StatsTemplate : public QWidget
{
public:
    StatsTemplate(std::shared_ptr<Tables::creature_template> creature, QWidget* parent);
};

#endif // STATSTEMPLATE_H
