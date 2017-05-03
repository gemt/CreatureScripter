#ifndef QSWWRAPPER_H
#define QSWWRAPPER_H

#include <QDialog>
#include "MainForm.h"

class QSWWrapper : public QDialog
{
public:
    static QSWWrapper& Get();

    void ShowSpell(int id);

    MainForm* qsw;
private:
    QSWWrapper();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // QSWWRAPPER_H
