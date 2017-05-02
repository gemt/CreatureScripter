#include "spellidwidget.h"
#include "cache.h"
#include "warnings.h"

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

//#include "QSpellWork/QSW/plugins/spellinfo/interface.h"
//#include "plugins/spellinfo/pre-tbc/spellinfo.h"
//#include "plugins/spellinfo/pre-tbc/structure.h"
//#include "mustache/mustache.h"
//#include "MainForm.h"
#if 0
class QSWPageCopy : public QWebEnginePage
{
    public:
        QSWPageCopy(int id, QObject* parent = nullptr)
            : QWebEnginePage(parent),  m_spellId(0)
        {
            setInfo(id);
        }

        quint32 getSpellId() const { return m_spellId; }
        QString getSourceHtml() const { return m_sourceHtml; }

        void setCompareInfo(const QString &html)
        {
            setHtml(html, QUrl(QString("http://spellwork/%0").arg(m_spellId)));
        }

        void setInfo(quint32 id)
        {
            QVariantHash values = Cache::Get().spellInfo->getValues(id);
            values["style"] = Cache::Get().m_styleCss;
            Mustache::Renderer renderer;
            Mustache::QtVariantContext context(values);

            QString html;
            QTextStream stream(&html);
            stream << renderer.render(Cache::Get().m_templateHtml, &context);

            html.replace("\n",  "");
            html.replace("><", ">\n<");

            if (id)
                m_spellId = id;

            m_sourceHtml = html;
            setHtml(html, QUrl(QString("http://spellwork/%0").arg(id)));
        }
        bool acceptNavigationRequest(const QUrl& url, QWebEnginePage::NavigationType type, bool)
        {
            if (type == QWebEnginePage::NavigationTypeLinkClicked)
            {
                qint32 id = url.toString().section('/', -1).toUInt();
                history.push(m_spellId);
                setInfo(id);
                return false;
            }else if(type == QWebEnginePage::NavigationTypeBackForward){

            }
            return true;
        }
        void triggerAction(WebAction action, bool b) {
            if(action == WebAction::Back){
                if(history.size() > 0){
                    setInfo(history.pop());
                }
            }else{
                QWebEnginePage::triggerAction(action, b);
            }
        }

    private:
        quint32 m_spellId;
        QString m_sourceHtml;
        QStack<int> history;
};

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
    }

private:
    QSWPageCopy* page;
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
    spellInfo = Spell::getRecord(spellId, true);
    if (!spellInfo){
        nameLabel->setText("SPELL NOT FOUND");
        return;
    }
    nameLabel->setText(spellInfo->name());
    nameLabel->setContentsMargins(0,0,0,0);
    iconLabel = new SpellIconWidget(getSpellIcon(spellInfo->spellIconId), this);
    iconLabel->setContentsMargins(0,0,0,0);
    connect(iconLabel, &SpellIconWidget::spellIconClicked, this, &SpellIDWidget::onShowSpellDetails);
    l->addWidget(iconLabel);
    l->addLayout(form);

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

#endif
