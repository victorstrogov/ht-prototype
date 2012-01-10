#ifndef HEADER_H
#define HEADER_H
#include <QtCore>
QT_FORWARD_DECLARE_CLASS(SubHeader)
class HeaderItem
{
  public:

   typedef QList<HeaderItem *> HeaderItems;
        enum Type
        {
            HeaderType,
            SubHeaderType,
            RootType

        };

     HeaderItem();
     virtual ~HeaderItem();
     virtual int type() const;
     HeaderItem * parent();
     HeaderItems & childs();
     const HeaderItems & childs() const;
   protected:
     void setParent(HeaderItem * parent);
   private:
     HeaderItem * m_parent;
     HeaderItems m_childs;

};


class Header: public HeaderItem
{
    public:

        Header(Header* parent=0);
        int type() const;
        const QString & text() const;
        void setText(const QString & text);
        Header* addHeader();
        SubHeader* addSubHeader();
    private:
        QString m_text;


};

class SubHeader: public Header
{
    public:
        SubHeader(Header* parent);
        int type() const;
        const QString & number() const;
        void setNumber( const QString & number);
    private:
        QString m_number;

};

#endif
