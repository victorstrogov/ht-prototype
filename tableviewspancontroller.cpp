#include "tableviewspancontroller.h"

TableViewSpanController::TableViewSpanController(QObject *parent) :
    QObject(parent)
{
}

void TableViewSpanController::updateSpan()
{
    tableView()->clearSpans();
    QAbstractItemModel * model=tableView()->model();
    for(int i=0;i<model->rowCount(tableView()->rootIndex());i++)
    {
        for(int j=0;j<model->columnCount(tableView()->rootIndex());j++)
        {
            QSize span=model->span(model->index(i,j,
                                                tableView()->rootIndex()));
            tableView()->setSpan(i,j,span.height(),span.width());
        }
    }
}



QTableView * TableViewSpanController::tableView()
{
    return m_tableView;
}

void TableViewSpanController::setTableView(QTableView *tableView)
{
    m_tableView=tableView;
}
