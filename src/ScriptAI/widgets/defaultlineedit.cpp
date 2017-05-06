#include "defaultlineedit.h"
#include <QSqlField>
#include <QDebug>
#include <QIntValidator>

DefaultLineEdit::DefaultLineEdit(QSqlRecord &r, const QString fieldName, const EventAI::Parameter &param, QWidget *parent)
    : QLineEdit(parent), record(r), parameter(param)
{
    setValidator(new QIntValidator(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
    rIdx = record.indexOf(fieldName);
    setText(record.value(rIdx).toString());
    setToolTip(param.description);
    connect(this, &QLineEdit::textChanged, this, &DefaultLineEdit::onTextChange);
}

void DefaultLineEdit::onTextChange(const QString &newText)
{
    bool ok;
    record.setValue(rIdx, newText.toInt(&ok));
    Q_ASSERT(ok);
}
