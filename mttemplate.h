#ifndef MTTEMPLATE_H
#define MTTEMPLATE_H
class MtTemplateItem;
class MtHeader;
class MtSubHeader;
class MtFooter;

class MtTemplateItem
{
    public:
        MtTemplateItem();
        virtual ~MtTemplateItem();
        typedef QList<MtTemplateItem *> MtTemplateItems;
        virtual int type() const;

};

class MtTemplate
{
public:
    enum Type
      {
        Header,
        SubHeader,
        Footer

      };
    MtTemplate();
    int code() const;
    void setCode(int code);



};

#endif // MTTEMPLATE_H
