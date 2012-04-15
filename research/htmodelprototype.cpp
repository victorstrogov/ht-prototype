#include "htmodelprototype.h"
#include <QDebug>
HtModelPrototype::HtModelPrototype(QObject *parent) :
    QAbstractItemModel(parent)
{
}



int HtModelPrototype::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return m_rootItem->childs().count();
    }
    else
    {
        return static_cast<HeaderItem *>
                (parent.internalPointer())->childs().count();
    }
}

int HtModelPrototype::columnCount(const QModelIndex & /*parent*/) const
{

    return 2;
}

QVariant HtModelPrototype::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    switch (role)
    {
        case Qt::DisplayRole:
        {
            HeaderItem * item=
                    static_cast<HeaderItem*> (index.internalPointer());
            switch(item->type())
            {
                case HeaderItem::HeaderType:
                    switch(index.column())
                    {
                        case 0:
                            return static_cast<Header*>(item)->text();
                        default:
                            return QVariant();
                    }
                case HeaderItem::SubHeaderType:
                {
                    switch(index.column())
                    {
                        case 0:
                            return static_cast<SubHeader*>(item)->number();
                        default:
                            return static_cast<SubHeader*>(item)->text();
                    }
                }
            }
         }

        case ItemTypeRole:

        default:
            return QVariant();
    }
}

QModelIndex HtModelPrototype::index(int row,
                                    int column,
                                    const QModelIndex &parent) const
{

   if (!hasIndex(row, column, parent))
   {
        return QModelIndex();
   }
    HeaderItem * parentItem;
    if(!parent.isValid())
    {
        parentItem=m_rootItem;
    }
    else
    {
        parentItem=static_cast<HeaderItem *>
                   (parent.internalPointer());

    }
    if(parentItem->childs().count()>row)
    {

        return createIndex(row,column,parentItem->childs().at(row));
    }
    else
    {
        return QModelIndex();
    }

}

QModelIndex HtModelPrototype::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    HeaderItem *childItem = static_cast<HeaderItem*>(child.internalPointer());
    HeaderItem *parentItem = childItem->parent();

    if (parentItem==0 ||
            parentItem == m_rootItem)
        return QModelIndex();

    HeaderItem * superParent=parentItem->parent();
    if(superParent)
    {
        return createIndex(superParent->childs().indexOf(parentItem),
                           0, parentItem);
    }
    return createIndex(0,
                       0, parentItem);
}

HeaderItem * HtModelPrototype::rootItem()
{
    return m_rootItem;
}

void HtModelPrototype::setRootItem(HeaderItem *rootItem)
{
    m_rootItem=rootItem;
}

Qt::ItemFlags HtModelPrototype::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QSize HtModelPrototype::span(const QModelIndex &index) const
{
    HeaderItem * item=static_cast<HeaderItem *> (index.internalPointer());
    switch(item->type())
    {
        case HeaderItem::HeaderType:
            return QSize(2,1);
        default: return QAbstractItemModel::span(index);
    }
}


