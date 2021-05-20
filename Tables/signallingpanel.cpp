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
#include "defaultsignalmastlogicmanager.h"
#include "proxyturnoutmanager.h"
#include "block.h"
#include "QHeaderView"
#include "../LayoutEditor/layoutblockmanager.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include "joptionpane.h"
#include "box.h"
#include "stringutil.h"
#include "jtabbedpane.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "tablerowsorter.h"
#include "alphanumcomparator.h"
#include "rowsorterutil.h"

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
// /*private*/ /*static*/ /*final*/ JButton* SignallingPanel::sizer = new JButton("Sizer");  // NOI18N

void SignallingPanel::init()
{
 fixedSourceMastLabel = new QLabel();
 fixedDestMastLabel = new QLabel();
 sourceMastLabel = new QLabel(tr("Source Mast"));
 destMastLabel = new QLabel(tr("Destination Mast"));
 updateButton = new QPushButton(tr("Update Signal Logic"));
 useLayoutEditor = new JCheckBox(tr("Use Layout Editor Paths"));
 useLayoutEditorTurnout = new JCheckBox(tr("Use Turnout Details From Layout Editor"));
 useLayoutEditorBlock = new JCheckBox(tr("Use Block Details From Layout Editor"));
 allowAutoMastGeneration = new JCheckBox(tr("Allow the Logic to Automatically Determine ConflictingSignalMasts"));
 lockTurnouts = new JCheckBox(tr("Lock Turnouts when SignalMast Logic is Active"));

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

/*public*/ SignallingPanel::SignallingPanel(JFrame* frame, QWidget* parent) : JmriPanel(parent)
{
 common(NULL, NULL, frame);
}

/*public*/ SignallingPanel::SignallingPanel(SignalMast* source, SignalMast* dest, JFrame *frame, QWidget* parent) : JmriPanel(parent)
{
 //super();
 jFrame = frame;
 common(source, dest, frame);
}

void SignallingPanel::common(SignalMast* source, SignalMast* dest, JFrame* frame)
{
 init();
 JButton* cancelButton = new JButton(tr("Cancel"));  // NOI18N
 JButton* updateButton = new JButton(tr("Update Signal Logic"));  // NOI18N
 JButton* applyButton = new JButton(tr("Apply"));  // NOI18N
 JLabel* mastSpeed = new JLabel();

 if (source!=NULL)
 {
  this->sourceMast = source;
  this->sml = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(source);
  fixedSourceMastLabel = new QLabel(sourceMast->getDisplayName());
  // if (dest != null) {
  //   frame->setTitle(source.getDisplayName() + " to " + dest.getDisplayName());
  // }
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
        mastSpeed->setText(tr("Path Speed") + " : " + speed);
   else
        mastSpeed->setText(tr("Path Speed") + " : " + QString::number(pathSpeed));
  }
 }
 else if (dest==NULL)
 {
  sml=NULL;
 }

 SignalMastManager* smm = (SignalMastManager*)InstanceManager::getDefault("SignalMastManager");
 sourceMastBox = new NamedBeanComboBox(smm, sourceMast, NamedBean::DISPLAYNAME);
 sourceMastBox->setMaximumSize(sourceMastBox->sizeHint());
 destMastBox = new NamedBeanComboBox(smm, destMast, NamedBean::DISPLAYNAME);
 destMastBox->setMaximumSize(destMastBox->sizeHint());

// JComboBoxUtil->setupComboBoxMaxRows(sourceMastBox);
// JComboBoxUtil->setupComboBoxMaxRows(destMastBox);

 // directly add sub-panes onto JFrame's content pane to allow resizing (2018)
 //QWidget* contentPane = frame->getContentPane();
 //QWidget* containerPanel = new QWidget();
 QVBoxLayout* containerPanelLayout = (QVBoxLayout*)frame->getContentPane(true)->layout();

 JPanel* header = new JPanel();
// header->setLayout(new QVBoxLayout(header/*, BoxLayout.Y_AXIS*/));
 QVBoxLayout* headerLayout = new QVBoxLayout;
 header->setLayout(headerLayout);

 JPanel* mastGrid = new JPanel();
 QGridLayout* layout = new QGridLayout();//2, 2, 10, 0); // (int rows, int cols, int hgap, int vgap)
 mastGrid->setLayout(layout);
 // row 1
 mastGrid->layout()->addWidget(sourceMastLabel);

 JPanel* sourcePanel = new JPanel();
// sourcePanel->setLayout(new QHBoxLayout());
 QHBoxLayout* sourcePanelLayout = new QHBoxLayout;
 sourcePanel->setLayout(sourcePanelLayout);
 sourcePanelLayout->addWidget(sourceMastLabel);
 sourcePanelLayout->addWidget(sourceMastBox);
 sourcePanelLayout->addWidget(fixedSourceMastLabel);
 mastGrid->layout()->addWidget(sourcePanel);
 // row 2
 mastGrid->layout()->addWidget(destMastLabel);

 headerLayout->addLayout(sourcePanelLayout);

 JPanel* destPanel = new JPanel();
// destPanel->setLayout(new QHBoxLayout());
 QHBoxLayout* destPanelLayout = new QHBoxLayout;
 destPanel->setLayout(destPanelLayout);
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

 mastGrid->layout()->addWidget(destPanel);
 header->layout()->addWidget(mastGrid);

 headerLayout->addWidget(mastSpeed);

 JPanel* editor = new JPanel();
 QVBoxLayout* editorLayout = new QVBoxLayout;
 //editor->setLayout(editorLayout = new QVBoxLayout(editor/*, BoxLayout.Y_AXIS*/));
 editor->setLayout(editorLayout);
 editorLayout->addWidget(useLayoutEditor,0, Qt::AlignLeft);

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

 JPanel* useLayoutEditorSubPanel = new JPanel(); // indent 2 options connected to LayoutEditor choice
 useLayoutEditorSubPanel->setLayout(new QVBoxLayout());//useLayoutEditorSubPanel, BoxLayout.Y_AXIS));
 useLayoutEditorSubPanel->setBorder(BorderFactory::createEmptyBorder(0, 20, 0, 0));
 useLayoutEditorSubPanel->layout()->addWidget(useLayoutEditorTurnout);
 useLayoutEditorSubPanel->layout()->addWidget(useLayoutEditorBlock);
 editorLayout->addWidget(useLayoutEditorSubPanel);
 useLayoutEditorSubPanel->setVisible(false);

 //useLayoutEditor.addActionListener(e -> {
 connect(useLayoutEditor, &JCheckBox::clicked, [=]{
     useLayoutEditorSubPanel->setVisible(useLayoutEditor->isChecked());
     // Setup for display of all Turnouts, if needed
     bool valid;
     if (useLayoutEditor->isChecked()) {
         jFrame->pack();
         if (!((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled()) {
             int response;

             response = JOptionPane::showConfirmDialog(nullptr, tr("Layout Block Routing is not enabled.\nDo you want to enable it?"));  // NOI18N
             if (response == 0) {
                 ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->enableAdvancedRouting(true);
                 JOptionPane::showMessageDialog(nullptr, tr("Layout Block Routing has been enabled.\nPlease close and reopen this window for the changes to take effect."));  // NOI18N
             }
         }

         if ((sml != nullptr) && (destMast != nullptr)) {
             try {
                 sml->useLayoutEditor(useLayoutEditor->isChecked(), destMast);
             } catch (JmriException je) {
                 JOptionPane::showMessageDialog(nullptr, je.toString());
             }
             try {
                 valid = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(VPtr<LayoutBlock>::asPtr(sourceMastBox->currentData()),
                         VPtr<LayoutBlock>::asPtr(destMastBox->currentData()), LayoutBlockConnectivityTools::Routing::MASTTOMAST);
                 if (!valid) {
                     JOptionPane::showMessageDialog(nullptr, tr("The Destination Mast is not directly reachable from the Source Mast"));
                 }
             } catch (JmriException je) {
                 JOptionPane::showMessageDialog(nullptr, tr("It has not been possible to validate the path between the two Signal Masts"));
             }
         }
     }
 });
 headerLayout->addWidget(editor);
 headerLayout->addWidget(allowAutoMastGeneration);
 headerLayout->addWidget(lockTurnouts);

 JPanel* py = new JPanel();
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

 containerPanelLayout->addWidget(header);

 // build_x_Panel() returns a JScrollFrame
 JTabbedPane* detailsTab = new JTabbedPane();
 detailsTab->addTab(tr("Blocks"), buildBlocksPanel());
 detailsTab->addTab(tr("Turnouts"),buildTurnoutPanel());
 detailsTab->addTab(tr("Sensors"), buildSensorPanel());
 detailsTab->addTab(tr("Signal Masts"), buildSignalMastPanel());

 containerPanelLayout->addWidget(detailsTab);

 JPanel* footer = new JPanel();
 footer->setLayout(new QHBoxLayout());

 // Cancel button
 footer->layout()->addWidget(cancelButton);
 //cancelButton.addActionListener(this::cancelPressed);
 connect(cancelButton, &JButton::clicked, [=]{cancelPressed();});

 footer->layout()->addWidget(updateButton);
//    updateButton->layout()->addWidgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            updatePressed(e);
//        }
//    });
 updateButton->setToolTip(tr("Change this Route and leave Edit mode"));
 updateButton->setVisible(true);
 connect(updateButton, SIGNAL(clicked()), this, SLOT(updatePressed()));

 // Apply (and Close) button
 footer->layout()->addWidget(applyButton);
 //applyButton.addActionListener(this::applyPressed);
 connect(applyButton, &JButton::clicked, [=]{applyPressed();});
 applyButton->setToolTip(tr("Change this Signal Mast Logic and leave Edit mode"));  // NOI18N
 applyButton->setVisible(true);

 containerPanelLayout->addWidget(Box::createVerticalGlue()); // glue above buttons
 containerPanelLayout->addWidget(footer);

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
 manualBlockTable = new JTable(/*_blockModel*/);
 TableRowSorter/*<BlockModel>*/* manualBlockSorter = new TableRowSorter(_blockModel);
 // configure row height for comboBox
 manualBlockTable->setRowHeight(JButton("sizer").sizeHint().height() - 2); // row height has to be greater than for plain tables
 manualBlockSorter->setComparator(BlockModel::SNAME_COLUMN, new AlphanumComparator());
 manualBlockSorter->setComparator(BlockModel::UNAME_COLUMN, new AlphanumComparator());
 RowSorterUtil::setSortOrder(manualBlockSorter, BlockModel::SNAME_COLUMN, SortOrder::ASCENDING);manualBlockTable->setSelectionMode(QAbstractItemView::SingleSelection);
 manualBlockTable->setSelectionBehavior(QAbstractItemView::SelectRows);
 manualBlockTable->setEnabled(true);
 manualBlockTable->setRowSorter(manualBlockSorter);
 manualBlockTable->setSortingEnabled(true);
 manualBlockTable->setModel(manualBlockSorter);
 //manualBlockTable->setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
 manualBlockTable->setMinimumSize(280,100);
// QComboBox* stateCCombo = new QComboBox();
// stateCCombo->addItem(SET_TO_UNOCCUPIED);
// stateCCombo->addItem(SET_TO_OCCUPIED);
// stateCCombo->addItem(SET_TO_ANY);
 QStringList blockStates;
 blockStates << SET_TO_UNOCCUPIED << SET_TO_OCCUPIED << SET_TO_ANY;
 //manualBlockTable->setItemDelegateForColumn(BlockModel::STATE_COLUMN, new SPComboBoxDelegate(blockStates));
 _blockModel->setColumnToHoldDelegate(manualBlockTable, BlockModel::STATE_COLUMN, new JComboBoxEditor(blockStates, true));

 TableColumnModel* _manualBlockColumnModel = manualBlockTable->getColumnModel();
 TableColumn* includeColumnC = _manualBlockColumnModel->
                                        getColumn(BlockModel::INCLUDE_COLUMN);
 manualBlockTable->setColumnWidth(BlockModel::INCLUDE_COLUMN, 60);
 includeColumnC->setResizable(false);
 includeColumnC->setMinWidth(50);
 includeColumnC->setMaxWidth(60);
 TableColumn* sNameColumnC = _manualBlockColumnModel->
                                     getColumn(BlockModel::SNAME_COLUMN);
 sNameColumnC->setResizable(true);
 sNameColumnC->setMinWidth(75);
 sNameColumnC->setMaxWidth(95);

 TableColumn* stateColumnC = _manualBlockColumnModel->
                                     getColumn(BlockModel::STATE_COLUMN);
 //stateColumnC->setCellEditor(new DefaultCellEditor(stateCCombo));
 stateColumnC->setResizable(false);
 stateColumnC->setMinWidth(90);
 stateColumnC->setMaxWidth(100);

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
 autoBlockTable = new JTable(_autoBlockModel);
 //jmri.util.JTableUtil.sortableDataModel(_autoBlockModel);
 TableRowSorter/*<AutoBlockModel>*/* autoBlockSorter = new TableRowSorter(_autoBlockModel);
 autoBlockSorter->setComparator(AutoBlockModel::SNAME_COLUMN, new AlphanumComparator());
 autoBlockSorter->setComparator(AutoBlockModel::UNAME_COLUMN, new AlphanumComparator());
 RowSorterUtil::setSortOrder(autoBlockSorter, AutoBlockModel::SNAME_COLUMN, SortOrder::ASCENDING);
 autoBlockTable->setRowSorter(autoBlockSorter);
 autoBlockTable->setRowSelectionAllowed(false);
 autoBlockTable->setSortingEnabled(true);
 autoBlockTable->setModel(autoBlockSorter);
 //    autoBlockTable->setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
 autoBlockTable->setMinimumSize(280,100);

    TableColumnModel* _autoBlockColumnModel = autoBlockTable->getColumnModel();
    TableColumn* sNameColumnA = _autoBlockColumnModel->
                                        getColumn(AutoBlockModel::SNAME_COLUMN);
    sNameColumnA->setResizable(true);
    sNameColumnA->setMinWidth(75);
    sNameColumnA->setMaxWidth(95);

    TableColumn* stateColumnA = _autoBlockColumnModel->
                                        getColumn(AutoBlockModel::STATE_COLUMN);
    //stateColumnA->setCellEditor(new DefaultCellEditor(stateCCombo));
    stateColumnA->setResizable(false);
    stateColumnA->setMinWidth(90);
    stateColumnA->setMaxWidth(100);

 //autoBlockScrollPane = new JScrollPane(autoBlockTable);
 //p2xb.add(_autoBlockScrollPane,BorderLayout.CENTER);
 p2xbLayout->addWidget(autoBlockTable);
 blockPanelLayout->addWidget(p2xb);
 p2xb->setVisible(true);

 //ROW_HEIGHT = autoBlockTable->rowHeight(0);
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
   bool valid = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(sourceMastBox->getSelectedItem(),
                            destMastBox->getSelectedItem(), LayoutBlockConnectivityTools::MASTTOMAST);
   if(!valid)
    JOptionPane::showMessageDialog(NULL, tr("The Destination Mast is not directly reachable from the source Mast"));
  }
  catch (JmriException je)
  {
   JOptionPane::showMessageDialog(NULL, tr("It has not been possible to validate the path between the two SignalMasts"));
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
   int response;
   response = JOptionPane::showConfirmDialog(NULL, tr("Layout Block Routing is not enabled.\nDo you want to enable it?"));
   if(response == 0)
   {
     static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->enableAdvancedRouting(true);
       JOptionPane::showMessageDialog(nullptr, tr(" Please close and reopen this window for the changes to take effect."));
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
    JOptionPane::showMessageDialog(NULL, je.toString());
   }
   try
   {
    valid = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(sourceMastBox->getSelectedItem(),
                destMastBox->getSelectedItem(), LayoutBlockConnectivityTools::MASTTOMAST);
    if(!valid)
    {
     JOptionPane::showMessageDialog(NULL, tr("The Destination Mast is not directly reachable from the source Mast"));
    }
   }
   catch (JmriException je)
   {
    JOptionPane::showMessageDialog(NULL, tr("It has not been possible to validate the path between the two Signal Masts"));
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
    manualTurnoutTable = new JTable(_turnoutModel);
    TableRowSorter/*<TurnoutModel*/* manualTurnoutSorter = new TableRowSorter(_turnoutModel);
    // configure row height for comboBox
    manualTurnoutTable->setRowHeight(JButton("sizer").sizeHint().height() - 2); // row height has to be greater than for plain tables
    manualTurnoutSorter->setComparator(TurnoutModel::SNAME_COLUMN, new AlphanumComparator());
    manualTurnoutSorter->setComparator(TurnoutModel::UNAME_COLUMN, new AlphanumComparator());
    RowSorterUtil::setSortOrder(manualTurnoutSorter, TurnoutModel::SNAME_COLUMN, SortOrder::ASCENDING);
    //_turnoutModel->configStateColumn(manualTurnoutTable); // create static comboBox in State column
    manualTurnoutTable->setRowSorter(manualTurnoutSorter);
    manualTurnoutTable->setRowSelectionAllowed(false);
    manualBlockTable->setSortingEnabled(true);
    manualBlockTable->setModel(manualTurnoutSorter);//manualTurnoutTable->setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    manualTurnoutTable->setMinimumSize(280, 100);
//    QComboBox* stateCCombo = new QComboBox();
//    stateCCombo->addItem(SET_TO_THROWN);
//    stateCCombo->addItem(SET_TO_CLOSED);
//    stateCCombo->addItem(SET_TO_ANY);
    QStringList statesList;
    statesList << SET_TO_THROWN <<SET_TO_CLOSED << SET_TO_ANY;
    //manualTurnoutTable->setItemDelegateForColumn(SPTableModel::STATE_COLUMN, new SPComboBoxDelegate(statesList));
    _turnoutModel->setColumnToHoldDelegate(manualTurnoutTable, SPTableModel::STATE_COLUMN, new JComboBoxEditor(statesList, true));

    TableColumnModel* _manualTurnoutColumnModel = manualTurnoutTable->getColumnModel();
    TableColumn* includeColumnC = _manualTurnoutColumnModel->
                                        getColumn(TurnoutModel::INCLUDE_COLUMN);
    includeColumnC->setResizable(false);
    includeColumnC->setMinWidth(50);
    includeColumnC->setMaxWidth(60);
    TableColumn* sNameColumnC = _manualTurnoutColumnModel->
                                        getColumn(TurnoutModel::SNAME_COLUMN);
    sNameColumnC->setResizable(true);
    sNameColumnC->setMinWidth(75);
    sNameColumnC->setMaxWidth(95);

    TableColumn* stateColumnC = _manualTurnoutColumnModel->
                                        getColumn(TurnoutModel::STATE_COLUMN);
    //stateColumnC->setCellEditor(new DefaultCellEditor(stateCCombo));
    stateColumnC->setResizable(false);
    stateColumnC->setMinWidth(90);
    stateColumnC->setMaxWidth(100);

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
    autoTurnoutTable = new JTable(_autoTurnoutModel); //) jmri.util.JTableUtil.sortableDataModel(_autoTurnoutModel);
//    try {
//        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)autoTurnoutTable.getModel());
//        tmodel->setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel->setSortingStatus(AutoTurnoutModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
    autoTurnoutTable->setSelectionMode(QAbstractItemView::NoSelection);
    //autoTurnoutTable->setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    autoTurnoutTable->setMinimumSize(280,100);

    TableColumnModel* _autoTurnoutColumnModel = autoTurnoutTable->getColumnModel();
    TableColumn* sNameColumnA = _autoTurnoutColumnModel->
                                        getColumn(AutoTurnoutModel::SNAME_COLUMN);
    sNameColumnA->setResizable(true);
    sNameColumnA->setMinWidth(75);
    sNameColumnA->setMaxWidth(95);

    TableColumn* stateColumnA = _autoTurnoutColumnModel->
                                        getColumn(AutoTurnoutModel::STATE_COLUMN);
    //stateColumnA->setCellEditor(new DefaultCellEditor(stateCCombo));
    stateColumnA->setResizable(false);
    stateColumnA->setMinWidth(90);
    stateColumnA->setMaxWidth(100);

    //_autoTurnoutScrollPane = new JScrollPane(autoTurnoutTable);
    p2xaLayout->addWidget(autoTurnoutTable);
    //contentPane->layout()->addWidget(p2xa);
    turnoutPanel->layout()->addWidget(p2xa);
    p2xa->setVisible(true);

    //ROW_HEIGHT = autoTurnoutTable->rowHeight(0);
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
    manualSensorTable = new JTable(_sensorModel);
    TableRowSorter/*<SensorModel>*/* manualSensorSorter = new TableRowSorter(_sensorModel);
    // configure row height for comboBox
    manualSensorTable->setRowHeight(JButton("sizer").sizeHint().height() - 2); // row height has to be greater than for plain tables
    manualSensorSorter->setComparator(SensorModel::SNAME_COLUMN, new AlphanumComparator());
    manualSensorSorter->setComparator(SensorModel::UNAME_COLUMN, new AlphanumComparator());
    RowSorterUtil::setSortOrder(manualSensorSorter, SensorModel::SNAME_COLUMN, SortOrder::ASCENDING);
//    _sensorModel.configStateColumn(manualSensorTable); // create static comboBox in State column
    manualSensorTable->setRowSorter(manualSensorSorter);
    manualSensorTable->setRowSelectionAllowed(false);
    manualSensorTable->setSortingEnabled(true);
    manualSensorTable->setModel(manualSensorSorter);//manualSensorTable->setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    manualSensorTable->setMinimumSize(280,100);
//    QComboBox* stateCCombo = new QComboBox();
//    stateCCombo->addItem(SET_TO_INACTIVE);
//    stateCCombo->addItem(SET_TO_ACTIVE);
    QStringList statesList;
    statesList << SET_TO_INACTIVE << SET_TO_ACTIVE;
    //manualSensorTable->setItemDelegateForColumn(SPTableModel::STATE_COLUMN, new SPComboBoxDelegate( statesList));
    _sensorModel->setColumnToHoldDelegate(manualSensorTable, SPTableModel::STATE_COLUMN, new JComboBoxEditor( statesList, true) );

    TableColumnModel* _manualSensorColumnModel = manualSensorTable->getColumnModel();
    TableColumn* includeColumnC = _manualSensorColumnModel->
                                        getColumn(SensorModel::INCLUDE_COLUMN);
    includeColumnC->setResizable(false);
    includeColumnC->setMinWidth(50);
    includeColumnC->setMaxWidth(60);
    TableColumn* sNameColumnC = _manualSensorColumnModel->
                                        getColumn(SensorModel::SNAME_COLUMN);
    sNameColumnC->setResizable(true);
    sNameColumnC->setMinWidth(75);
    sNameColumnC->setMaxWidth(95);

    TableColumn* stateColumnC = _manualSensorColumnModel->
                                        getColumn(SensorModel::STATE_COLUMN);
    //stateColumnC->setCellEditor(new DefaultCellEditor(stateCCombo));
    stateColumnC->setResizable(false);
    stateColumnC->setMinWidth(90);
    stateColumnC->setMaxWidth(100);

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
    manualSignalMastTable = new JTable(_signalMastModel);
    //_signalMastModel.makeJTable(sorter);
    //sorter->setTableHeader(manualSignalMastTable.getTableHeader());
    //manualSignalMastTable->setModel(_signalMastModel);

    manualSignalMastTable->setSelectionMode(QAbstractItemView::SingleSelection);
    manualSignalMastTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    //manualSignalMastTable->setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    manualSignalMastTable->setMinimumSize(280,100);

    TableColumnModel* _manualSignalMastColumnModel = manualSignalMastTable->getColumnModel();
    TableColumn* includeColumnC = _manualSignalMastColumnModel->
                                        getColumn(SignalMastModel::INCLUDE_COLUMN);
    includeColumnC->setResizable(false);
    includeColumnC->setMinWidth(50);
    includeColumnC->setMaxWidth(60);
    TableColumn* sNameColumnC = _manualSignalMastColumnModel->
                                        getColumn(SignalMastModel::SNAME_COLUMN);
    sNameColumnC->setResizable(true);
    sNameColumnC->setMinWidth(75);
    sNameColumnC->setMaxWidth(95);
    manualSignalMastTable->setItemDelegateForColumn(SPTableModel::STATE_COLUMN, new SignalMastComboBoxDelegate(this));

    //_manualSignalMastScrollPane = new JScrollPane(manualSignalMastTable);
    p2xm->layout()->addWidget(manualSignalMastTable);
    //contentPane.add(p2xm);
    signalMastPanel->layout()->addWidget(p2xm);
    p2xm->setVisible(true);

//    ROW_HEIGHT = manualSignalMastTable->rowHeight(0);
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
    JTable* autoMastTable = new JTable(_autoSignalMastModel);
    //jmri.util.JTableUtil.sortableDataModel(_autoSignalMastModel);
//    try {
//        jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)autoMastTable.getModel());
//        tmodel->setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        tmodel->setSortingStatus(AutoMastModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//    } catch (ClassCastException e3) {}  // if not a sortable table model
    autoMastTable->setSelectionMode(QAbstractItemView::SingleSelection);
    //autoMastTable->setPreferredScrollableViewportSize(new java.awt.Dimension(480,100));
    autoMastTable->setMinimumSize(280,100);

    TableColumnModel* _autoMastColumnModel = autoMastTable->getColumnModel();
    TableColumn* sNameColumnA = _autoMastColumnModel->
                                        getColumn(AutoMastModel::SNAME_COLUMN);
    sNameColumnA->setResizable(true);
    sNameColumnA->setMinWidth(75);
    sNameColumnA->setMaxWidth(95);

    TableColumn* stateColumnA = _autoMastColumnModel->
                                        getColumn(AutoMastModel::STATE_COLUMN);
    //stateColumnA->setCellEditor(new DefaultCellEditor(stateCCombo));
    stateColumnA->setResizable(false);
    stateColumnA->setMinWidth(90);
    stateColumnA->setMaxWidth(100);

    //_autoSignalMastScrollPane = new JScrollPane(autoMastTable);
    p2xsm->layout()->addWidget(autoMastTable);
    //contentPane->layout()->addWidget(p2xa);
    signalMastPanel->layout()->addWidget(p2xsm);
    p2xsm->setVisible(true);

    //ROW_HEIGHT = autoMastTable->rowHeight(0);
    p2xaSpace->setVisible(false);

    return signalMastPanel;
}

void SignallingPanel::updatePressed(/*ActionEvent e*/)
{
 sourceMast = (SignalMast*)sourceMastBox->getSelectedItem();
 destMast = (SignalMast*)destMastBox->getSelectedItem();

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
void SignallingPanel::setAssociatedSection(SignalMast* destMast){
        SectionManager* sm = (SectionManager*)InstanceManager::getDefault("SectionManager");
        if (!sml->getAutoBlocksBetweenMasts(destMast).isEmpty()) {
            Section* sec = sm->createNewSection(sml->getSourceMast()->getDisplayName() + ":" + destMast->getDisplayName());
            if (sec == nullptr) {
                //A Section already exists, lets grab it and check that it is one used with the SML, if so carry on using that.
                sec = sm->getSection(sml->getSourceMast()->getDisplayName() + ":" + destMast->getDisplayName());
                if (sec->getSectionType() != Section::SIGNALMASTLOGIC) {
                    return;
                }
            }
            sml->setAssociatedSection(sec, destMast);
        }
    }

/**
    * When Apply button is pressed, call updatePressed and afterwards close the
    * edit pane.
    *
    * @param e the event heard
    */
   void SignallingPanel::applyPressed(/*ActionEvent e*/) {
       updatePressed(/*e*/); // store edits
       if (destOK) { // enable user to correct configuration if warned the destMast is incorrect by skipping pane closing
           cancelPressed(/*e*/); // close panel signaling acceptance of edits/Apply to the user
       }
   }

   /**
    * Clean up when Cancel button is pressed.
    *
    * @param e the event heard
    */
   void SignallingPanel::cancelPressed(/*ActionEvent e*/) {
       if (jFrame != nullptr) {
           jFrame->setVisible(false);
           jFrame->dispose();
       }
       jFrame = nullptr;
   }

   int SignallingPanel::blockModeFromBox(JComboBox* box) {
       QString mode =  box->getSelectedItem();
       int result = StringUtil::getStateFromName(mode, blockInputModeValues.toVector(), blockInputModes.toVector());

       if (result < 0) {
           log->warn(tr("unexpected mode string in blockMode: %1").arg(mode));  // NOI18N
           throw  IllegalArgumentException();
       }
       return result;
   }

   void SignallingPanel::setBlockModeBox(int mode, JComboBox/*<String>*/* box) {
       QString result = StringUtil::getNameFromState(mode, blockInputModeValues.toVector(), blockInputModes);
       box->setSelectedItem(result);
   }

   ///*public*/ void initComponents(){

//}

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
            box->setSelectedIndex(i);
        }
    }
}
#endif

void SignallingPanel::editDetails(){

    int setRow = 0;
    for (int i=_manualBlockList.size()-1; i>=0; i--) {
        ManualBlockList* block = _manualBlockList.at(i);
        QString tSysName = block->getSysName();
        Block* blk = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(tSysName);
        if (((DefaultSignalMastLogic*)sml)->isBlockIncluded(blk, destMast)) {
            block->setIncluded(true);
            block->setState(((DefaultSignalMastLogic*)sml)->getBlockState(blk, destMast));
            setRow = i;
        } else {
            block->setIncluded(false);
            block->setState(Block::UNOCCUPIED);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    //_manualBlockScrollPane->getVerticalScrollBar()->setValue(setRow*ROW_HEIGHT);
    manualBlockTable->scrollTo(_blockModel->index(setRow,0));
    _blockModel->fireTableDataChanged();

    setRow = 0;
    for (int i=_manualTurnoutList.size()-1; i>=0; i--) {
        ManualTurnoutList* turnout = _manualTurnoutList.at(i);
        QString tSysName = turnout->getSysName();
        Turnout* turn = InstanceManager::turnoutManagerInstance()->getTurnout(tSysName);
        if (((DefaultSignalMastLogic*)sml)->isTurnoutIncluded(turn, destMast)) {
            turnout->setIncluded(true);
            turnout->setState(((DefaultSignalMastLogic*)sml)->getTurnoutState(turn, destMast));
            setRow = i;
        } else {
            turnout->setIncluded(false);
            turnout->setState(Turnout::CLOSED);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    //_manualSensorScrollPane.getVerticalScrollBar()->setValue(setRow*ROW_HEIGHT);
    manualSensorTable->scrollTo(_sensorModel->index(setRow,0));
    _sensorModel->fireTableDataChanged();

    setRow = 0;
    for (int i=_manualSensorList.size()-1; i>=0; i--) {
        ManualSensorList* sensor = _manualSensorList.at(i);
        QString tSysName = sensor->getSysName();
        Sensor* sen = InstanceManager::sensorManagerInstance()->getSensor(tSysName);
        if (((DefaultSignalMastLogic*)sml)->isSensorIncluded(sen, destMast)) {
            sensor->setIncluded(true);
            sensor->setState(((DefaultSignalMastLogic*)sml)->getSensorState(sen, destMast));
            setRow = i;
        } else {
            sensor->setIncluded(false);
            sensor->setState(Sensor::INACTIVE);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    //_manualSensorScrollPane.getVerticalScrollBar()->setValue(setRow*ROW_HEIGHT);
    manualSensorTable->scrollTo(_sensorModel->index(setRow,0));
    _sensorModel->fireTableDataChanged();

    setRow = 0;
    for (int i=_manualSignalMastList.size()-1; i>=0; i--) {
        ManualSignalMastList* mast = _manualSignalMastList.at(i);
        SignalMast* sigMast = _manualSignalMastList.at(i)->getMast();
        if (((DefaultSignalMastLogic*)sml)->isSignalMastIncluded(sigMast, destMast)) {
            mast->setIncluded(true);
            mast->setSetToState(((DefaultSignalMastLogic*)sml)->getSignalMastState(sigMast, destMast));
            setRow = i;
        } else {
            mast->setIncluded(false);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    //_manualSignalMastScrollPane.getVerticalScrollBar()->setValue(setRow*ROW_HEIGHT);
    manualSignalMastTable->scrollTo(_signalMastModel->index(setRow, 0));
    _signalMastModel->fireTableDataChanged();
}

//private abstract class SignalMastElement {

    SignalMastElement::SignalMastElement(SignallingPanel* signallingPanel)
    {
        this->signallingPanel = signallingPanel;
    }

    SignalMastElement::SignalMastElement(QString sysName, QString userName, SignallingPanel* signallingPanel) {
        _sysName = sysName;
        _userName = userName;
        _included = false;
        _setToState = Sensor::INACTIVE;
        this->signallingPanel = signallingPanel;
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

//private class ManualBlockList extends SignalMastElement {
    ManualBlockList::ManualBlockList(Block* block, SignallingPanel* signallingPanel) : SignalMastElement(signallingPanel) {
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
                return signallingPanel->SET_TO_OCCUPIED;
            case Block::UNOCCUPIED:
                return signallingPanel->SET_TO_UNOCCUPIED;
        }
        return signallingPanel->SET_TO_ANY;
    }

    void ManualBlockList::setSetToState(QString state) {
        if (signallingPanel->SET_TO_UNOCCUPIED==(state)) {
            _setToState = Block::UNOCCUPIED;
        } else if (signallingPanel->SET_TO_OCCUPIED==(state)) {
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
                return signallingPanel->SET_TO_THROWN;
            case Turnout::CLOSED:
                return signallingPanel->SET_TO_CLOSED;
        }
        return signallingPanel->SET_TO_ANY;
    }

    void ManualTurnoutList::setSetToState(QString state) {
        if (signallingPanel->SET_TO_THROWN==(state)) {
            _setToState = Turnout::THROWN;
        } else if (signallingPanel->SET_TO_CLOSED==(state)) {
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
                return signallingPanel->SET_TO_INACTIVE;
            case Sensor::ACTIVE:
                return signallingPanel->SET_TO_ACTIVE;
        }
        return "";
    }
    void ManualSensorList::setSetToState(QString state)
    {
        if (signallingPanel->SET_TO_INACTIVE==(state))
        {
            _setToState = Sensor::INACTIVE;
        } else if (signallingPanel->SET_TO_ACTIVE==(state)) {
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
    SPTableModel::SPTableModel(SignallingPanel *signallingPanel)
    {
     this->signallingPanel = signallingPanel;
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
         if(qobject_cast<BlockManager*>(e->getSource()))
         {
          BlockManager* bm = ((BlockManager*)InstanceManager::getDefault("BlockManager"));
          QStringList systemNameList = bm->getSystemNameList();
          signallingPanel->_manualBlockList =  QList<ManualBlockList*> (); //systemNameList.size());
          QStringListIterator iter(systemNameList);
          while (iter.hasNext())
          {
           QString systemName = iter.next();
           //String userName = bm.getBySystemName(systemName).getUserName();
           signallingPanel->_manualBlockList.append(new ManualBlockList((Block*)bm->getBySystemName(systemName),signallingPanel));
          }
          signallingPanel->initializeIncludedList();
          fireTableDataChanged();
         }
         else if(qobject_cast<SensorManager*>(e->getSource()))
         {
          SensorManager* bm = InstanceManager::sensorManagerInstance();
          QStringList systemNameList = ((ProxySensorManager*)bm)->getSystemNameList();
          signallingPanel->_manualSensorList =  QList <ManualSensorList*> (); //systemNameList.size());
          QStringListIterator iter (systemNameList);
          while (iter.hasNext()) {
              QString systemName = iter.next();
              QString userName = ((ProxySensorManager*)bm)->getBySystemName(systemName)->getUserName();
              signallingPanel->_manualSensorList.append(new ManualSensorList(systemName, userName, signallingPanel));
          }
          signallingPanel->initializeIncludedList();
          fireTableDataChanged();
         }
         else if(qobject_cast<TurnoutManager*>(e->getSource()))
         {
          TurnoutManager* bm = InstanceManager::turnoutManagerInstance();
          QStringList systemNameList = ((ProxyTurnoutManager*)bm)->getSystemNameList();
          signallingPanel->_manualTurnoutList =  QList <ManualTurnoutList*> (); //systemNameList.size());
          QStringListIterator iter(systemNameList);
          while (iter.hasNext()) {
              QString systemName = iter.next();
              QString userName = ((ProxyTurnoutManager*)bm)->getBySystemName(systemName)->getUserName();
              signallingPanel->_manualTurnoutList.append(new ManualTurnoutList(systemName, userName,signallingPanel));
          }
          signallingPanel->initializeIncludedList();
          fireTableDataChanged();
         }
         else if(qobject_cast<SignalMastManager*>(e->getSource()))
         {
          SignalMastManager* bm = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"));
          QStringList systemNameList = ((DefaultSignalMastManager*)bm)->getSystemNameList();
          signallingPanel->_manualSignalMastList = QList <ManualSignalMastList*> (); //systemNameList.size());
          QStringListIterator iter (systemNameList);
          while (iter.hasNext()) {
              QString systemName = iter.next();
              signallingPanel->_manualSignalMastList.append(new ManualSignalMastList(((DefaultSignalMastManager*)bm)->getBySystemName(systemName),signallingPanel));
          }
          signallingPanel->initializeIncludedList();
          fireTableDataChanged();
         }
        }
    }

    /*public*/ void SPTableModel::dispose() {
        InstanceManager::turnoutManagerInstance()->removePropertyChangeListener(this);
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
    BlockModel::BlockModel(SignallingPanel* signallingPanel) : SPTableModel(signallingPanel)
    {
     BlockManager* mgr = qobject_cast<BlockManager*>(InstanceManager::getDefault("BlockManager")); //.addPropertyChangeListener(this);
     mgr->addPropertyChangeListener(this);
     connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }

    /*public*/ int BlockModel::rowCount(const QModelIndex &/*parent*/) const{
        if (signallingPanel->showAll)
            return signallingPanel->_manualBlockList.size();
        else
            return signallingPanel->_includedManualBlockList.size();
    }

//    /*public*/ static final int SPEED_COLUMN = 4;
//    /*public*/ static final int PERMISSIVE_COLUMN = 5;

    /*public*/ int BlockModel::columnCount(const QModelIndex &/*parent*/) const {return 6;}

    /*public*/ QVariant BlockModel::data(const QModelIndex &index, int role) const
    {
     int c = index.column();
     int r = index.row();
     QList <ManualBlockList*> blockList = QList <ManualBlockList*>();
     if (signallingPanel->showAll)
      blockList = signallingPanel->_manualBlockList;
     else
      blockList = signallingPanel->_includedManualBlockList;
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
      default:
       break;
       }
     }
     return QVariant();
    }

    /*public*/ QString BlockModel::getColumnClass(int c) const{
        if (c == PERMISSIVE_COLUMN) {
            return "Boolean";
        }
        return SPTableModel::getColumnClass(c);
    }

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
        if (signallingPanel->showAll)
            blockList = signallingPanel->_manualBlockList;
        else
            blockList = signallingPanel->_includedManualBlockList;
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
        if (signallingPanel->showAll)
            return signallingPanel->_manualTurnoutList.size();
        else
            return signallingPanel->_includedManualTurnoutList.size();
    }

    /*public*/ QVariant TurnoutModel::data(const QModelIndex &index, int role) const
    {
     int c= index.column();
     int r = index.column();
     QList <ManualTurnoutList*> turnoutList = QList <ManualTurnoutList*>();
     if (signallingPanel->showAll)
         turnoutList = signallingPanel->_manualTurnoutList;
     else
         turnoutList = signallingPanel->_includedManualTurnoutList;
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
        if (signallingPanel->showAll) {
            turnoutList = signallingPanel->_manualTurnoutList;
        }
        else {
            turnoutList = signallingPanel->_includedManualTurnoutList;
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
        if (signallingPanel->showAll)
            return signallingPanel->_manualSensorList.size();
        else
            return signallingPanel->_includedManualSensorList.size();
    }

    /*public*/ QVariant SensorModel::data(const QModelIndex &index, int role) const
    {
     int r = index.row();
     int c = index.column();
     QList <ManualSensorList*> sensorList = QList <ManualSensorList*>();
     if (signallingPanel->showAll)
         sensorList = signallingPanel->_manualSensorList;
     else
         sensorList = signallingPanel->_includedManualSensorList;
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
        if (signallingPanel->showAll) {
            sensorList = signallingPanel->_manualSensorList;
        }
        else
        {
            sensorList = signallingPanel->_includedManualSensorList;
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
        if (signallingPanel->showAll)
            return signallingPanel->_manualSignalMastList.size();
        else
            return signallingPanel->_includedManualSignalMastList.size();
    }

    /*public*/ QVariant SignalMastModel::data(const QModelIndex &index, int role) const
    {
     int r = index.row();
     int c = index.column();
     QList <ManualSignalMastList*> signalMastList = QList <ManualSignalMastList*>();
     if (signallingPanel->showAll)
      signalMastList = signallingPanel->_manualSignalMastList;
     else
      signalMastList = signallingPanel->_includedManualSignalMastList;
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
       if (signallingPanel->showAll)
       {
        signalMastList = signallingPanel->_manualSignalMastList;
       }
       else
       {
        signalMastList = signallingPanel->_includedManualSignalMastList;
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

    AutoTableModel::AutoTableModel(SignallingPanel* signallingPanel)
    {
     this->signallingPanel = signallingPanel;
        smlValid();
    }

    /*public*/ void AutoTableModel::smlValid()
    {
     if (signallingPanel->sml!=NULL)
     {
//            ((DefaultSignalMastLogic*)sml)->addPropertyChangeListener(this);
      DefaultSignalMastLogic* l = (DefaultSignalMastLogic*)signallingPanel->sml;
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
     if (this->signallingPanel->sml!=NULL)
     {
      //((DefaultSignalMastLogic*)sml)->addPropertyChangeListener(this);
      DefaultSignalMastLogic* l = (DefaultSignalMastLogic*)this->signallingPanel->sml;
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
            signallingPanel->initializeIncludedList();
            fireTableDataChanged();
        }
    }

    /*public*/ QString AutoBlockModel::getColumnClass(int c) {
        if (c == PERMISSIVE_COLUMN) {
            return "Boolean";
        }
        return AutoTableModel::getColumnClass(c);
    }

    /*public*/ int AutoBlockModel::rowCount(const QModelIndex &/*parent*/) const {
        return signallingPanel->_automaticBlockList->size();
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
                return signallingPanel->_automaticBlockList->at(r)->getSysName();
            case UNAME_COLUMN:  //
                return signallingPanel->_automaticBlockList->at(r)->getUserName();
            case STATE_COLUMN:
                return signallingPanel->_automaticBlockList->at(r)->getSetToState();
            case SPEED_COLUMN:
                return signallingPanel->_automaticBlockList->at(r)->getBlockSpeed();
            default:
                break;
        }
     }
     if(role == Qt::CheckStateRole)
     {
      if( c == PERMISSIVE_COLUMN)
      {
             //return new Boolean(_automaticBlockList.get(r).getPermissiveWorking());
             return signallingPanel->_automaticBlockList->at(r)->getPermissiveWorking()?Qt::Checked:Qt::Unchecked;
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
        return signallingPanel->_automaticTurnoutList->size();
    }

    /*public*/ void AutoTurnoutModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()==("autoturnouts")) {
            // a new NamedBean is available in the manager
            signallingPanel->initializeIncludedList();
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
                return signallingPanel->_automaticTurnoutList->at(r)->getSysName();
            case UNAME_COLUMN:  //
                return signallingPanel->_automaticTurnoutList->at(r)->getUserName();
            case STATE_COLUMN:
                return signallingPanel->_automaticTurnoutList->at(r)->getSetToState();
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
        return signallingPanel->_automaticSignalMastList->size();
    }

    /*public*/ void AutoMastModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()==("automasts")) {
            // a new NamedBean is available in the manager
            signallingPanel->initializeIncludedList();
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
                return signallingPanel->_automaticSignalMastList->at(r)->getSysName();
            case UNAME_COLUMN:  //
                return signallingPanel->_automaticSignalMastList->at(r)->getUserName();
            case STATE_COLUMN:
                return signallingPanel->_automaticSignalMastList->at(r)->getSetToState();
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
            super->setBackground(table.getSelectionBackground());
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
    : JComboBoxEditor(false, parent)
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
