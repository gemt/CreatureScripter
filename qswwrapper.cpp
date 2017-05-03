#include "qswwrapper.h"
#include <QHBoxLayout>
#include "MainForm.h"

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
