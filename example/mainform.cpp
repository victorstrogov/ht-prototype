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
    // Обьект серриализации
    ExampleTempateSerrialization serrialization;
    // загружаем шаблон
    MtTemplate * t = serrialization.loadTemplate();
    //создаем иеррархическую модель
    MtTemplateModel * model = new MtTemplateModel(this);
    // прокси модель для представления иеррархических данных в виде таблицы
    TreeToTableProxy * proxy = new TreeToTableProxy(this);
    // обьект управляющий корректной отрисовкой обьединенных ячеек
    TableViewSpanController * spanController =
            new TableViewSpanController(this);
    //задаем прокси модели иерархическую модель которая будет представленна в виде таблицы
    proxy->setSourceModel(model);
    //задаем иерархической модели шаблон для отображения
    model->setHandledTemplate(t);
    //отображаем иерархическую модель в иерархическом представлении
    ui->treeView->setModel(model);
    //отображаем табличную модель в табличном представлении
    ui->tableView->setModel(proxy);
    //задаем спан контроллеру представление которым он будет управлять
    spanController->setTableView(ui->tableView);
    //обновляем информацию об обьединенных ячейках
    spanController->updateSpan();
}

MainForm::~MainForm()
{
    delete ui;
}
