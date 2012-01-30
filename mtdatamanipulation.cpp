#include "mtdatamanipulation.h"
MtDataItem::MtDataItem(MtTemplateItem * parent):m_parent(parent)
{

}

 MtDataItem::~MtDataItem()
{

}

const QVariantList &MtDataItem::data() const
{
	
}

void MtDataItem::setData(const QVariantList &data)
{
}

QVariant MtDataItem::dataView() const
{
}

bool MtDataItem::isReadOnly() const
{
}

bool MtDataItem::isIndicator() const
{
}

const MtDataItem::MtIndicatorItems &MtDataItem::indicators() const
{
}

void MtDataItem::setIndicators(const MtDataItem::MtIndicatorItems &indicators)
{
}

const MtTemplateItem *MtDataItem::parent() const
{
}

MtIndicatorItem::MtIndicatorItem(MtTemplateItem *parent, MtDataItem *watch):MtDataItem(parent)
{
}

const MtDataItem::MtDataItems &MtIndicatorItem::watchers() const
{
}

void MtIndicatorItem::addWatcher(MtDataItem *watcher)
{
}

void MtIndicatorItem::removeWatcher(MtDataItem *watcher)
{
}

void MtIndicatorItem::update(MtDataItem *updateRequester)
{
}

bool MtIndicatorItem::isIndicator() const
{
}

bool MtIndicatorItem::isReadOnly() const
{
}

MtTemplateSerialization::MtTemplateSerialization(QObject *parent):QObject(parent)
{
}
