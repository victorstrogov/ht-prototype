#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDialog>
#include <QAbstractItemModel>
class MtTemplateModel;
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
private:
    MtTemplateModel * m_model;
    TreeToTableProxy * m_proxy;
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
