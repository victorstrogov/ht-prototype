#ifndef TABLEVIEWSPANCONTROLLER_H
#define TABLEVIEWSPANCONTROLLER_H

#include <QObject>
#include <QAbstractItemModel>
#include <QTableView>

class TableViewSpanController : public QObject
{
    Q_OBJECT
public:
    explicit TableViewSpanController(QObject *parent = 0);
    QTableView * tableView();
    void setTableView(QTableView * tableView);
public slots:
    void updateSpan();
private:
    QTableView *m_tableView;






};

#endif // TABLEVIEWSPANCONTROLLER_H
