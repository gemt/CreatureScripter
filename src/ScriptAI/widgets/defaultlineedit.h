#ifndef DEFAULTLINEEDIT_H
#define DEFAULTLINEEDIT_H

#include <QLineEdit>
#include <QSqlRecord>

#include "mangoscreature.h"
#include "eventaidef.h"

class DefaultLineEdit : public QLineEdit
{
public:
    DefaultLineEdit(MangosRecord& r, const QString fieldName, const EventAI::Parameter& param,  QWidget* parent = nullptr);

private slots:
    void onTextChange(const QString& newText);

private:
    MangosRecord& record;
    const EventAI::Parameter& parameter;
    int rIdx;
};

#endif // DEFAULTLINEEDIT_H
