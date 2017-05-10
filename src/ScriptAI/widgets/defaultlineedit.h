#ifndef DEFAULTLINEEDIT_H
#define DEFAULTLINEEDIT_H

#include <QLineEdit>
#include <QSqlRecord>

#include "mangoscreature.h"
#include "eventaidef.h"

class DefaultLineEdit : public QLineEdit
{
public:
    DefaultLineEdit(MangosRecord& r, const QString fieldName, const QString& tooltip, QWidget* parent = nullptr);

private slots:
    void onTextChange(const QString& newText);

private:
    MangosRecord& record;
    int rIdx;
};

#endif // DEFAULTLINEEDIT_H
