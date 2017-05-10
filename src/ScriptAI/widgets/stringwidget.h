#ifndef STRINGWIDGET_H
#define STRINGWIDGET_H

#include "mangosrecord.h"

#include <QLineEdit>

class StringWidget : public QLineEdit
{
    Q_OBJECT
public:
    StringWidget(MangosRecord& r, const QString fieldName, const QString& tooltip, QWidget* parent = nullptr);

private slots:
    void onTextChange(const QString& newText);

private:
    MangosRecord& record;
    int rIdx;
};

#endif // STRINGWIDGET_H
