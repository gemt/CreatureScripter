#ifndef FLAGSWIDGET_H
#define FLAGSWIDGET_H

#include <QComboBox>
#include <QSqlRecord>

#include "eventaidef.h"


#include <QWidget>
#include <QComboBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QEvent>
#include <QStyledItemDelegate>
#include <QListView>
#include <QVBoxLayout>

/**
 * @brief QComboBox with support of checkboxes
 * http://stackoverflow.com/questions/8422760/combobox-of-checkboxes
 */
class FlagsWidget : public QComboBox
{
    Q_OBJECT
public:
    FlagsWidget(const QVector<EventAI::TypeValue>& values, QSqlRecord& r, const QString& fieldName, QWidget* parent);
    QStandardItem* addCheckItem(const QString &label, const QVariant &data, const QString& tt, const Qt::CheckState checkState);
protected:
    bool eventFilter(QObject* _object, QEvent* _event);
private:
    QStandardItemModel* m_model;
    void updateText();
    bool is_shown;
    QSqlRecord& record;
    const QString& fieldName;

private slots:
    void on_itemPressed(const QModelIndex &index);
};

#endif // FLAGSWIDGET_H
