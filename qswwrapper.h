#ifndef QSWWRAPPER_H
#define QSWWRAPPER_H

#include <QDialog>
#include "MainForm.h"

class QSWWrapper : public QDialog
{
public:
    static QSWWrapper& Get();
private:
    QSWWrapper();
    MainForm* qswf;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // QSWWRAPPER_H
