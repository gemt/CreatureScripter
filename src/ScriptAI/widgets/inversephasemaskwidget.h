#ifndef INVERSEPHASEMASKWIDGET_H
#define INVERSEPHASEMASKWIDGET_H

#include "eventaidef.h"
#include "mangosrecord.h"

#include <QWidget>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlField>
#include <QComboBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QEvent>
#include <QStyledItemDelegate>
#include <QListView>
#include <QVBoxLayout>

class InversePhaseMaskWidget : public QWidget
{
public:
    InversePhaseMaskWidget(MangosRecord& r, const QString& fieldName, QWidget* parent, bool verbose);
    void UpdateVerboseLabel();
private:
    MangosRecord& record;
    const QString fieldName;

    // QWidget interface
public:
    QSize minimumSizeHint() const;
};



class PhaseWidgetList : public QComboBox
{
    Q_OBJECT
public:
    PhaseWidgetList(MangosRecord &r, const QString &fieldName, InversePhaseMaskWidget* parent);
    QStandardItem* addCheckItem(const QString &label, const QVariant &data, const Qt::CheckState checkState);
protected:
    bool eventFilter(QObject* _object, QEvent* _event);
private:
    QStandardItemModel* m_model;
    void updateText();
    bool is_shown;
    MangosRecord& record;
    const QString fieldName;
    InversePhaseMaskWidget* _parent;
private slots:
    void on_itemPressed(const QModelIndex &index);
};
#endif // INVERSEPHASEMASKWIDGET_H
