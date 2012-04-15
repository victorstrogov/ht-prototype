#ifndef MTTEMPLATE_H
#define MTTEMPLATE_H
#include <QtCore>
class MtTemplateItem;
class MtHeader;
class MtSubHeader;
class MtFooter;
class MtFooterHolder;
class MtTemplate;
class MtDataItem;

//TODO: replace hard coded creation with factory using
class MtTemplateFactory
{
public:
    virtual MtHeader* addHeader(MtTemplate* parentTemplate) =0;
    virtual MtHeader* addHeader(MtHeader* parentTemplate) =0;
    virtual MtSubHeader* addSubHeader(MtHeader * parent)=0;
    virtual MtFooter* addFooter(MtFooterHolder * parent)=0;
};

class MtTemplateHolder:public QObject
{
    Q_OBJECT
public:
    explicit MtTemplateHolder(QObject * parent);
    const int code() const;
    void setCode(int code);
    const QString & name() const;
    void setName(const QString & name);
    const QString & brief() const;
    void setBrief(const QString & brief);
    const int templateCode() const;
    void setTemplateCode(int code);
private:
    int m_code;
    QString  m_name;
    QString m_brief;
    int m_templateCode;

};

class MtTemplateItem
{
    public:
    enum Type
    {
        Header,
        Footer,
        Subheader,
        Template
    };
    typedef QList<MtDataItem * > ItemData;
        MtTemplateItem(MtTemplate * parentTemplate);
        virtual ~MtTemplateItem();

        virtual int type() const=0;

        MtTemplateItem * child(int at);
        const MtTemplateItem * child(int at) const;

        bool removeChild(MtTemplateItem * child);
        bool removeChild(int at);

        bool swapChild(int from, int too);
        bool swapChild(MtTemplateItem* which,MtTemplateItem * with);
        bool swapChild(MtTemplateItem *which, int to);

        int  childCount() const;
        bool hasChilds() const;

        MtTemplateItem *parent();
        MtTemplate * parentTemplate() ;

        MtTemplate * toTemplate();
        MtHeader * toHeader();
        MtSubHeader * toSubHeader();
        MtFooter * toFooter();
        typedef QList<MtTemplateItem *> MtTemplateItems;
        MtTemplateItems & childs();
        const MtTemplateItems & childs()const;
        ItemData & itemData();
        const ItemData & itemData() const;
    protected:
        void setParent(MtTemplateItem * parent);
    private:
        MtTemplateItems m_childs;
        MtTemplateItem * m_parent;
        MtTemplate * m_parentTemplate;
        ItemData  m_itemData;

};

class MtFooterHolder:public MtTemplateItem
{
    public:
        typedef QList<MtFooter*> MtFooters;
        MtFooterHolder(MtTemplate * parentTemplate);
        virtual ~MtFooterHolder();
        MtFooters & footers();
        const MtFooters & footers() const;
        MtFooter * addFooter();
    protected:
        void stableFooters();
        MtTemplateItem *phyzicalHolder();
    private:
        MtFooters m_footers;
};


class MtTemplate:public MtFooterHolder
{
public:

    MtTemplate(MtTemplateFactory * factory);
    int columnCount() const;
    void setColumnCount(int columnCount);

    int type() const;

    MtHeader * addHeader();
    MtTemplateFactory * factory();
private:
    MtTemplateFactory * m_factory;
    int m_columns;


};

class MtHeader:public MtFooterHolder
{
  public:
        MtHeader(MtTemplate* parent);
        MtHeader(MtHeader * parent);
        int type() const;

        MtHeader * addHeader();
        MtSubHeader * addSubHeader();
};

class MtSubHeader:public MtTemplateItem
{
public:
    MtSubHeader(MtHeader * parent);
    int type() const;
};
class MtFooter:public MtTemplateItem
{
   public:
        MtFooter(MtTemplateItem * holder);
        int type()const;
};

#endif // MTTEMPLATE_H
