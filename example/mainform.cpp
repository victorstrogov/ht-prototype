#include "mainform.h"
#include "ui_mainform.h"
#include "exampletempateserrialization.h"
#include "mttemplatemodel.h"
#include "treetotableproxy.h"
#include "tableviewspancontroller.h"
MainForm::MainForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ExampleTempateSerrialization serrialization;
    MtTemplate * t = serrialization.loadTemplate();
    MtTemplateModel * model = new MtTemplateModel(this);
    TreeToTableProxy * proxy = new TreeToTableProxy(this);
    TableViewSpanController * spanController =
            new TableViewSpanController(this);
    proxy->setSourceModel(model);
    model->setHandledTemplate(t);
    ui->treeView->setModel(model);
    ui->tableView->setModel(proxy);
    spanController->setTableView(ui->tableView);
    spanController->updateSpan();
}

MainForm::~MainForm()
{
    delete ui;
}
