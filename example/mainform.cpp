#include "mainform.h"
#include "ui_mainform.h"
#include "exampletempateserrialization.h"
#include "mttemplatemodel.h"
#include "treetotableproxy.h"
#include "tableviewspancontroller.h"
#include <QDebug>
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
    m_model = new MtTemplateModel(this);
    // прокси модель для представления иеррархических данных в виде таблицы
    m_proxy = new TreeToTableProxy(this);
    // обьект управляющий корректной отрисовкой обьединенных ячеек
    m_spanController =
            new TableViewSpanController(this);
    //задаем прокси модели иерархическую модель которая будет представленна в виде таблицы
    m_proxy->setSourceModel(m_model);
    //задаем иерархической модели шаблон для отображения
    m_model->setHandledTemplate(t);
    //отображаем иерархическую модель в иерархическом представлении
    ui->treeView->setModel(m_model);
    //отображаем табличную модель в табличном представлении
    ui->tableView->setModel(m_proxy);
    //задаем спан контроллеру представление которым он будет управлять
    m_spanController->setTableView(ui->tableView);
    //обновляем информацию об обьединенных ячейках
    m_spanController->updateSpan();

    connect(ui->tableView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_current_selection_changed(QModelIndex,QModelIndex)));
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_current_selection_changed(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    QModelIndex experimentIndex = m_proxy->mapToSource(current);
    MtTemplateItem * item = m_model->itemFromIndex(experimentIndex);
    QString itemType = "Unknown type";
    if(!item)return;
    switch(item->type())
    {
        case MtTemplateItem::Header:
        itemType = "Header";
        break;
        case MtTemplateItem::Subheader:
        itemType = "Sub Header";
        break;
        case MtTemplateItem::Footer:
        itemType = "Footer";
        break;
        case MtTemplateItem::Template:
        itemType = "Template";
        break;
    }
    ui->lbStatus->setText(itemType + " selected - " + item->itemData().at(0)->dataView().toString() );
}


void MainForm::on_pbAddHeader_clicked()
{
    QModelIndex current = ui->tableView->selectionModel()->currentIndex();
    MtTemplateItem * item = m_model->itemFromIndex(m_proxy->mapToSource(current));
    MtHeader * newHeader = 0;
    if(!item)return;
    switch(item->type())
    {
        case MtTemplateItem::Header:
        {
            MtHeader * header = item->toHeader();
            newHeader = header->addHeader();
            newHeader->itemData().at(0)->setData(QVariantList()<<"Inserted in Header");
            m_model->updateItem(header);


        }
        break;
        case MtTemplateItem::Subheader:
    {
        MtHeader * header = item->parent()->toHeader();
        newHeader = header->addHeader();
        newHeader->itemData().at(0)->setData(QVariantList()<<"Inserted for subheader Header");
        m_model->updateItem(header);
    }
        break;
        case MtTemplateItem::Footer:
    {
        MtTemplate * t = item->parent()->toTemplate();
        MtHeader * header = item->parent()->toHeader();
        if(header)
         newHeader= header->addHeader();
        else
          newHeader = t->addHeader();
        newHeader->itemData().at(0)->setData(QVariantList()<<"Inserted Header");
        m_model->updateItem(header);

    }
        break;
        case MtTemplateItem::Template:
        break;
    }
    m_model->update();
    m_proxy->update();
    m_spanController->updateSpan();
    if(newHeader)
    {
        ui->tableView->selectionModel()->
                select(m_proxy->mapFromSource(m_model->findItem(newHeader)),QItemSelectionModel::Select|QItemSelectionModel::Rows);

    }
}
