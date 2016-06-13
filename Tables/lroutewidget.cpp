#include "lroutewidget.h"
#include "ui_lroutewidget.h"
#include "lroutetableaction.h"
#include "pushbuttondelegate.h" // for PushButtonItemDelegate
#include <QModelIndex>
#include <QSignalMapper>

LRouteWidget::LRouteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LRouteWidget)
{
    ui->setupUi(this);
    lrta = new LRouteTableAction("LRoute Table", this);
    model = new LBeanTableDataModel(lrta);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegateForColumn(LBeanTableDataModel::EDITCOL, new PushButtonDelegate());
    ui->tableView->resizeColumnsToContents();

}

LRouteWidget::~LRouteWidget()
{
    delete ui;
}

void LRouteWidget::on_btnAdd_clicked()
{
 lrta->addPressed(NULL);
}
