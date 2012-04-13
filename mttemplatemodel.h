#ifndef MTTEMPLATEMODEL_H
#define MTTEMPLATEMODEL_H

#include <QAbstractItemModel>

class MtTemplateModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MtTemplateModel(QObject *parent = 0);
    
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row,
                      int column,
                      const QModelIndex &parent =
            QModelIndex()) const;
    QModelIndex  parent(const QModelIndex &child) const;
    QSize span(const QModelIndex & index) const;
public slots:
    
};

#endif // MTTEMPLATEMODEL_H
