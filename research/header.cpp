#include "header.h"

HeaderItem::HeaderItem():m_parent(0)
{

}
HeaderItem::~HeaderItem()
{
    foreach(HeaderItem * i,childs())
    {
        delete i;
    }
    childs().clear();
}

int HeaderItem::type() const
{
    return RootType;
}

int Header::type() const
{
    return HeaderItem::HeaderType;
}

HeaderItem * HeaderItem::parent()
{
    return m_parent;
}

HeaderItem::HeaderItems & HeaderItem::childs()
{
    return m_childs;
}

const HeaderItem::HeaderItems & HeaderItem::childs() const
{
    return m_childs;
}

Header::Header(Header*parent):HeaderItem()
{
    setParent(parent);
}

const QString & Header::text() const
{
    return m_text;
}

void Header::setText(const QString &text)
{
    m_text=text;
}

SubHeader::SubHeader(Header*parent):Header(parent)
{

}

int SubHeader::type() const
{
    return HeaderItem::SubHeaderType;
}

const QString & SubHeader::number() const
{
    return m_number;
}

void SubHeader::setNumber(const QString &number)
{
    m_number=number;
}

Header * Header::addHeader()
{
    childs().push_back(new Header(this));
    return static_cast<Header*>(childs().back());
}

SubHeader * Header::addSubHeader()
{
    childs().push_back(new SubHeader(this));
    return static_cast<SubHeader*>(childs().back());
}

void HeaderItem::setParent(HeaderItem *parent)
{
    m_parent=parent;
}


