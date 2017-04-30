#include "spellidwidget.h"
#include "cache.h"
#include "warnings.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>

SpellIDWidget::SpellIDWidget(QSqlRecord& r, int idx, QWidget* parent)
 : QWidget(parent),
   record(r),
   rIdx(idx)
{
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
    Warnings::Warning("SpellIDWidget::onChangeSpellBtn unimplemented", QMessageBox::Information);
}

void SpellIDWidget::PopulateInfoFromDBC()
{
    bool ok;
    int spellId = record.value(rIdx).toInt(&ok);
    Q_ASSERT(ok);

    idLabel->setText(QString::number(spellId));
    nameLabel->setText("missing dbc integration");
    //todo: need dbc integration...
}
