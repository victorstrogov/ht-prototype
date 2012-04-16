#include "mttemplatemodel.h"
#include "mttemplate.h"
#include "mtdatamanipulation.h"
#include <QDebug>
MtTemplateModel::MtTemplateModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

Qt::ItemFlags MtTemplateModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
    {
        Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        MtTemplateItem * item= itemFromIndex(index);
        if(item)
        {
            if(index.column() < item->itemData().size())
            {
                if(!item->itemData().at(index.column())->isReadOnly())
                {
                    flags |= Qt::ItemIsEditable;

                }

            }

        }
        return flags;
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
    return m_template->columnCount();
}

QVariant MtTemplateModel::data(const QModelIndex &index, int role) const
{
    const MtTemplateItem * item = itemFromIndex(index);
    switch (role) {
    case Qt::DisplayRole:
        if(index.column() < item->itemData().size())
        {

            QVariant data = item->itemData().
                    at(index.column())->dataView();
            return data;
        }
        break;
    default:
        return QVariant();
    }
    return QVariant();
}

bool MtTemplateModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role)
    {
        case Qt::EditRole:
        {
            MtTemplateItem * item = itemFromIndex(index);
            if(!item)return false;
            if(index.column()>= item->itemData().size())
            {
                return false;
            }
            MtDataItem * data = item->itemData().at(index.column());
            if(data->isReadOnly()) return false;
            QVariantList vlData = (value.type() == QVariant::List) ? value.toList() : QVariantList()<<value;
            data->setData(vlData);
        }
        break;
        default:
        return QAbstractItemModel::setData(index,value,role);

    }
    return true;
}

QModelIndex MtTemplateModel::
index(int row, int column, const QModelIndex &parent) const
{

    MtTemplateItem * item = itemFromIndex(parent);
    if(!item ) return QModelIndex();

    if(row >= item->childCount())
    {

        return QModelIndex();
    }
    QModelIndex i =createIndex(row,column,item->child(row));

    return i;

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
    if(!superParent)
    {
        superParent = m_template;
    }
    return createIndex(superParent->childs().
                       indexOf(parentItem),0,parentItem);

}

QSize MtTemplateModel::span(const QModelIndex &index) const
{
    MtTemplateItem * item = itemFromIndex(index);
    if(item->itemData().count()-1 == index.column() )
    {
        return QSize(columnCount() - index.column(), 1);
    }
    return QSize();
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
