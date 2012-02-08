#include "mttemplate.h"

MtTemplate::MtTemplate()
{
}

MtFooterHolder::~MtFooterHolder()
{
}

MtTemplateHolder::MtTemplateHolder(QObject * parent):QObject(parent),m_code(-1),m_templateCode(-1)
{
}

const int MtTemplateHolder::code() const
{
    return m_code;
}

void MtTemplateHolder::setCode(int code)
{
    m_code=code;
}

const QString & MtTemplateHolder::name() const
{
    return m_name;
}

void MtTemplateHolder::setName(const QString &name)
{
    m_name=name;
}

const int MtTemplateHolder::templateCode() const
{
    return m_templateCode;
}

void MtTemplateHolder::setTemplateCode(int code)
{
    m_templateCode=code;
}

const QString & MtTemplateHolder::brief() const
{
    return m_brief;
}

void MtTemplateHolder::setBrief(const QString &brief)
{
    m_brief=brief;
}

MtTemplateItem::MtTemplateItem(MtTemplate * parentTemplate):m_parentTemplate(parentTemplate)
{
    setParent(0);
}

MtTemplateItem::~MtTemplateItem()
{
    foreach(MtTemplateItem * i,childs())
    {
        childs().removeAll(i);
        delete i;
    }
}

MtTemplateItem * MtTemplateItem::child(int at)
{
    return childs().at(at);
}

const MtTemplateItem * MtTemplateItem::child(int at) const
{
    return childs().at(at);
}

bool MtTemplateItem::removeChild(MtTemplateItem *child)
{
    return childs().removeAll(child);
}

bool MtTemplateItem::removeChild(int at)
{
    if(at>=childs().count()||at<0)return false;
    childs().removeAt(at);
    return false;
}

bool MtTemplateItem::swapChild(int from, int to)
{
    if(from>=childCount()||from<0||to>=childCount()||to<0||to==from)return false;
    childs().swap(from,too);
    return true;
}

bool MtTemplateItem::swapChild(MtTemplateItem* which,MtTemplateItem * with)
{
    int from=childs().indexOf(which);
    int to=childs().indexOf(with);
    return swapChild(from,to);
}

bool MtTemplateItem::swapChild(MtTemplateItem *which, int to)
{
    int from=childs().indexOf(which);
    return swapChild(from,to);

}

int MtTemplateItem::childCount() const
{
    return childs().count();
}

bool MtTemplateItem::hasChilds() const
{
    return childs().count()>0;
}

const MtTemplateItem * MtTemplateItem::parent() const
{
    return m_parent;
}

MtTemplateItem::MtTemplateItems & MtTemplateItem::childs()
{
    return m_childs;
}

const MtTemplateItem::MtTemplateItems & MtTemplateItem::childs() const
{
    return m_childs;
}

void MtTemplateItem::setParent(MtTemplateItem *parent)
{
    m_parent=parent;
}
MtTemplate * MtTemplateItem::toTemplate() const
{
    if(type()==Template)
        return static_cast<MtTemplate*>(this);
    else
        return 0;
}
MtHeader * MtTemplateItem::toHeader() const
{
    if(type()==Header)
        return static_cast<MtHeader*>(this);
    else
        return 0;
}
MtSubHeader * MtTemplateItem::toSubHeader() const
{
    if(type()==Subheader)
        return static_cast<MtSubHeader*>(this);
    else
        return 0;
}
MtFooter * MtTemplateItem::toFooter() const
{
    if(type()==Footer)
        return static_cast<MtFooter*>(this);
    else
        return 0;
}
MtFooterHolder::MtFooterHolder(MtTemplate * parentTemplate):MtTemplateItem(parentTemplate)
{

}

MtFooterHolder::~MtFooterHolder()
{
    foreach(MtFooters f,m_footers)
    {
        phyzicalHolder()->removeChild(f);
        delete f;
    }
}

MtFooterHolder::MtFooters & MtFooterHolder::footers()
{
    return m_footers;
}

const MtFooterHolder::MtFooters & MtFooterHolder::footers() const
{
    return m_footers;
}

MtFooter * MtFooterHolder::addFooter()
{
    MtFooter f = new MtFooter(this);
    footers().append(f);
    int index=phyzicalHolder()->childs().indexOf(this);
    if(index<0)
        phyzicalHolder()->childs().append(f);
    else
        phyzicalHolder()->childs().insert(index+1,f);
    return f;
}



MtTemplateItem * MtFooterHolder::phyzicalHolder()
{
    MtTemplateItem * physicalHolder=this->parent();
    if(!physicalHolder)physicalHolder=this;
    return physicalHolder;
}


MtTemplate::MtTemplate():MtFooterHolder(this)
{

}

int MtTemplate::columnCount() const
{
    return m_columns;
}

void MtTemplate::setColumnCount(int columnCount)
{
    m_columns=columnCount;
}

int MtTemplate::type() const
{
    return Template;
}

MtHeader * MtTemplate::addHeader()
{
    MtHeader * h=new Header(this);
    this->childs().append(h);
    return h;
}

MtHeader::MtHeader(MtTemplate *parent):MtFooterHolder(parent)
{
    this->setParent(parent);
}

MtHeader::MtHeader(MtHeader * parent):MtFooterHolder(parent->parentTemplate())
{
    setParent(parent);
}

int MtHeader::type() const
{
    return Header;
}

MtHeader * MtHeader::addHeader()
{
    MtHeader * h=new Header(this);
    this->childs().append(h);
    return h;
}

MtSubHeader * MtHeader::addSubHeader()
{
    MtSubHeader*h=new MtSubHeader(this);
    this->childs.append(h);
    return h;
}

MtSubHeader::MtSubHeader(MtHeader *parent)
{
    setParent(parent);
}

int MtSubHeader::type() const
{
    return Subheader;
}

MtFooter::MtFooter(MtTemplateItem *holder)
{
    setParent(holder);
}

int MtFooter::type() const
{
    return Footer;
}
