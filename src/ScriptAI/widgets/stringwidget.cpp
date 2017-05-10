#include "stringwidget.h"
#include <QSqlField>

StringWidget::StringWidget(MangosRecord &r, const QString fieldName, const QString& tooltip, QWidget *parent)
    : QLineEdit(parent), record(r)
{
    rIdx = record.indexOf(fieldName);
    setText(record.value(rIdx).toString());
    setToolTip(tooltip);
    connect(this, &QLineEdit::textChanged, this, &StringWidget::onTextChange);
}

void StringWidget::onTextChange(const QString &newText)
{
    record.setValue(rIdx, newText);
}
