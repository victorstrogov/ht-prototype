#ifndef MTTEMPLATE_H
#define MTTEMPLATE_H
#include <QtCore>
class MtTemplateItem;
class MtHeader;
class MtSubHeader;
class MtFooter;
class MtTemplate;

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
        MtTemplateItem(MtTemplate * parentTemplate);
        virtual ~MtTemplateItem();

        virtual int type() const=0;

        MtTemplateItem * child(int at);
        const MtTemplateItem * child(int at) const;

        bool removeChild(MtTemplateItem * child);
        bool removeChild(int at);

        bool swapChild(int from,int to);
        bool swapChild(MtTemplateItem* which,MtTemplateItem * with);
        bool swapChild(MtTemplateItem *which, int to);

        int  childCount() const;
        bool hasChilds() const;

        const MtTemplateItem * parent() const;
        const MtTemplate * parentTemplate() const;

        MtTemplate * toTemplate() const;
        MtHeader * toHeader() const;
        MtSubHeader * toSubHeader() const;
        MtFooter * toFooter() const;
    protected:
        typedef QList<MtTemplateItem *> MtTemplateItems;
        MtTemplateItems & childs();
        const MtTemplateItems & childs()const;
        void setParent(MtTemplateItem * parent);
    private:
        MtTemplateItems m_childs;
        MtTemplateItem * m_parent;
        MtTemplate * m_parentTemplate;

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
        MtTemplateItem * phyzicalHolder();
    private:
        MtFooters m_footers;
};


class MtTemplate:public MtFooterHolder
{
public:

    MtTemplate();
    int columnCount() const;
    void setColumnCount(int columnCount);

    int type() const;

    MtHeader * addHeader();
private:
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
};
class MtFooter:public MtTemplateItem
{
   public:
        MtFooter(MtTemplateItem * holder);
        int type()const;
};

#endif // MTTEMPLATE_H
