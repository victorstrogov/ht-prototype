#ifndef DATAMANIPULATION_H
#define DATAMANIPULATION_H
#include <QtCore>
//TODO: определить владельца алгоритма сравнения и метод загрузки алгоритмов
class MtTemplate;
class QWidget;
class MtIndicatorItem;
class MtTemplateSerialization
{
    public:
        /*pure*/virtual MtTemplate * loadTemplate()=0;
        /*pure*/virtual void saveTemplate(MtTemplate * mtTemplate) =0;
};

class MtDataItem
{
     public:
        typedef QList<MtIndicatorItem * > MtIndicatorItems;
        typedef QList<MtDataItem *> MtDataItems;
        virtual ~MtDataItem();
        const QVariantList & data() const;
        void setData(const QVariantList & data);


        virtual bool isReadOnly() const =0;
        virtual bool isIndicator() const=0;

        virtual QWidget * editor() =0;
        virtual void readFromWidget(QWidget * wigdet)=0;

        const MtIndicatorItems  & indicators() const;
        void setIndicators(const MtIndicatorItems & indicators);
       protected:
        MtIndicatorItems  & indicators();
       private:
};

class MtIndicatorItem:public MtDataItem
{
      public:
        MtIndicatorItem(MtDataItem * watch);
        const MtDataItems & watchers() const;
        void addWatcher(MtDataItem * watcher);
        void removeWatcher(MtDataItem * watcher);
        void update(MtDataItem * updateRequester);

};

#endif // DATAMANIPULATION_H
