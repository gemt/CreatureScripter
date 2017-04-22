#ifndef CREATUREMODIFIER_H
#define CREATUREMODIFIER_H

#include <QTabWidget>

namespace Ui {
class CreatureModifier;
}

class CreatureModifier : public QTabWidget
{
    Q_OBJECT

public:
    explicit CreatureModifier(QWidget *parent = 0);
    ~CreatureModifier();

private:
    Ui::CreatureModifier *ui;
};

#endif // CREATUREMODIFIER_H
