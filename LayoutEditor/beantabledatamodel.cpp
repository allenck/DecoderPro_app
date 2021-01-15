#include "beantabledatamodel.h"
#include "manager.h"
#include "abstractmanager.h"
#include "exceptions.h"
#include "namedbean.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSizePolicy>
#include <QPushButton>
#include "instancemanager.h"
#include "jtextfield.h"
#include "jtable.h"
#include "systemnamecomparator.h"
#include "../Tables/logixtableaction.h"
#include <QLabel>
#include "../Tables/turnouttableaction.h"
#include <QHeaderView>
#include "hardcopywriter.h"
#include <QVector>
#include <QSortFilterProxyModel>
#include "xtablecolumnmodel.h"
#include "userpreferencesmanager.h"
#include <QMenu>
#include <QClipboard>
#include <QApplication>
#include "inputdialog.h"
#include <QComboBox>
//#include "pushbuttondelegate.h"
#include "tabledelegates.h"
#include "buttoncolumndelegate.h"
#include "jtablepersistencemanager.h"
#include <QSignalMapper>
#include "borderfactory.h"
#include "namedbeanpropertydescriptor.h"

//BeanTableDataModel::BeanTableDataModel(QObject *parent) :
//    QAbstractTableModel(parent)
//{
//}
/**
 * Table data model for display of NamedBean manager contents
 * @author		Bob Jacobsen   Copyright (C) 2003
 * @author      Dennis Miller   Copyright (C) 2006
 * @version		$Revision: 21081 $
 */
//abstract /*public*/ class BeanTableDataModel extends javax.swing.table.AbstractTableModel
//            implements PropertyChangeListener {

///*static*/ /*public*/ /*final*/ int BeanTableDataModel::NUMCOLUMN = 5;

//template<class T>
/*public*/ BeanTableDataModel::BeanTableDataModel(QObject *parent) :   AbstractTableModel(parent)
{
 //super();
 setObjectName("BeanTableDataModel");
 sysNameList = QStringList();
 noWarnDelete = false;
 nbMan = (NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager");
 // propertyColumns = new ArrayList<>(getManager().getKnownBeanProperties());
 propertyColumns = new QList<NamedBeanPropertyDescriptor*>();
  // init() can ony be run after sub-classes' constructors are complete!
}
//template<class T>
void /*public*/ BeanTableDataModel::init() // SLOT
{
 AbstractManager* manager = (AbstractManager*)getManager();
 if(manager != NULL)
 {
  manager->addPropertyChangeListener((PropertyChangeListener*)this);
  updateNameList();
  connect(manager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //connect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
BeanTableDataModel::~BeanTableDataModel()
{
}

/*protected*/ int BeanTableDataModel::getPropertyColumnCount() const{
    return propertyColumns->size();
}

/*protected*/ NamedBeanPropertyDescriptor/*<?>*/* BeanTableDataModel::getPropertyColumnDescriptor(int column) {
        int totalCount = getColumnCount();
        int propertyCount = propertyColumns->size();
        int tgt = column - (totalCount - propertyCount);
        if (tgt < 0) {
            return nullptr;
        }
        return propertyColumns->value(tgt);
    }
//template<class T>
Manager* BeanTableDataModel::getManager() {return NULL;}

//template<class T>
void BeanTableDataModel::setManager(Manager *) {}

/*protected*/ /*synchronized*/ void BeanTableDataModel::updateNameList()
{
 AbstractManager* mgr = (AbstractManager*)getManager();

 // first, remove listeners from the individual objects
 if (!sysNameList.isEmpty())
 {
  for (int i = 0; i< sysNameList.size(); i++)
  {
   // if object has been deleted, it's not here; ignore it
   NamedBean* b = getBySystemName(sysNameList.at(i));
   AbstractNamedBean* anb = (AbstractNamedBean*)b;

   if (b!=NULL)
   {
    b->removePropertyChangeListener((PropertyChangeListener*)this);
//    disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
  }
 }
 sysNameList = mgr->getSystemNameList();
 qSort(sysNameList.begin(), sysNameList.end(), SystemNameComparator::compare);
 // and add them back in
 for (int i = 0; i< sysNameList.size(); i++)
 {
  // if object has been deleted, it's not here; ignore it
  NamedBean* b = getBySystemName(sysNameList.at(i));
  if (b != nullptr) {
      b->addPropertyChangeListener((PropertyChangeListener*)this);
  }
 }
}

/*public*/ void BeanTableDataModel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("length"))
 {
  // a new NamedBean is available in the manager
  updateNameList();
  log->debug("Table changed length to "+QString::number(sysNameList.size()));
  fireTableDataChanged();
 }
 else if (matchPropertyName(e))
 {
  // a value changed.  Find it, to avoid complete redraw
  //if(e.getSource() instanceof NamedBean)
  if(dynamic_cast<NamedBean*>(e->getSource())!= NULL)
  {
   QString name = ((NamedBean*)e->getSource())->getSystemName();
   if (log->isDebugEnabled()) log->debug("Update cell "+QString::number(sysNameList.indexOf(name))+"," +QString::number(VALUECOL)+" for "+name);
   // since we can add columns, the entire row is marked as updated
   int row = sysNameList.indexOf(name);
   try
   {
    fireTableRowsUpdated(row, row);
    fireTableDataChanged();
   }
   catch (Exception ex)
   {
    log->error(ex.getMessage());
   }
  }
 }
}

/**
 * Is this property event announcing a change this table should display?
 * <P>
 * Note that events will come both from the NamedBeans and also from the manager
 */
/*protected*/ bool BeanTableDataModel::matchPropertyName(PropertyChangeEvent* e)
{
 return (e->getPropertyName().indexOf("State")>=0
         || e->getPropertyName().indexOf("Appearance")>=0
         || e->getPropertyName().indexOf("Comment")>=0)
         || e->getPropertyName().indexOf("UserName")>=0;
}

/*public*/ int BeanTableDataModel::rowCount(const QModelIndex &/*parent*/) const
{
 return sysNameList.size();
}

/*public*/ int BeanTableDataModel::columnCount(const QModelIndex &/*parent*/) const
{ return NUMCOLUMN;}

/*public*/ QVariant BeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role  == Qt::DisplayRole)
 {
    switch (section)
    {
    case SYSNAMECOL: return tr("System Name"); //"System Name";
    case USERNAMECOL: return tr("User Name"); //"User Name";
    case VALUECOL: return tr("State"); //"State";
    case COMMENTCOL: return tr("Comment"); //"Comment";
    case DELETECOL: return "";

    default: break;
    }
 }
 return QVariant();
}

 /*public*/ QString BeanTableDataModel::getColumnClass(int col) const {
    switch (col) {
    case SYSNAMECOL:
    case USERNAMECOL:
    case COMMENTCOL:
        return "String";
    case VALUECOL:
    case DELETECOL:
        return "JButton";
    default:
        return QString();
    }
}

/*public*/ Qt::ItemFlags BeanTableDataModel::flags(const QModelIndex &index) const
{
 switch (index.column())
 {
  case VALUECOL:
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
  case COMMENTCOL:
  case DELETECOL:
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  case USERNAMECOL:
  {
   NamedBean* b = getBySystemName(sysNameList.at(index.row()));
   if(b != NULL &&((b->getUserName()=="") || b->getUserName()==("")))
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    //$FALL-THROUGH$
  }
 case SYSNAMECOL:
  default:
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }
 return Qt::NoItemFlags;
}

/*public*/ QVariant BeanTableDataModel::data(const QModelIndex &index, int role) const
{
 if(!index.isValid())
   return QVariant();
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  NamedBean* b = NULL;
  switch (index.column())
  {
    case SYSNAMECOL:  // slot number
        return sysNameList.at(index.row());
    case USERNAMECOL:  // return user name
        // sometimes, the TableSorter invokes this on rows that no longer exist, so we check
        b = getBySystemName(sysNameList.at(index.row()));
        return (b!=NULL) ? b->getUserName() : NULL;
    case VALUECOL:  //
        return getValue(sysNameList.at(index.row()));
    case COMMENTCOL:
        b = getBySystemName(sysNameList.at(index.row()));
        return (b!=NULL) ? b->getComment() : NULL;
    case DELETECOL:  //
        return ("Delete");
    default:
//        log->error("internal state inconsistent with table request for "+QString::number(index.row())+" "+QString::number(index.column()));
        break;
  }
 }
  return QVariant();
}

/*public*/ int BeanTableDataModel::getPreferredWidth(int col) {
    switch (col) {
    case SYSNAMECOL:
        return  JTextField(5).getPreferredSize().width();
    case COMMENTCOL:
    case USERNAMECOL:
        return  JTextField(15).getPreferredSize().width();
    case VALUECOL: // not actually used due to the configureTable, setColumnToHoldButton, configureButton
    case DELETECOL: // not actually used due to the configureTable, setColumnToHoldButton, configureButton
        return  JTextField(22).getPreferredSize().width();
    default:
        log->warn("Unexpected column in getPreferredWidth: "+QString::number(col));
        return  JTextField(8).getPreferredSize().width();
    }
}

/*abstract*/ /*public*/ QString BeanTableDataModel::getValue(QString /*systemName*/) const {return "";}

//abstract protected Manager getManager();
//protected void setManager(Manager man){ }

/*abstract*/ /*protected*/ NamedBean* BeanTableDataModel::getBySystemName(QString /*name*/) const
{
 return NULL;
}

/*abstract*/ /*protected*/ NamedBean* BeanTableDataModel::getByUserName(QString /*name*/){return NULL;}
//abstract protected void clickOn(NamedBean t);

/*public*/ int BeanTableDataModel::getDisplayDeleteMsg()
{
 return ((UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager"))->getMultipleChoiceOption(getMasterClassName(),"deleteInUse");
}

/*public*/ void BeanTableDataModel::setDisplayDeleteMsg(int boo)
{
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMultipleChoiceOption(getMasterClassName(), "deleteInUse", boo);
}

/*abstract*/ /*protected*/ QString BeanTableDataModel::getMasterClassName() {return "";}

/*public*/ bool BeanTableDataModel:: setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(!index.isValid()) return false;
 int col = index.column();
 int row = index.row();
 if(role == Qt::EditRole)
 {
  if (col==USERNAMECOL)
  {
   //Directly changing the username should only be possible if the username was previously NULL or ""
   // check to see if user name already exists
//   if (((String)value)==("")) value = NULL;
//   else {
   NamedBean* nB = getByUserName(value.toString());
   if (nB != NULL)
   {
    log->error("User name is not unique " + value.toString());
//    QString msg;
//        msg = java.text.MessageFormat.format(AbstractTableAction.rb
//                .getString("WarningUserName"),
//                new Object[] { ("" + value) });
//        JOptionPane.showMessageDialog(NULL, msg,
//                AbstractTableAction.rb.getString("WarningTitle"),
//                JOptionPane.ERROR_MESSAGE);
    QMessageBox::warning(0, tr("Warning"), tr("User Name \" %1 \" has already been used.").arg(value.toString()));
     return false;
    }
    NamedBean* nBean = getBySystemName(sysNameList.at(row));
    nBean->setUserName( value.toString());
    if(nbMan->inUse(sysNameList.at(row), nBean))
    {
//    String msg = java.text.MessageFormat.format(AbstractTableAction.rb
//        .getString("UpdateToUserName"),
//        new Object[] { getBeanType(),value,sysNameList.get(row) });
//    int optionPane = JOptionPane.showConfirmDialog(NULL,
//        msg, AbstractTableAction.rb.getString("UpdateToUserNameTitle"),
//        JOptionPane.YES_NO_OPTION);
//    if(optionPane == JOptionPane.YES_OPTION){
    switch(QMessageBox::question(NULL, tr("Update usage to UserName"), tr("\"Do you want to update references to this %1\nto use the UserName \"%2\" rather than its SystemName \"%3}?").arg(getBeanType()).arg(value.toString()).arg(sysNameList.at(row) ),QMessageBox::Yes | QMessageBox::No))
    {
    case QMessageBox::Yes:
     //This will update the bean reference from the systemName to the userName
     try
     {
      nbMan->updateBeanFromSystemToUser(nBean);
     } catch (JmriException ex) {
            //We should never get an exception here as we already check that the username is not valid
     }
     break;
    default:
     break;
    }
   }

   fireTableRowsUpdated(row, row);
  }
  else if (col==COMMENTCOL)
  {
   getBySystemName(sysNameList.at(row))->setComment(value.toString());
   fireTableRowsUpdated(row, row);
  }
  else if (col==VALUECOL)
  {
   // button fired, swap state
   NamedBean* t = getBySystemName(sysNameList.at(row));
   clickOn(t);
   fireTableRowsUpdated(row, row);
  }
  else if (col==DELETECOL)
  {
   // button fired, delete Bean
   //beginRemoveRows(QModelIndex(), row, row);
   deleteBean(row, col);
   //endRemoveRows();
  }
  else
  {
   NamedBeanPropertyDescriptor/*<?>*/* desc = getPropertyColumnDescriptor(col);
   if (desc == nullptr) {
       return true;
   }
//   if (value instanceof JComboBox) {
//       value = ((JComboBox<?>) value).getSelectedItem();
//   }
   NamedBean* b = getBySystemName(sysNameList.at(row));
   b->setProperty(desc->propertyKey, value);
  }
  return true;
 }
 return false;
}

void BeanTableDataModel::On_deleteBean_triggered()
{
 deleteBean(row, 0);
}

/*protected*/ void BeanTableDataModel::deleteBean(int row, int /*col*/)
{
 /*final*/ t = getBySystemName(sysNameList.at(row));
 int count = ((AbstractNamedBean*)t)->getNumPropertyChangeListeners()-1; // one is this table
 if (log->isDebugEnabled()) log->debug("Delete with "+QString::number(count));
 if (getDisplayDeleteMsg()==QMessageBox::Yes)
 {
  this->row = row;
  doDelete(t);
 }
 else
 {
  /*final*/ dialog = new QDialog();
  QString msg;
  QString msg1;
  dialog->setWindowTitle(tr("Warning"));
  //dialog.setLocationRelativeTo(NULL);
  //dialog.setDefaultCloseOperation(javax.swing.JFrame.DISPOSE_ON_CLOSE);
  JPanel* container = new JPanel();
  container->setBorder(BorderFactory::createEmptyBorder(10,10,10,10));
  container->setLayout(new QVBoxLayout(container/*, BoxLayout.Y_AXIS*/));
  if (count>0)
  { // warn of listeners attached before delete
   msg = tr("Are you sure you want to delete %1?").arg(t->getSystemName());

   QLabel* question = new QLabel(msg);
   //question.setAlignmentX(Component.CENTER_ALIGNMENT);
   container->layout()->addWidget(question);

   msg1 = tr("It is in use by %1 other objects.").arg(count);

   question = new QLabel(msg1);
   //question.setAlignmentX(Component.CENTER_ALIGNMENT);
   container->layout()->addWidget(question);

   QList<QString>* listenerRefs = t->getListenerRefs();
   if(listenerRefs->size()>0)
   {
    question = new QLabel("    ");
    container->layout()->addWidget(question);
    QStringList listeners = QStringList();
    for (int i = 0; i<listenerRefs->size(); i++)
    {
     if(!listeners.contains(listenerRefs->at(i)))
      listeners.append(listenerRefs->at(i));
    }

    for (int i = 0; i<listeners.size(); i++)
    {
     question = new QLabel(listeners.at(i));
     //question.setAlignmentX(Component.CENTER_ALIGNMENT);
     container->layout()->addWidget(question);
    }
   }
  }
  else
  {
   msg = tr("Are you sure you want to delete %1?").arg(t->getSystemName());
   QLabel* question = new QLabel(msg);
   //question.setAlignmentX(Component.CENTER_ALIGNMENT);
   container->layout()->addWidget(question);
  }

  /*final*/  remember = new QCheckBox(tr("Remember this setting for next time?"));
  //remember->setFont(remember.getFont().deriveFont(10f));
  //remember.setAlignmentX(Component.CENTER_ALIGNMENT);

  QPushButton* yesButton = new QPushButton(tr("Yes"));
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(yesButton->sizePolicy().hasHeightForWidth());
  yesButton->setSizePolicy(sizePolicy);

  QPushButton* noButton = new QPushButton("No");
  noButton->setSizePolicy(sizePolicy);
  QWidget* button = new QWidget();
  //button.setAlignmentX(Component.CENTER_ALIGNMENT);
  button->setLayout(new QHBoxLayout());
  button->layout()->addWidget(yesButton);
  button->layout()->addWidget(noButton);
  container->layout()->addWidget(button);

//  noButton.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            //there is no point in remembering this the user will never be
//            //able to delete a bean!
//            /*if(remember.isSelected()){
//                setDisplayDeleteMsg(0x01);
//            }*/
//            dialog.dispose();
//        }
//    });
  connect(noButton, SIGNAL(clicked()), this, SLOT(on_noButton_clicked()));
//    yesButton.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if(remember.isSelected()) {
//               setDisplayDeleteMsg(0x02);
//            }
//            doDelete(t);
//            dialog.dispose();
//        }
//    });
  connect(yesButton, SIGNAL(clicked()), this, SLOT(on_yesButton_clicked()));
  container->layout()->addWidget(remember);
  //container.setAlignmentX(Component.CENTER_ALIGNMENT);
  //container.setAlignmentY(Component.CENTER_ALIGNMENT);
  dialog->setLayout(new QVBoxLayout());
  dialog->layout()->addWidget(container);
  //dialog.pack();
  /*dialog.setModal(true);
  dialog.setVisible(true)*/;
  dialog->exec();
 }
}

void BeanTableDataModel::on_noButton_clicked()
{
 dialog->reject();
 dialog->close();
}
void BeanTableDataModel::on_yesButton_clicked()
{
 dialog->accept();
 if(remember->isChecked())
 {
  setDisplayDeleteMsg(0x02);
 }
 row = sysNameList.indexOf(t->getSystemName());

 //beginRemoveRows(parent, row, row);
 doDelete(t);
 //endRemoveRows();
 dialog->close();
 fireTableDataChanged();
}


/**
 * Delete the bean after all the checking has been done.
 * <P>
 * Separate so that it can be easily subclassed if other functionality is needed.
 */
void BeanTableDataModel::doDelete(NamedBean*  bean)
{
 getManager()->deregister(bean);
 bean->dispose();
}

/**
 * Configure a table to have our standard rows and columns.
 * This is optional, in that other table formats can use this table model.
 * But we put it here to help keep it consistent.
 * @param table
 */
/*public*/ void BeanTableDataModel::configureTable(JTable* table)
{
 this->_table = table;
 // allow reordering of the columns
//    table.getTableHeader().setReorderingAllowed(true);

//    // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
//    table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

 // resize columns as requested
 for (int i=0; i<table->horizontalHeader()->count(); i++)
 {
  int width = getPreferredWidth(i);
  //table.getColumnModel().getColumn(i).setPreferredWidth(width);
  table->setColumnWidth(i,width);
 }
 //table.sizeColumnsToFit(-1);
 //table->resizeColumnsToContents();
 table->resizeRowsToContents();
 //table->setRowHeight(0, QPushButton().sizeHint().height());

 configValueColumn(table);
 configDeleteColumn(table);

//    MouseListener popupListener = new PopupListener();
//    table.addMouseListener(popupListener);

 this->persistTable(table);

// loadTableColumnDetails(table);

 table->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(table, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showPopup(QPoint)));
 table->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(table->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this,SLOT(showTableHeaderPopup(const QPoint &)));
 //setPersistentButtons();
 //table->resizeColumnsToContents();

}

/*protected*/ void BeanTableDataModel::configValueColumn(JTable* table) {
    // have the value column hold a button
 setColumnToHoldButton(table, VALUECOL, configureButton());
 connect(table, SIGNAL(clicked(QModelIndex)),this, SLOT(On_itemClicked(QModelIndex)));
}

void BeanTableDataModel::On_itemClicked(QModelIndex index)
{
 if(index.column() == VALUECOL)
 {
  if(index.row() > sysNameList.count()) return;
  NamedBean* t = getBySystemName(sysNameList.at(index.row()));
  clickOn(t);
 }
}

/*public*/ QPushButton* BeanTableDataModel::configureButton()
{
 // pick a large size
 QPushButton* b = new QPushButton(tr("Inconsistent"));
//    b.putClientProperty("JComponent.sizeVariant","small");
//    b.putClientProperty("JButton.buttonType","square");
 return b;
}

/*protected*/ void BeanTableDataModel::configDeleteColumn(JTable* table)
{
 // have the delete column hold a button
 setColumnToHoldButton(table, DELETECOL/*, new QPushButton(tr("Delete"))*/);
}

/**
 * Service method to setup a column so that it will hold a
 * button for it's values
 * @param table
 * @param column
 * @param sample Typical button, used for size
 */
/*protected*/ void BeanTableDataModel::setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/)
{ //
 // install a button renderer & editor
//    ButtonRenderer buttonRenderer = new ButtonRenderer();
//    table.setDefaultRenderer(JButton.class,buttonRenderer);
//    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//    table.setDefaultEditor(JButton.class,buttonEditor);
//    // ensure the table rows, columns have enough room for buttons
//    table.setRowHeight(sample.getPreferredSize().height);
//    table.getColumnModel().getColumn(column)
//        .setPreferredWidth((sample.getPreferredSize().width)+4);
 this->_table = table;
 table->setItemDelegateForColumn(column, new ButtonEditor());
 //buttonMap.append(column);
 //setPersistentButtons();
}

void BeanTableDataModel::OnButtonClicked(QObject* o)
{
 QModelIndex* index = (QModelIndex*)o;
 QString name = sysNameList.at(index->row());
 setData(*index, 0, Qt::EditRole);
 emit buttonClicked(index, name);
}

/*synchronized*/ /*public*/ void BeanTableDataModel::dispose()
{
 getManager()->removePropertyChangeListener((PropertyChangeListener*)this);
 if (!sysNameList.isEmpty())
 {
  for (int i = 0; i< sysNameList.size(); i++)
  {
   NamedBean* b = getBySystemName(sysNameList.at(i));
   if (b!=NULL) b->removePropertyChangeListener((PropertyChangeListener*)this);
  }
 }
}

/**
 * Method to self print or print preview the table.
 * Printed in equally sized columns across the page with headings and
 * vertical lines between each column. Data is word wrapped within a column.
 * Can handle data as strings, comboboxes or booleans
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*public*/ void BeanTableDataModel::printTable(HardcopyWriter* w)
{
 // determine the column size - evenly sized, with space between for lines
 int columnSize = (w->getCharactersPerLine()- this->columnCount(QModelIndex()) - 1)/this->columnCount(QModelIndex());

 // Draw horizontal dividing line
 w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(),
       (columnSize+1)*this->columnCount(QModelIndex()));

 // print the column header labels
 QVector<QString> columnStrings =  QVector<QString>(this->columnCount(QModelIndex()));
 // Put each column header in the array
 for (int i = 0; i < this->columnCount(QModelIndex()); i++)
 {
     columnStrings.replace(i, this->headerData(i, Qt::Horizontal,Qt::DisplayRole).toString());
 }
 w->setFontWeight(QFont::Bold);
 printColumns(w, columnStrings.toList(), columnSize);
 w->setFontWeight(QFont::Normal);
 w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(),
         (columnSize+1)*this->columnCount(QModelIndex()));

 // now print each row of data
 // create a base string the width of the column
 QString spaces = "";
 for (int i = 0; i < columnSize; i++) {
     spaces = spaces + " ";
 }
 for (int i = 0; i < this->rowCount(QModelIndex()); i++)
 {
  for (int j = 0; j < this->columnCount(QModelIndex()); j++)
  {
   //check for special, non string contents
   QVariant val = data(index(i,j),Qt::DisplayRole);
   if (val == QVariant())
   {
    columnStrings.replace(j, spaces);
   }
//   else if (this->getValueAt(i, j)instanceof JComboBox)
//   {
//    columnStrings[j] = (String)((JComboBox) this->getValueAt(i, j)).getSelectedItem();
//   }
//   else if (this->getValueAt(i, j)instanceof Boolean)
//   {
//    columnStrings[j] = ( this->getValueAt(i, j)).toString();
//   }
//   else columnStrings[j] = (String) this->getValueAt(i, j);
   else columnStrings.replace(j,val.toString());
  }
 printColumns(w, columnStrings.toList(), columnSize);
 w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(),
         (columnSize+1)*this->columnCount(QModelIndex()));
 }
 w->close();
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*protected*/ void BeanTableDataModel::printColumns(HardcopyWriter* w, QStringList columnStrings, int columnSize)
{
 QString columnString = "";
 QString lineString = "";
 // create a base string the width of the column
 QString spaces = "";
 for (int i = 0; i < columnSize; i++) {
     spaces = spaces + " ";
 }
 // loop through each column
 bool complete = false;
 while (!complete)
 {
  complete = true;
  for (int i = 0; i < columnStrings.length(); i++)
  {
   // if the column string is too wide cut it at word boundary (valid delimiters are space, - and _)
   // use the intial part of the text,pad it with spaces and place the remainder back in the array
   // for further processing on next line
   // if column string isn't too wide, pad it to column width with spaces if needed
   if (columnStrings[i].length() > columnSize)
   {
    bool noWord = true;
    for (int k = columnSize; k >= 1 ; k--)
    {
     if (columnStrings[i].mid(k-1,k)==(" ")
         || columnStrings[i].mid(k-1,k)==("-")
         || columnStrings[i].mid(k-1,k)==("_"))
     {
      columnString = columnStrings[i].mid(0,k)
          + spaces.mid(columnStrings[i].mid(0,k).length());
      columnStrings.replace(i, columnStrings[i].mid(k));
      noWord = false;
      complete = false;
      break;
     }
    }
    if (noWord)
    {
     columnString = columnStrings[i].mid(0,columnSize);
     columnStrings.replace(i, columnStrings[i].mid(columnSize));
     complete = false;
    }
   }
   else
   {
    columnString = columnStrings[i] + spaces.mid(columnStrings[i].length());
    columnStrings[i] = "";
   }
   lineString = lineString + columnString + " ";
  }
  try
  {
   w->write(QColor(Qt::black), lineString);
   //write vertical dividing lines
   for (int i = 0; i < w->getCharactersPerLine(); i = i+columnSize+1)
   {
    w->write(w->getCurrentLineNumber(), i, w->getCurrentLineNumber() + 1, i);
   }
   lineString = "\n";
   w->write(QColor(Qt::black),lineString);
   lineString = "";
  }
  catch (IOException e)
  { log->warn("error during printing: "+e.getMessage());}
 }
}

/**
 * Create and configure a new table using the given model and row sorter.
 *
 * @param name   the name of the table
 * @param model  the data model for the table
 * @param sorter the row sorter for the table; if null, the table will not
 *               be sortable
 * @return the table
 * @throws NullPointerException if name or model are null
 */
/*public*/ JTable* BeanTableDataModel::makeJTable(/*@Nonnull */QString name, /*@Nonnull */TableModel* /*model*/, /*@Nullable*/ RowSorter* /*<? extends TableModel>*/ sorter) {
//    Objects.requireNonNull(name, "the table name must be nonnull");
//    Objects.requireNonNull(model, "the table model must be nonnull");
    JTable* table = _table = new JTable((QAbstractItemModel*)sorter);
    table->setName(name);
    table->setSortingEnabled(true);
//    table->setRowSorter(sorter);
    table->horizontalHeader()->sectionsMovable();
    //table->getTableHeader().setReorderingAllowed(true);
    table->setColumnModel(new XTableColumnModel(table));
    //table->createDefaultColumnsFromModel();
//    table->resizeColumnsToContents();
//    table->horizontalHeader()->setStretchLastSection(true);

//    addMouseListenerToHeader(table);
    return table;
}

/*public*/ JTable* BeanTableDataModel::makeJTable(QSortFilterProxyModel* sorter)
{
 JTable* table = new JTable(sorter);
 table->setObjectName(this->metaObject()->className());

// {
//  /*public*/ boolean editCellAt(int row, int column, java.util.EventObject e) {
//      boolean res = super.editCellAt(row, column, e);
//      java.awt.Component c = this->getEditorComponent();
//      if (c instanceof javax.swing.JTextField) {
//          ( (JTextField) c).selectAll();
//      }
//      return res;
//  }
// };
// table.getTableHeader().setReorderingAllowed(true);
 table->resizeRowsToContents();
 table->setColumnModel(new XTableColumnModel(table));
 table->createDefaultColumnsFromModel();

// addMouseListenerToHeader(table);
 return table;
}
/**
 * Configure a new table using the given model and row sorter.
 *
 * @param table  the table to configure
 * @param name   the table name
 * @param sorter the row sorter for the table; if null, the table will not
 *               be sortable
 * @return the table
 * @throws NullPointerException if table or the table name is null
 */
/*protected*/ JTable* BeanTableDataModel::configureJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ JTable* table, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter) {
//    Objects.requireNonNull(table, "the table must be nonnull");
//    Objects.requireNonNull(name, "the table name must be nonnull");
    table->setRowSorter(sorter);
    table->setName(name);
//    table->getTableHeader()->setReorderingAllowed(true);
    table->setColumnModel(new XTableColumnModel(table));
    table->createDefaultColumnsFromModel();
//    addMouseListenerToHeader(table);
    return table;
}

/*abstract*/ /*protected*/ QString BeanTableDataModel::getBeanType()
{
    return "Bean";
}
/**
 * Updates the visibility settings of the property columns.
 *
 * @param table   the JTable object for the current display.
 * @param visible true to make the property columns visible, false to hide.
 */
/*public*/ void BeanTableDataModel::setPropertyColumnsVisible(JTable* table, bool visible) {
    XTableColumnModel* columnModel = (XTableColumnModel*) table->getColumnModel();
    for (int i = getColumnCount() - 1; i >= getColumnCount() - getPropertyColumnCount(); --i) {
        TableColumn* column = columnModel->getColumnByModelIndex(i);
        columnModel->setColumnVisible(column, visible);
    }
}
#if 0
class PopupListener extends MouseAdapter {
    /*public*/ void mousePressed(MouseEvent e) {
        if (e.isPopupTrigger())
            showPopup(e);
    }

    /*public*/ void mouseReleased(MouseEvent e) {
        if (e.isPopupTrigger())
            showPopup(e);
    }
}
#endif
/*protected*/ void BeanTableDataModel::showPopup(QPoint p)
{
 QModelIndex index= _table->indexAt(p);
// if(static_cast<QSortFilterProxyModel*>(index.model()))
//  row = static_cast<QSortFilterProxyModel*>(_table->getModel())->mapToSource(index).row();
// else
  row = index.row();
// JTable* source = (JTable)e.getSource();
//    TableSorter tmodel = ((TableSorter)source.getModel());
//    int row = source.rowAtPoint( e.getPoint() );
//    int column = source.columnAtPoint( e.getPoint() );
//    if (! source.isRowSelected(row))
//        source.changeSelection(row, column, false, false);
//    final int rowindex = tmodel.modelIndex(row);
 QMenu* popupMenu = new QMenu();
 QAction* menuItem = new QAction(tr("Copy User Name"),this);
//    menuItem.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            copyName(rowindex, 0);
//        }
//    });
 connect(menuItem, SIGNAL(triggered()), this, SLOT(On_copyName_triggered()));
 popupMenu->addAction(menuItem);

 menuItem = new QAction(tr("Rename"), this);
//    menuItem.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            renameBean(rowindex, 0);
//        }
//    });
 connect(menuItem, SIGNAL(triggered()), this, SLOT(On_renameBean_triggered()));
 popupMenu->addAction(menuItem);

 menuItem = new QAction(tr("Remove User Name"),this);
//    menuItem.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            removeName(rowindex, 0);
//        }
//    });
 connect(menuItem, SIGNAL(triggered()), this, SLOT(On_removeName_triggered()));
 popupMenu->addAction(menuItem);

 menuItem = new QAction(tr("Move"),this);
//    menuItem.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            moveBean(rowindex, 0);
//        }
//    });
 connect(menuItem, SIGNAL(triggered()), this, SLOT(On_moveBean_triggered()));
 popupMenu->addAction(menuItem);

 menuItem = new QAction(tr("Delete"),this);
//    menuItem.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            deleteBean(rowindex, 0);
//        }
//    });
 connect(menuItem, SIGNAL(triggered()), this, SLOT(On_deleteBean_triggered()));
 popupMenu->addAction(menuItem);
 addToPopUp(popupMenu);
 popupMenu->popup(_table->viewport()->mapToGlobal(p));

}

void BeanTableDataModel::addToPopUp(QMenu */*popup*/) {}

#if 0
class popupmenuRemoveName implements ActionListener {
    int row;
    popupmenuRemoveName(int row) {
        this->row=row;
    }
    /*public*/ void actionPerformed(ActionEvent e) {
        deleteBean(row, 0);
    }
}


#endif
void BeanTableDataModel::On_copyName_triggered()
{
 copyName(row);
}

/*public*/ void BeanTableDataModel::copyName(int row)
{
 NamedBean* nBean = getBySystemName(sysNameList.at(row));
 QClipboard* clipboard = QApplication::clipboard();
 //   StringSelection name = new StringSelection(nBean.getUserName());
 clipboard->setText(nBean->getUserName());
}

void BeanTableDataModel::On_renameBean_triggered()
{
 renameBean(row);
}

/*public*/ void BeanTableDataModel::renameBean(int row)
{
 NamedBean* nBean = getBySystemName(sysNameList.at(row));
 QString oldName = nBean->getUserName();
 JTextField* _newName = new JTextField(20);
 _newName->setText(oldName);
// Object[] renameBeanOption = {"Cancel", "OK", _newName};
// int retval = JOptionPane.showOptionDialog(NULL,
//                                           "Rename UserName From " + oldName, "Rename " + getBeanType(),
//                                           0, JOptionPane.INFORMATION_MESSAGE, NULL,
//                                           renameBeanOption, renameBeanOption[2] );
 InputDialog* dlg = new InputDialog("Rename UserName From '" + oldName+ "' to:", oldName, NULL);
 dlg->setWindowTitle("Rename " + getBeanType());
 if(dlg->exec() != QDialog::Accepted ) return;

 QString value = dlg->value().trimmed();

 if(value==(oldName))
 {
  //name not changed.
  return;
 }
 else
 {
  NamedBean* nB = getByUserName(value);
  if (nB != NULL)
  {
   log->error("User name is not unique " + value);
   QString msg;
//      msg = java.text.MessageFormat.format(AbstractTableAction.rb
//              .getString("WarningUserName"),
//              new Object[] { ("" + value) });
//      JOptionPane.showMessageDialog(NULL, msg,
//              AbstractTableAction.rb.getString("WarningTitle"),
//              JOptionPane.ERROR_MESSAGE);
   QMessageBox::warning(NULL, tr("Warning"), tr("User Name \" %1 \" has already been used.").arg(value));
   return;
  }
 }

 nBean->setUserName(value);
 fireTableRowsUpdated(row, row);
 if(value!=(""))
 {
  if(oldName==NULL || oldName==(""))
  {
   if(!nbMan->inUse(sysNameList.at(row), nBean))
    return;
//   QString msg = java.text.MessageFormat.format(AbstractTableAction.rb
//           .getString("UpdateToUserName"),
//           new Object[] { getBeanType(),value,sysNameList.get(row) });
//   int optionPane = JOptionPane.showConfirmDialog(NULL,
//       msg, AbstractTableAction.rb.getString("UpdateToUserNameTitle"),
//       JOptionPane.YES_NO_OPTION);
//   if(optionPane == JOptionPane.YES_OPTION)
   if(QMessageBox::question(NULL, tr("Update usage to UserName"), tr("Do you want to update references to this %1\nto use the UserName \"%2\" rather than its SystemName \"%3?\"").arg(getBeanType()).arg(value).arg(sysNameList.at(row)),QMessageBox::Yes | QMessageBox::No)!= QMessageBox::Yes)
   {
    //This will update the bean reference from the systemName to the userName
    try
    {
     nbMan->updateBeanFromSystemToUser(nBean);
    }
    catch (JmriException ex)
    {
     //We should never get an exception here as we already check that the username is not valid
    }
   }
  }
  else
  {
   nbMan->renameBean(oldName, value, nBean);
  }

 }
 else
 {
  //This will update the bean reference from the old userName to the SystemName
  nbMan->updateBeanFromUserToSystem(nBean);
 }
}
void BeanTableDataModel::On_removeName_triggered()
{
 removeName(row);
}

/*public*/ void BeanTableDataModel::removeName(int row){
    NamedBean* nBean = getBySystemName(sysNameList.at(row));
//    QString msg = java.text.MessageFormat.format(AbstractTableAction.rb
//            .getString("UpdateToSystemName"),
//            new Object[] { getBeanType()});
//    int optionPane = JOptionPane.showConfirmDialog(NULL,
//        msg, AbstractTableAction.rb.getString("UpdateToSystemNameTitle"),
//        JOptionPane.YES_NO_OPTION);
//    if(optionPane == JOptionPane.YES_OPTION)
    if(QMessageBox::question(NULL, tr("Update usage to SystemName").arg(getBeanType()), tr("Do you want to update references to this %1\nto use the SystemName?").arg(getBeanType()), QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
    {
     nbMan->updateBeanFromUserToSystem(nBean);
    }
    nBean->setUserName("");
    fireTableRowsUpdated(row, row);
}
void BeanTableDataModel::On_moveBean_triggered()
{
 moveBean(row);
}

/*public*/ void BeanTableDataModel::moveBean(int row)
{
 /*final*/ NamedBean* t = getBySystemName(sysNameList.at(row));
 QString currentName = t->getUserName();
 NamedBean* oldNameBean = getBySystemName(sysNameList.at(row));

 if((currentName==NULL) || currentName==(""))
 {
  //        JOptionPane.showMessageDialog(NULL,"Can not move an empty UserName");
  QMessageBox::warning(NULL, tr("Warning"), tr("Can not move an empty UserName"));
  return;
 }

 QComboBox* box = new QComboBox();
 QStringList nameList = getManager()->getSystemNameList();
 for(int i = 0; i<nameList.size(); i++)
 {
  NamedBean* nb = getBySystemName(nameList.at(i));
  //Only add items that do not have a username assigned.
  if(nb->getDisplayName()==(nameList.at(i)))
   box->addItem(nameList.at(i));
 }

// int retval = JOptionPane.showOptionDialog(NULL,
//      "Move " + getBeanType() + " " + currentName + " from " + oldNameBean.getSystemName(), "Move UserName",
//                                          0, JOptionPane.INFORMATION_MESSAGE, NULL,
//                                          new Object[]{"Cancel", "OK", box}, NULL );
 int retval = QMessageBox::information(NULL, tr("Move UserName"), "Move " + getBeanType() + " " + currentName + " from " + oldNameBean->getSystemName(), QMessageBox::Ok | QMessageBox::Cancel);
 log->debug("Dialog value "+QString::number(retval)+" selected "+QString::number(box->currentIndex())+":"
          +box->currentText());
 if (retval != QMessageBox::Ok) return;
 QString entry = box->currentText();
 NamedBean* newNameBean = getBySystemName(entry);
 if(oldNameBean!=newNameBean)
 {
  oldNameBean->setUserName("");
  newNameBean->setUserName(currentName);
  ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->moveBean(oldNameBean, newNameBean, currentName);
  if(nbMan->inUse(newNameBean->getSystemName(), newNameBean))
  {
//            String msg = java.text.MessageFormat.format(AbstractTableAction.rb
//                .getString("UpdateToUserName"),
//                new Object[] { getBeanType(),currentName,sysNameList.get(row)});
//            int optionPane = JOptionPane.showConfirmDialog(NULL,msg, AbstractTableAction.rb.getString("UpdateToUserNameTitle"), JOptionPane.YES_NO_OPTION);
//        if(optionPane == JOptionPane.YES_OPTION)
   if(QMessageBox::question(NULL, tr("UpdateToUserNameTitle"), tr("UpdateToUserName").arg(getBeanType()).arg(currentName).arg(sysNameList.at(row)), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
   {
    try
    {
     nbMan->updateBeanFromSystemToUser(newNameBean);
    }
    catch (JmriException ex)
    {
     //We should never get an exception here as we already check that the username is not valid
    }
   }
  }
  fireTableRowsUpdated(row, row);
  ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
        showInfoMessage("Reminder",getBeanType() + " " + tr("UpdateComplete"),"BeanTableDataModel", "remindSaveReLoad");
    //JOptionPane.showMessageDialog(NULL, getBeanType() + " " + AbstractTableAction.rb.getString("UpdateComplete"));
 }
}

/*protected*/ void BeanTableDataModel::showTableHeaderPopup(QMouseEvent* e, JTable* table) {
    QMenu* popupMenu = new QMenu();
    QSignalMapper* mapper = new QSignalMapper(this);

    XTableColumnModel* tcm = (XTableColumnModel*) table->getColumnModel();
    for (int i = 0; i < tcm->getColumnCount(false); i++) {
        TableColumn* tc = tcm->getColumnByModelIndex(i);
        QString columnName = _table->getModel()->headerData(i, Qt::Horizontal).toString();
        if (columnName != "" ) {
            QAction* menuItem = new QAction(_table->getModel()->headerData(i, Qt::Horizontal).toString()/*, tcm.isColumnVisible(tc)*/);
            menuItem->setCheckable(true);
            menuItem->setChecked(tcm->isColumnVisible(tc));
//            menuItem.addActionListener(new HeaderActionListener(tc, tcm));
            popupMenu->addAction(menuItem);
            mapper->setMapping(menuItem, tc);
            connect(menuItem, SIGNAL(toggled(bool)), mapper, SLOT(map()));

        }
        connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(onColumnSelected(QObject*)));

    }
    //popupMenu.show(e.getComponent(), e.getX(), e.getY());
    popupMenu->exec(QCursor::pos());
}

/*protected*/ void BeanTableDataModel::showTableHeaderPopup(const QPoint &){
    QMenu* popupMenu = new QMenu();
    QSignalMapper* mapper = new QSignalMapper(this);
    XTableColumnModel* tcm = (XTableColumnModel*)_table->getColumnModel();
    for (int i = 0; i < tcm->getColumnCount(false); i++)
    {
     TableColumn* tc = tcm->getColumnByModelIndex(i);
     QString columnName = _table->getModel()->headerData(i, Qt::Horizontal).toString();
     if(!columnName.isEmpty())
     {
      QAction* menuItem = new QAction(_table->getModel()->headerData(i, Qt::Horizontal).toString(), this);
      menuItem->setCheckable(true);
      menuItem->setChecked(/*tcm->isColumnVisible(tc)*/!_table->isColumnHidden(i));
//            menuItem.addActionListener(new headerActionListener(tc, tcm));
      popupMenu->addAction(menuItem);
      mapper->setMapping(menuItem, tc);
      connect(menuItem, SIGNAL(toggled(bool)), mapper, SLOT(map()));
     }
    }
    connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(onColumnSelected(QObject*)));
    //popupMenu.show(e.getComponent(), e.getX(), e.getY());
    popupMenu->exec(QCursor::pos());
}

void BeanTableDataModel::onColumnSelected(QObject* obj)
{
 TableColumn* tc = qobject_cast<TableColumn*>(obj);
 XTableColumnModel* tcm = (XTableColumnModel*)_table->getColumnModel();
 int column = tc->getModelIndex();
  //tcm->setColumnVisible(tc, !tcm->isColumnVisible(tc));
 _table->setColumnHidden(column, !_table->isColumnHidden(column));
 if(!_table->isColumnHidden(column))
 {
  if(_table->columnWidth(column)< 1)
   _table->setColumnWidth(column, 22);
 }
}
#if 0
static class headerActionListener implements ActionListener {
    TableColumn tc;
    XTableColumnModel tcm;
    headerActionListener(TableColumn tc, XTableColumnModel tcm){
         this->tc = tc;
         this->tcm = tcm;
    }

    /*public*/ void actionPerformed(ActionEvent e){
        JCheckBoxMenuItem check = (JCheckBoxMenuItem) e.getSource();
        //Do not allow the last column to be hidden
        if(!check.isSelected() && tcm.getColumnCount(true)==1){
            return;
        }
        tcm.setColumnVisible(tc, check.isSelected());
    }
}
#endif
/*protected*/ void BeanTableDataModel::addMouseListenerToHeader(JTable* /*table*/)
{
#if 0 // TODO:
    MouseListener mouseHeaderListener = new TableHeaderListener(table);
    table.getTableHeader().addMouseListener(mouseHeaderListener);
#endif
}
#if 0
class TableHeaderListener extends MouseAdapter {

    JTable table;
    TableHeaderListener(JTable tbl){
        super();
        table=tbl;
    }

    @Override
    /*public*/ void mousePressed(MouseEvent e) {
        if (e.isPopupTrigger()) {
            showTableHeaderPopup(e, table);
        }
    }

    @Override
    /*public*/ void mouseReleased(MouseEvent e) {
        if (e.isPopupTrigger()) {
            showTableHeaderPopup(e, table);
        }
    }

    @Override
    /*public*/ void mouseClicked(MouseEvent e) {
        if (e.isPopupTrigger()) {
            showTableHeaderPopup(e, table);
        }
    }
}
#endif
#if 0
/*public*/ void BeanTableDataModel::saveTableColumnDetails(JTable* table){
    saveTableColumnDetails(table, getMasterClassName());
}

// NOTE: Java no longer has this!
/*public*/ void BeanTableDataModel::saveTableColumnDetails(JTable* table, QString beantableref)
{
 UserPreferencesManager* p = (UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager");
#if 1
 XTableColumnModel* tcm = (XTableColumnModel*)table->getColumnModel();
 QSortFilterProxyModel* tmodel = ((QSortFilterProxyModel*)table->getModel());
 Q_UNUSED(tmodel);
 QListIterator<TableColumn*> en = tcm->getColumns(false);
 while(en.hasNext())
 {
  TableColumn* tc = en.next();

  try
  {
   QString columnName = tc->getHeaderValue().toString();
   //skip empty or blank columns
   if(columnName!=(""))
   {
    int index = tcm->getColumnIndex(tc->getIdentifier(), false);
    p->setTableColumnPreferences(beantableref, columnName, index, tc->getPreferredWidth(), /*tmodel->getSortingStatus(tc->getModelIndex())*/true, !tcm->isColumnVisible(tc));
   }
  }
  catch (Exception e)
  {
   log->warn("unable to store settings for table column " + tc->getHeaderValue().toString());
   //e.printStackTrace();
  }
 }
#endif
}
#endif
/**
 * Persist the state of the table after first setting the table to the last
 * persisted state.
 *
 * @param table the table to persist
 * @throws NullPointerException if the name of the table is null
 */
/*public*/ void BeanTableDataModel::persistTable(/*@Nonnull*/ JTable* table) //throws NullPointerException
{
    JTablePersistenceManager* manager = (JTablePersistenceManager*) InstanceManager::getNullableDefault("JTablePersistenceManager");
    if (manager != NULL) {
        manager->resetState(table); // throws NPE if table name is null
        manager->persist(table);
    }
}

/**
 * Stop persisting the state of the table.
 *
 * @param table the table to stop persisting
 * @throws NullPointerException if the name of the table is null
 */
/*public*/ void BeanTableDataModel::stopPersistingTable(/*@Nonnull*/ JTable* table) //throws NullPointerException
{
    JTablePersistenceManager* manager = (JTablePersistenceManager*) InstanceManager::getNullableDefault("JTablePersistenceManager");
    if (manager != NULL) {
        manager->stopPersisting(table); // throws NPE if table name is null
    }
}

/*private*/ /*final*/ /*static*/ Logger* BeanTableDataModel::log = LoggerFactory::getLogger("BeanTableDataModel");
