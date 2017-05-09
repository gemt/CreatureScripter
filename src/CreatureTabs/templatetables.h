#ifndef TEMPLATETABLES_H
#define TEMPLATETABLES_H

#include <QWidget>

#include "mangosrecord.h"

class QTreeView;
class TemplateTableModel;
class TemplateTreeView;
class TemplateTables : public QWidget
{
    Q_OBJECT
public:
    TemplateTables(const QVector<std::pair<QString,QSqlRecord>>& records, QWidget *parent = 0);


public slots:
    void onTextChange(const QString& s);

private:
    void SetHideRow(const QModelIndex& idx, int row, bool hide);
    TemplateTreeView* view;
    TemplateTableModel* model;
};

#endif // TEMPLATETABLES_H
