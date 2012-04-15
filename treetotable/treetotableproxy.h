#ifndef SIMPLETREETOTABLEPROXY_H
#define SIMPLETREETOTABLEPROXY_H

#include <QAbstractProxyModel>

class TreeToTableProxy : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit TreeToTableProxy(QObject *parent = 0);
    QModelIndex mapToSource( const QModelIndex & proxyIndex ) const;
    QModelIndex	mapFromSource( const QModelIndex & sourceIndex ) const;
    QModelIndex index(int row,
                      int column,
                      const QModelIndex &parent =
               QModelIndex()) const;
    QModelIndex  parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QSize span(const QModelIndex & index) const;
protected:
    QModelIndex indexFromRow(int row) const;
    QModelIndex findRow(int & row,QModelIndex searchIn) const;
    int rowNumber(QModelIndex index) const;
    int itemsCount(QModelIndex index) const;


};

#endif // SIMPLETREETOTABLEPROXY_H
