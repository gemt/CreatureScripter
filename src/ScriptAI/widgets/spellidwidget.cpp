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
 : ClickableWidget(parent),
   record(r),
   parameter(param)
{
    setMouseTracking(true);
    rIdx = record.indexOf(fieldName);
    QHBoxLayout* l = new QHBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    setLayout(l);
    QFormLayout* form = new QFormLayout();
    idLabel = new QLabel(this);
    idLabel->setStyleSheet("background-color: rgba(0,0,0,0)");
    idLabel->setContentsMargins(0,0,0,0);
    form->addRow("ID:", idLabel);

    nameLabel = new QLabel(this);
    nameLabel->setContentsMargins(0,0,0,0);
    form->addRow("Name:", nameLabel);


    iconLabel = new QLabel(this);
    l->addWidget(iconLabel);

    l->addLayout(form);

    UpdateInfo();

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

        iconLabel->setPixmap(QPixmap::fromImage(img.scaled(48,48, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
    }
    idLabel->setText(QString::number(spellId));

}

void SpellIDWidget::OnClicked()
{
    onChangeSpellBtn();
}
