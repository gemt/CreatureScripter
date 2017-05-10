#include "defaultlineedit.h"
#include <QSqlField>
#include <QDebug>
#include <QIntValidator>

DefaultLineEdit::DefaultLineEdit(MangosRecord &r, const QString fieldName, const QString& tooltip, QWidget *parent)
    : QLineEdit(parent), record(r)
{
    setValidator(new QIntValidator(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
    rIdx = record.indexOf(fieldName);
    setText(record.value(rIdx).toString());
    setToolTip(tooltip);
    connect(this, &QLineEdit::textChanged, this, &DefaultLineEdit::onTextChange);
}

void DefaultLineEdit::onTextChange(const QString &newText)
{
    bool ok;
    int val = newText.toInt(&ok);
    if(!ok) {
        QPalette pal = palette();
        pal.setBrush(QPalette::Base, QColor(Qt::red));
        setPalette(pal);
    }else{
        setPalette(QPalette());
        setFont(QFont());
        record.setValue(rIdx, val);

    }
}
