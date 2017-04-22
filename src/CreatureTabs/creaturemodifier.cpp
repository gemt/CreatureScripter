#include "creaturemodifier.h"
#include "ui_creaturemodifier.h"

CreatureModifier::CreatureModifier(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CreatureModifier)
{
    ui->setupUi(this);
    //ui->nameLabel->sette
}

CreatureModifier::~CreatureModifier()
{
    delete ui;
}
