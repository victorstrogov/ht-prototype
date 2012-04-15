#include "mtdatamanipulation.h"
MtDataItem::MtDataItem(MtTemplateItem * parent):m_parent(parent)
{

}

 MtDataItem::~MtDataItem()
{

}

const QVariantList &MtDataItem::data() const
{
        return m_data;
}

void MtDataItem::setData(const QVariantList &data)
{
    m_data=data;
}

QVariant MtDataItem::dataView() const
{
    if(m_data.count()>0)return m_data[0];
    else return QVariant();
}

bool MtDataItem::isReadOnly() const
{
    return false;
}

bool MtDataItem::isIndicator() const
{
    return false;
}

const MtDataItem::MtIndicatorItems &MtDataItem::indicators() const
{
    return m_indicators;
}

void MtDataItem::setIndicators(const MtDataItem::MtIndicatorItems &indicators)
{
    m_indicators=indicators;
}

const MtTemplateItem *MtDataItem::parent() const
{
    return m_parent;
}

MtDataItem::MtIndicatorItems &MtDataItem::indicators()
{
    return m_indicators;
}


MtIndicatorItem::MtIndicatorItem(MtTemplateItem *parent, MtDataItem *watch):MtDataItem(parent)
{
    addWatcher(watch);
}

const MtDataItem::MtDataItems &MtIndicatorItem::watchers() const
{
    return  m_watchers;
}

void MtIndicatorItem::addWatcher(MtDataItem *watcher)
{

    m_watchers.append(watcher);
    watcher->indicators().append(this);
}

void MtIndicatorItem::removeWatcher(MtDataItem *watcher)
{
    m_watchers.removeAll(watcher);
    watcher->indicators().removeAll(this);
}

void MtIndicatorItem::update(MtDataItem *updateRequester)
{
    //TODO: make update
}

bool MtIndicatorItem::isIndicator() const
{
    return true;
}

bool MtIndicatorItem::isReadOnly() const
{
    return true;
}

MtTemplateSerialization::MtTemplateSerialization(QObject *parent):QObject(parent)
{
}

void MtDataItem::save()
{
}

void MtDataItem::load()
{
}


MtReadOnlyItem::MtReadOnlyItem(MtTemplateItem *parent)
    :MtDataItem(parent)
{
}

bool MtReadOnlyItem::isReadOnly() const
{
    return true;
}
