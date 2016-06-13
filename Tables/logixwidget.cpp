#include "logixwidget.h"
#include "ui_logixwidget.h"
#include "defaultlogix.h"
#include "instancemanager.h"
#include "logixtableaction.h"
#include <QMessageBox>
#include <QSignalMapper>
#include <QComboBox>

LogixWidget::LogixWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogixWidget)
{
 ui->setupUi(this);
 //ui->tableWidget->clearContents();
 log = new Logger("RouteWidget");
//    rows.clear();
//    mgr = (DefaultLogixManager*)InstanceManager::logixManagerInstance();
//    connect(mgr, SIGNAL(newLogixCreated(Logix*)), this, SLOT(on_newLogixCreated(Logix*)));
//    int row = ui->tableWidget->rowCount();
//    QStringList list = mgr->getSystemNameList();
//    ui->tableWidget->setRowCount(row + list.count());
//    ui->tableWidget->setColumnCount(5);
//    ui->tableWidget->setAlternatingRowColors(true);
//    ui->tableWidget->resizeColumnsToContents();
 act = new LogixTableAction("", (QObject*)this);
 bLoading = true;
 act->createModel();
 act->m->updateNameList();
 ui->tableView->setModel(act->m);
 act->m->configDeleteColumn(ui->tableView);
//    foreach (QString sysName, list)
//    {
//     DefaultLogix* x = (DefaultLogix*)mgr->getBySystemName(sysName);
//     rows.append(x);
//     updateRow(row, x);
//   //  PropertyChangeListener* listener;
//   //  b->addPropertyChangeListener(listener = new PropertyChangeListener());
//     connect(x, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     row++;
//    }
 bLoading = false;
//    ui->tableWidget->resizeColumnsToContents();
//    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(on_tableWidget_cellChanged(int,int)));
}

LogixWidget::~LogixWidget()
{
    delete ui;
}

LogixTableAction* LogixWidget::logixTableAction(){return act;}
#if 0
void LogixWidget::updateRow(int row, DefaultLogix* x)
{
  QTableWidgetItem* sn = new QTableWidgetItem(x->getSystemName());
  sn->setFlags(Qt::NoItemFlags);
  ui->tableWidget->setItem(row, 0, sn);
  QTableWidgetItem* un = new QTableWidgetItem(x->getUserName());
  un->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
  ui->tableWidget->setItem(row, 1, un);
  QTableWidgetItem* enabled = new QTableWidgetItem();
  enabled->setFlags(Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);
  enabled->setCheckState(x->getEnabled()?Qt::Checked:Qt::Unchecked);
  ui->tableWidget->setItem(row, 2,enabled);
  QTableWidgetItem* comment = new QTableWidgetItem(x->getComment());
  ui->tableWidget->setItem(row, 3, comment);
  QTableWidgetItem* action = new QTableWidgetItem(tr("Select"));
  QStringList items = QStringList() << tr("Select") << tr("Edit") << tr("Delete") << tr("Copy");
  ItemDelegate* itemDelegate = new ItemDelegate(items, this);
  ui->tableWidget->setItemDelegateForColumn(4,itemDelegate);
  ui->tableWidget->setItem(row, 4,action);
}
#endif
void LogixWidget::on_btnAdd_clicked()
{
 act->addPressed();
}

//void LogixWidget::propertyChange(PropertyChangeEvent *e)
//{
// DefaultLogix* xTarget = qobject_cast<DefaultLogix*>(e->source);
// for(int row =0; row<rows.count(); row++)
// {
//  DefaultLogix* x = rows.at(row);
//  if(x == xTarget)
//  {
//   updateRow(row, x);
//   break;
//  }
// }
//}
#if 0
void LogixWidget::on_newLogixCreated( Logix *o)
{
 DefaultLogix* x = (DefaultLogix*)o;
 int row = rows.count();
 ui->tableWidget->setRowCount(row + 1);
 updateRow(row, (DefaultLogix*)x);
 ui->tableWidget->setRowHidden(row,false);
 rows.append((DefaultLogix*)x);
}
void LogixWidget::on_tableWidget_cellChanged(int row, int col)
{
 if(rows.isEmpty()) return;
 if(row == rows.count()) return;
 if(bLoading) return;
 DefaultLogix* x = rows.at(row);
 switch(col)
 {
  case 1: // user name
   {
    //Directly changing the username should only be possible if the username was previously null or ""
    // check to see if user name already exists
    QString value = ui->tableWidget->item(row,col)->text();
    if ((value)==(""))
    {
     x->setUserName(value);
     return;
    }
    else
    {
     NamedBean* nB = (NamedBean*)mgr->getByUserName(value);
     if (nB != NULL)
     {
      log->error("User name is not unique " + value);
      QString msg;
      msg = tr("User Name \" %1 \" has already been used.").arg(value);
      QMessageBox::warning(this, tr("Warning"), msg);
      ui->tableWidget->item(row,col)->setText(x->getUserName()); // restore original value
      return;
     }
    }
    NamedBean* nBean = (NamedBean*)mgr->getBySystemName(ui->tableWidget->item(row,0)->text());
    nBean->setUserName( value);
    //fireTableRowsUpdated(row, row);
    break;
   }
  case 3:
   x->setComment(ui->tableWidget->item(row,col)->text());
   break;
  case 4:
     QString action = ui->tableWidget->item(row, col)->text();
     log->debug(tr("action %1 row %2").arg(action).arg(row));
     if(action == tr("Edit"))
     {
      logixTableAction()->editPressed(rows.at(row)->getSystemName());
     }
     else if (tr("Copy")==(action) )
     {
      logixTableAction()->copyPressed(rows.at(row)->getSystemName());
     } else if ( tr("Delete")==(action) ) {
      logixTableAction()->deletePressed(rows.at(row)->getSystemName());
     }
 }
}
#endif

ItemDelegate::ItemDelegate(QStringList items, QObject *parent)
: QAbstractItemDelegate(parent)
{
 Items = items;
}


QWidget* ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex & index ) const
{
  QComboBox* editor = new QComboBox(parent);
  editor->addItems(Items);
  return editor;
}

void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  int value = index.model()->data(index, Qt::EditRole).toUInt();
  comboBox->setCurrentIndex(value);
}

void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);

  model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void ItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}
void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItemV4 myOption = option;
  QString text = Items.at(index.row());

  myOption.text = text;

  QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
}
QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 return QSize (80, 100);
}
