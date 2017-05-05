#include "defaultlineedit.h"
#include <QSqlField>

DefaultLineEdit::DefaultLineEdit(QSqlRecord &r, const QString fieldName, const EventAI::Parameter &param, QWidget *parent)
    : QLineEdit(parent), record(r), parameter(param)
{
    rIdx = record.indexOf(fieldName);
    setText(record.value(rIdx).toString());
    setToolTip(param.description);
    connect(this, &QLineEdit::textChanged, this, &DefaultLineEdit::onTextChange);
}

void DefaultLineEdit::onTextChange(const QString &newText)
{
    record.setValue(rIdx, QSqlField(newText, record.field(rIdx).type()).value());
}
