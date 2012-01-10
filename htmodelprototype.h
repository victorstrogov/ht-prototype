#ifndef HTMODELPROTOTYPE_H
#define HTMODELPROTOTYPE_H

#include <QAbstractItemModel>
#include <header.h>

class HtModelPrototype : public QAbstractItemModel
{
    Q_OBJECT
public:

    enum Roles
    {
        ItemTypeRole=Qt::UserRole+1
    };

    explicit HtModelPrototype(QObject *parent = 0);
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
    QSize span(const QModelIndex & index) const;

private:

    HeaderItem * m_rootItem;


};

#endif // HTMODELPROTOTYPE_H
