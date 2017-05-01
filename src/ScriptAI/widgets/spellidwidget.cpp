#include "spellidwidget.h"
#include "cache.h"
#include "warnings.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>

#include "QSpellWork/QSW/plugins/spellinfo/interface.h"
#include "plugins/spellinfo/pre-tbc/spellinfo.h"
#include "plugins/spellinfo/pre-tbc/structure.h"
#include <QLabel>
#include <QPixmap>
#include <QIcon>

SpellIDWidget::SpellIDWidget(QSqlRecord& r, const QString fieldName, const EventAI::Parameter& param, QWidget* parent)
 : QWidget(parent),
   record(r),
   parameter(param)
{
    rIdx = record.indexOf(fieldName);
    QHBoxLayout* l = new QHBoxLayout(this);
    setLayout(l);
    QFormLayout* form = new QFormLayout();

    changeButton = new QPushButton("...", this);
    connect(changeButton, &QPushButton::clicked, this, &SpellIDWidget::onChangeSpellBtn);

    l->addWidget(changeButton);
    l->addLayout(form);

    idLabel = new QLabel(this);
    nameLabel = new QLabel(this);
    form->addRow("ID:", idLabel);
    form->addRow("Name:", nameLabel);

    PopulateInfoFromDBC();
}

void SpellIDWidget::onChangeSpellBtn()
{
    // new modal dialog showing a spell-searcher type gui, like the creatureSearcher
    //Warnings::Warning("SpellIDWidget::onChangeSpellBtn unimplemented", QMessageBox::Information);
}

void SpellIDWidget::PopulateInfoFromDBC()
{
    bool ok;
    int spellId = record.value(rIdx).toInt(&ok);
    Q_ASSERT(ok);
    idLabel->setText(QString::number(spellId));
    const Spell::entry* spellInfo = Spell::getRecord(spellId, true);
    if (!spellInfo){
        nameLabel->setText("SPELL NOT FOUND");
        return;
    }
    nameLabel->setText(spellInfo->name());
    QImage img = getSpellIcon(spellInfo->spellIconId);
    QIcon ico(QPixmap::fromImage(img));
    changeButton->setIcon(ico);
    changeButton->setIconSize(img.size());
    changeButton->setFixedSize(img.size());
}
