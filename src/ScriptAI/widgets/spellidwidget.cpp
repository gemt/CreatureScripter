#include "spellidwidget.h"
#include "cache.h"
#include "warnings.h"
#include "qswwrapper.h"


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QWebEngineView>
#include <QProcess>


SpellIDWidget::SpellIDWidget(QSqlRecord& r, const QString fieldName, const EventAI::Parameter& param, QWidget* parent)
 : QWidget(parent),
   record(r),
   parameter(param)
{
    setContentsMargins(0,0,0,0);
    rIdx = record.indexOf(fieldName);
    QHBoxLayout* l = new QHBoxLayout(this);
    setLayout(l);
    QFormLayout* form = new QFormLayout();

    idLabel = new QLabel(this);
    nameLabel = new QLabel(this);
    iconLabel = new QLabel(this);
    nameLabel->setContentsMargins(0,0,0,0);
    iconLabel->setContentsMargins(0,0,0,0);
    idLabel->setContentsMargins(0,0,0,0);

    l->addWidget(iconLabel);
    l->addLayout(form);

    UpdateInfo();

    QPushButton* changeBtn = new QPushButton("Change/View", this);
    connect(changeBtn, &QPushButton::clicked, this, &SpellIDWidget::onChangeSpellBtn);

    form->addRow("ID:", idLabel);
    form->addRow("Name:", nameLabel);
    form->setWidget(2, QFormLayout::SpanningRole, changeBtn);
}

void SpellIDWidget::onChangeSpellBtn()
{
    QSWWrapperModal dialog(record.value(rIdx).toInt());
    int retSpellId = dialog.exec();
    if(retSpellId > 0){
        record.setValue(rIdx, retSpellId);
        UpdateInfo();
    }
}

void SpellIDWidget::UpdateInfo()
{
    bool ok;
    int spellId = record.value(rIdx).toInt(&ok);
    Q_ASSERT(ok);

    if(auto* plugin = QSWWrapper::Get().Plugin()){
        auto vals = plugin->getValues(spellId);
        QImage img = vals["qimage"].value<QImage>();
        nameLabel->setText(vals["nameWithRank"].toString());
        iconLabel->setPixmap(QPixmap::fromImage(img));
    }
    idLabel->setText(QString::number(spellId));

}
