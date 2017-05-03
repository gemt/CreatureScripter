#ifndef QSWWRAPPER_H
#define QSWWRAPPER_H

#include <QDialog>
#include "MainForm.h"
#include "plugins/spellinfo/interface.h"

class QSWWrapper : public QDialog
{
public:
    static QSWWrapper& Get();

    void ShowSpell(int id);

    SpellInfoInterface* Plugin();
    SpellWork* SW();
    MainForm* qsw;
private:
    QSWWrapper();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

class QSWWrapperModal : public QDialog
{
public:
    QSWWrapperModal(int id);

private slots:
    void onAccepted();

private:
    MainForm* qsw;

};

#endif // QSWWRAPPER_H
