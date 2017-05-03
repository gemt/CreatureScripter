#include "qswwrapper.h"
#include "warnings.h"
#include "MainForm.h"

#include <QHBoxLayout>
#include <QDialogButtonBox>

QSWWrapper &QSWWrapper::Get()
{
    static QSWWrapper wrapper;
    return wrapper;
}

void QSWWrapper::ShowSpell(int id)
{
    qsw->ShowSpell(id);
    show();
}

SpellInfoInterface *QSWWrapper::Plugin()
{
    if(SpellInfoInterface* i = qsw->m_sw->getActivePlugin()){
       return i;
    }else{
        Warnings::Warning("No QSW plugin loaded");
        return nullptr;
    }
}

SpellWork *QSWWrapper::SW()
{
    if(!Plugin())
        return nullptr;
    return qsw->m_sw;
}

QSWWrapper::QSWWrapper()
{
    setModal(false);
    QHBoxLayout* l = new QHBoxLayout(this);
    setLayout(l);
    qsw = new MainForm();
    l->addWidget(qsw);
    setWindowTitle("QSpellWorks");
    hide();
}

void QSWWrapper::closeEvent(QCloseEvent *event)
{
    hide();
}


QSWWrapperModal::QSWWrapperModal(int id)
{
    setModal(true);
    QVBoxLayout* l = new QVBoxLayout(this);
    setLayout(l);
    qsw = new MainForm();
    qsw->m_sw->setActivePlugin2(QSWWrapper::Get().SW()->GetActivePlugin());
    qsw->ShowSpell(id);
    l->addWidget(qsw);
    setWindowTitle("QSpellWorks");
    QDialogButtonBox* buttons = new QDialogButtonBox(this);
    QPushButton* cancelButton = buttons->addButton("Cancel", QDialogButtonBox::RejectRole);
    QPushButton* useButton = buttons->addButton("Use current spell", QDialogButtonBox::AcceptRole);
    l->addWidget(buttons);
    connect(cancelButton, &QPushButton::clicked, [this](){
        done(-1);
    });
    connect(useButton, &QPushButton::clicked, this, &QSWWrapperModal::onAccepted);
}

void QSWWrapperModal::onAccepted()
{
    done(qsw->m_sw->getForm()->getPage(QSW::PAGE_MAIN)->getSpellId());
}
