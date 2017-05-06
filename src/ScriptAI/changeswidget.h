#ifndef CHANGESWIDGET_H
#define CHANGESWIDGET_H

#include <QTextEdit>

class ChangesWidget : public QWidget
{
public:
    ChangesWidget(QWidget* parent);

private:
    QTextEdit* textEdit;
};

#endif // CHANGESWIDGET_H
