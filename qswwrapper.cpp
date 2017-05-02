#include "qswwrapper.h"
#include <QHBoxLayout>
#include "MainForm.h"

QSWWrapper &QSWWrapper::Get()
{
    static QSWWrapper wrapper;
    return wrapper;
}

QSWWrapper::QSWWrapper()
{
    setModal(false);
    QHBoxLayout* l = new QHBoxLayout(this);
    setLayout(l);
    qswf = new MainForm();
    l->addWidget(qswf);
    setWindowTitle("QSpellWorks");
    hide();
    for (quint8 i = 0; i < 3; ++i) {
        QObject::connect(qswf, SIGNAL(aboutToQuit()), qswf->getBrowser(i), SLOT(deleteLater()));
    }
}

void QSWWrapper::closeEvent(QCloseEvent *event)
{
    hide();
}
