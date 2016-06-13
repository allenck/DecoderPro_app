#include "signalgroupswidget.h"
#include "ui_signalgroupswidget.h"
#include "signalgrouptableaction.h"
#include "pushbuttondelegate.h" // for PushButtonItemDelegate
#include "jtextfield.h"

SignalGroupsWidget::SignalGroupsWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalGroupsWidget)
{
 ui->setupUi(this);
 sgta = new SignalGroupTableAction(this);
 buttonMap = QList<int>();
 sgta->createModel();
 ui->tableView->setModel(sgta->model());
 ui->tableView->setItemDelegateForColumn(SGBeanTableDataModel::SETCOL, new PushButtonDelegate());
 buttonMap.append(SGBeanTableDataModel::SETCOL);
 ui->tableView->resizeColumnsToContents();
 ui->tableView->setItemDelegateForColumn(SGBeanTableDataModel::DELETECOL, new PushButtonDelegate());
 buttonMap.append(SGBeanTableDataModel::DELETECOL);
 connect(ui->btnAdd, SIGNAL(clicked()), sgta, SLOT(addPressed()));
 sgta->model()->fireTableDataChanged();
}

SignalGroupsWidget::~SignalGroupsWidget()
{
 delete ui;
}
void SignalGroupsWidget::on_editMapper_triggered(int row)
{
 QString name = sgta->model()->data(sgta->model()->index(row, SGBeanTableDataModel::SYSNAMECOL),Qt::DisplayRole).toString();

 sgta->addPressed(NULL);
 sgta->_systemName->setText(name);
 sgta->editPressed(NULL);
}
void SignalGroupsWidget::on_deleteMapper_triggered(int row)
{
 QString name = sgta->model()->data(sgta->model()->index(row, SGBeanTableDataModel::SYSNAMECOL),Qt::DisplayRole).toString();
 sgta->deletePressed();
}
