#ifndef MTTEMPLATEMODEL_H
#define MTTEMPLATEMODEL_H

#include <QAbstractItemModel>
class MtTemplate;
class MtTemplateItem;
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

    MtTemplate * handledTemplate();
    void setHandledTemplate(MtTemplate * pTemplate);
public slots:
private:
    MtTemplateItem *itemFromIndex(QModelIndex i) const;
    MtTemplate * m_template;
};

#endif // MTTEMPLATEMODEL_H
