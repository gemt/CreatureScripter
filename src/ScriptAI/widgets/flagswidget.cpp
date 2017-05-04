#include "flagswidget.h"


class QCheckListStyledItemDelegate : public QStyledItemDelegate
{
public:
    QCheckListStyledItemDelegate(QObject* parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
        QStyleOptionViewItem & refToNonConstOption = const_cast<QStyleOptionViewItem &>(option);
        refToNonConstOption.showDecorationSelected = false;
        QStyledItemDelegate::paint(painter, refToNonConstOption, index);
    }
};

FlagsWidget::FlagsWidget(const QVector<EventAI::TypeValue>& values, QSqlRecord& r, const QString& fn, QWidget* parent) :
    QComboBox(parent),
    is_shown(false),
    record(r),
    fieldName(fn)
{
    m_model = new QStandardItemModel(this);
    setModel(m_model);

    setEditable(true);
    lineEdit()->setReadOnly(true);
    lineEdit()->installEventFilter(this);
    setItemDelegate(new QCheckListStyledItemDelegate(this));

    connect(lineEdit(), &QLineEdit::selectionChanged, lineEdit(), &QLineEdit::deselect);
    connect((QListView*) view(), SIGNAL(pressed(QModelIndex)), this, SLOT(on_itemPressed(QModelIndex)));


    bool ok;
    int value = r.value(fieldName).toInt(&ok);
    Q_ASSERT(ok);

    foreach(const EventAI::TypeValue& v, values){
        if(v.name.isEmpty()) continue;
        QString nameTag = QString("(%1) %2").arg(v.value).arg(v.name);
        Qt::CheckState check = (v.value & value) ? Qt::Checked : Qt::Unchecked;
        addCheckItem(nameTag, v.value, v.description, check);
    }
}

QStandardItem* FlagsWidget::addCheckItem(const QString &label, const QVariant &data, const QString& tt, const Qt::CheckState checkState)
{
    QStandardItem* item = new QStandardItem(label);
    item->setCheckState(checkState);
    item->setData(data);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setToolTip(tt);
    m_model->appendRow(item);

    updateText();

    return item;
}

bool FlagsWidget::eventFilter(QObject *_object, QEvent *_event)
{
    if (_object == lineEdit() && _event->type() == QEvent::MouseButtonPress)
    {
        if(is_shown){
            hidePopup();
            is_shown = false;
        } else {
            showPopup();
            is_shown = true;
        }
        return true;
    }

    return false;
}

void FlagsWidget::updateText()
{
    QString text;
    for (int i = 0; i < m_model->rowCount(); i++)
    {
        if (m_model->item(i)->checkState() == Qt::Checked)
        {
            if (!text.isEmpty())
            {
                text+= ", ";
            }

            text+= QString::number(m_model->item(i)->data().toInt());
        }
    }
    lineEdit()->setText(text);
}

void FlagsWidget::on_itemPressed(const QModelIndex &index)
{
    QStandardItem* item = m_model->itemFromIndex(index);
    bool ok;
    int thisFlag = item->data().toInt(&ok);
    Q_ASSERT(ok);

    int curVal = record.value(fieldName).toInt(&ok);

    if (item->checkState() == Qt::Checked) {
        item->setCheckState(Qt::Unchecked);
        curVal & ~thisFlag;
    }
    else {
        item->setCheckState(Qt::Checked);
        curVal |= thisFlag;
    }


    record.setValue(fieldName, curVal);

    updateText();
}
