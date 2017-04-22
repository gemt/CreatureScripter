#include "scriptaitab.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QComboBox>


ScriptAITab::ScriptAITab(FullCreature &creature, QWidget *parent) :
    QWidget(parent),
    creature(creature)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    QFormLayout* infoForm = new QFormLayout(this);
    QComboBox* aiTypeBox = new QComboBox(this);
    QStringList types{"", "EventAI"};
    QString thisType = creature.cTemplate.value("AIName");
    if(!types.contains(thisType))
        types.push_back(thisType);
    aiTypeBox->addItems(types);
    aiTypeBox->setCurrentText(thisType);
    infoForm->addRow("AIName", aiTypeBox);
    mainLayout->addLayout(infoForm);
}
