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

FlagsWidget::FlagsWidget(const QVector<EventAI::TypeValue> &values, QSqlRecord &r,
                         const QString &fieldName, QWidget *parent, bool verbose) :
    QWidget(parent),
    _verbose(verbose),
    verboseLayout(nullptr)
{
    setContentsMargins(0,0,0,0);
    QVBoxLayout* l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    setLayout(l);

    if(verbose){
        verboseLayout = new QVBoxLayout(this);
        l->addLayout(verboseLayout);
    }

    FlagsWidgetList* list = new FlagsWidgetList(values, r, fieldName, this);
    l->addWidget(list);
}

void FlagsWidget::SetLabels(const QStringList& lbls)
{
    if(_verbose){
        Q_ASSERT(verboseLayout);
        while(!verboseList.isEmpty()){
            QWidget* w = verboseList.takeLast();
            verboseLayout->removeWidget(w);
            w->deleteLater();
        }
        verboseList.clear();
        foreach(const QString& s, lbls){
            QLabel* lbl = new QLabel(s);
            verboseLayout->addWidget(lbl);
            verboseList.push_back(lbl);
        }
    }
}



FlagsWidgetList::FlagsWidgetList(const QVector<EventAI::TypeValue>& values, QSqlRecord& r,
                                 const QString& fn, FlagsWidget* parent) :
    QComboBox(parent),
    is_shown(false),
    record(r),
    fieldName(fn),
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
    int value = r.value(fieldName).toInt(&ok);
    Q_ASSERT(ok);

    foreach(const EventAI::TypeValue& v, values){
        if(v.name.isEmpty()) continue;
        QString nameTag = QString("(%1) %2").arg(v.value).arg(v.name);
        Qt::CheckState check = (v.value & value) ? Qt::Checked : Qt::Unchecked;
        addCheckItem(nameTag, v.value, v.description, check);
    }
    updateText();
}

QStandardItem* FlagsWidgetList::addCheckItem(const QString &label, const QVariant &data, const QString& tt, const Qt::CheckState checkState)
{
    QStandardItem* item = new QStandardItem(label);
    item->setCheckState(checkState);
    item->setData(data);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setToolTip(tt);
    m_model->appendRow(item);
    return item;
}

bool FlagsWidgetList::eventFilter(QObject *_object, QEvent *_event)
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

void FlagsWidgetList::updateText()
{
    QString text;
    int num = 0;
    QStringList parentList;
    for (int i = 0; i < m_model->rowCount(); i++)
    {
        if (m_model->item(i)->checkState() == Qt::Checked)
        {
            if (!text.isEmpty())
            {
                text+= ",";
            }
            int thisNum = m_model->item(i)->data().toInt();
            num |= thisNum;
            text+= QString::number(thisNum);
            parentList.push_back(m_model->item(i)->text());
        }
    }
    if(!text.isEmpty()){
        text.prepend("(");
        text += ")";
    }
    text.prepend(QString("%1 ").arg(num));
    lineEdit()->setText(text);
    lineEdit()->setCursorPosition(0);
    _parent->SetLabels(parentList);
}

void FlagsWidgetList::on_itemPressed(const QModelIndex &index)
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
