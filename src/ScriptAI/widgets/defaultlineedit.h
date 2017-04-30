#ifndef DEFAULTLINEEDIT_H
#define DEFAULTLINEEDIT_H

#include <QLineEdit>
#include <QSqlRecord>

#include "eventaidef.h"

class DefaultLineEdit : public QLineEdit
{
public:
    DefaultLineEdit(QSqlRecord& r, const QString fieldName, const EventAI::Parameter& param,  QWidget* parent = nullptr);

private slots:
    void onTextChange(const QString& newText);

private:
    QSqlRecord& record;
    const EventAI::Parameter& parameter;
    int rIdx;
};

#endif // DEFAULTLINEEDIT_H
