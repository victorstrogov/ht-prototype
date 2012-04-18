#include "treetotableproxy.h"
#include <QSize>
#include <QDebug>
TreeToTableProxy::TreeToTableProxy(QObject *parent) :
    QAbstractProxyModel(parent)
{
}

QModelIndex TreeToTableProxy::mapFromSource(const QModelIndex &sourceIndex) const
{

    return index(rowNumber(sourceIndex),sourceIndex.column());
}

QModelIndex TreeToTableProxy::mapToSource(const QModelIndex &proxyIndex) const
{

    QModelIndex rowIndex=indexFromRow(proxyIndex.row());

    return sourceModel()->index(rowIndex.row(),proxyIndex.column(),rowIndex.parent());
}

int TreeToTableProxy::rowNumber(QModelIndex index) const
{
    if(!index.isValid()) return 0;
    QModelIndex i =index.parent();
    QModelIndex iP = index;
    int row =0;
    for(int j = 0; j < iP.row(); j++)
    {
        int itemsCount = this->itemsCount(iP.model()->index(j,0,iP.parent()));
        row += itemsCount;
    }
    row += iP.row();

    if(i.isValid())
    {
        row++;
        row += rowNumber(i);
    }


    return row;
}



int TreeToTableProxy::itemsCount(QModelIndex index) const
{
    int hightCount=sourceModel()->rowCount(index);
    int  items =hightCount;
    for(int i=0;i<hightCount;i++)
    {
        items+=itemsCount(sourceModel()->index(i,0,index));
    }
    return items;
}

int TreeToTableProxy::columnCount(const QModelIndex &parent) const
{
    return sourceModel()->columnCount(parent);
}

int TreeToTableProxy::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())return 0;
    return itemsCount(parent);
}

QModelIndex TreeToTableProxy::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.isValid())return QModelIndex();
    return createIndex(row,column);
}

QModelIndex TreeToTableProxy::parent(const QModelIndex &/*child*/) const
{
    return QModelIndex();
}

QModelIndex TreeToTableProxy::indexFromRow(int row) const
{
    QModelIndex index;
    while(!index.isValid())
    {
        index=findRow(row,index);
    }
    return index;
}

QModelIndex TreeToTableProxy::findRow(int &row, QModelIndex searchIn) const
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

QSize TreeToTableProxy::span(const QModelIndex &index) const
{
    return sourceModel()->span(mapToSource(index));
}

Qt::ItemFlags TreeToTableProxy::flags(const QModelIndex &index) const
{
    return sourceModel()->flags(mapToSource(index));
}

void TreeToTableProxy::setSourceModel(QAbstractItemModel *sourceModel)
{
    QAbstractProxyModel::setSourceModel(sourceModel);

}

void TreeToTableProxy::update()
{
    reset();
}
