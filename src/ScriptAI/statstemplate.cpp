#include "statstemplate.h"
#include "tables.h"

#include <QSharedPointer>
#include <QLabel>
#include <QFormLayout>

StatsTemplate::StatsTemplate(std::shared_ptr<Tables::creature_template> _creature, QWidget *parent) :
    QWidget(parent)
{
    using namespace Tables;

}
