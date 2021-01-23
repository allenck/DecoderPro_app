#include "signalmastlogictableaction.h"
#include "signallingaction.h"
#include "jtable.h"
#include <QMenuBar>
#include <QMenu>
#include "jmrijframe.h"
#include <QLabel>
#include <instancemanager.h>
#include "signalmast.h"
#include "signalmastlogic.h"
#include "signalmastlogicmanager.h"
#include "jtextfield.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "defaultsignalmastlogicmanager.h"
#include <QPushButton>
#include "joptionpane.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include "layoutblockmanager.h"
#include "mysortfilterproxymodel.h"

//SignalMastLogicTableAction::SignalMastLogicTableAction()
//{
//}
 /**
  * Create an action with a specific title.
  * <P>
  * Note that the argument is the Action title, not the title of the
  * resulting frame. Perhaps this should be changed?
  *
  * @param s title of the action
  */
 /*public*/ SignalMastLogicTableAction::SignalMastLogicTableAction(QString s, QObject* parent) : AbstractTableAction(s, parent)
{
     //super(s);
     common();
 }

 /*public*/ SignalMastLogicTableAction::SignalMastLogicTableAction(QObject* parent)
    : AbstractTableAction(tr("Signal Mast Logic Table"), parent)
{
     //this(tr("TitleSignalMastLogicTable"));
    common();
 }

void SignalMastLogicTableAction::common()
{
    sigLog = new SignallingAction();
    signalMastLogicList = NULL;
     suppressUpdate = false;
    signalMastLogicFrame = NULL;
    sourceLabel = new QLabel();

}

 //@Override
 /*public*/ void SignalMastLogicTableAction::actionPerformed(JActionEvent * /*e*/) {
#if 1
     // create the JTable model, with changes for specific NamedBean
     createModel();
     MySortFilterProxyModel* sorter = new MySortFilterProxyModel(m);
     JTable* dataTable = m->makeJTable(sorter);
     dataTable->setObjectName("SignalMastLogicTable");
     //sorter.setTableHeader(dataTable.getTableHeader());
     // create the frame
     f = new BeanTableFrame(m, helpTarget(), dataTable);
     setMenuBar(f);
     setTitle();
     addToFrame(f);
     f->pack();
     f->setVisible(true);
#endif
 }

 /*public*/ void SignalMastLogicTableAction::setMenuBar(BeanTableFrame* f) {
     finalF = f;			// needed for anonymous ActionListener class
     QMenuBar* menuBar = f->menuBar();
     QMenu* pathMenu = new QMenu(tr("Tools"));
     menuBar->addMenu(pathMenu);
     QAction* item = new QAction(tr("AutoGen"), this);
     pathMenu->addAction(item);
//     item.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             autoCreatePairs(finalF);
//         }
//     });
     connect(item, SIGNAL(triggered(bool)), this, SLOT(autoCreatePairs()));
     item = new QAction(tr("Auto Gen Sections"), this);
     pathMenu->addAction(item);
//     item.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
     connect(item, &QAction::triggered, [=]{
             ((DefaultSignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->generateSection();
             JOptionPane::showMessageDialog(NULL,tr("Generation of Sections Complete"));
//         }
     });
     QAction* setSMLDirSensors = new QAction(tr("Add Direction Sensors to SML"));
     pathMenu->addAction(setSMLDirSensors);
//     setSMLDirSensors.addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent e) {
     connect(setSMLDirSensors, &QAction::triggered, [=]{
             int n = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->setupSignalMastsDirectionSensors();
             if (n > 0) {
                 JOptionPane::showMessageDialog(finalF, tr("There were %1 errors, see console log.").arg(n),
                         tr("Error"), JOptionPane::ERROR_MESSAGE);
             }
//         }
     });
}


 /*protected*/ void SignalMastLogicTableAction::createModel()
{
 m = new SmlBeanTableDataModel(this);
}

SmlBeanTableDataModel::SmlBeanTableDataModel(SignalMastLogicTableAction* act)
{
  this->act = act;
  log = new Logger("SmlBeanTableDataModel");
  source = ((DefaultSignalMastLogicManager*)getManager())->getSignalMastLogicList();
  act->signalMastLogicList = new QList<QHash<SignalMastLogic*, SignalMast*>*>();
 init();
}
 //We have to set a manager first off, but this gets replaced.
 /*protected*/ Manager* SmlBeanTableDataModel::getManager() {
     return (Manager*)InstanceManager::getDefault("SignalMastLogicManager");
 }

 /*public EcosLocoAddress getByDccAddress(int address) {return getManager().getByDccAddress(address);}*/
 /*public*/ QString SmlBeanTableDataModel::getValue(QString /*s*/) const{
     return "Set";
 }

 /*protected*/ QString SmlBeanTableDataModel::getMasterClassName() {
     return act->getClassName();
 }

 /*public*/ void SmlBeanTableDataModel::clickOn(NamedBean* /*t*/) {
 }

 //@Override
 /*protected*/ /*synchronized*/ void SmlBeanTableDataModel::updateNameList()
{
 // first, remove listeners from the individual objects
 if (act->signalMastLogicList != NULL)
 {
     for (int i = 0; i < act->signalMastLogicList->size(); i++) {
         // if object has been deleted, it's not here; ignore it
         QHash<SignalMastLogic*, SignalMast*>* b = act->signalMastLogicList->at(i);
         QListIterator<SignalMastLogic*> en = b->keys();
         while (en.hasNext()) {
             SignalMastLogic* sm = en.next();
             SignalMast* dest = b->value(sm);
             sm->removePropertyChangeListener((PropertyChangeListener*)this);
//             disconnect(sm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             sm->getSourceMast()->removePropertyChangeListener((PropertyChangeListener*)this);
//             disconnect(sm->getSourceMast()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             dest->removePropertyChangeListener((PropertyChangeListener*)this);
//             disconnect(dest, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }
 for (int i = 0; i < source.size(); i++) {
     QList<SignalMast*> destList = source.at(i)->getDestinationList();
     source.at(i)->addPropertyChangeListener((PropertyChangeListener*)this);
     //connect(source.at(i)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     source.at(i)->getSourceMast()->addPropertyChangeListener((PropertyChangeListener*)this);
     //connect(source.at(i)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     for (int j = 0; j < destList.size(); j++) {
         QHash<SignalMastLogic*, SignalMast*>* hash = new QHash<SignalMastLogic*, SignalMast*>(/*1*/);
         hash->insert(source.at(i), destList.at(j));
         //destList.a(j).addPropertyChangeListener(this);
         connect(destList.at(j)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         act->signalMastLogicList->append(hash);
     }
  }
 }

 //Will need to redo this so that we work out the row number from looking in the signalmastlogiclist.
 //@Override
 /*public*/ void SmlBeanTableDataModel::propertyChange(PropertyChangeEvent* e) {
     if (act->suppressUpdate) {
         return;
     }
     // updateNameList();
     if ( e->getPropertyName() == ("length") ||  e->getPropertyName() == ("updatedDestination") ||  e->getPropertyName() == ("updatedSource")) {
         updateNameList();
         //log.debug("Table changed length to "+signalMastLogicList.size());
         fireTableDataChanged();
     }
     //else if (e.getSource() instanceof SignalMastLogic) {
     else if(qobject_cast<SignalMastLogic*>( e->getSource())!= NULL)
     {
         SignalMastLogic* logic = (SignalMastLogic*)  e->getSource();
         if (matchPropertyName(e)) {
             for (int i = 0; i < act->signalMastLogicList->size(); i++) {
                 QHash<SignalMastLogic*, SignalMast*>* b = act->signalMastLogicList->at(i);
                 QListIterator<SignalMastLogic*> en = b->keys();
                 while (en.hasNext()) {
                     SignalMastLogic* sm = en.next();
                     if (sm == logic) {
                         fireTableRowsUpdated(i, i);
                     }
                 }
             }
         }
     }
     //else if (e.getSource() instanceof jmri.SignalMast) {
     else if(qobject_cast<SignalMast*>(e->getSource())!= NULL)
     {
         SignalMast* sigMast = (SignalMast*)  e->getSource();
         for (int i = 0; i < act->signalMastLogicList->size(); i++) {
             QHash<SignalMastLogic*, SignalMast*>* b = act->signalMastLogicList->at(i);
             QListIterator<SignalMastLogic*> en = b->keys();
             while (en.hasNext()) {
                 SignalMastLogic* sm = en.next();
                 //SignalMast dest = b.get(sm);
                 if (sm->getSourceMast() == sigMast) {
                     fireTableRowsUpdated(i, i);
                 }
             }
         }
     }
 }

 //}
 /**
  * Is this property event announcing a change this table should
  * display?
  * <P>
  * Note that events will come both from the NamedBeans and also from
  * the manager
  */
/*protected*/ bool SmlBeanTableDataModel::matchPropertyName(PropertyChangeEvent* e)
{
     return (( e->getPropertyName().indexOf("Comment") >= 0) || ( e->getPropertyName().indexOf("Enable") >= 0));
 }

 //@Override
 /*public*/ int SmlBeanTableDataModel::columnCount(const QModelIndex &/*parent*/) const
{
     return EDITLOGICCOL + 1;
 }

 //@Override
 /*public*/ bool SmlBeanTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int col = index.column();
    int row = index.row();
    if(role == Qt::EditRole)
    {
     if (col == COMCOL) {
         getLogicFromRow(row)->setComment( value.toString(), getDestMastFromRow(row));
     }
     else if (col == EDITLOGICCOL)
     {
//         class WindowMaker implements Runnable {

//             int row;

//             WindowMaker(int r) {
//                 row = r;
//             }

//             /*public*/ void run() {
                 editLogic(row, 0);
//             }
//         }
//         WindowMaker t = new WindowMaker(row);
//         javax.swing.SwingUtilities.invokeLater(t);

     }
     else if (col == DELCOL)
     {
         // button fired, delete Bean
         deleteLogic(row, col);
     }
     return true;
    }
    if(role == Qt::CheckStateRole)
    {
     if (col == ENABLECOL)
     {
         bool enable =value.toBool();
         if (enable) {
             getLogicFromRow(row)->setEnabled(getDestMastFromRow(row));
         } else {
             getLogicFromRow(row)->setDisabled(getDestMastFromRow(row));
         }
     }
     return true;
    }
    return BeanTableDataModel::setData(index, value, role);
 }

 //@Override
 /*public*/ QVariant SmlBeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
   {
     switch (section) {
         case SOURCECOL:
             return tr("Source");
         case DESTCOL:
             return tr("Destination");
         case SOURCEAPPCOL:
             return tr("Aspect Type");
         case DESTAPPCOL:
             return tr("Aspect Type");
         case COMCOL:
             return tr("Comment");
         case DELCOL:
             return ""; // override default, no title for Delete column
         case EDITLOGICCOL:
             return ""; // override default, no title for Edit column
         case ENABLECOL:
             return tr("Head Enabled");
         case MAXSPEEDCOL:
             return tr("Max speed");
         default:
             break;
     }
   }
   return BeanTableDataModel::headerData(section, orientation, role);
 }

// @Override
 /*public*/ QString SmlBeanTableDataModel::getColumnClass(int col) const {
     switch (col) {
         case SOURCECOL:
         case DESTCOL:
         case SOURCEAPPCOL:
         case COMCOL:
         case DESTAPPCOL:
             return "String";
         case ENABLECOL:
             return "Boolean";
         case EDITLOGICCOL:
         case DELCOL:
             return "JButton";
         default:
             return QString();
     }
 }

 //@Override
 /*public*/ Qt::ItemFlags SmlBeanTableDataModel::flags(const QModelIndex &index) const
{
 switch (index.column())
 {
     case COMCOL:
     case EDITLOGICCOL:
     case DELCOL:
     return Qt::ItemIsEnabled | Qt::ItemIsEditable;
     case ENABLECOL:
         return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
     default:
         return Qt::ItemIsEnabled;
 }
}

 void SmlBeanTableDataModel::editLogic(int row, int /*col*/) {
     act->sigLog->setMast(getLogicFromRow(row)->getSourceMast(), getDestMastFromRow(row));
     act->sigLog->actionPerformed();
 }

 void SmlBeanTableDataModel::deleteLogic(int row, int /*col*/) {
     //This needs to be looked at
     ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->removeSignalMastLogic(getLogicFromRow(row), getDestMastFromRow(row));
 }

 /*public*/ SignalMast* SmlBeanTableDataModel::getDestMastFromRow(int row) const{
     // if object has been deleted, it's not here; ignore it
     QHash<SignalMastLogic*, SignalMast*>* b = act->signalMastLogicList->at(row);
     QListIterator<SignalMastLogic*> en = b->keys();
     while (en.hasNext()) {
         return b->value(en.next());
     }
     return NULL;
 }

 /*public*/ SignalMastLogic* SmlBeanTableDataModel::getLogicFromRow(int row) const
 {
     QHash<SignalMastLogic*, SignalMast*>* b = act->signalMastLogicList->at(row);
     QListIterator<SignalMastLogic*> en = b->keys();
     while (en.hasNext()) {
         return en.next();
     }
     return NULL;
 }

 //@Override
 /*public*/ int SmlBeanTableDataModel::getPreferredWidth(int col) {
     switch (col) {
         case SOURCECOL:
             return  JTextField(10).sizeHint().width();
         case MAXSPEEDCOL:
             return  JTextField(10).sizeHint().width();
         case COMCOL:
             return 75;
         case DESTCOL:
             return  JTextField(10).sizeHint().width();
         case EDITLOGICCOL: // not actually used due to the configureTable, setColumnToHoldButton, configureButton
             return  JTextField(6).sizeHint().width();
         case DELCOL: // not actually used due to the configureTable, setColumnToHoldButton, configureButton
             return  JTextField(5).sizeHint().width();
         case DESTAPPCOL:
             return  JTextField(10).sizeHint().width();
         case SOURCEAPPCOL:
             return  JTextField(10).sizeHint().width();
         case ENABLECOL:
             return  JTextField(5).sizeHint().width();
         default:
             //log.warn("Unexpected column in getPreferredWidth: "+col);
             return  JTextField(8).sizeHint().width();
     }
 }

 /*public*/ void SmlBeanTableDataModel::configureTable(JTable* table) {
     setColumnToHoldButton(table, EDITLOGICCOL,
             new QPushButton(tr("Edit")));
     //table.getTableHeader().setReorderingAllowed(true);

     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
     //table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

     // resize columns as requested
     table->createDefaultColumnsFromModel();
     for (int i = 0; i < table->model()->columnCount(); i++) {
         int width = getPreferredWidth(i);
         table->getColumnModel()->getColumn(i)->setPreferredWidth(width);
     }
     //table.sizeColumnsToFit(-1);
     table->resizeColumnsToContents();

     // configValueColumn(table);
     configDeleteColumn(table);
 }

// /*public*/ NamedBean* SmlBeanTableDataModel::getBySystemName(QString /*name*/) const {
//     return NULL;
// }

// /*public*/ NamedBean* SmlBeanTableDataModel::getByUserName(QString /*name*/) {
//     return NULL;
// }

 /*synchronized*/ /*public*/ void SmlBeanTableDataModel::dispose() {

     //getManager().removePropertyChangeListener(this);
     disconnect(getManager(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if (act->signalMastLogicList != NULL) {
         for (int i = 0; i < act->signalMastLogicList->size(); i++) {
             SignalMastLogic* b = getLogicFromRow(i);
             if (b != NULL) {
                 b->removePropertyChangeListener((PropertyChangeListener*)this);
//                 disconnect(b->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             }
         }
     }
 }

 /*public*/ int SmlBeanTableDataModel::rowCount(const QModelIndex &/*parent*/) const
 {
     return act->signalMastLogicList->size();
 }

 //@Override
 /*public*/ QVariant SmlBeanTableDataModel::data(const QModelIndex &index, int role) const
 {
  int col = index.column();
  int row = index.row();
  SignalMastLogic* b = getLogicFromRow(row);

  if(role == Qt::CheckStateRole)
  {
   if(col == ENABLECOL)
   {
    return (b != NULL) ? (b->isEnabled(getDestMastFromRow(row))?Qt::Checked:Qt::Unchecked) : QVariant();
   }
  }
  if(role == Qt::DisplayRole)
  {
     // some error checking
     if (row >= act->signalMastLogicList->size()) {
         log->debug("row is greater than list size");
         return QVariant();
     }
     switch (col) {
         case SOURCECOL:
             return getLogicFromRow(row)->getSourceMast()->getDisplayName();
         case DESTCOL:  // return user name
             // sometimes, the TableSorter invokes this on rows that no longer exist, so we check
             return (b != NULL) ? getDestMastFromRow(row)->getDisplayName() : NULL;
         case SOURCEAPPCOL:  //
             return (b != NULL) ? b->getSourceMast()->getAspect() : NULL;
         case DESTAPPCOL:  //
             return (b != NULL) ? getDestMastFromRow(row)->getAspect() : NULL;
         case COMCOL:
             return (b != NULL) ? b->getComment(getDestMastFromRow(row)) : NULL;
         case DELCOL:
             return tr("Delete");
         case EDITLOGICCOL:
             return tr("Edit");
         case MAXSPEEDCOL:
             return  (b != nullptr) ? b->getMaximumSpeed(getDestMastFromRow(row)) : 0.0;
         default:
             //log.error("internal state inconsistent with table requst for "+row+" "+col);
             break;;
     }
  }
     return BeanTableDataModel::data(index, role);
 }

 /*protected*/ void SmlBeanTableDataModel::configDeleteColumn(JTable* table) {
     // have the delete column hold a button
     setColumnToHoldButton(table, DELCOL,
             new QPushButton(tr("Delete")));
 }

 /*protected*/ QString SmlBeanTableDataModel::getBeanType() {
     return "Signal Mast Logic";
 }

 //@Override
 /*protected*/ void SmlBeanTableDataModel::showPopup(QMouseEvent* e) {

 }


 /*protected*/ void SignalMastLogicTableAction::setTitle() {
     f->setTitle(tr("TitleSignalMastLogicTable"));
 }

 //@Override
 /*protected*/ QString SignalMastLogicTableAction::helpTarget() {
     return "package.jmri.jmrit.beantable.SignalMastLogicTable";// NOI18N
 }

 /*protected*/ void SignalMastLogicTableAction::addPressed() {
     sigLog->setMast(NULL, NULL);
     sigLog->actionPerformed(/*e*/);
 }


 void SignalMastLogicTableAction::autoCreatePairs(/*jmri.util.JmriJFrame f*/) {
     if (!((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled()) {
         int response = JOptionPane::showConfirmDialog(NULL, tr("Layout Block routing is not enabled\nDo you want to enable it?"));
         if (response == 0)
         {
             ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->enableAdvancedRouting(true);
             JOptionPane::showMessageDialog(NULL, tr("Layout Block routing has been enabled."));
         } else {
             return;
         }
     }
     signalMastLogicFrame = new JmriJFrameX(tr("DiscoverSignalMastPairs"), false, false);
     //signalMastLogicFrame->resize(NULL);
     QWidget* panel1 = new QWidget();
     QVBoxLayout* panel1Layout = new QVBoxLayout(panel1);
     sourceLabel = new QLabel(tr("Discovering Signal Mast Pairs"));
     panel1Layout->addWidget(sourceLabel);
     signalMastLogicFrame->setContentPane(panel1);
     signalMastLogicFrame->adjustSize();
     signalMastLogicFrame->setVisible(true);

     QCheckBox* genSect = new QCheckBox(tr("Generate Sections from Mast Pairs"));
     genSect->setToolTip(tr("Generate sections that match the Signaling Logic, for later use with Transits and AutoDispatcher"));
     QString params = tr("Do you want to automatically generate\nthe Signal Mast Pairs and Logic, based\nupon the track plan in the Layout Editor?"); //, " ", genSect};
#if 0 // TODO:
     int retval = JOptionPane.showConfirmDialog(f, params, tr("AutoGenSignalMastLogicTitle"),
             JOptionPane.YES_NO_OPTION);

     if (retval == 0)
     {
         InstanceManager::signalMastLogicManagerInstance().addPropertyChangeListener(propertyGenerateListener);
         // This process can take some time, so we do split it off then return to Swing/AWT
         Runnable r = new Runnable() {
             /*public*/ void run() {
                 //While the global discovery is taking place we remove the listener as this can result in a race condition.
                 suppressUpdate = true;
                 try {
                     InstanceManager::signalMastLogicManagerInstance().automaticallyDiscoverSignallingPairs();
                 } catch (jmri.JmriException e) {
                     // Notify of problem
                     try {
                         javax.swing.SwingUtilities.invokeAndWait(()->{
                             InstanceManager::signalMastLogicManagerInstance().removePropertyChangeListener(propertyGenerateListener);
                             JOptionPane.showMessageDialog(NULL, e.toString());
                             signalMastLogicFrame.setVisible(false);
                         });
                     } catch (java.lang.reflect.InvocationTargetException ex) {
                         log.error("failed to notify of problem with automaticallyDiscoverSignallingPairs", ex );
                     } catch (InterruptedException ex) {
                         log.error("interrupted while notifying of problem with automaticallyDiscoverSignallingPairs", ex );
                     }
                 }

                 // process complete, update GUI
                 try {
                     javax.swing.SwingUtilities.invokeAndWait(()->{
                         m.updateNameList();
                         suppressUpdate = false;
                         m.fireTableDataChanged();
                         if (genSect.isSelected()) {
                             ((jmri.managers.DefaultSignalMastLogicManager)
                                 InstanceManager::signalMastLogicManagerInstance()).generateSection();
                         }
                     });
                 } catch (java.lang.reflect.InvocationTargetException ex) {
                     log.error("failed to update at end of automaticallyDiscoverSignallingPairs", ex );
                 } catch (InterruptedException ex) {
                     log.error("interrupted during update at end of automaticallyDiscoverSignallingPairs", ex );
                 }
             }
         };
         Thread thr = new Thread(r, "Discover Signal Mast Logic");  // NOI18N
         thr.start();

     }
     else
#endif
     {
         signalMastLogicFrame->setVisible(false);
     }
 }
#if 0
 /*protected*/ transient PropertyChangeListener propertyGenerateListener = new PropertyChangeListener() {
     /*public*/ void propertyChange(PropertyChangeEvent evt) {
         if (evt.getPropertyName() == ("autoGenerateComplete")) {// NOI18N
             if (signalMastLogicFrame != NULL) {
                 signalMastLogicFrame.setVisible(false);
             }
             InstanceManager::signalMastLogicManagerInstance().removePropertyChangeListener(this);
             JOptionPane.showMessageDialog(NULL, tr("SignalMastPairGenerationComplete"));
         } else if (evt.getPropertyName() == ("autoGenerateUpdate")) {// NOI18N
             sourceLabel.setText((QString) evt.getNewValue());
             signalMastLogicFrame.pack();
             signalMastLogicFrame.repaint();
         }
     }
 };

}
#endif
 /*protected*/ QString SignalMastLogicTableAction::getClassName() {
     return "jmri.jmrit.beantable.SignalMastLogicTableAction";
 }


