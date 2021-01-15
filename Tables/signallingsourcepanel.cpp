#include "signallingsourcepanel.h"
#include "instancemanager.h"
#include "signalmastlogicmanager.h"
#include "signalmastlogic.h"
#include "signalmast.h"
#include "../LayoutEditor/layoutblockmanager.h"
#include "propertychangeevent.h"
#include "jtable.h"
#include "../LayoutEditor/jmrijframe.h"
#include <QMessageBox>
#include "../LayoutEditor/panelmenu.h"
#include "defaultsignalmastlogic.h"
#include "QHeaderView"
#include "jtextfield.h"
#include "defaultsignalmastlogicmanager.h"
#include "signallingaction.h"
#include "joptionpane.h"

//SignallingSourcePanel::SignallingSourcePanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Frame for Signal Mast Add / Edit Panel
 * @author	Kevin Dickerson   Copyright (C) 2011
 * @version $Revision: 20084 $
*/

///*public*/ class SignallingSourcePanel extends jmri.util.swing.JmriPanel implements PropertyChangeListener {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.SignallingBundle");


/*public*/ SignallingSourcePanel::SignallingSourcePanel(/*final*/ SignalMast* sourceMast, QWidget* parent) : JmriPanel(parent)
{
 //super();
 fixedSourceMastLabel = new QLabel();
 discoverPairs = new QPushButton(tr("Discover"));
 sml = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(sourceMast);
 this->sourceMast = sourceMast;
 fixedSourceMastLabel = new QLabel(sourceMast->getDisplayName());
 signalMastLogicFrame = NULL;
 sourceLabel = new QLabel();


 if (sml!=NULL)
 {
  _signalMastList = ((DefaultSignalMastLogic*)sml)->getDestinationList();
 }

  //InstanceManager::layoutBlockManagerInstance().addPropertyChangeListener(this);
  LayoutBlockManager* lbm = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"));
  connect(lbm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  connect(static_cast<DefaultSignalMastLogicManager*>(InstanceManager::getDefault("SignalMastLogicManager"))->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));


  setLayout(new /*BorderLayout()*/QVBoxLayout);

  QWidget* header = new QWidget();
  header->setLayout(new QVBoxLayout(header/*, BoxLayout.Y_AXIS*/));

  QWidget* sourcePanel = new QWidget();
  sourcePanel->setLayout(new QHBoxLayout());
  sourcePanel->layout()->addWidget(fixedSourceMastLabel);
  header->layout()->addWidget(sourcePanel);
  layout()->addWidget(header /*, BorderLayout.NORTH*/);

  _AppearanceModel = new SignalMastAppearanceModel(this);
  //JTable* SignalAppearanceTable = jmri.util.JTableUtil.sortableDataModel(_AppearanceModel);
  JTable* signalAppearanceTable = new JTable();

  // TODO:
  //  try {
  //    jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)SignalAppearanceTable.getModel());
  //    tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
  //    tmodel.setSortingStatus(SignalMastAppearanceModel.SYSNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
  //  }
  //  catch (ClassCastException e3) {}  // if not a sortable table model
  signalAppearanceTable->setModel(_AppearanceModel);

  //signalAppearanceTable.setRowSelectionAllowed(false);
  signalAppearanceTable->setSelectionBehavior(QAbstractItemView::SelectItems);
  signalAppearanceTable->setSelectionMode(QAbstractItemView::SingleSelection);
  //signalAppearanceTable.setPreferredScrollableViewportSize(new java.awt.Dimension(600,120));
  _AppearanceModel->configureTable(signalAppearanceTable);
//  _SignalAppearanceScrollPane = new QScrollArea();
//  _SignalAppearanceScrollPane->setWidget(signalAppearanceTable);
  _AppearanceModel->fireTableDataChanged();
  layout()->addWidget(/*_SignalAppearanceScrollPane*/signalAppearanceTable/*, BorderLayout.CENTER)*/);

  QWidget* footer = new QWidget();
  footer->setLayout(new QHBoxLayout());
  footer->layout()->addWidget(discoverPairs);
//  discoverPairs.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        discoverPressed(e);
//    }
//  });
  connect(discoverPairs, SIGNAL(clicked()), this, SLOT(discoverPressed()));

  QPushButton* addLogic = new QPushButton(tr("Add Logic"));
  footer->layout()->addWidget(addLogic);
//  addLogic.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        class WindowMaker implements Runnable {
//        WindowMaker(){
//        }
//        /*public*/ void run() {
//            SignallingAction sigLog = new SignallingAction();
//            sigLog.setMast(sourceMast, NULL);
//            sigLog.actionPerformed(NULL);
//        }
//    }
//    WindowMaker t = new WindowMaker();
//    javax.swing.SwingUtilities.invokeLater(t);
//    }
//  });
  connect(addLogic, SIGNAL(clicked()), this, SLOT(on_addLogic_pressed()));

  /*if(!InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled())
    discoverPairs.setEnabled(false);*/
  layout()->addWidget(footer/*, BorderLayout.SOUTH*/);
}

/**
 * Remove references to and from this object, so that it can eventually be
 * garbage-collected.
 */
//@Override
/*public*/ void SignallingSourcePanel::dispose()
{
    //static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->removePropertyChangeListener(this);
 disconnect(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    //InstanceManager.getDefault(jmri.SignalMastLogicManager.class).removePropertyChangeListener(this);
 disconnect(static_cast<DefaultSignalMastLogicManager*>(InstanceManager::getDefault("SignalMastLogicManager"))->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    JmriPanel::dispose();
}

void SignallingSourcePanel::on_addLogic_pressed()
{
 SignallingAction* sigLog = new SignallingAction();
 sigLog->setMast(sourceMast, NULL);
 sigLog->actionPerformed();
}

void SignallingSourcePanel::discoverPressed(/*ActionEvent e*/)
{
 if (!(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled()))
 {
 //    int response = JOptionPane.showConfirmDialog(NULL, tr("EnableLayoutBlockRouting"));
 //    if (response == 0){
 //        InstanceManager::layoutBlockManagerInstance().enableAdvancedRouting(true);
 //        JOptionPane.showMessageDialog(NULL, tr("LayoutBlockRoutingEnabledShort"));
 //    }
     switch(QMessageBox::question(NULL, tr("Confirm"), tr("Layout block routing is not enabled\n Do you want to enable it?"), QMessageBox::Yes | QMessageBox::No))
     {
     default:
     case QMessageBox::No:
      return;
     case QMessageBox::Yes:
      static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->enableAdvancedRouting(true);
      QMessageBox::information(NULL, tr("Information"), tr("Layout Block routing has been enabled."));
      break;
     }
 }

 signalMastLogicFrame = new JmriJFrameX("Discover Signal Mast Pairs", false, false);
 signalMastLogicFrame->setMinimumSize(QSize());
 QWidget* panel1 = new QWidget();
 panel1->setLayout(new QHBoxLayout());
 sourceLabel = new QLabel("Discovering Signalmasts");
 panel1->layout()->addWidget(sourceLabel);
 if(signalMastLogicFrame->getContentPane()->layout() == nullptr)
 {
  signalMastLogicFrame->getContentPane()->setLayout(new QVBoxLayout());
 }
 signalMastLogicFrame->getContentPane()->layout()->addWidget(/*sourceLabel*/panel1);
 signalMastLogicFrame->pack();
 signalMastLogicFrame->setVisible(true);

 QList<LayoutEditor*>* layout = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
 if(layout->size() > 0)
 {
  for(int i = 0; i<layout->size(); i++)
  {
   try
   {
       ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->discoverSignallingDest(sourceMast, layout->at(i));
   }
   catch (JmriException ex) {
       signalMastLogicFrame->setVisible(false);
       JOptionPane::showMessageDialog(NULL, ex.toString());
   }
  }
 }
 else {
   // don't take the trouble of searching
   JOptionPane::showMessageDialog(nullptr, tr("Cannot search for Pairs as there are\nno Layout Editor panels available."));  // NOI18N
 }
}

/*public*/ void SignallingSourcePanel::propertyChange(PropertyChangeEvent* e) // [slot]
{
 if (e->getPropertyName()==("autoSignalMastGenerateComplete"))
 {
    signalMastLogicFrame->setVisible(false);
    signalMastLogicFrame->dispose();

    if(sml==NULL){
        updateDetails();
    }
    //JOptionPane.showMessageDialog(NULL, "Generation of Signalling Pairs Completed");
    QMessageBox::information(NULL, tr("Information"), tr("Generation of Signalling Pairs Completed"));
 }
 if(e->getPropertyName()==("advancedRoutingEnabled")){
    bool newValue =  e->getNewValue().toBool();
    discoverPairs->setEnabled(newValue);
 }
}


/*private*/ void SignallingSourcePanel::updateDetails()
{
 SignalMastLogic* old = sml;
 sml = qobject_cast<SignalMastLogicManager*>(InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(sourceMast);
 if (sml!=NULL)
 {
  _signalMastList = sml->getDestinationList();
  _AppearanceModel->updateSignalMastLogic(old, sml);
 }
}

///*public*/ class SignalMastAppearanceModel extends AbstractTableModel implements PropertyChangeListener
//{
SignalMastAppearanceModel::SignalMastAppearanceModel(SignallingSourcePanel* self, QObject* parent) : QAbstractTableModel(parent)
 {
  //super();
    log = new Logger("SignalMastAppearanceModel");
  this->self = self;
  if(self->sml!=NULL)
  {
   //sml.addPropertyChangeListener(this);
   DefaultSignalMastLogic* sml = (DefaultSignalMastLogic*)self->sml;
   connect(sml->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(propertyChangeEvent*)));
  }
 }

 void SignalMastAppearanceModel::updateSignalMastLogic(SignalMastLogic* smlOld, SignalMastLogic* smlNew)
 {
  if(smlOld!=NULL){
   //smlOld.removePropertyChangeListener(this);
   DefaultSignalMastLogic* sml = (DefaultSignalMastLogic*)smlOld->self();
   disconnect(sml->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(propertyChangeEvent*)));
  }

  if(smlNew!=NULL)
  {
   //smlNew.addPropertyChangeListener(this);
   DefaultSignalMastLogic* sml = (DefaultSignalMastLogic*)smlNew->self();
   disconnect(sml->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(propertyChangeEvent*)));
  }

   fireTableDataChanged();
 }

////@Override
///*public*/ Class<?> getColumnClass(int c) {
//    if (c ==ACTIVE_COLUMN)
//        return Boolean.class;
//    if (c ==ENABLE_COLUMN)
//        return Boolean.class;
//    if(c==EDIT_COLUMN)
//        return JButton.class;
//    if(c==DEL_COLUMN)
//        return JButton.class;
//    return String.class;
//}

/*public*/ void SignalMastAppearanceModel::configureTable(JTable* table)
 {
    // allow reordering of the columns
    table->setSortingEnabled(true);

    // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
    //table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

    // resize columns as requested
    for (int i=0; i<table->model()->columnCount(); i++) {
        int width = getPreferredWidth(i);
        //table.getColumnModel().getColumn(i).setPreferredWidth(width);
        table->setColumnWidth(i,width);
    }
    //table.sizeColumnsToFit(-1);

    configEditColumn(table);

}

/*public*/ int SignalMastAppearanceModel::getPreferredWidth(int col)
 {
    switch (col) {
    case SYSNAME_COLUMN:
        return JTextField(15).getPreferredSize().width();
    case ENABLE_COLUMN:
    case ACTIVE_COLUMN:
        return JTextField(5).getPreferredSize().width();
    case USERNAME_COLUMN:
        return JTextField(15).getPreferredSize().width();
    case EDIT_COLUMN: // not actually used due to the configureTable, setColumnToHoldButton, configureButton
        return JTextField(22).getPreferredSize().width();
    case DEL_COLUMN: // not actually used due to the configureTable, setColumnToHoldButton, configureButton
        return JTextField(22).getPreferredSize().width();
    default:
        log->warn("Unexpected column in getPreferredWidth: "+QString::number(col));
        return  JTextField(8).getPreferredSize().width();
    }
}

//@Override
/*public*/ QVariant SignalMastAppearanceModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    if (section==USERNAME_COLUMN) return tr("User Name");
    if (section==SYSNAME_COLUMN) return tr("System Name");
    if (section==ACTIVE_COLUMN) return tr("Active");
    if (section==ENABLE_COLUMN) return tr("Enabled");
    if (section==EDIT_COLUMN) return tr("Edit");
    if (section==DEL_COLUMN) return tr("Delete");
  }
  return QVariant();
}

/*public*/ void SignalMastAppearanceModel::dispose()
 {
  if(self->sml!=NULL)
  {
   DefaultSignalMastLogic* sml = (DefaultSignalMastLogic*)self->sml;
        //sml.removePropertyChangeListener(this);
   disconnect(sml->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(propertyChangeEvent*)));
  }
}

/*public*/ void SignalMastAppearanceModel::propertyChange(PropertyChangeEvent* e)
 {
  if (e->getPropertyName()==("length"))
  {
   beginResetModel();
   self->_signalMastList = ((DefaultSignalMastLogic*)self->sml)->getDestinationList();
   int length =  e->getNewValue().toInt();
   if(length==0)
   {
    //((DefaultSignalMastLogic*)self->sml)->removePropertyChangeListener(this);
    disconnect(((DefaultSignalMastLogic*)self->sml)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    self->sml = NULL;
   }
        //fireTableDataChanged();
   endResetModel();
  }
  else if (e->getPropertyName()==("updatedDestination"))
  {
   // a new NamedBean is available in the manager
   self->_signalMastList = ((DefaultSignalMastLogic*)self->sml)->getDestinationList();
        //fireTableDataChanged();
  }
  else if((e->getPropertyName()==("state")) || (e->getPropertyName()==("Enabled")))
  {
   //fireTableDataChanged();
   beginResetModel();
   //fireTableRowsUpdated(0, self->_signalMastList.size());
   endResetModel();
  }
}


/*protected*/ void SignalMastAppearanceModel::configEditColumn(JTable* table) {
    // have the delete column hold a button
    /*AbstractTableAction.tr("EditDelete")*/
    setColumnToHoldButton(table, EDIT_COLUMN,
            new QPushButton(tr("Edit")));
    setColumnToHoldButton(table, DEL_COLUMN,
            new QPushButton(tr("Delete")));
}

/*protected*/ void SignalMastAppearanceModel::setColumnToHoldButton(JTable* /*table*/, int /*column*/, QPushButton* /*sample*/) {
    //TableColumnModel tcm = table.getColumnModel();
    // install a button renderer & editor
#if 0 // TODO:
    ButtonRenderer buttonRenderer = new ButtonRenderer();
    table.setDefaultRenderer(JButton.class,buttonRenderer);
    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
    table.setDefaultEditor(JButton.class,buttonEditor);
    // ensure the table rows, columns have enough room for buttons
    table.setRowHeight(sample.getPreferredSize().height);
    table.getColumnModel().getColumn(column)
        .setPreferredWidth((sample.getPreferredSize().width)+4);
#endif
}

/*public*/ int SignalMastAppearanceModel::columnCount (const QModelIndex &/*parent*/) const {return 6;}

//@Override
/*public*/ Qt::ItemFlags SignalMastAppearanceModel::flags(const QModelIndex &index) const
{
    int c = index.column();
    if (c==EDIT_COLUMN)
        return Qt::ItemIsEditable | Qt::ItemIsSelectable;
    if (c==DEL_COLUMN)
        return Qt::ItemIsEditable | Qt::ItemIsSelectable;
    if (c==ENABLE_COLUMN)
        return Qt::ItemIsEditable | Qt::ItemIsSelectable;
    if (c==USERNAME_COLUMN)
        return Qt::ItemIsEditable | Qt::ItemIsSelectable;
    return Qt::ItemIsSelectable;
}

/*protected*/ void SignalMastAppearanceModel::editPair(int row)
 {
    #if 0
    class WindowMaker implements Runnable {
        int row;
        WindowMaker(int r){
            row = r;
        }
        /*public*/ void run() {
            SignallingAction sigLog = new SignallingAction();
            sigLog.setMast(sourceMast, _signalMastList.get(row));
            sigLog.actionPerformed(NULL);
        }
    }
    WindowMaker t = new WindowMaker(r);
    javax.swing.SwingUtilities.invokeLater(t);
#endif
    SignallingAction* sigLog = new SignallingAction();
    sigLog->setMast(self->sourceMast, self->_signalMastList.at(row));
    sigLog->actionPerformed(/*NULL*/);

}

/*protected*/ void SignalMastAppearanceModel::deletePair(int r){
    ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->removeSignalMastLogic(self->sml, self->_signalMastList.at(r));
}


///*public*/ void setSetToState(String x){}

/*public*/ int SignalMastAppearanceModel::rowCount (const QModelIndex &/*parent*/) const {
    if (self->_signalMastList.isEmpty())
        return 0;
    return self->_signalMastList.size();
}

/*public*/ QVariant SignalMastAppearanceModel::data(const QModelIndex &index, int role) const
 {
  if(!index.isValid()) return QVariant();
  int c = index.column();
  int r = index.row();
  if(role == Qt::DisplayRole || role == Qt::EditRole)
  {

    if(self->sml==NULL)
        return QVariant();
    // some error checking
    if (r >= self->_signalMastList.size()){
        log->debug("row is greater than turnout list size");
        return QVariant();
    }
    switch (c)
    {
        case USERNAME_COLUMN:
            return self->_signalMastList.at(r)->getUserName();
        case SYSNAME_COLUMN:  // slot number
            return self->_signalMastList.at(r)->getSystemName();
        case EDIT_COLUMN:
            return tr("Edit");
        case DEL_COLUMN:
            return tr("Delete");
        default:
        return QVariant();
                    ;
    }
  }
  if(role == Qt::CheckStateRole)
  {
   switch (c)
   {
    case ACTIVE_COLUMN:
          if (((DefaultSignalMastLogic*)self->sml)->isActive(self->_signalMastList.at(r)))
           return Qt::Checked;
          else
           return Qt::Unchecked;
       case ENABLE_COLUMN:
          if(((DefaultSignalMastLogic*)self->sml)->isEnabled(self->_signalMastList.at(r)))
              return Qt::Checked;
             else
              return Qt::Unchecked;
      default:
       break;
   }
  }
  return QVariant();
}

//@Override
/*public*/ bool SignalMastAppearanceModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  if(role == Qt::EditRole)
  {
   int c = index.column();
   int r = index.row();
   if (c==EDIT_COLUMN)
    editPair(r);
   else if (c==DEL_COLUMN)
    deletePair(r);
   else if (c==ENABLE_COLUMN)
   {
    bool b = value.toBool();
    if(b)
     ((DefaultSignalMastLogic*)self->sml)->setEnabled(self->_signalMastList.at(r));
    else
     ((DefaultSignalMastLogic*)self->sml)->setDisabled(self->_signalMastList.at(r));
   }
   return true;
  }
  return false;
 }
 void SignalMastAppearanceModel::fireTableDataChanged()
 {
  beginResetModel();
  endResetModel();
 }

//}; // end /*public*/ class SignalMastAppearanceModel extends AbstractTableModel implements PropertyChangeListener



//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SignallingSourcePanel.class.getName());

//}
