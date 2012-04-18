#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDialog>
#include <QAbstractItemModel>
class TableViewSpanController;
class MtTemplateModel;
class MtTemplateItem;
class TreeToTableProxy;
namespace Ui {
class MainForm;
}

class MainForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
private slots:
void on_current_selection_changed( const QModelIndex & current, const QModelIndex & previous );
void on_pbAddHeader_clicked();

private:
    MtTemplateModel * m_model;
    TreeToTableProxy * m_proxy;
    TableViewSpanController * m_spanController;
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
