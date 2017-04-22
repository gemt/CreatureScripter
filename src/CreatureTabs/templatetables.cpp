#include "templatetables.h"
#include "cache.h"

#include <QVector>
#include <QLineEdit>
#include <QAbstractItemModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QTreeView>

class TemplateTreeItem
{
private:
    enum itemType{ROOT,TABLE,FIELD};
    itemType type;
    const char* _cData;
    TemplateTreeItem *_parentItem;
    QSqlField _itemData;
    QSqlField _originalData;
    QVector<TemplateTreeItem*> _childItems;
public:
    TemplateTreeItem() : type(ROOT),_parentItem(nullptr){}
    TemplateTreeItem(const char* n,TemplateTreeItem* p) : type(TABLE), _cData(n),_parentItem(p)
    {
        p->appendChild(this);
    }
    TemplateTreeItem(const QSqlField& f, TemplateTreeItem* p) :
        type(FIELD),
        _parentItem(p),
        _itemData(f),
        _originalData(f)
    {
        p->appendChild(this);
    }
    ~TemplateTreeItem(){
        qDeleteAll(_childItems);
        _childItems.clear();
    }
    void appendChild(TemplateTreeItem *item)
    {
        _childItems.append(item);
    }
    TemplateTreeItem *child(int row){
        return _childItems.at(row);
    }

    int childCount() const{ return _childItems.count(); }
    int columnCount() const {
        return _itemData.isNull() ? 0 : 2; // XXX not sure if should be 0 or 1
    }
    QVariant data(int column) const{
        switch(type){
        case ROOT: return QVariant(); break;
        case TABLE: return _cData; break;
        case FIELD: return column ? _itemData.value() : _itemData.name();
        }
    }
    int row() const {
        if (_parentItem)
               return _parentItem->_childItems.indexOf(const_cast<TemplateTreeItem*>(this));
           return 0;
    }
    TemplateTreeItem *parentItem() {return _parentItem; }
    bool SetData(QVariant data){
        Q_ASSERT(type==FIELD);
        _itemData.setValue(data);
        return true;
    }
};

class TemplateTableModel : public QAbstractItemModel
{
private:
    TemplateTreeItem* rootItm;
public:
    TemplateTableModel(QVector<std::pair<const char*,QSqlRecord>>& records, QWidget* parent) :
        QAbstractItemModel(parent),
        rootItm(new TemplateTreeItem)
    {
        for(auto r = records.begin(); r != records.end(); r++){
            TemplateTreeItem* itm = new TemplateTreeItem(r->first, rootItm);
            for(int col = 0; col < r->second.count(); col++){
                new TemplateTreeItem(r->second.field(col), itm);
            }
        }
    }
    ~TemplateTableModel() { rootItm; }

    QModelIndex index(int row, int column, const QModelIndex &parent) const override
    {
        if (!hasIndex(row, column, parent))
            return QModelIndex();

        TemplateTreeItem *parentItem;

        if (!parent.isValid())
            parentItem = rootItm;
        else
            parentItem = static_cast<TemplateTreeItem*>(parent.internalPointer());

        TemplateTreeItem *childItem = parentItem->child(row);
        if (childItem)
            return createIndex(row, column, childItem);
        else
            return QModelIndex();
    }
    QModelIndex parent(const QModelIndex &index) const
    {
        if (!index.isValid())
            return QModelIndex();

        TemplateTreeItem *childItem = static_cast<TemplateTreeItem*>(index.internalPointer());
        TemplateTreeItem *parentItem = childItem->parentItem();

        if (parentItem == rootItm)
            return QModelIndex();

        return createIndex(parentItem->row(), 0, parentItem);
    }
    int rowCount(const QModelIndex &parent) const
    {
        TemplateTreeItem *parentItem;
        if (parent.column() > 0)
            return 0;

        if (!parent.isValid())
            parentItem = rootItm;
        else
            parentItem = static_cast<TemplateTreeItem*>(parent.internalPointer());

        return parentItem->childCount();
    }
    int columnCount(const QModelIndex& parent) const override
    {
        if (parent.isValid())
            return static_cast<TemplateTreeItem*>(parent.internalPointer())->columnCount();
        else
            return rootItm->columnCount();
    }
    QVariant data(const QModelIndex &index, int role) const override
    {
        if (!index.isValid())
            return QVariant();

        if (role != Qt::DisplayRole)
            return QVariant();

        TemplateTreeItem *item = static_cast<TemplateTreeItem*>(index.internalPointer());

        return item->data(index.column());
    }
    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        if(index.column() == 1)
            return Qt::ItemIsEditable | Qt::ItemIsSelectable;
        else
            return Qt::NoItemFlags;
        /*
        //todo: currently readonly
        if (!index.isValid())
            return 0;

        return QAbstractItemModel::flags(index);
        */
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
            return rootItm->data(section);

        return QVariant();
    }
    bool setData(const QModelIndex &index, const QVariant &value, int /*role*/) override
    {
        return static_cast<TemplateTreeItem*>(index.internalPointer())->SetData(value);
    }
};

TemplateTables::TemplateTables(QWidget *parent) :
    QWidget(parent)
{
    QLineEdit* searchEdit = new QLineEdit(this);
    connect(searchEdit, &QLineEdit::textChanged, this, &TemplateTables::onTextChange);

    QVector<std::pair<const char*,QSqlRecord>> records;
    QTreeView* view = new QTreeView(this);
    TemplateTableModel* model = new TemplateTableModel(records, this);
    view->setModel(model);
}

void TemplateTables::onTextChange(const QString &s)
{

}
