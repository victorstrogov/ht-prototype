#ifndef HTFLATMODELPROTOTYPE_H
#define HTFLATMODELPROTOTYPE_H

#include <QAbstractItemModel>
#include <header.h>
class HtFlatModelPrototype : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit HtFlatModelPrototype(QObject *parent = 0);
    HeaderItem * rootItem();
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setRootItem(  HeaderItem * rootItem);
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row,
                      int column,
                      const QModelIndex &parent =
               QModelIndex()) const;
    QModelIndex  parent(const QModelIndex &child) const;
 private:
    int itemsCount(HeaderItem * item)const;
    HeaderItem * itemFromRow(int row) const;
    HeaderItem * findRow(int & row,HeaderItem * searchIn) const;
        HeaderItem * m_rootItem;

};

#endif // HTFLATMODELPROTOTYPE_H
