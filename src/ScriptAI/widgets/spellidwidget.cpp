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

SpellIconWidget::SpellIconWidget(const QImage &img, QWidget *parent)
    :QLabel(parent)
{
    setPixmap(QPixmap::fromImage(img));
    //setScaledContents(true);
}

void SpellIconWidget::mouseDoubleClickEvent(QMouseEvent *){
    emit spellIconClicked();
}

class SpellView : public QDialog {
public:
    SpellView(int id, QWidget* parent){
        /*
        if(!Cache::Get().spellInfo){
            qCritical() << "SpellView widget ctor, but spellInfo ptr in Cache is nullptr";
            return;
        }
        QHBoxLayout* l = new QHBoxLayout(this);
        setLayout(l);
        QWebEngineView* view = new QWebEngineView(this);
        l->addWidget(view);
        page = new QSWPageCopy(id, parent);

        view->setPage(page);
        */
    }

private:
};

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

    bool ok;
    int spellId = record.value(rIdx).toInt(&ok);
    Q_ASSERT(ok);

    if(SpellInfoInterface* qsi = QSWWrapper::Get().qsw->m_sw->getActivePlugin()){
        /*
        qsi->
        qsi->get getValues(spellId);
        qvh[""].to
        QSWWrapper::Get().qsw->ShowSpell(spellId);
        const Spell::entry* spellInfo = Spell::getRecord(id, true);

        nameLabel->setText(spellInfo->name());
        nameLabel->setContentsMargins(0,0,0,0);
        iconLabel = new SpellIconWidget(getSpellIcon(spellInfo->spellIconId), this);
        iconLabel->setContentsMargins(0,0,0,0);
        connect(iconLabel, &SpellIconWidget::spellIconClicked, this, &SpellIDWidget::onShowSpellDetails);
        l->addWidget(iconLabel);
        l->addLayout(form);
        */
    }else{
        Warnings::Warning("No loaded QSW plugin");
    }
    idLabel->setText(QString::number(spellId));
    idLabel->setContentsMargins(0,0,0,0);

    QPushButton* changeBtn = new QPushButton("Change", this);
    connect(changeBtn, &QPushButton::clicked, [this](){
        static QProcess* p = nullptr;
        if(!p){
             p = new QProcess();
             //p->start("C:/Users/G3m7/Documents/git/CreatureScripter/CreatureScripter/QSpellWork/build-qsw-msvc2015_64bit-Release/bin/x64/Release/ QSW.exe");
             //p->execute("C:\Users\G3m7\Documents\git\CreatureScripter\CreatureScripter\QSpellWork\build-qsw-msvc2015_64bit-Release\bin\x64\Release\QSW.exe");
             if(!p->waitForStarted())
                 qDebug() << p->errorString();
        }
    });

    form->addRow("ID:", idLabel);
    form->addRow("Name:", nameLabel);
    form->setWidget(2, QFormLayout::SpanningRole, changeBtn);
    //form->addWidget(changeBtn);

}

void SpellIDWidget::onChangeSpellBtn()
{
    // new modal dialog showing a spell-searcher type gui, like the creatureSearcher
    //Warnings::Warning("SpellIDWidget::onChangeSpellBtn unimplemented", QMessageBox::Information);
}

void SpellIDWidget::onShowSpellDetails()
{
    //todo: show dialog with spell-info or something
    qDebug() << "YAY";
    SpellView dialog(record.value(rIdx).toInt(), this);
    dialog.exec();
}
