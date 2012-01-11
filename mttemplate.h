#ifndef MTTEMPLATE_H
#define MTTEMPLATE_H
#include <QtCore>
class MtTemplateItem;
class MtHeader;
class MtSubHeader;
class MtFooter;
class MtTemplate;


class MtTemplateItem
{
    public:
        MtTemplateItem();
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

class MtFooterHolder
{
    public:
        typedef QList<MtFooter*> MtFooters;
        virtual ~MtFooterHolder();
        MtFooters & footers();
        const MtFooters & footers() const;
        MtFooter * addFooter();
    private:
        MtFooters m_footers;
};


class MtTemplate:public MtFooterHolder
{
public:
    enum Type
      {
        Header,
        SubHeader,
        Footer,
        Template

      };
    MtTemplate();
    int code() const;
    void setCode(int code);

    int columnCount() const;
    void setColumnCount(int columnCount);

    int type() const;

    MtHeader * addHeader();



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

class MtFooter:public MtTemplateItem
{
   public:
        MtFooter(MtTemplateItem * holder);
        int type()const;
};

#endif // MTTEMPLATE_H
