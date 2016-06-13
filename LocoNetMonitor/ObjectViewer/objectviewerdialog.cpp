#include "objectviewerdialog.h"
#include "ui_objectviewerdialog.h"

ObjectViewerDialog::ObjectViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectViewerDialog)
{
 ui->setupUi(this);
 model = new OVTableModel(this);
 ui->tableView->setModel(model);
 ui->tableView->resizeColumnsToContents();
 ui->tableView->horizontalHeader()->setStretchLastSection(true);
 ui->tableView->setSortingEnabled(true);
}
ObjectViewerDialog::~ObjectViewerDialog()
{
 delete ui;
}
void ObjectViewerDialog::setData(QList<ItemData>* list)
{
 model->setData(list);
}

