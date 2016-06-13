#include "sectionwidget.h"
#include "ui_sectionwidget.h"
#include "sectiontableaction.h"
#include "../LayoutEditor/sectionmanager.h"
#include "logixtableaction.h"
#include "xtablecolumnmodel.h"

SectionWidget::SectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SectionWidget)
{
    ui->setupUi(this);
    act = new SectionTableAction(tr("Section Table"));
    act->createModel();
    ui->tableView->setModel(act->m);
    ui->tableView->setColumnModel(new XTableColumnModel());
    act->m->configureTable(ui->tableView); // setup deleteButton
    act->m->setColumnToHoldButton(ui->tableView, SectionTableDataModel::EDITCOL,new QPushButton);
    act->m->updateNameList();
    act->m->fireTableDataChanged();
    connect(act->m, SIGNAL(buttonClicked(int,QString)), this, SLOT(handleButton(int,QString)));
    connect(ui->btnAdd, SIGNAL(clicked()), act, SLOT(addPressed()));
}

SectionWidget::~SectionWidget()
{
    delete ui;
}
void SectionWidget::handleButton(int col, QString name)
{
    switch(col)
    {
     case SectionTableDataModel::DELETECOL:
      act->deleteSectionPressed(name);
      return;
    case SectionTableDataModel::EDITCOL:
        act->editPressed(name);
        return;
    }
}

