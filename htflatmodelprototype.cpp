#include "htflatmodelprototype.h"

HtFlatModelPrototype::HtFlatModelPrototype(QObject *parent) :
    QAbstractItemModel(parent)
{
}

Qt::ItemFlags HtFlatModelPrototype::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void HtFlatModelPrototype::setRootItem(HeaderItem *rootItem)
{
    m_rootItem=rootItem;
}

HeaderItem * HtFlatModelPrototype::rootItem()
{
    return m_rootItem;
}

int HtFlatModelPrototype::rowCount(const QModelIndex &parent) const
{
    if(!m_rootItem)return 0;
    return itemsCount(m_rootItem);
}

int HtFlatModelPrototype::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant HtFlatModelPrototype::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    switch(role)
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
        default:
            return QVariant();
    }
}

QModelIndex HtFlatModelPrototype::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid())return QModelIndex();

    return createIndex(row,column,itemFromRow(row));

}

QModelIndex HtFlatModelPrototype::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int HtFlatModelPrototype::itemsCount(HeaderItem *item) const
{
    int count=item->childs().count();
    int childs=count;
    for(int i =0;i<childs;i++)
    {
        count+=itemsCount(item->childs()[i]);
    }
    return count;
}

HeaderItem * HtFlatModelPrototype::itemFromRow(int  row) const
{
    HeaderItem * item=0;
    while(!item)
    {
        item=findRow(row,m_rootItem);
    }
    return item;
}

HeaderItem * HtFlatModelPrototype::findRow(int &row, HeaderItem *searchIn) const
{
    HeaderItem * finded=0;
    for(int i=0;i<searchIn->childs().count();i++)
    {
        if(finded)break;
        HeaderItem * item=searchIn->childs()[i];
        row--;
        if(row<0 )
        {
            finded=item;
            break;
        }
        else
        {
            finded=findRow(row,item);
        }
    }
    return finded;
}
