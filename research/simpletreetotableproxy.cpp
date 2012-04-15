#include "simpletreetotableproxy.h"
#include <QSize>
SimpleTreeToTableProxy::SimpleTreeToTableProxy(QObject *parent) :
    QAbstractProxyModel(parent)
{
}

QModelIndex SimpleTreeToTableProxy::mapFromSource(const QModelIndex &sourceIndex) const
{
    return index(rowNumber(sourceIndex),sourceIndex.column());
}

QModelIndex SimpleTreeToTableProxy::mapToSource(const QModelIndex &proxyIndex) const
{

    QModelIndex rowIndex=indexFromRow(proxyIndex.row());

    return sourceModel()->index(rowIndex.row(),proxyIndex.column(),rowIndex.parent());
}

int SimpleTreeToTableProxy::rowNumber(QModelIndex index) const
{
    int row=index.row();
    QModelIndex i =index.parent();
    while(i.isValid())
    {
        row+=i.row();
        i=i.parent();
    }
    return row;
}



int SimpleTreeToTableProxy::itemsCount(QModelIndex index) const
{
    int hightCount=sourceModel()->rowCount(index);
    int  items =hightCount;
    for(int i=0;i<hightCount;i++)
    {
        items+=itemsCount(sourceModel()->index(i,0,index));
    }
    return items;
}

int SimpleTreeToTableProxy::columnCount(const QModelIndex &parent) const
{
    return sourceModel()->columnCount(parent);
}

int SimpleTreeToTableProxy::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())return 0;
    return itemsCount(parent);
}

QModelIndex SimpleTreeToTableProxy::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid())return QModelIndex();
    return createIndex(row,column);
}

QModelIndex SimpleTreeToTableProxy::parent(const QModelIndex &/*child*/) const
{
    return QModelIndex();
}

QModelIndex SimpleTreeToTableProxy::indexFromRow(int row) const
{
    QModelIndex index;
    while(!index.isValid())
    {
        index=findRow(row,index);
    }
    return index;
}

QModelIndex SimpleTreeToTableProxy::findRow(int &row, QModelIndex searchIn) const
{
    QAbstractItemModel * model=sourceModel();
    QModelIndex  finded;
    for(int i=0;i<model->rowCount(searchIn);i++)
    {
        if(finded.isValid())break;
        QModelIndex item=model->index(i,0,searchIn);
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

QSize SimpleTreeToTableProxy::span(const QModelIndex &index) const
{
    return sourceModel()->span(mapToSource(index));
}
