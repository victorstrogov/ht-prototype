#ifndef DATAMANIPULATION_H
#define DATAMANIPULATION_H
#include <QtCore>
//TODO: определить владельца алгоритма сравнения и метод загрузки алгоритмов
class MtTemplateItem;
class MtTemplate;
class QWidget;
class MtIndicatorItem;
class MtTemplateHolder;
class MtTemplateSerialization:public QObject
{
    Q_OBJECT
signals:
    void begin();
    void error(int code);
    void end();
    public:
    MtTemplateSerialization(QObject * parent=0);
        /*pure*/virtual MtTemplate *
    loadTemplate(const MtTemplateHolder *holder)=0;
        /*pure*/virtual const MtTemplateHolder *
    saveTemplate(MtTemplate * mtTemplate) =0;
};

class MtDataItem
{
     public:
        MtDataItem(MtTemplateItem * parent);
        typedef QList<MtIndicatorItem * > MtIndicatorItems;
        typedef QList<MtDataItem *> MtDataItems;
        virtual ~MtDataItem();

        const QVariantList & data() const;
        void setData(const QVariantList & data);
        virtual QVariant dataView() const;

        virtual bool isReadOnly() const ;
        virtual bool isIndicator() const;

        virtual QWidget * editor() =0;
        virtual void readFromWidget(QWidget * wigdet)=0;

        const MtIndicatorItems  & indicators() const;
        void setIndicators(const MtIndicatorItems & indicators);

        const MtTemplateItem * parent() const;
       protected:
        MtIndicatorItems  & indicators();
       private:
        MtIndicatorItems m_indicators;
        MtTemplateItem * m_parent;
};

class MtIndicatorItem:public MtDataItem
{
      public:
        MtIndicatorItem(MtTemplateItem * parent,MtDataItem * watch=0);
        const MtDataItems & watchers() const;
        void addWatcher(MtDataItem * watcher);
        void removeWatcher(MtDataItem * watcher);
        void update(MtDataItem * updateRequester);
        bool isIndicator() const;
        bool isReadOnly() const;

};

#endif // DATAMANIPULATION_H
