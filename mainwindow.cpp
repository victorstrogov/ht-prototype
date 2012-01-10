#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTableView>
#include <UngroupProxyModel.h>
#include<htflatmodelprototype.h>
#include <RowsJoinerProxy.h>
#include <simpletreetotableproxy.h>
#include <tableviewspancontroller.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model=new HtModelPrototype(this);
    m_rootItem=new Header();
    Header * h1=m_rootItem->addHeader();
    Header * h2=m_rootItem->addHeader();
    Header * h3=h2->addHeader();
    Header * h4=h3->addHeader();

    SubHeader * sh1=h1->addSubHeader();
    SubHeader * sh2=h2->addSubHeader();
    SubHeader * sh3=h2->addSubHeader();
    SubHeader * sh4=h3->addSubHeader();
    SubHeader * sh5=h1->addSubHeader();

    h1->setText("Header 1");
    h2->setText("Header 2");
    h3->setText("Header 3");
    h4->setText("H3ader 4");

    sh1->setText("Sub Header 1");
    sh1->setNumber("1");

    sh2->setText("Sub Header  2");
    sh2->setNumber("2");

    sh3->setText("Sub Header  3");
    sh3->setNumber("3");

    sh4->setText("Sub Header  4");
    sh4->setNumber("4");

    sh5->setText("Sub Header  5");
    sh5->setNumber("5");

    m_model->setRootItem(m_rootItem);
    ui->tvMain->setModel(m_model);

    qDebug()<<m_model->rowCount();
    QModelIndex i=m_model->index(1,0);
    qDebug()<<i.data();
   i=i.child(0,0);
    qDebug()<<i.data();
    HtFlatModelPrototype * flatModel=new HtFlatModelPrototype(this);
    SimpleTreeToTableProxy * sttProxy=new SimpleTreeToTableProxy(this);
    sttProxy->setSourceModel(m_model);
    flatModel->setRootItem(m_rootItem);
    QTableView * tv=new QTableView();
    TableViewSpanController * spanControl=new TableViewSpanController(this);
    tv->setModel(sttProxy);
    spanControl->setTableView(tv);
    tv->show();
    spanControl->updateSpan();






}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_rootItem;
}
