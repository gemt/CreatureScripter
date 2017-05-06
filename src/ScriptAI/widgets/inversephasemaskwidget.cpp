#include "inversephasemaskwidget.h"

#include <QFontMetrics>

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

InversePhaseMaskWidget::InversePhaseMaskWidget(QSqlRecord &r, const QString &fieldName, QWidget *parent, bool verbose) :
     QWidget(parent),
     record(r),
     fieldName(fieldName)
{
    setToolTip(EventAI::short_phasemask_tooltip);
    setContentsMargins(0,0,0,0);
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    QVBoxLayout* l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    setLayout(l);

    PhaseWidgetList* list = new PhaseWidgetList(record, fieldName, this);
    l->addWidget(list);
}

void InversePhaseMaskWidget::UpdateVerboseLabel()
{
    //Q_ASSERT(0); // todo;
}

QSize InversePhaseMaskWidget::minimumSizeHint() const
{
    QFont f;
    QFontMetrics fm(f);
    int width = fm.width("Phase 31", f.pointSize()) *2;
    return QSize(width, size().height());
}


PhaseWidgetList::PhaseWidgetList(QSqlRecord &r, const QString &fieldName, InversePhaseMaskWidget *parent) :
    QComboBox(parent),
    is_shown(false),
    record(r),
    fieldName(fieldName),
    _parent(parent)
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
    quint32 value = r.value(fieldName).toUInt(&ok);
    Q_ASSERT(ok);

    for(int i = 0; i < 32; i++){
        QString nameTag = QString("Phase %1").arg(i+1);
        quint32 mask = (1<<i);
        bool activePhase = !(value & mask);
        Qt::CheckState check = activePhase ? Qt::Checked : Qt::Unchecked;
        addCheckItem(nameTag, mask, check);
    }
    updateText();
}

QStandardItem* PhaseWidgetList::addCheckItem(const QString &label, const QVariant &data, const Qt::CheckState checkState)
{
    QStandardItem* item = new QStandardItem(label);
    item->setCheckState(checkState);
    item->setData(data);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    m_model->appendRow(item);
    return item;
}

bool PhaseWidgetList::eventFilter(QObject *_object, QEvent *_event)
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

void PhaseWidgetList::updateText()
{
    QString text;
    bool ok;
    quint32 value = record.value(fieldName).toUInt(&ok);
    Q_ASSERT(ok);
    for (int i = 0; i < m_model->rowCount(); i++)
    {
        if (m_model->item(i)->checkState() == Qt::Checked)
        {
            if (!text.isEmpty())
            {
                text+= ",";
            }
            Q_ASSERT( !(m_model->item(i)->data().toUInt(&ok) & value));
            Q_ASSERT(ok);
            text+= QString::number(i);
        }
    }

    lineEdit()->setText(text);
    lineEdit()->setCursorPosition(0);
    _parent->UpdateVerboseLabel();
}

void PhaseWidgetList::on_itemPressed(const QModelIndex &index)
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
