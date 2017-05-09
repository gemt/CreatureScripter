#ifndef CHANGESWIDGET_H
#define CHANGESWIDGET_H

#include <QTextEdit>
#include <QSet>

#include <memory>

#include "mangosrecord.h"

class QVBoxLayout;

namespace Tables{
struct creature_template;
}

class ChangesWidget : public QWidget
{
    Q_OBJECT
public:
    ChangesWidget(QWidget* parent, std::shared_ptr<Tables::creature_template> creature);

    bool AnyNewChanges();

public slots:
    //void ValueChanged(QString table, QString field, QVariant value, QString pk, QVariant pkVal);
    void ValueChanged(MangosRecord rec);

private:
    QTextEdit* textEdit;
    QSet<QString> changestrings;
    QVBoxLayout* l;
    QMap<QString,QWidget*> changes;
};

#endif // CHANGESWIDGET_H
