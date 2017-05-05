#ifndef FLAGSWIDGET_H
#define FLAGSWIDGET_H

#include <QComboBox>
#include <QSqlRecord>

#include "eventaidef.h"

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QEvent>
#include <QStyledItemDelegate>
#include <QListView>
#include <QVBoxLayout>


class QVBoxLayout;
class QListWidget;
class FlagsWidget : public QWidget{
public:
    FlagsWidget(const QVector<EventAI::TypeValue>& values, QSqlRecord& r,
                const QString& fieldName, QWidget* parent, bool verbose);
    void SetLabels(const QStringList& lbls);
private:
    bool _verbose;
    QVector<QWidget*> verboseList;
    QVBoxLayout* verboseLayout;
};

class FlagsWidgetList : public QComboBox
{
    Q_OBJECT
public:
    FlagsWidgetList(const QVector<EventAI::TypeValue>& values, QSqlRecord& r, const QString& fieldName, FlagsWidget* parent);
    QStandardItem* addCheckItem(const QString &label, const QVariant &data, const QString& tt, const Qt::CheckState checkState);
protected:
    bool eventFilter(QObject* _object, QEvent* _event);
private:
    QStandardItemModel* m_model;
    void updateText();
    bool is_shown;
    QSqlRecord& record;
    const QString fieldName;
    FlagsWidget* _parent;
private slots:
    void on_itemPressed(const QModelIndex &index);
};


#endif // FLAGSWIDGET_H
