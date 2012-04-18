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
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QModelIndex index(int row,
                      int column,
                      const QModelIndex &parent =
            QModelIndex()) const;
    QModelIndex  parent(const QModelIndex &child) const;
    QSize span(const QModelIndex & index) const;

    MtTemplate * handledTemplate();
    void setHandledTemplate(MtTemplate * pTemplate);

    MtTemplateItem *itemFromIndex(QModelIndex i) const;
    QModelIndex findItem(MtTemplateItem * item, QModelIndex parent = QModelIndex());
    void updateItem(MtTemplateItem * item);
    void updateItem(QModelIndex item);
    void update();


public slots:
private:

    MtTemplate * m_template;
};

#endif // MTTEMPLATEMODEL_H
