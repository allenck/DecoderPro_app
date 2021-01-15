#include "signallingpanel.h"
#include "instancemanager.h"
#include "signalmast.h"
#include "abstractsignalmast.h"
#include "signalmastlogic.h"
#include "signalmastmanager.h"
#include "defaultsignalmastlogic.h"
#include "defaultsignalmastmanager.h"
#include "signalspeedmap.h"
#include <QVBoxLayout>
#include "../Tables/jmribeancombobox.h"
#include "defaultsignalmastlogicmanager.h"
#include "proxyturnoutmanager.h"
#include "block.h"
#include <QTableView>
#include "QHeaderView"
#include "../LayoutEditor/layoutblockmanager.h"
#include <QMessageBox>
#include <QVBoxLayout>

//SignallingPanel::SignallingPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version	$Revision: 22033 $
 */
///*public*/ class SignallingPanel extends jmri.util.swing.JmriPanel {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.SignallingBundle");
/*private*/ /*static*/ QStringList SignallingPanel::blockInputModes =  QStringList() << tr("UnOccupied")<< tr("Occupied");
/*private*/ /*static*/ QList<int> SignallingPanel::blockInputModeValues =  QList<int>() << Block::UNOCCUPIED <<  Block::OCCUPIED;
/*private*/ /*static*/ QString SignallingPanel::SET_TO_ACTIVE = tr("Active");
/*private*/ /*static*/ QString SignallingPanel::SET_TO_INACTIVE = tr("Inactive");
/*private*/ /*static*/ QString SignallingPanel::SET_TO_CLOSED = tr("Closed");//((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText();
/*private*/ /*static*/ QString SignallingPanel::SET_TO_THROWN = tr("Thrown");//((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getThrownText();
/*private*/ /*static*/ QString SignallingPanel::SET_TO_UNOCCUPIED = tr("UnOccupied");
/*private*/ /*static*/ QString SignallingPanel::SET_TO_OCCUPIED = tr("Occupied");
/*private*/ /*static*/ QString SignallingPanel::SET_TO_ANY = tr("Any State");

/*private*/ /*static*/ int SignallingPanel::ROW_HEIGHT = 0;

void SignallingPanel::init()
{
 fixedSourceMastLabel = new QLabel();
 fixedDestMastLabel = new QLabel();
 sourceMastLabel = new QLabel(tr("Source Mast"));
 destMastLabel = new QLabel(tr("Destination Mast"));
 updateButton = new QPushButton(tr("Update Signal Logic"));
 useLayoutEditor = new QCheckBox(tr("Use Layout Editor Paths"));
 useLayoutEditorTurnout = new QCheckBox(tr("Use Turnout Details From Layout Editor"));
 useLayoutEditorBlock = new QCheckBox(tr("Use Block Details From Layout Editor"));
 allowAutoMastGeneration = new QCheckBox(tr("Allow the Logic to Automatically Determine ConflictingSignalMasts"));
 lockTurnouts = new QCheckBox(tr("Lock Turnouts when SignalMast Logic is Active"));

 smm = (SignalMastManager*)InstanceManager::getDefault("SignalMastManager");

 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");

 p2xc = NULL;
 p2xt = NULL;
 p2xs = NULL;
 p2xm = NULL;
 _automaticBlockList = new QList<AutoBlockList*>();

 _automaticTurnoutList = new QList<AutoTurnoutList*>();

 _automaticSignalMastList = new QList<AutoSignalMastList*>();
 p2xb = new QWidget();
 selGroup = NULL;
 allButton = NULL;
 includedButton = NULL;

 showAll = true;   // false indicates show only included items
 p2xa = new QWidget();
 p2xsm = new QWidget();
 sourceMast = NULL;
 destMast = NULL;
 sml= NULL;
}

/*public*/ SignallingPanel::SignallingPanel(QFrame* frame, QWidget* parent) : QWidget(parent)
{
 common(NULL, NULL, frame);
}

/*public*/ SignallingPanel::SignallingPanel(SignalMast* source, SignalMast* dest, QFrame* frame, QWidget* parent) : QWidget(parent)
{
 //super();
 jFrame = frame;
 common(source, dest, frame);
}
void SignallingPanel::common(SignalMast* source, SignalMast* dest, QFrame* /*frame*/)
{
 init();
 QLabel* mastSpeed = new QLabel();

 if (source!=NULL)
 {
  this->sourceMast = source;
  this->sml = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(source);
  fixedSourceMastLabel = new QLabel(sourceMast->getDisplayName());
 }
 if ((dest!=NULL) && (sml!=NULL))
 {
  this->destMast=dest;
  if (!((DefaultSignalMastLogic*)sml)->isDestinationValid(dest))
  {
   ((DefaultSignalMastLogic*)sml)->setDestinationMast(dest);
  }

  fixedDestMastLabel = new QLabel(destMast->getDisplayName());
  useLayoutEditor->setChecked(((DefaultSignalMastLogic*)sml)->useLayoutEditor(destMast));
  useLayoutEditorTurnout->setChecked(((DefaultSignalMastLogic*)sml)->useLayoutEditorTurnouts(destMast));
  useLayoutEditorBlock->setChecked(((DefaultSignalMastLogic*)sml)->useLayoutEditorBlocks(destMast));
  allowAutoMastGeneration->setChecked(((DefaultSignalMastLogic*)sml)->allowAutoMaticSignalMastGeneration(destMast));
  lockTurnouts->setChecked(((DefaultSignalMastLogic*)sml)->isTurnoutLockAllowed(destMast));

  float pathSpeed = ((DefaultSignalMastLogic*)sml)->getMaximumSpeed(dest);
  if(pathSpeed == 0.0f)
  {
    mastSpeed->setText(tr("PathSpeed") + " : None Set");
  }
  else
  {
   QString speed = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getNamedSpeed(pathSpeed);
   if (speed != NULL)
        mastSpeed->setText(tr("PathSpeed") + " : " + speed);
   else
        mastSpeed->setText(tr("PathSpeed") + " : " + QString::number(pathSpeed));
  }
 }
 else if (dest==NULL)
 {
  sml=NULL;
 }

 sourceMastBox = new JmriBeanComboBox(smm, sourceMast, JmriBeanComboBox::DISPLAYNAME);
 destMastBox = new JmriBeanComboBox(smm, destMast, JmriBeanComboBox::DISPLAYNAME);
 //signalMastCombo(sourceMastBox, sourceMast);
 //signalMastCombo(destMastBox, destMast);

// QWidget* containerPanel = new QWidget();
// containerPanel->setLayout(new /*BorderLayout()*/QVBoxLayout());
 QVBoxLayout* containerPanelLayout = new QVBoxLayout;

// QWidget* header = new QWidget();
// header->setLayout(new QVBoxLayout(header/*, BoxLayout.Y_AXIS*/));
 QVBoxLayout* headerLayout = new QVBoxLayout;

// QWidget* sourcePanel = new QWidget();
// sourcePanel->setLayout(new QHBoxLayout());
 QHBoxLayout* sourcePanelLayout = new QHBoxLayout;
 sourcePanelLayout->addWidget(sourceMastLabel);
 sourcePanelLayout->addWidget(sourceMastBox);
 sourcePanelLayout->addWidget(fixedSourceMastLabel);

 headerLayout->addLayout(sourcePanelLayout);

// QWidget* destPanel = new QWidget();
// destPanel->setLayout(new QHBoxLayout());
 QHBoxLayout* destPanelLayout = new QHBoxLayout;
 destPanelLayout->addWidget(destMastLabel);
 destPanelLayout->addWidget(destMastBox);
 destPanelLayout->addWidget(fixedDestMastLabel);

// destMastBox.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (useLayoutEditor.isSelected()){
//                try {
//                    bool valid = InstanceManager.layoutBlockManagerInstance().getLayoutBlockConnectivityTools().checkValidDest(sourceMastBox.getSelectedBean(),
//                        destMastBox.getSelectedBean());
//                    if(!valid)
//                        JOptionPane.showMessageDialog(NULL, tr("ErrorUnReachableDestination"));
//                }
//                catch (jmri.JmriException je){
//                    JOptionPane.showMessageDialog(NULL, tr("WarningUnabletoValidate"));
//                }
//            }
//        }
//    });
 connect(destMastBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_destMastBox_currentSelectionChanged(int)));
 headerLayout->addLayout(destPanelLayout);
 headerLayout->addWidget(mastSpeed);

//        QWidget* srcSigSpeed = new QWidget();

 //QWidget* editor = new QWidget();
 QVBoxLayout* editorLayout = new QVBoxLayout;
 //editor->setLayout(editorLayout = new QVBoxLayout(editor/*, BoxLayout.Y_AXIS*/));
 editorLayout->addWidget(useLayoutEditor);

 editorLayout->addWidget(useLayoutEditorTurnout);
 editorLayout->addWidget(useLayoutEditorBlock);
 useLayoutEditorBlock->setVisible(false);
 useLayoutEditorTurnout->setVisible(false);

// useLayoutEditor.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {

//            useLayoutEditorBlock->setVisible(useLayoutEditor.isSelected());
//            useLayoutEditorTurnout->setVisible(useLayoutEditor.isSelected());
//            // Setup for display of all Turnouts, if needed
//            bool valid = false;
//            if (useLayoutEditor.isSelected()){
//                jFrame.pack();
//                if (!InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled()){
//                   int response;

//                    response = JOptionPane.showConfirmDialog(NULL, tr("EnableLayoutBlockRouting"));
//                    if (response == 0){
//                        InstanceManager.layoutBlockManagerInstance().enableAdvancedRouting(true);
//                        JOptionPane.showMessageDialog(NULL, tr("LayoutBlockRoutingEnabled"));
//                    }
//                }

//                if ((sml!=NULL) && (destMast!=NULL)){
//                    try {
//                        ((DefaultSignalMastLogic*)sml)->useLayoutEditor(useLayoutEditor.isSelected(), destMast);
//                    } catch (jmri.JmriException je){
//                        JOptionPane.showMessageDialog(NULL, je.toString());
//                    }
//                    try {
//                        valid = InstanceManager.layoutBlockManagerInstance().getLayoutBlockConnectivityTools().checkValidDest(sourceMastBox.getSelectedBean(),
//                            destMastBox.getSelectedBean());
//                        if(!valid){
//                            JOptionPane.showMessageDialog(NULL, tr("ErrorUnReachableDestination"));
//                        }
//                    }
//                    catch (jmri.JmriException je){
//                        JOptionPane.showMessageDialog(NULL, tr("WarningUnabletoValidate"));
//                    }
//                }
//            }
//        }

//    });
 connect(useLayoutEditor, SIGNAL(toggled(bool)), this, SLOT(on_useLayoutEditor_toggled(bool)));
 headerLayout->addLayout(editorLayout);
 headerLayout->addWidget(allowAutoMastGeneration);
 headerLayout->addWidget(lockTurnouts);
 QWidget* py = new QWidget();
 py->setLayout(new QHBoxLayout());
 py->layout()->addWidget(new QLabel(tr("Show")));
 selGroup = new QButtonGroup();
 allButton = new QRadioButton(tr("All"));
 allButton->setChecked(true);
 selGroup->addButton(allButton);
 py->layout()->addWidget(allButton);
//    allButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of all Turnouts, if needed
//                if (!showAll) {
//                    showAll = true;
//                    _blockModel.fireTableDataChanged();
//                    _turnoutModel.fireTableDataChanged();
//                    _signalMastModel.fireTableDataChanged();
//                    _sensorModel.fireTableDataChanged();
//                }
//            }
//        });
 connect(allButton, SIGNAL(toggled(bool)), this, SLOT(on_allButton_toggled(bool)));
 includedButton = new QRadioButton(tr("Included")/*,false*/);
 selGroup->addButton(includedButton);
 py->layout()->addWidget(includedButton);
//    includedButton->layout()->addWidgetActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of included Turnouts only, if needed
//                if (showAll) {
//                    showAll = false;
//                    initializeIncludedList();
//                    _blockModel.fireTableDataChanged();
//                    _turnoutModel.fireTableDataChanged();
//                    _signalMastModel.fireTableDataChanged();
//                    _sensorModel.fireTableDataChanged();
//                }
//            }
//        });
 connect(includedButton, SIGNAL(toggled(bool)), this, SLOT(on_includedButton_toggled(bool)));
 py->layout()->addWidget(new QLabel("  " + tr("Turnouts and Sensors")));
 headerLayout->addWidget(py);

 containerPanelLayout->addLayout(headerLayout/*, BorderLayout.NORTH*/);

//        QWidget* sensorPanel = new QWidget();
//        QWidget* signalMastPanel = new QWidget();

    QTabWidget* detailsTab = new QTabWidget();
    detailsTab->addTab( buildBlocksPanel(),tr(("Blocks")));
    detailsTab->addTab(buildTurnoutPanel(), tr("Turnouts"));
    detailsTab->addTab( buildSensorPanel(),tr(("Sensors")));
    detailsTab->addTab(buildSignalMastPanel(), tr(("SignalMasts")));

    containerPanelLayout->addWidget(detailsTab/*, BorderLayout.CENTER*/);

    QWidget* footer = new QWidget();
    footer->setLayout(new QHBoxLayout());
    footer->layout()->addWidget(updateButton);
//    updateButton->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            updatePressed(e);
//        }
//    });
 updateButton->setToolTip(tr("Change this Route and leave Edit mode"));
 updateButton->setVisible(true);
 QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(updateButton->sizePolicy().hasHeightForWidth());
 updateButton->setSizePolicy(sizePolicy);
 connect(updateButton, SIGNAL(clicked()), this, SLOT(updatePressed()));

 containerPanelLayout->addWidget(footer/*, BorderLayout.SOUTH*/);
 QVBoxLayout* thisLayout;
 if(layout()== NULL)
  setLayout(thisLayout =new QVBoxLayout());
 else thisLayout = (QVBoxLayout*)layout();
thisLayout->addLayout(containerPanelLayout);
 if(sourceMast!=NULL)
 {
  fixedSourceMastLabel->setVisible(true);
  sourceMastBox->setVisible(false);
 }
 else
 {
  fixedSourceMastLabel->setVisible(false);
  sourceMastBox->setVisible(true);
 }
 if ((sml!=NULL) && (destMast!=NULL))
 {
  fixedDestMastLabel->setVisible(true);
  destMastBox->setVisible(false);
  useLayoutEditorBlock->setVisible(useLayoutEditor->isChecked());
  useLayoutEditorTurnout->setVisible(useLayoutEditor->isChecked());
  initializeIncludedList();
  editDetails();
 }
 else
 {
  useLayoutEditorBlock->setVisible(useLayoutEditor->isChecked());
  useLayoutEditorTurnout->setVisible(useLayoutEditor->isChecked());
  fixedDestMastLabel->setVisible(false);
  destMastBox->setVisible(true);
 }
}


QWidget* SignallingPanel::buildBlocksPanel()
{
 QWidget* blockPanel = new QWidget();
#if 1
 QVBoxLayout* blockPanelLayout;
 blockPanel->setLayout(blockPanelLayout = new QVBoxLayout(blockPanel/*, BoxLayout.Y_AXIS*/));

 BlockManager* bm = ((BlockManager*)InstanceManager::getDefault("BlockManager"));
 QStringList systemNameList = bm->getSystemNameList();
 _manualBlockList =  QList<ManualBlockList*> (); //systemNameList.size());
 QStringListIterator iter(systemNameList);
 while (iter.hasNext())
 {
  QString systemName = iter.next();
  //String userName = bm.getBySystemName(systemName).getUserName();
  _manualBlockList.append(new ManualBlockList((Block*)bm->getBySystemName(systemName),this));
 }

 if ((sml!=NULL) && (destMast!=NULL))
 {
  QList<Block*> blkList = ((DefaultSignalMastLogic*)sml)->getAutoBlocks(destMast);
  _automaticBlockList = new QList <AutoBlockList*> (); //blkList.size());
  QListIterator<Block*> iterBlk(blkList);
  while (iterBlk.hasNext())
  {
   Block* blk = iterBlk.next();

   AutoBlockList* blockitem =  new AutoBlockList(blk, this);
   blockitem->setState(((DefaultSignalMastLogic*)sml)->getAutoBlockState(blk, destMast));

   _automaticBlockList->append(blockitem);
  }
 }
 QWidget* p2xc = new QWidget();  //this hides a field
 QHBoxLayout* p2xcLayout;
 p2xc->setLayout(p2xcLayout = new QHBoxLayout());
    //p2xc = new QWidget();
 QWidget* p2xcSpace = new QWidget();
 p2xcSpace->setLayout(new QVBoxLayout(p2xcSpace/*, BoxLayout.Y_AXIS*/));
 p2xcSpace->layout()->addWidget(new QLabel("XXX"));
 p2xcLayout->addWidget(p2xcSpace);
 QWidget* p21c = new QWidget();
 QVBoxLayout* p21cLayout;
 p21c->setLayout(p21cLayout = new QVBoxLayout(p21c/*, BoxLayout.Y_AXIS*/));
 p21cLayout->addWidget(new QLabel(tr("Please select")));
 p21cLayout->addWidget(new QLabel(tr("Blocks to be ")));
 p21cLayout->addWidget(new QLabel(tr("checked")));
 p2xcLayout->addLayout(p21cLayout);

 _blockModel = new BlockModel(this);
 JTable* manualBlockTable = new JTable(_blockModel);
 QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(manualBlockTable->sizePolicy().hasHeightForWidth());
 manualBlockTable->setSizePolicy(sizePolicy);
 //jmri.util.JTableUtil.sortableDataModel(_blockModel);
//    try
//    {
//        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)manualBlockTable.getModel());
//        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel.setSortingStatus(BlockModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
 //manualBlockTable->setModel(_blockModel);
 manualBlockTable->setSelectionMode(QAbstractItemView::SingleSelection);
 manualBlockTable->setSelectionBehavior(QAbstractItemView::SelectRows);
 manualBlockTable->setEnabled(true);
 //manualBlockTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
 manualBlockTable->setMinimumSize(280,100);
// QComboBox* stateCCombo = new QComboBox();
// stateCCombo->addItem(SET_TO_UNOCCUPIED);
// stateCCombo->addItem(SET_TO_OCCUPIED);
// stateCCombo->addItem(SET_TO_ANY);
 QStringList blockStates;
 blockStates << SET_TO_UNOCCUPIED << SET_TO_OCCUPIED << SET_TO_ANY;
 //manualBlockTable->setItemDelegateForColumn(BlockModel::STATE_COLUMN, new SPComboBoxDelegate(blockStates));
 _blockModel->setColumnToHoldDelegate(manualBlockTable, BlockModel::STATE_COLUMN, new JComboBoxEditor(blockStates));

// TableColumnModel _manualBlockColumnModel = manualBlockTable.getColumnModel();
// TableColumn includeColumnC = _manualBlockColumnModel.
//                                        getColumn(BlockModel.INCLUDE_COLUMN);
 manualBlockTable->setColumnWidth(BlockModel::INCLUDE_COLUMN, 60);
 //includeColumnC.setResizable(false);
 //includeColumnC.setMinWidth(50);
 //includeColumnC.setMaxWidth(60);
//    TableColumn sNameColumnC = _manualBlockColumnModel.
//                                        getColumn(BlockModel.SNAME_COLUMN);
//    sNameColumnC.setResizable(true);
//    sNameColumnC.setMinWidth(75);
//    sNameColumnC.setMaxWidth(95);

//    TableColumn stateColumnC = _manualBlockColumnModel.
//                                        getColumn(BlockModel.STATE_COLUMN);
//    stateColumnC.setCellEditor(new DefaultCellEditor(stateCCombo));
//    stateColumnC.setResizable(false);
//    stateColumnC.setMinWidth(90);
//    stateColumnC.setMaxWidth(100);

 //_manualBlockScrollPane = new JScrollPane(manualBlockTable);
 //p2xc.add(_manualBlockScrollPane,BorderLayout.CENTER);
 p2xcLayout->addWidget(manualBlockTable);
    //contentPane.add(p2xc);
 blockPanelLayout->addWidget(p2xc);
 p2xc->setVisible(true);

 ROW_HEIGHT = manualBlockTable->getRowHeight();
 p2xcSpace->setVisible(false);


 QWidget* p2xaSpace = new QWidget();
 QVBoxLayout* p2xaSpaceLayout;
 p2xaSpace->setLayout(p2xaSpaceLayout = new QVBoxLayout(p2xaSpace/*, BoxLayout.Y_AXIS*/));
 p2xaSpaceLayout->addWidget(new QLabel("XXX"));
 QHBoxLayout* p2xbLayout;
 p2xb->setLayout(p2xbLayout = new QHBoxLayout());
 p2xbLayout->addLayout(p2xaSpaceLayout);
// QWidget* p21a = new QWidget();
// p21a->setLayout(new QVBoxLayout(p21a/*, BoxLayout.Y_AXIS*/));
 QVBoxLayout* p21aLayout = new QVBoxLayout;
 p21aLayout->addWidget(new QLabel(tr("These Blocks")));
 p21aLayout->addWidget(new QLabel(tr("are auto generated ")));
 p21aLayout->addWidget(new QLabel(tr("and can not be changed")));
 p2xbLayout->addLayout(p21aLayout);

 _autoBlockModel = new AutoBlockModel(this);
 QTableView* autoBlockTable = new QTableView();
 autoBlockTable->setSizePolicy(sizePolicy);
 //jmri.util.JTableUtil.sortableDataModel(_autoBlockModel);
 autoBlockTable->setModel(_autoBlockModel);
//    try
//    {
//        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)autoBlockTable.getModel());
//        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel.setSortingStatus(AutoBlockModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
 autoBlockTable->setSelectionMode(QAbstractItemView::NoSelection);
//    autoBlockTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
 autoBlockTable->setMinimumSize(280,100);

//    TableColumnModel _autoBlockColumnModel = autoBlockTable.getColumnModel();
//    TableColumn sNameColumnA = _autoBlockColumnModel.
//                                        getColumn(AutoBlockModel::SNAME_COLUMN);
//    sNameColumnA.setResizable(true);
//    sNameColumnA.setMinWidth(75);
//    sNameColumnA.setMaxWidth(95);

//    TableColumn stateColumnA = _autoBlockColumnModel.
//                                        getColumn(AutoBlockModel.STATE_COLUMN);
//    //stateColumnA.setCellEditor(new DefaultCellEditor(stateCCombo));
//    stateColumnA.setResizable(false);
//    stateColumnA.setMinWidth(90);
//    stateColumnA.setMaxWidth(100);

 //autoBlockScrollPane = new JScrollPane(autoBlockTable);
 //p2xb.add(_autoBlockScrollPane,BorderLayout.CENTER);
 p2xbLayout->addWidget(autoBlockTable);
 blockPanelLayout->addWidget(p2xb);
 p2xb->setVisible(true);

 ROW_HEIGHT = autoBlockTable->rowHeight(0);
 p2xaSpace->setVisible(false);
#endif

 return blockPanel;
}
void SignallingPanel::on_destMastBox_currentSelectionChanged(int)
{
 if (useLayoutEditor->isChecked())
 {
  try
  {
   bool valid = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(sourceMastBox->getSelectedBean(),
                            destMastBox->getSelectedBean(), LayoutBlockConnectivityTools::MASTTOMAST);
   if(!valid)
    //JOptionPane.showMessageDialog(NULL, tr("ErrorUnReachableDestination"));
       QMessageBox::critical(this, tr("Error"), tr("The Destination Mast is not directly reachable from the source Mast"));
  }
  catch (JmriException je)
  {
   //JOptionPane.showMessageDialog(NULL, tr("WarningUnabletoValidate"));
   QMessageBox::critical(this, tr("Error"), tr("It has not been possible to validate the path between the two SignalMasts"));
  }
 }
}
void SignallingPanel::on_allButton_toggled(bool bState)
{
 if(!bState) return;
 //Setup for display of all Turnouts, if needed
 if (!showAll)
 {
  showAll = true;
 _blockModel->fireTableDataChanged();
 _turnoutModel->fireTableDataChanged();
 _signalMastModel->fireTableDataChanged();
  _sensorModel->fireTableDataChanged();
 }
}
void SignallingPanel::on_includedButton_toggled(bool bState)
{
 if(!bState) return;
 // Setup for display of included Turnouts only, if needed
 if (showAll)
 {
    showAll = false;
    initializeIncludedList();
    _blockModel->fireTableDataChanged();
    _turnoutModel->fireTableDataChanged();
    _signalMastModel->fireTableDataChanged();
    _sensorModel->fireTableDataChanged();
 }
}

void SignallingPanel::on_useLayoutEditor_toggled(bool)
{
 useLayoutEditorBlock->setVisible(useLayoutEditor->isChecked());
 useLayoutEditorTurnout->setVisible(useLayoutEditor->isChecked());
 // Setup for display of all Turnouts, if needed
 bool valid = false;
 if (useLayoutEditor->isChecked())
 {
  //jFrame->pack();
  if (!static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
  {
//   int response;
//   response = JOptionPane.showConfirmDialog(NULL, tr("EnableLayoutBlockRouting"));
   switch(QMessageBox::question(this, tr("Question"), tr("Layout block routing is not enabled\n                                                     Do you want to enable it?"), QMessageBox::Yes | QMessageBox::No))
   {
   case QMessageBox::Yes:
    {
     static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->enableAdvancedRouting(true);
       //JOptionPane.showMessageDialog(NULL, tr("LayoutBlockRoutingEnabled"));
     QMessageBox::information(this, tr("Information"), tr(" Please close and reopen this window for the changes to take effect."));
    }
    break;
    default:
        break;
   }
  }

  if ((sml!=NULL) && (destMast!=NULL))
  {
   try
   {
    ((DefaultSignalMastLogic*)sml)->useLayoutEditor(useLayoutEditor->isChecked(), destMast);
   }
   catch (JmriException je)
   {
    //JOptionPane.showMessageDialog(NULL, je.toString());
    QMessageBox::critical(this, tr("Error"), je.getMessage());
   }
   try
   {
    valid = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(sourceMastBox->getSelectedBean(),
                destMastBox->getSelectedBean(), LayoutBlockConnectivityTools::MASTTOMAST);
    if(!valid)
    {
     //JOptionPane.showMessageDialog(NULL, tr("ErrorUnReachableDestination"));
     QMessageBox::critical(this, tr("Error"), tr("The Destination Mast is not directly reachable from the source Mast"));
    }
   }
   catch (JmriException je)
   {
    //JOptionPane.showMessageDialog(NULL, tr("WarningUnabletoValidate"));
    QMessageBox::critical(this, tr("Error"), je.getMessage());
   }
  }
 }
}

QWidget* SignallingPanel::buildTurnoutPanel(){

    QWidget* turnoutPanel = new QWidget();
#if 1

    turnoutPanel->setLayout(new QVBoxLayout(turnoutPanel/*, BoxLayout.Y_AXIS*/));

    TurnoutManager* bm = InstanceManager::turnoutManagerInstance();
    QStringList systemNameList = ((ProxyTurnoutManager*)bm)->getSystemNameList();
    _manualTurnoutList =  QList <ManualTurnoutList*> (); //systemNameList.size());
    QStringListIterator iter(systemNameList);
    while (iter.hasNext()) {
        QString systemName = iter.next();
        QString userName = ((ProxyTurnoutManager*)bm)->getBySystemName(systemName)->getUserName();
        _manualTurnoutList.append(new ManualTurnoutList(systemName, userName,this));
    }

    if ((sml!=NULL)  && (destMast!=NULL)){
        QList<Turnout*> turnList = ((DefaultSignalMastLogic*)sml)->getAutoTurnouts(destMast);
        _automaticTurnoutList = new QList <AutoTurnoutList*> (); //turnList.size());
        QListIterator<Turnout*> iterTurn(turnList);
        while (iterTurn.hasNext()) {
            Turnout* turn = iterTurn.next();
            QString systemName = turn->getSystemName();
            QString userName = turn->getUserName();
            AutoTurnoutList* turnitem = new AutoTurnoutList(systemName, userName, this);
            turnitem->setState(((DefaultSignalMastLogic*)sml)->getAutoTurnoutState(turn, destMast));
            _automaticTurnoutList->append(turnitem);
        }
    }

    p2xt = new QWidget();
    QHBoxLayout* p2xtLayout;
    p2xt->setLayout(p2xtLayout = new QHBoxLayout);
    QWidget* p2xcSpace = new QWidget();
    p2xcSpace->setLayout(new QVBoxLayout(p2xcSpace/*, BoxLayout.Y_AXIS*/));
    p2xcSpace->layout()->addWidget(new QLabel("XXX"));
    p2xtLayout->addWidget(p2xcSpace);
//    QWidget* p21c = new QWidget();
//    p21c->setLayout(new QVBoxLayout(p21c/*, BoxLayout.Y_AXIS*/));
    QVBoxLayout* p21cLayout = new QVBoxLayout;
    p21cLayout->addWidget(new QLabel("Please select"));
    p21cLayout->addWidget(new QLabel("Turnouts to be "));
    p21cLayout->addWidget(new QLabel("checked"));
    p2xtLayout->addLayout(p21cLayout);

    _turnoutModel = new TurnoutModel(this);
    JTable* manualTurnoutTable = new JTable(_turnoutModel);
    manualTurnoutTable->setSizePolicy(sizePolicy());
    //jmri.util.JTableUtil.sortableDataModel(_turnoutModel);
    //manualTurnoutTable->setModel(_turnoutModel);
//    try {
//        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)manualTurnoutTable.getModel());
//        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel.setSortingStatus(TurnoutModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
    manualTurnoutTable->setSelectionMode(QAbstractItemView::SingleSelection);
    manualTurnoutTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //manualTurnoutTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    manualTurnoutTable->setMinimumSize(280, 100);
//    QComboBox* stateCCombo = new QComboBox();
//    stateCCombo->addItem(SET_TO_THROWN);
//    stateCCombo->addItem(SET_TO_CLOSED);
//    stateCCombo->addItem(SET_TO_ANY);
    QStringList statesList;
    statesList << SET_TO_THROWN <<SET_TO_CLOSED << SET_TO_ANY;
    //manualTurnoutTable->setItemDelegateForColumn(SPTableModel::STATE_COLUMN, new SPComboBoxDelegate(statesList));
    _turnoutModel->setColumnToHoldDelegate(manualTurnoutTable, SPTableModel::STATE_COLUMN, new JComboBoxEditor(statesList));

//    TableColumnModel _manualTurnoutColumnModel = manualTurnoutTable.getColumnModel();
//    TableColumn includeColumnC = _manualTurnoutColumnModel.
//                                        getColumn(TurnoutModel.INCLUDE_COLUMN);
//    includeColumnC.setResizable(false);
//    includeColumnC.setMinWidth(50);
//    includeColumnC.setMaxWidth(60);
//    TableColumn sNameColumnC = _manualTurnoutColumnModel.
//                                        getColumn(TurnoutModel.SNAME_COLUMN);
//    sNameColumnC.setResizable(true);
//    sNameColumnC.setMinWidth(75);
//    sNameColumnC.setMaxWidth(95);

//    TableColumn stateColumnC = _manualTurnoutColumnModel.
//                                        getColumn(TurnoutModel.STATE_COLUMN);
//    stateColumnC.setCellEditor(new DefaultCellEditor(stateCCombo));
//    stateColumnC.setResizable(false);
//    stateColumnC.setMinWidth(90);
//    stateColumnC.setMaxWidth(100);

    //_manualTurnoutScrollPane = new JScrollPane(manualTurnoutTable);
    p2xt->layout()->addWidget(manualTurnoutTable);
    //contentPane.add(p2xc);
    turnoutPanel->layout()->addWidget(p2xt);
    p2xt->setVisible(true);

    ROW_HEIGHT = manualTurnoutTable->getRowHeight();
    p2xcSpace->setVisible(false);


    QWidget* p2xaSpace = new QWidget();
    QVBoxLayout* p2xaSpaceLayout;
    p2xaSpace->setLayout(p2xaSpaceLayout = new QVBoxLayout(p2xaSpace/*, BoxLayout.Y_AXIS)*/));
    p2xaSpaceLayout->addWidget(new QLabel("XXX"));
    QHBoxLayout* p2xaLayout;
    p2xa->setLayout(p2xaLayout = new QHBoxLayout());
    p2xaLayout->addLayout(p2xaSpaceLayout);
//    QWidget* p21a = new QWidget();
//    p21a->setLayout(new QVBoxLayout(p21a/*, BoxLayout.Y_AXIS*/));
    QVBoxLayout* p21aLayout = new QVBoxLayout;
    p21aLayout->addWidget(new QLabel("These Turnouts"));
    p21aLayout->addWidget(new QLabel("are auto generated "));
    p21aLayout->addWidget(new QLabel("and can not be changed"));
    p2xaLayout->addLayout(p21aLayout);

    _autoTurnoutModel = new AutoTurnoutModel(this);
    QTableView* autoTurnoutTable = new QTableView(); //) jmri.util.JTableUtil.sortableDataModel(_autoTurnoutModel);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(autoTurnoutTable->sizePolicy().hasHeightForWidth());
    autoTurnoutTable->setSizePolicy(sizePolicy);
    autoTurnoutTable->setModel(_autoTurnoutModel);
//    try {
//        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)autoTurnoutTable.getModel());
//        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel.setSortingStatus(AutoTurnoutModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
    autoTurnoutTable->setSelectionMode(QAbstractItemView::NoSelection);
    //autoTurnoutTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    autoTurnoutTable->setMinimumSize(280,100);

//    TableColumnModel _autoTurnoutColumnModel = autoTurnoutTable.getColumnModel();
//    TableColumn sNameColumnA = _autoTurnoutColumnModel.
//                                        getColumn(AutoTurnoutModel.SNAME_COLUMN);
//    sNameColumnA.setResizable(true);
//    sNameColumnA.setMinWidth(75);
//    sNameColumnA.setMaxWidth(95);

//    TableColumn stateColumnA = _autoTurnoutColumnModel.
//                                        getColumn(AutoTurnoutModel.STATE_COLUMN);
//    //stateColumnA.setCellEditor(new DefaultCellEditor(stateCCombo));
//    stateColumnA.setResizable(false);
//    stateColumnA.setMinWidth(90);
//    stateColumnA.setMaxWidth(100);

    //_autoTurnoutScrollPane = new JScrollPane(autoTurnoutTable);
    p2xaLayout->addWidget(autoTurnoutTable);
    //contentPane->layout()->addWidget(p2xa);
    turnoutPanel->layout()->addWidget(p2xa);
    p2xa->setVisible(true);

    ROW_HEIGHT = autoTurnoutTable->rowHeight(0);
    p2xaSpace->setVisible(false);

#endif
    return turnoutPanel;
}

QWidget* SignallingPanel::buildSensorPanel(){
    QWidget* sensorPanel = new QWidget();

    sensorPanel->setLayout(new QVBoxLayout(sensorPanel/*, BoxLayout.Y_AXIS*/));

    SensorManager* bm = InstanceManager::sensorManagerInstance();
    QStringList systemNameList = ((ProxySensorManager*)bm)->getSystemNameList();
    _manualSensorList =  QList <ManualSensorList*> (); //systemNameList.size());
    QStringListIterator iter (systemNameList);
    while (iter.hasNext()) {
        QString systemName = iter.next();
        QString userName = ((ProxySensorManager*)bm)->getBySystemName(systemName)->getUserName();
        _manualSensorList.append(new ManualSensorList(systemName, userName, this));
    }

    p2xs = new QWidget();
    QHBoxLayout* p2xsLayout;
    p2xs->setLayout(p2xsLayout = new QHBoxLayout());
    QWidget* p2xsSpace = new QWidget();
    p2xsSpace->setLayout(new QVBoxLayout(p2xsSpace/*, BoxLayout.Y_AXIS*/));
    p2xsSpace->layout()->addWidget(new QLabel("XXX"));
    p2xs->layout()->addWidget(p2xsSpace);
//    QWidget* p21c = new QWidget();
//    p21c->setLayout(new QVBoxLayout(p21c/*, BoxLayout.Y_AXIS*/));
    QVBoxLayout* p21cLayout = new QVBoxLayout;
    p21cLayout->addWidget(new QLabel("Please select"));
    p21cLayout->addWidget(new QLabel("Sensors to be "));
    p21cLayout->addWidget(new QLabel("checked"));
    p2xsLayout->addLayout(p21cLayout);

    _sensorModel = new SensorModel(this);
    JTable* manualSensorTable = new JTable(_sensorModel);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(manualSensorTable->sizePolicy().hasHeightForWidth());
    manualSensorTable->setSizePolicy(sizePolicy);
    //manualSensorTable->setModel(_sensorModel);
            //jmri.util.JTableUtil.sortableDataModel(_sensorModel);
//    try {
//        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)manualSensorTable.getModel());
//        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel.setSortingStatus(SensorModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
    manualSensorTable->setSelectionMode(QAbstractItemView::SingleSelection);
    manualSensorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //manualSensorTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    manualSensorTable->setMinimumSize(280,100);
//    QComboBox* stateCCombo = new QComboBox();
//    stateCCombo->addItem(SET_TO_INACTIVE);
//    stateCCombo->addItem(SET_TO_ACTIVE);
    QStringList statesList;
    statesList << SET_TO_INACTIVE << SET_TO_ACTIVE;
    //manualSensorTable->setItemDelegateForColumn(SPTableModel::STATE_COLUMN, new SPComboBoxDelegate( statesList));
    _sensorModel->setColumnToHoldDelegate(manualSensorTable, SPTableModel::STATE_COLUMN, new JComboBoxEditor( statesList) );

//    TableColumnModel _manualSensorColumnModel = manualSensorTable.getColumnModel();
//    TableColumn includeColumnC = _manualSensorColumnModel.
//                                        getColumn(SensorModel.INCLUDE_COLUMN);
//    includeColumnC.setResizable(false);
//    includeColumnC.setMinWidth(50);
//    includeColumnC.setMaxWidth(60);
//    TableColumn sNameColumnC = _manualSensorColumnModel.
//                                        getColumn(SensorModel.SNAME_COLUMN);
//    sNameColumnC.setResizable(true);
//    sNameColumnC.setMinWidth(75);
//    sNameColumnC.setMaxWidth(95);

//    TableColumn stateColumnC = _manualSensorColumnModel.
//                                        getColumn(SensorModel.STATE_COLUMN);
//    stateColumnC.setCellEditor(new DefaultCellEditor(stateCCombo));
//    stateColumnC.setResizable(false);
//    stateColumnC.setMinWidth(90);
//    stateColumnC.setMaxWidth(100);

    //_manualSensorScrollPane = new JScrollPane(manualSensorTable);
    p2xs->layout()->addWidget(manualSensorTable);

    sensorPanel->layout()->addWidget(p2xs);
    p2xs->setVisible(true);

    ROW_HEIGHT = manualSensorTable->getRowHeight();
    p2xsSpace->setVisible(false);

    return sensorPanel;
}


QWidget* SignallingPanel::buildSignalMastPanel(){
    QWidget* signalMastPanel = new QWidget();

    signalMastPanel->setLayout(new QVBoxLayout(signalMastPanel/*, BoxLayout.Y_AXIS*/));

    SignalMastManager* bm = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"));
    QStringList systemNameList = ((DefaultSignalMastManager*)bm)->getSystemNameList();
    _manualSignalMastList = QList <ManualSignalMastList*> (); //systemNameList.size());
    QStringListIterator iter (systemNameList);
    while (iter.hasNext()) {
        QString systemName = iter.next();
        _manualSignalMastList.append(new ManualSignalMastList(((DefaultSignalMastManager*)bm)->getBySystemName(systemName),this));
    }

    p2xm = new QWidget();
    QHBoxLayout* p2xmLayout;
    p2xm->setLayout(p2xmLayout = new QHBoxLayout());
    QWidget* p2xmSpace = new QWidget();
    p2xmSpace->setLayout(new QVBoxLayout(p2xmSpace/*, BoxLayout.Y_AXIS*/));
    p2xmSpace->layout()->addWidget(new QLabel("XXX"));
    p2xmLayout->addWidget(p2xmSpace);
//    QWidget* p21c = new QWidget();
//    p21c->setLayout(new QVBoxLayout(p21c/*, BoxLayout.Y_AXIS*/));
    QVBoxLayout* p21cLayout = new QVBoxLayout;
    p21cLayout->addWidget(new QLabel("Please select"));
    p21cLayout->addWidget(new QLabel("SignalMasts to be "));
    p21cLayout->addWidget(new QLabel("checked"));
    p2xmLayout->addLayout(p21cLayout);

    _signalMastModel = new SignalMastModel(this);

//    TableSorter sorter = new TableSorter(_signalMastModel);
    QTableView* manualSignalMastTable = new QTableView();
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(manualSignalMastTable->sizePolicy().hasHeightForWidth());
    manualSignalMastTable->setSizePolicy(sizePolicy);
    //_signalMastModel.makeJTable(sorter);
    //sorter.setTableHeader(manualSignalMastTable.getTableHeader());
    manualSignalMastTable->setModel(_signalMastModel);

    manualSignalMastTable->setSelectionMode(QAbstractItemView::SingleSelection);
    manualSignalMastTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    //manualSignalMastTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    manualSignalMastTable->setMinimumSize(280,100);

//    TableColumnModel _manualSignalMastColumnModel = manualSignalMastTable.getColumnModel();
//    TableColumn includeColumnC = _manualSignalMastColumnModel.
//                                        getColumn(SignalMastModel.INCLUDE_COLUMN);
//    includeColumnC.setResizable(false);
//    includeColumnC.setMinWidth(50);
//    includeColumnC.setMaxWidth(60);
//    TableColumn sNameColumnC = _manualSignalMastColumnModel.
//                                        getColumn(SignalMastModel.SNAME_COLUMN);
//    sNameColumnC.setResizable(true);
//    sNameColumnC.setMinWidth(75);
//    sNameColumnC.setMaxWidth(95);
    manualSignalMastTable->setItemDelegateForColumn(SPTableModel::STATE_COLUMN, new SignalMastComboBoxDelegate(this));

    //_manualSignalMastScrollPane = new JScrollPane(manualSignalMastTable);
    p2xm->layout()->addWidget(manualSignalMastTable);
    //contentPane.add(p2xm);
    signalMastPanel->layout()->addWidget(p2xm);
    p2xm->setVisible(true);

    ROW_HEIGHT = manualSignalMastTable->rowHeight(0);
    p2xmSpace->setVisible(false);


    QWidget* p2xaSpace = new QWidget();
    QVBoxLayout* p2xaSpaceLayout;
    p2xaSpace->setLayout(p2xaSpaceLayout = new QVBoxLayout(p2xaSpace/*, BoxLayout.Y_AXIS*/));
    p2xaSpaceLayout->addWidget(new QLabel("XXX"));
    QHBoxLayout* p2xsmLayout;
    p2xsm->setLayout(p2xsmLayout = new QHBoxLayout());
    p2xsmLayout->addLayout(p2xaSpaceLayout);
//    QWidget* p21a = new QWidget();
//    p21a->setLayout(new QVBoxLayout(p21a/*, BoxLayout.Y_AXIS*/));
    QVBoxLayout* p21aLayout = new QVBoxLayout;
    p21aLayout->addWidget(new QLabel("These SignalMasts"));
    p21aLayout->addWidget(new QLabel("are auto generated "));
    p21aLayout->addWidget(new QLabel("and can not be changed"));
    p2xsmLayout->addLayout(p21aLayout);

    _autoSignalMastModel = new AutoMastModel(this);
    QTableView* autoMastTable = new QTableView();
    autoMastTable->setSizePolicy(sizePolicy);
    //jmri.util.JTableUtil.sortableDataModel(_autoSignalMastModel);
//    try {
//        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)autoMastTable.getModel());
//        tmodel.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel.setSortingStatus(AutoMastModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
    autoMastTable->setModel(_autoSignalMastModel);
    autoMastTable->setSelectionMode(QAbstractItemView::SingleSelection);
    //autoMastTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    autoMastTable->setMinimumSize(280,100);

//    TableColumnModel _autoMastColumnModel = autoMastTable.getColumnModel();
//    TableColumn sNameColumnA = _autoMastColumnModel.
//                                        getColumn(AutoMastModel.SNAME_COLUMN);
//    sNameColumnA.setResizable(true);
//    sNameColumnA.setMinWidth(75);
//    sNameColumnA.setMaxWidth(95);

//    TableColumn stateColumnA = _autoMastColumnModel.
//                                        getColumn(AutoMastModel.STATE_COLUMN);
//    //stateColumnA.setCellEditor(new DefaultCellEditor(stateCCombo));
//    stateColumnA.setResizable(false);
//    stateColumnA.setMinWidth(90);
//    stateColumnA.setMaxWidth(100);

    //_autoSignalMastScrollPane = new JScrollPane(autoMastTable);
    p2xsm->layout()->addWidget(autoMastTable);
    //contentPane->layout()->addWidget(p2xa);
    signalMastPanel->layout()->addWidget(p2xsm);
    p2xsm->setVisible(true);

    ROW_HEIGHT = autoMastTable->rowHeight(0);
    p2xaSpace->setVisible(false);

    return signalMastPanel;
}

void SignallingPanel::updatePressed(/*ActionEvent e*/)
{
 sourceMast = (SignalMast*)sourceMastBox->getSelectedBean();
 destMast = (SignalMast*)destMastBox->getSelectedBean();

 if((sml==NULL) && (useLayoutEditor->isChecked()))
 {
  bool valid = false;
  try
  {
   valid = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(sourceMast,
                destMast, LayoutBlockConnectivityTools::MASTTOMAST);
  if(!valid)
  {
   //JOptionPane.showMessageDialog(NULL,  tr("ErrorUnReachableDestination"));
   QMessageBox::critical(this, tr("Error"), tr("The Destination Mast is not directly reachable from the source Mast"));
   return;
  }
 }
 catch (JmriException je)
  {
   //JOptionPane.showMessageDialog(NULL,  tr("WarningUnabletoValidate"));
   QMessageBox::critical(this, tr("Error"), je.getMessage());

  }
 }

 if (sml==NULL)
 {
  sml = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->newSignalMastLogic(sourceMast);
  ((DefaultSignalMastLogic*)sml)->setDestinationMast(destMast);
  fixedSourceMastLabel->setText(sourceMast->getDisplayName());
  fixedDestMastLabel->setText(destMast->getDisplayName());
  sourceMastBox->setVisible(false);
  destMastBox->setVisible(false);
  fixedSourceMastLabel->setVisible(true);
  fixedDestMastLabel->setVisible(true);
  _autoTurnoutModel->smlValid();
  _autoBlockModel->smlValid();
  _autoSignalMastModel->smlValid();
 }
 initializeIncludedList();
 ((DefaultSignalMastLogic*)sml)->allowAutoMaticSignalMastGeneration(allowAutoMastGeneration->isChecked(), destMast);
 bool layouteditorgen = true;
 try
 {
  ((DefaultSignalMastLogic*)sml)->useLayoutEditor(useLayoutEditor->isChecked(), destMast);
 }
 catch (JmriException je)
 {
  //JOptionPane.showMessageDialog(NULL, je.toString());
  QMessageBox::critical(this, tr("Error"), je.getMessage());

  layouteditorgen=false;
 }

 try
 {
  if(useLayoutEditor->isChecked())
  {
   ((DefaultSignalMastLogic*)sml)->useLayoutEditorDetails(useLayoutEditorTurnout->isChecked(), useLayoutEditorBlock->isChecked(), destMast);
  }
 }
 catch (JmriException ji)
 {
  if (layouteditorgen)
  {
   //JOptionPane.showMessageDialog(NULL, ji.toString());
   QMessageBox::critical(this, tr("Error"), ji.getMessage());

  }
 }
 QHash<Block*, int> hashBlocks =  QHash<Block*, int>();
 for(int i = 0; i<_includedManualBlockList.size(); i++)
 {
   Block* blk = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(_includedManualBlockList.at(i)->getSysName());
        hashBlocks.insert(blk, _includedManualBlockList.at(i)->getState());
 }
 ((DefaultSignalMastLogic*)sml)->setBlocks(hashBlocks, destMast);

 QHash<NamedBeanHandle<Turnout*>*, int> hashTurnouts =  QHash<NamedBeanHandle<Turnout*>*, int>();
 for(int i = 0; i<_includedManualTurnoutList.size(); i++)
 {
   QString turnoutName = _includedManualTurnoutList.at(i)->getDisplayName();
   Turnout* turnout = ((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getTurnout(_includedManualTurnoutList.at(i)->getDisplayName());
   NamedBeanHandle<Turnout*>* namedTurnout = nbhm->getNamedBeanHandle(turnoutName, turnout);
        hashTurnouts.insert(namedTurnout, _includedManualTurnoutList.at(i)->getState());
 }
 ((DefaultSignalMastLogic*)sml)->setTurnouts(hashTurnouts, destMast);

 QHash<NamedBeanHandle<Sensor*>*, int> hashSensors =  QHash<NamedBeanHandle<Sensor*>*, int>();
 for(int i = 0; i<_includedManualSensorList.size(); i++)
 {
  QString sensorName = _includedManualSensorList.at(i)->getDisplayName();
  Sensor* sensor = ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->getSensor(_includedManualSensorList.at(i)->getDisplayName());
  NamedBeanHandle<Sensor*>* namedSensor = nbhm->getNamedBeanHandle(sensorName, sensor);
  hashSensors.insert(namedSensor, _includedManualSensorList.at(i)->getState());
 }
 ((DefaultSignalMastLogic*)sml)->setSensors(hashSensors, destMast);

 QHash<SignalMast*, QString> hashSignalMast =  QHash<SignalMast*, QString>();
 for(int i = 0; i<_includedManualSignalMastList.size(); i++)
 {
  if(_includedManualSignalMastList.at(i)->getMast()==sourceMast || _includedManualSignalMastList.at(i)->getMast()==destMast)
  {
//   int mes = JOptionPane.showConfirmDialog(NULL, java.text.MessageFormat.format(tr("SignalMastCriteriaOwn"),
//                new Object[]{ _includedManualSignalMastList.get(i).getMast().getDisplayName() }),
//                tr("SignalMastCriteriaOwnTitle"),
//                JOptionPane.YES_NO_OPTION);
//            if(mes ==0) {
   int mes = QMessageBox::question(this, tr("Signalmast Error"),tr("Signalmast state to be checked against \"%1\" is either this logics source or destination mast\n                                                                   This may result in this logic not working correctly.\n                                                                   Are you sure you want to use it?").arg(_includedManualSignalMastList.at(i)->getMast()->getDisplayName()),QMessageBox::Yes | QMessageBox::No);
   if(mes == QMessageBox::Yes)
   {
    hashSignalMast.insert(_includedManualSignalMastList.at(i)->getMast(), _includedManualSignalMastList.at(i)->getSetToState());
   }
   else
   {
    _includedManualSignalMastList.at(i)->setIncluded(false);
    initializeIncludedList();
    _signalMastModel->fireTableDataChanged();
   }
  }
  else
  {
   hashSignalMast.insert(_includedManualSignalMastList.at(i)->getMast(),   _includedManualSignalMastList.at(i)->getSetToState());
  }
 }
 ((DefaultSignalMastLogic*)sml)->setMasts(hashSignalMast, destMast);
 ((DefaultSignalMastLogic*)sml)->allowTurnoutLock(lockTurnouts->isChecked(), destMast);
 ((DefaultSignalMastLogic*)sml)->initialise(destMast);
}

///*public*/ void initComponents(){

//}
#if 0
int blockModeFromBox(JComboBox box) {
    String mode = (String)box.getSelectedItem();
    int result = jmri.util.StringUtil.getStateFromName(mode, blockInputModeValues, blockInputModes);

    if (result<0) {
        log.warn("unexpected mode string in sensorMode: "+mode);
        throw  IllegalArgumentException();
    }
    return result;
}

void setBlockModeBox(int mode, JComboBox box) {
    String result = jmri.util.StringUtil.getNameFromState(mode, blockInputModeValues, blockInputModes);
    box.setSelectedItem(result);
}

#endif
void SignallingPanel::initializeIncludedList()
{
 _includedManualBlockList = QList <ManualBlockList*>();
 for (int i=0; i<_manualBlockList.size(); i++)
 {
  if (_manualBlockList.at(i)->isIncluded())
  {
   _includedManualBlockList.append(_manualBlockList.at(i));
  }
 }

 if ((sml!=NULL) && (destMast!=NULL))
 {
  QList<Block*> blkList = ((DefaultSignalMastLogic*)sml)->getAutoBlocks(destMast);
  _automaticBlockList = new QList <AutoBlockList*> ();//blkList.size());
  QListIterator<Block*> iter(blkList);
  while (iter.hasNext())
  {
   Block* blk = iter.next();
   AutoBlockList* newABlk = new AutoBlockList(blk,this);
   _automaticBlockList->append(newABlk);
   newABlk->setState(((DefaultSignalMastLogic*)sml)->getAutoBlockState(blk, destMast));
  }
 }

 _includedManualTurnoutList =  QList <ManualTurnoutList*>();
 for (int i=0; i<_manualTurnoutList.size(); i++)
 {
  if (_manualTurnoutList.at(i)->isIncluded())
  {
   _includedManualTurnoutList.append(_manualTurnoutList.at(i));
  }
 }

 if ((sml!=NULL) && (destMast!=NULL))
 {
  QList<Turnout*> turnList = ((DefaultSignalMastLogic*)sml)->getAutoTurnouts(destMast);
  _automaticTurnoutList = new QList <AutoTurnoutList*> ();//turnList.size());
  QListIterator<Turnout*> iter (turnList);
  while (iter.hasNext())
  {
   Turnout* turn = iter.next();
   QString systemName = turn->getSystemName();
   QString userName = turn->getUserName();
   AutoTurnoutList* newAturn = new AutoTurnoutList(systemName, userName, this);
   _automaticTurnoutList->append(newAturn);
   newAturn->setState(((DefaultSignalMastLogic*)sml)->getAutoTurnoutState(turn, destMast));
  }
 }

 _includedManualSensorList =  QList <ManualSensorList*>();
 for (int i=0; i<_manualSensorList.size(); i++)
 {
  if (_manualSensorList.at(i)->isIncluded())
  {
   _includedManualSensorList.append(_manualSensorList.at(i));
  }
 }

 _includedManualSignalMastList =  QList <ManualSignalMastList*>();
 for (int i=0; i<_manualSignalMastList.size(); i++)
 {
  if (_manualSignalMastList.at(i)->isIncluded())
  {
   _includedManualSignalMastList.append(_manualSignalMastList.at(i));
  }
 }

 if ((sml!=NULL)&& (destMast!=NULL))
 {
  QList<SignalMast*> mastList = ((DefaultSignalMastLogic*)sml)->getAutoMasts(destMast);
  _automaticSignalMastList = new QList <AutoSignalMastList*> ();//mastList.size());
  QListIterator<SignalMast*> iter(mastList);
  while (iter.hasNext())
  {
   SignalMast* mast = iter.next();
   AutoSignalMastList* newAmast = new AutoSignalMastList(mast, this);
   _automaticSignalMastList->append(newAmast);
   newAmast->setState(((DefaultSignalMastLogic*)sml)->getAutoSignalMastState(mast, destMast));
  }
 }
}
// to free resources when no longer used
/*public*/ void SignallingPanel::dispose(){
}


#if 0
/**
 * Cancels included only option
 */
void cancelIncludedOnly() {
    if (!showAll) {
        allButton.doClick();
    }
}

void signalMastCombo(JComboBox box, SignalMast select){
    box.removeAllItems();
    List<String> nameList = smm.getSystemNameList();
    String[] displayList = new String[nameList.size()];
    for(int i = 0; i<nameList.size(); i++){
        SignalMast sm = smm.getBySystemName(nameList.get(i));
        displayList[i] = sm.getDisplayName();
    }
    java.util.Arrays.sort(displayList);
    for(int i = 0; i<displayList.length; i++){
        box.addItem(displayList[i]);
        if ((select!=NULL) && (displayList[i].equals(select.getDisplayName()))){
            box.setSelectedIndex(i);
        }
    }
}
#endif

void SignallingPanel::editDetails(){
#if 0
    int setRow = 0;
    for (int i=_manualBlockList.size()-1; i>=0; i--) {
        ManualBlockList block = _manualBlockList.get(i);
        String tSysName = block.getSysName();
        Block blk = InstanceManager.blockManagerInstance().getBlock(tSysName);
        if (((DefaultSignalMastLogic*)sml)->isBlockIncluded(blk, destMast)) {
            block.setIncluded(true);
            block.setState(((DefaultSignalMastLogic*)sml)->getBlockState(blk, destMast));
            setRow = i;
        } else {
            block.setIncluded(false);
            block.setState(Block.UNOCCUPIED);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    _manualBlockScrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
    _blockModel.fireTableDataChanged();

    setRow = 0;
    for (int i=_manualTurnoutList.size()-1; i>=0; i--) {
        ManualTurnoutList turnout = _manualTurnoutList.get(i);
        String tSysName = turnout.getSysName();
        Turnout turn = InstanceManager.turnoutManagerInstance().getTurnout(tSysName);
        if (((DefaultSignalMastLogic*)sml)->isTurnoutIncluded(turn, destMast)) {
            turnout.setIncluded(true);
            turnout.setState(((DefaultSignalMastLogic*)sml)->getTurnoutState(turn, destMast));
            setRow = i;
        } else {
            turnout.setIncluded(false);
            turnout.setState(Turnout.CLOSED);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    _manualSensorScrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
    _sensorModel.fireTableDataChanged();

    setRow = 0;
    for (int i=_manualSensorList.size()-1; i>=0; i--) {
        ManualSensorList sensor = _manualSensorList.get(i);
        String tSysName = sensor.getSysName();
        Sensor sen = InstanceManager.sensorManagerInstance().getSensor(tSysName);
        if (((DefaultSignalMastLogic*)sml)->isSensorIncluded(sen, destMast)) {
            sensor.setIncluded(true);
            sensor.setState(((DefaultSignalMastLogic*)sml)->getSensorState(sen, destMast));
            setRow = i;
        } else {
            sensor.setIncluded(false);
            sensor.setState(Sensor.INACTIVE);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    _manualSensorScrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
    _sensorModel.fireTableDataChanged();

    setRow = 0;
    for (int i=_manualSignalMastList.size()-1; i>=0; i--) {
        ManualSignalMastList mast = _manualSignalMastList.get(i);
        SignalMast sigMast = _manualSignalMastList.get(i).getMast();
        if (((DefaultSignalMastLogic*)sml)->isSignalMastIncluded(sigMast, destMast)) {
            mast.setIncluded(true);
            mast.setSetToState(((DefaultSignalMastLogic*)sml)->getSignalMastState(sigMast, destMast));
            setRow = i;
        } else {
            mast.setIncluded(false);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    _manualSignalMastScrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
    _signalMastModel.fireTableDataChanged();
#endif
}
#if 1
//private abstract class SignalMastElement {

    SignalMastElement::SignalMastElement(SignallingPanel* self)
    {
        this->self = self;
    }

    SignalMastElement::SignalMastElement(QString sysName, QString userName, SignallingPanel* self) {
        _sysName = sysName;
        _userName = userName;
        _included = false;
        _setToState = Sensor::INACTIVE;
        this->self = self;
    }

    QString SignalMastElement::getSysName() {
        return _sysName;
    }
    QString SignalMastElement::getUserName() {
        return _userName;
    }

    QString SignalMastElement::getDisplayName() {
        QString name = getUserName();
        if (name != NULL && name.length() > 0) {
            return name;
        } else {
            return getSysName();
        }
    }

    bool SignalMastElement::isIncluded() {
        return _included;
    }

    void SignalMastElement::setIncluded(bool include) {
        _included = include;
    }
//    abstract String getSetToState();
//    abstract void setSetToState(String state);

    int SignalMastElement::getState() {
        return _setToState;
    }
    void SignalMastElement::setState(int state) {
        _setToState = state;
    }
//}
#endif
//private class ManualBlockList extends SignalMastElement {
    ManualBlockList::ManualBlockList(Block* block, SignallingPanel* self) : SignalMastElement(self) {
        this->block = block;
    }

    QString ManualBlockList::getSysName() {
        return block->getSystemName();
    }
    QString ManualBlockList::getUserName() {
        return block->getUserName();
    }

    bool ManualBlockList::getPermissiveWorking(){
        return block->getPermissiveWorking();
    }

    QString ManualBlockList::getBlockSpeed(){
        return block->getBlockSpeed();
    }

    QString ManualBlockList::getSetToState() {
        switch (_setToState) {
            case Block::OCCUPIED:
                return self->SET_TO_OCCUPIED;
            case Block::UNOCCUPIED:
                return self->SET_TO_UNOCCUPIED;
        }
        return self->SET_TO_ANY;
    }

    void ManualBlockList::setSetToState(QString state) {
        if (self->SET_TO_UNOCCUPIED==(state)) {
            _setToState = Block::UNOCCUPIED;
        } else if (self->SET_TO_OCCUPIED==(state)) {
            _setToState = Block::OCCUPIED;
        } else _setToState = 0x03;
    }
//}

//private class AutoBlockList extends ManualBlockList {
    AutoBlockList::AutoBlockList(Block* block, SignallingPanel* self) : ManualBlockList(block, self)
    {
        //super(block);
    }

    void AutoBlockList::setSetToState(QString /*state*/){ }
//}
///*private*/ class ManualTurnoutList extends SignalMastElement {
    ManualTurnoutList::ManualTurnoutList (QString sysName, QString userName, SignallingPanel* self) : SignalMastElement(sysName, userName,self)
    {
        //super(sysName, userName);
    }
    QString ManualTurnoutList::getSetToState() {
        switch (_setToState) {
            case Turnout::THROWN:
                return self->SET_TO_THROWN;
            case Turnout::CLOSED:
                return self->SET_TO_CLOSED;
        }
        return self->SET_TO_ANY;
    }

    void ManualTurnoutList::setSetToState(QString state) {
        if (self->SET_TO_THROWN==(state)) {
            _setToState = Turnout::THROWN;
        } else if (self->SET_TO_CLOSED==(state)) {
            _setToState = Turnout::CLOSED;
        } else{
            _setToState= 0x00;
        }
    }
//}

///*private*/ class AutoTurnoutList extends ManualTurnoutList {
    AutoTurnoutList::AutoTurnoutList(QString sysName, QString userName, SignallingPanel* self) : ManualTurnoutList(sysName, userName, self)
    {
        //super(sysName, userName);
    }

    void AutoTurnoutList::setSetToState(QString /*state*/){ }
//}

///*private*/ class ManualSensorList extends SignalMastElement {
    ManualSensorList::ManualSensorList (QString sysName, QString userName, SignallingPanel* self) : SignalMastElement(sysName, userName,self)
    {
        //super(sysName, userName);
    }
    QString ManualSensorList::getSetToState() {
        switch (_setToState) {
            case Sensor::INACTIVE:
                return self->SET_TO_INACTIVE;
            case Sensor::ACTIVE:
                return self->SET_TO_ACTIVE;
        }
        return "";
    }
    void ManualSensorList::setSetToState(QString state)
    {
        if (self->SET_TO_INACTIVE==(state))
        {
            _setToState = Sensor::INACTIVE;
        } else if (self->SET_TO_ACTIVE==(state)) {
            _setToState = Sensor::ACTIVE;
        }
    }
;//}

///*private*/ class ManualSignalMastList extends SignalMastElement {
    ManualSignalMastList::ManualSignalMastList (SignalMast* s, SignallingPanel* self) :SignalMastElement(self)
    {
        mast = s;
        _setToAspect = "";
    }

    SignalMast* ManualSignalMastList::getMast(){
        return mast;
    }
    QString ManualSignalMastList::getSysName() {
        return mast->getSystemName();
    }
    QString ManualSignalMastList::getUserName() {
        return mast->getUserName();
    }
    QString ManualSignalMastList::getSetToState() {
        return _setToAspect;
    }

    void ManualSignalMastList::setSetToState(QString state) {
        _setToAspect = state;
    }
//}

///*private*/ class AutoSignalMastList extends ManualSignalMastList {
    AutoSignalMastList::AutoSignalMastList(SignalMast* s, SignallingPanel* self) : ManualSignalMastList(s, self)
    {
        //super(s);
    }

    void AutoSignalMastList::setSetToState(QString /*state*/){ }

    void AutoSignalMastList::setState(QString state) { _setToAspect = state; }
//}


//abstract class TableModel extends AbstractTableModel implements PropertyChangeListener
//{
    SPTableModel::SPTableModel(SignallingPanel *self)
    {
     this->self = self;
    }

//    /*public*/ QVariant SignallingPanel::TableModel::data(const QModelIndex &index, int role) const
//    {
//     if(role == Qt::EditRole || role == Qt::DisplayRole)
//     {
//      int c = index.column();
//      if (c == INCLUDE_COLUMN)
//      {
//            return Boolean.class;
//      }
//      else
//      {
//            return String.class;
//      }
//     }
//    }

    /*public*/ void SPTableModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()==("length")) {
            // a new NamedBean is available in the manager
            fireTableDataChanged();
        }
    }

    /*public*/ void SPTableModel::dispose() {
        //jmri.InstanceManager.turnoutManagerInstance().removePropertyChangeListener(this);

    }

    /*public*/ QVariant SPTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if (role != Qt::DisplayRole)
      return QVariant();

     if(orientation == Qt::Horizontal)
     {
      switch (section)
      {
        case SNAME_COLUMN: return tr("System Name");
        case UNAME_COLUMN: return tr("User Name");
        case INCLUDE_COLUMN: return tr("Include");
        case STATE_COLUMN: return tr("State");
        default: break;
      }
     }
     return QVariant();
    }

    /*public*/ int SPTableModel::columnCount(const QModelIndex &/*parent*/) const {return 4;}

    /*public*/ Qt::ItemFlags SPTableModel::flags(const QModelIndex &index) const
    {
      int c = index.column();

      if( c==INCLUDE_COLUMN)
       return  Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
      if(c==STATE_COLUMN )
       return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
      return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }

    void SPTableModel::fireTableDataChanged()
    {
     beginResetModel();
     endResetModel();
    }

//}

//class BlockModel extends TableModel
//{
    BlockModel::BlockModel(SignallingPanel* self) : SPTableModel(self)
    {
     BlockManager* mgr = static_cast<BlockManager*>(InstanceManager::getDefault("BlockMamager")); //.addPropertyChangeListener(this);
     connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }

    /*public*/ int BlockModel::rowCount(const QModelIndex &/*parent*/) const{
        if (self->showAll)
            return self->_manualBlockList.size();
        else
            return self->_includedManualBlockList.size();
    }

//    /*public*/ static final int SPEED_COLUMN = 4;
//    /*public*/ static final int PERMISSIVE_COLUMN = 5;

    /*public*/ int BlockModel::columnCount(const QModelIndex &/*parent*/) const {return 6;}

    /*public*/ QVariant BlockModel::data(const QModelIndex &index, int role) const
    {
     int c = index.column();
     int r = index.row();
     QList <ManualBlockList*> blockList = QList <ManualBlockList*>();
     if (self->showAll)
      blockList = self->_manualBlockList;
     else
      blockList = self->_includedManualBlockList;
     if(role == Qt::CheckStateRole)
     {
      if(c == INCLUDE_COLUMN)
       return blockList.at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
      if(c == PERMISSIVE_COLUMN)
       return blockList.at(r)->getPermissiveWorking()?Qt::Checked:Qt::Unchecked;
     }
     if(role == Qt::DisplayRole || role == Qt::EditRole)
     {
      switch (c)
      {
        case SNAME_COLUMN:  // slot number
            return  blockList.at(r)->getSysName();
        case UNAME_COLUMN:  //
            return  blockList.at(r)->getUserName();
        case STATE_COLUMN:
            return  blockList.at(r)->getSetToState();
        case SPEED_COLUMN:
            return blockList.at(r)->getBlockSpeed();
//        case PERMISSIVE_COLUMN:
//            return blockList.at(r)->getPermissiveWorking();
      default: QVariant();
       }
     }
     return QVariant();
    }

//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == PERMISSIVE_COLUMN) {
//            return Boolean.class;
//        }
//        return super.getColumnClass(c);
//    }

    /*public*/ QVariant BlockModel::headerData(int section, Qt::Orientation orientation, int role) const
     {
      if (role != Qt::DisplayRole)
         return QVariant();

      if(orientation == Qt::Horizontal)
      {
        switch (section) {
            case SPEED_COLUMN: return tr("Speed");
            case PERMISSIVE_COLUMN: return tr("Permissive");
        }
        return SPTableModel::headerData(section,orientation, role);
      }
      return QVariant();
    }

    /*public*/ bool BlockModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        int c = index.column();
        int r = index.row();
        QList <ManualBlockList*> blockList = QList <ManualBlockList*> ();
       if(role == Qt::EditRole)
       {
        if (self->showAll)
            blockList = self->_manualBlockList;
        else
            blockList = self->_includedManualBlockList;
        switch (c) {
            case STATE_COLUMN:
                blockList.at(r)->setSetToState(value.toString());
                break;
            default: break;
        }
       }
       if(role == Qt::CheckStateRole)
       {
        if( c ==INCLUDE_COLUMN)
        {
               blockList.at(r)->setIncluded(value.toBool());
               return true;
        }
      }
      return false;
    }
//    Qt::ItemFlags BlockModel::flags(const QModelIndex &index) const
//    {
//     if(index.column() == INCLUDE_COLUMN || index.column() == STATE_COLUMN || index.column() == PERMISSIVE_COLUMN)
//            return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
//      return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
//    }
//}
    void BlockModel::propertyChange(PropertyChangeEvent *e)
    {
     SPTableModel::propertyChange(e);
    }

//class TurnoutModel extends TableModel
//{
    TurnoutModel::TurnoutModel(SignallingPanel* self) : SPTableModel(self)
    {
     //jmri.InstanceManager.turnoutManagerInstance().addPropertyChangeListener(this);
        ProxyTurnoutManager* mgr = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
        connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }

    /*public*/ int  TurnoutModel::rowCount(const QModelIndex &/*parent*/) const
    {
        if (self->showAll)
            return self->_manualTurnoutList.size();
        else
            return self->_includedManualTurnoutList.size();
    }

    /*public*/ QVariant TurnoutModel::data(const QModelIndex &index, int role) const
    {
     int c= index.column();
     int r = index.column();
     QList <ManualTurnoutList*> turnoutList = QList <ManualTurnoutList*>();
     if (self->showAll)
         turnoutList = self->_manualTurnoutList;
     else
         turnoutList = self->_includedManualTurnoutList;
     if(role == Qt::CheckStateRole)
     {
      if(c == INCLUDE_COLUMN)
       return turnoutList.at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
     }
     if(role == Qt::DisplayRole || role == Qt::EditRole)
     {
        switch (c) {
//            case INCLUDE_COLUMN:
//                return turnoutList.at(r)->isIncluded();
            case SNAME_COLUMN:  // slot number
                return turnoutList.at(r)->getSysName();
            case UNAME_COLUMN:  //
                return turnoutList.at(r)->getUserName();
            case STATE_COLUMN:
                return turnoutList.at(r)->getSetToState();
            default:
                break;
        }
     }
     return QVariant();
    }

    /*public*/ bool TurnoutModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
     int c = index.column();
     int r = index.row();
     QList <ManualTurnoutList*> turnoutList = QList <ManualTurnoutList*>();
     if(role == Qt::EditRole)
     {
        if (self->showAll) {
            turnoutList = self->_manualTurnoutList;
        }
        else {
            turnoutList = self->_includedManualTurnoutList;
        }
        switch (c) {
            case STATE_COLUMN:
                turnoutList.at(r)->setSetToState(value.toString());
                break;
            default: break;
        }
     }
     if(role == Qt::CheckStateRole)
     {
      if(c == INCLUDE_COLUMN)
      {
       turnoutList.at(r)->setIncluded(value.toBool());
       return true;
      }
     }
     return false;
    }

    void TurnoutModel::propertyChange(PropertyChangeEvent *e)
    {
     SPTableModel::propertyChange(e);
    }

//};


 /**
 * Set up table for selecting Sensors and Sensor State
 */
//class SensorModel extends TableModel
//{
    SensorModel::SensorModel(SignallingPanel* self) : SPTableModel(self)
    {
        log = new Logger("SensorModel");
     //InstanceManager.sensorManagerInstance().addPropertyChangeListener(this);
        AbstractSensorManager* mgr = (AbstractSensorManager*)InstanceManager::sensorManagerInstance();
        connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }

    /*public*/ int SensorModel::rowCount(const QModelIndex &/*parent*/) const
    {
        if (self->showAll)
            return self->_manualSensorList.size();
        else
            return self->_includedManualSensorList.size();
    }

    /*public*/ QVariant SensorModel::data(const QModelIndex &index, int role) const
    {
     int r = index.row();
     int c = index.column();
     QList <ManualSensorList*> sensorList = QList <ManualSensorList*>();
     if (self->showAll)
         sensorList = self->_manualSensorList;
     else
         sensorList = self->_includedManualSensorList;
     if(role == Qt::CheckStateRole)
     {
      if(c == INCLUDE_COLUMN)
       return sensorList.at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;

     }
     if(role == Qt::DisplayRole || role == Qt::EditRole)
     {
        // some error checking
        if (r >= sensorList.size()){
            log->debug("row is greater than turnout list size");
            return QVariant();
        }
        switch (c) {
//            case INCLUDE_COLUMN:
//                return sensorList.at(r)->isIncluded();
            case SNAME_COLUMN:  // slot number
                return sensorList.at(r)->getSysName();
            case UNAME_COLUMN:  //
                return sensorList.at(r)->getUserName();
            case STATE_COLUMN:  //
                return sensorList.at(r)->getSetToState();
            default:
                break;
        }
     }
     return QVariant();
    }

    /*public*/ bool SensorModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
      if(role == Qt::EditRole)
      {
       int c= index.column();
       int r = index.row();
        QList <ManualSensorList*> sensorList = QList <ManualSensorList*>();
        if (self->showAll) {
            sensorList = self->_manualSensorList;
        }
        else
        {
            sensorList = self->_includedManualSensorList;
        }
        switch (c) {
            case INCLUDE_COLUMN:
                sensorList.at(r)->setIncluded(value.toBool());
                break;
            case STATE_COLUMN:
                sensorList.at(r)->setSetToState(value.toString());
                break;
            default: break;
        }
     }
     return false;
    }

    void SensorModel::propertyChange(PropertyChangeEvent *e)
    {
     SPTableModel::propertyChange(e);
    }

//}


//class SignalMastModel : public TableModel
//{
    SignalMastModel::SignalMastModel(SignallingPanel* self) : SPTableModel(self)
    {
        //InstanceManager::signalMastManagerInstance().addPropertyChangeListener(this);
        SignalMastManager* mgr = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"));
        connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }

    /*public*/ int SignalMastModel::rowCount(const QModelIndex &/*parent*/) const
    {
        if (self->showAll)
            return self->_manualSignalMastList.size();
        else
            return self->_includedManualSignalMastList.size();
    }

    /*public*/ QVariant SignalMastModel::data(const QModelIndex &index, int role) const
    {
     int r = index.row();
     int c = index.column();
     QList <ManualSignalMastList*> signalMastList = QList <ManualSignalMastList*>();
     if (self->showAll)
      signalMastList = self->_manualSignalMastList;
     else
      signalMastList = self->_includedManualSignalMastList;
     if(role == Qt::CheckStateRole)
     {
      if(c == INCLUDE_COLUMN)
       return signalMastList.at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
     }

     if(role == Qt::DisplayRole || role == Qt::EditRole)
     {
      switch (c) {
            case INCLUDE_COLUMN:
                return signalMastList.at(r)->isIncluded();
            case SNAME_COLUMN:  // slot number
                return signalMastList.at(r)->getSysName();
            case UNAME_COLUMN:  //
                return signalMastList.at(r)->getUserName();
            case STATE_COLUMN:
                return signalMastList.at(r)->getSetToState();
            default:
                break;
        }
     }
     return QVariant();
    }

    /*public*/ QString SignalMastModel::getValue(QString name) {
        return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getBySystemName(name)->getAspect();
    }

    /*public*/ QVariant SignalMastModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
     {
      if (section ==STATE_COLUMN) return tr("Aspect");
      else return SPTableModel::headerData(section, orientation, role);
     }
     return QVariant();
    }

     /*public*/ bool  SignalMastModel::setData(const QModelIndex &index, const QVariant &value, int role)
     {
     int c= index.column();
     int r = index.row();
     QList <ManualSignalMastList*> signalMastList = QList <ManualSignalMastList*>();

      if(role == Qt::EditRole)
      {
       if (self->showAll)
       {
        signalMastList = self->_manualSignalMastList;
       }
       else
       {
        signalMastList = self->_includedManualSignalMastList;
       }

       switch (c)
       {
            case STATE_COLUMN:
                signalMastList.at(r)->setSetToState(value.toString());
                fireTableRowsUpdated(r, r);
                break;
            case INCLUDE_COLUMN:
                signalMastList.at(r)->setIncluded(value.toBool());
                break;
            default: break;
        }
      }
      if(role == Qt::CheckStateRole)
      {
       if(c == INCLUDE_COLUMN)
       {
           signalMastList.at(r)->setIncluded(value.toBool());
           return true;
       }
      }
      return false;
    }

    void SignalMastModel::fireTableRowsUpdated(int /*r1*/, int /*r2*/)
    {
     beginResetModel();
     endResetModel();
    }
    void SignalMastModel::propertyChange(PropertyChangeEvent *e)
    {
     SPTableModel::propertyChange(e);
    }

#if 0
    TableSorter sorter;

    protected JTable makeJTable(TableSorter srtr) {
        this.sorter = srtr;
        return new JTable(sorter)  {
            /*public*/ bool editCellAt(int row, int column, java.util.EventObject e) {
                bool res = super.editCellAt(row, column, e);
                java.awt.Component c = this.getEditorComponent();
                if (c instanceof javax.swing.JTextField) {
                    ( (JTextField) c).selectAll();
                }
                return res;
            }
            /*public*/ TableCellRenderer getCellRenderer(int row, int column) {
                if (column == STATE_COLUMN) {
                    return getRenderer(row);
                } else
                    return super.getCellRenderer(row, column);
            }
            /*public*/ TableCellEditor getCellEditor(int row, int column) {
                if (column == STATE_COLUMN) {
                    return getEditor(row);
                } else
                    return super.getCellEditor(row, column);
            }
            TableCellRenderer getRenderer(int row) {
                TableCellRenderer retval = rendererMap.get(sorter.getValueAt(row,SNAME_COLUMN));
                if (retval == NULL) {
                    // create a new one with right aspects
                    retval = new MyComboBoxRenderer(getAspectVector(row));
                    rendererMap.put(sorter.getValueAt(row,SNAME_COLUMN), retval);
                }
                return retval;
            }
            Hashtable<Object, TableCellRenderer> rendererMap = new Hashtable<Object, TableCellRenderer>();

            TableCellEditor getEditor(int row) {
                TableCellEditor retval = editorMap.get(sorter.getValueAt(row,SNAME_COLUMN));
                if (retval == NULL) {
                    // create a new one with right aspects
                    retval = new MyComboBoxEditor(getAspectVector(row));
                    editorMap.put(sorter.getValueAt(row,SNAME_COLUMN), retval);
                }
                return retval;
            }
            Hashtable<Object, TableCellEditor> editorMap = new Hashtable<Object, TableCellEditor>();

            Vector<String> getAspectVector(int row) {
                Vector<String> retval = boxMap.get(sorter.getValueAt(row,SNAME_COLUMN));
                if (retval == NULL) {
                    // create a new one with right aspects
                    Vector<String> v = InstanceManager.signalMastManagerInstance()
                                        .getSignalMast((String)sorter.getValueAt(row,SNAME_COLUMN)).getValidAspects();
                    v.add(0, "");
                    retval = v;
                    boxMap.put(sorter.getValueAt(row,SNAME_COLUMN), retval);
                }
                return retval;
            }
            Hashtable<Object, Vector<String>> boxMap = new Hashtable<Object, Vector<String>>();
        };
    }

}
#endif
//abstract class AutoTableModel extends AbstractTableModel implements PropertyChangeListener
//{

    AutoTableModel::AutoTableModel(SignallingPanel* self)
    {
     this->self = self;
        smlValid();
    }

    /*public*/ void AutoTableModel::smlValid()
    {
     if (self->sml!=NULL)
     {
//            ((DefaultSignalMastLogic*)sml)->addPropertyChangeListener(this);
      DefaultSignalMastLogic* l = (DefaultSignalMastLogic*)self->sml;
      connect(l, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

    }
    void AutoTableModel::fireTableDataChanged()
    {
     beginResetModel();
     endResetModel();
    }
//}

//    /*public*/ Class<?> AutoTableModel::getColumnClass(int c) {
//        return String.class;
//    }

    /*public*/ void AutoTableModel::dispose()
    {
        //jmri.InstanceManager.turnoutManagerInstance().removePropertyChangeListener(this);
    ProxyTurnoutManager* t = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
     disconnect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }

    /*public*/ QVariant AutoTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
    if (role != Qt::DisplayRole)
     return QVariant();

     if(orientation == Qt::Horizontal)
     {
      switch (section)
      {
        case SNAME_COLUMN: return tr("System Name");
        case UNAME_COLUMN: return tr("User Name");
        case STATE_COLUMN: return tr("State");

      default: return QVariant();
      }
     }
    }

    /*public*/ int AutoTableModel::columnCount(const QModelIndex &/*parent*/) const {return 3;}

    /*public*/ Qt::ItemFlags AutoTableModel::flags(const QModelIndex &/*index*/) const
    {
        return Qt::ItemIsEnabled;
    }

    void AutoTableModel::propertyChange(PropertyChangeEvent */*e*/)
    {
      fireTableDataChanged();
    }

//};

 //class AutoBlockModel extends AutoTableModel {

    AutoBlockModel::AutoBlockModel(SignallingPanel* self) : AutoTableModel(self)
    {
     //this->self = self;
     if (this->self->sml!=NULL)
     {
      //((DefaultSignalMastLogic*)sml)->addPropertyChangeListener(this);
      DefaultSignalMastLogic* l = (DefaultSignalMastLogic*)this->self->sml;
      connect(l, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
    }
    /*public*/ int AutoBlockModel::columnCount(const QModelIndex &/*parent*/) const {return 5;}

    /*public*/ QVariant AutoBlockModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if (role != Qt::DisplayRole)
      return QVariant();

     if(orientation == Qt::Horizontal)
     {
        switch (section) {
            case SPEED_COLUMN: return tr("Speed");
            case PERMISSIVE_COLUMN: return tr("Permissive"); /*AbstractTableAction.tr("ColumnUserName"); //"User Name";*/
        }
        return AutoTableModel::headerData(section, orientation, role);
     }
     return QVariant();
    }

    /*public*/ void AutoBlockModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()==("autoblocks")) {
            // a new NamedBean is available in the manager
            self->initializeIncludedList();
            fireTableDataChanged();
        }
    }

//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == PERMISSIVE_COLUMN) {
//            return Boolean.class;
//        }
//        return super.getColumnClass(c);
//    }

    /*public*/ int AutoBlockModel::rowCount(const QModelIndex &/*parent*/) const {
        return self->_automaticBlockList->size();
    }

    /*public*/ QVariant AutoBlockModel::data(const QModelIndex &index, int role) const
    {
        int c = index.column();
        int r = index.row();
     if(role == Qt::DisplayRole || role == Qt::EditRole)
     {
        switch (c)
        {
            case SNAME_COLUMN:  // slot number
                return self->_automaticBlockList->at(r)->getSysName();
            case UNAME_COLUMN:  //
                return self->_automaticBlockList->at(r)->getUserName();
            case STATE_COLUMN:
                return self->_automaticBlockList->at(r)->getSetToState();
            case SPEED_COLUMN:
                return self->_automaticBlockList->at(r)->getBlockSpeed();
            default:
                break;
        }
     }
     if(role == Qt::CheckStateRole)
     {
      if( c == PERMISSIVE_COLUMN)
      {
             //return new Boolean(_automaticBlockList.get(r).getPermissiveWorking());
             return self->_automaticBlockList->at(r)->getPermissiveWorking()?Qt::Checked:Qt::Unchecked;
     }
    }
     return QVariant();
    }

    ///*public*/ void setValueAt(Object type,int r,int c) { }

    /*public*/ Qt::ItemFlags AutoBlockModel::flags(const QModelIndex &/*index*/) const
    {
        return Qt::ItemIsEnabled;
    }

    void AutoBlockModel::fireTableDataChanged()
    {
      beginResetModel();
      endResetModel();
    }

//};
//class AutoTurnoutModel extends AutoTableModel {
    AutoTurnoutModel::AutoTurnoutModel(SignallingPanel* self) : AutoTableModel(self)
    {
        //super();
    }

    /*public*/ int AutoTurnoutModel::rowCount(const QModelIndex &/*parent*/) const{
        return self->_automaticTurnoutList->size();
    }

    /*public*/ void AutoTurnoutModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()==("autoturnouts")) {
            // a new NamedBean is available in the manager
            self->initializeIncludedList();
            fireTableDataChanged();
        }
    }

    /*public*/ QVariant AutoTurnoutModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole || role == Qt::EditRole)
     {
      int c = index.column();
      int r = index.row();
        switch (c) {
            case SNAME_COLUMN:  // slot number
                return self->_automaticTurnoutList->at(r)->getSysName();
            case UNAME_COLUMN:  //
                return self->_automaticTurnoutList->at(r)->getUserName();
            case STATE_COLUMN:
                return self->_automaticTurnoutList->at(r)->getSetToState();
            default:
                break;
        }
     }
     return QVariant();
    }
//}


//class AutoMastModel extends AutoTableModel {
    AutoMastModel::AutoMastModel(SignallingPanel* self) : AutoTableModel(self)
    {
        //super();
    }

    /*public*/ int AutoMastModel::rowCount(const QModelIndex &parent) const
    {
        return self->_automaticSignalMastList->size();
    }

    /*public*/ void AutoMastModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()==("automasts")) {
            // a new NamedBean is available in the manager
            self->initializeIncludedList();
            fireTableDataChanged();
        }
    }

    /*public*/ QVariant AutoMastModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole || Qt::EditRole)
     {
      int c = index.column();
      int r = index.row();
      switch (c)
      {
            case SNAME_COLUMN:  // slot number
                return self->_automaticSignalMastList->at(r)->getSysName();
            case UNAME_COLUMN:  //
                return self->_automaticSignalMastList->at(r)->getUserName();
            case STATE_COLUMN:
                return self->_automaticSignalMastList->at(r)->getSetToState();
      default:
                break;

     }
      return QVariant();
   }
};
#if 0
/*public*/ static class MyComboBoxEditor extends DefaultCellEditor {
    /*public*/ MyComboBoxEditor(Vector<String> items) {
        super(new JComboBox(items));
    }
}

/*public*/ static class MyComboBoxRenderer extends JComboBox implements TableCellRenderer {
    /*public*/ MyComboBoxRenderer(Vector<String> items) {
        super(items);
    }

    /*public*/ Component getTableCellRendererComponent(JTable table, Object value,
            bool isSelected, bool hasFocus, int row, int column) {
        if (isSelected) {
            setForeground(table.getSelectionForeground());
            super.setBackground(table.getSelectionBackground());
        } else {
            setForeground(table.getForeground());
            setBackground(table.getBackground());
        }

        // Select the current value
        setSelectedItem(value);
        return this;
    }
}
#endif
#if 0
    SPComboBoxDelegate::SPComboBoxDelegate(QStringList items, QObject *parent)
    :QItemDelegate(parent)
    {
     this->items = items;
    }


    QWidget *SPComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
    {
      QComboBox* editor = new QComboBox(parent);
      editor->addItems(items);
      return editor;
    }

    void SPComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
    {
      QComboBox *comboBox = static_cast<QComboBox*>(editor);
      int value = index.model()->data(index, Qt::EditRole).toUInt();
      comboBox->setCurrentIndex(value);
    }

    void SPComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
      QComboBox *comboBox = static_cast<QComboBox*>(editor);
      model->setData(index, comboBox->currentText(), Qt::EditRole);
    }

    void SPComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
    {
      editor->setGeometry(option.rect);
    }
#endif
    SignalMastComboBoxDelegate::SignalMastComboBoxDelegate(SignallingPanel* panel, QObject *parent)
    : JComboBoxEditor(parent)
    {
     this->panel = panel;
    }

    QWidget *SignalMastComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex & index ) const
    {
      QComboBox* editor = new QComboBox(parent);
      QList <ManualSignalMastList*> signalMastList = QList <ManualSignalMastList*>();
      if (panel->showAll)
       signalMastList = panel->_manualSignalMastList;
      else
       signalMastList = panel->_includedManualSignalMastList;
      editor->addItems(((AbstractSignalMast*)signalMastList.at(index.row())->getMast())->getValidAspects().toList());
      return editor;
    }
#if 0
    void SignalMastComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
    {
      QComboBox *comboBox = static_cast<QComboBox*>(editor);
      int value = index.model()->data(index, Qt::EditRole).toUInt();
      comboBox->setCurrentIndex(value);
    }

    void SignalMastComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
      QComboBox *comboBox = static_cast<QComboBox*>(editor);
      model->setData(index, comboBox->currentText(), Qt::EditRole);
    }

    void SignalMastComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
    {
      editor->setGeometry(option.rect);
    }
#endif
//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SignallingPanel.class.getName());
//}

/* @(#)StatusPane.java */
