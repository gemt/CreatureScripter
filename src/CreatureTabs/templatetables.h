#ifndef TEMPLATETABLES_H
#define TEMPLATETABLES_H

#include <QWidget>
#include <QSqlRecord>

class QTreeView;
class TemplateTableModel;

class TemplateTables : public QWidget
{
    Q_OBJECT
public:
    TemplateTables(const QVector<std::pair<const char*,QSqlRecord>>& records, QWidget *parent = 0);


public slots:
    void onTextChange(const QString& s);

private:
    void SetHideRow(const QModelIndex& idx, int row, bool hide);
    QTreeView* view;
    TemplateTableModel* model;
};

#endif // TEMPLATETABLES_H
