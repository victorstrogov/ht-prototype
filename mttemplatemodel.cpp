#include "mttemplatemodel.h"
#include "mttemplate.h"
#include "mtdatamanipulation.h"
MtTemplateModel::MtTemplateModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

Qt::ItemFlags MtTemplateModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return 0;
}

int MtTemplateModel::rowCount(const QModelIndex &parent) const
{
    const MtTemplateItem * parentItem = itemFromIndex(parent);
    if(!parentItem) return 0;
    return parentItem->childCount();
}

int MtTemplateModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 5;
}

QVariant MtTemplateModel::data(const QModelIndex &index, int role) const
{
    const MtTemplateItem * item = itemFromIndex(index);
    switch (role) {
    case Qt::DisplayRole:
        if(index.column() < item->itemData().count())
        {
            return item->itemData().
                    at(index.column())->dataView();
        }
        break;
    default:
        return QVariant();
    }
    return QVariant();
}

QModelIndex MtTemplateModel::
index(int row, int column, const QModelIndex &parent) const
{
    MtTemplateItem * item = itemFromIndex(parent);
    if(!item ) return QModelIndex();

    if(row > item->childCount() ||
            column > item->child(row)->itemData().count())
    {
        return QModelIndex();
    }
    return createIndex(row,column,item->child(row));

}

QModelIndex MtTemplateModel::parent(const QModelIndex &child) const
{
    MtTemplateItem * childItem = itemFromIndex(child);
    if(!childItem)
    {
        return QModelIndex();
    }
    MtTemplateItem * parentItem = childItem->parent();
    if(!parentItem || parentItem == m_template)
    {
        return QModelIndex();
    }
    MtTemplateItem * superParent = parentItem->parent();
    if(superParent)
    {
        return createIndex(superParent->childs().
                           indexOf(parentItem),0,parentItem);
    }

    return createIndex(0,0,parentItem);
}

QSize MtTemplateModel::span(const QModelIndex &index) const
{
    return QAbstractItemModel::span(index);
}

MtTemplate *MtTemplateModel::handledTemplate()
{
    return m_template;
}


void MtTemplateModel::setHandledTemplate(MtTemplate *pTemplate)
{
    m_template = pTemplate;
    this->reset();
}

MtTemplateItem *MtTemplateModel::itemFromIndex(QModelIndex i) const
{

    if(!i.isValid() )
    {
        return m_template;
    }

    if( i.model() != this)
    {
        return 0;
    }
    return static_cast<MtTemplateItem*>(i.internalPointer());
}
