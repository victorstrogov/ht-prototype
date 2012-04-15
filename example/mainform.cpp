#include "mainform.h"
#include "ui_mainform.h"
#include "exampletempateserrialization.h"
#include "mttemplatemodel.h"

MainForm::MainForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ExampleTempateSerrialization serrialization;
    MtTemplate * t = serrialization.loadTemplate();
    MtTemplateModel * model = new MtTemplateModel(this);
    model->setHandledTemplate(t);
    ui->treeView->setModel(model);
}

MainForm::~MainForm()
{
    delete ui;
}
