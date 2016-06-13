#include "transitwidget.h"
#include "ui_transitwidget.h"
#include "beantabledatamodel.h"
#include <QSortFilterProxyModel>

TransitWidget::TransitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransitWidget)
{
 ui->setupUi(this);
 model = new BeanTableDataModel();
 QSortFilterProxyModel* sorter = new QSortFilterProxyModel();
 sorter->setSourceModel(model);
 ui->verticalLayout->removeWidget(ui->tableView);
 ui->tableView->deleteLater();
 ui->tableView = model->makeJTable(sorter);
 ui->verticalLayout->addWidget(ui->tableView);
}

TransitWidget::~TransitWidget()
{
    delete ui;
}
