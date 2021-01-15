#include "sectiontableaction.h"
#include "instancemanager.h"
#include "sectionmanager.h"
#include "jmriuserpreferencesmanager.h"
#include "jtextfield.h"
#include <namedbean.h>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QCheckBox>
#include "beantableframe.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include "flowlayout.h"
#include <QTableView>
#include "abstractsensor.h"
#include "panelmenu.h"
#include "layouteditor.h"
#include "entrypoint.h"
#include "systemnamecomparator.h"
#include "logixtableaction.h"
#include "transit.h"
#include "transitmanager.h"
#include "jdialog.h"
#include "borderlayout.h"
#include <QMenuBar>
#include <QMenu>
#include "inputdialog.h"
#include "path.h"
#include "actionevent.h"
#include "QHeaderView"

SectionTableAction::SectionTableAction(QObject *parent) :
    AbstractTableAction("Section Table", parent)
{
}

/**
 * Swing action to create and register a
 * SectionTable GUI.
  <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation. See the "COPYING" file for
 * a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author	Dave Duchamp    Copyright (C) 2008, 2011
 * @version     $Revision: 19235 $
 */
// GT - 12-Oct-2009 - Added "Entry Block" column in entryPointTable

// /*public*/ class SectionTableAction extends AbstractTableAction {

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param actionName
 */
/*public*/ SectionTableAction::SectionTableAction(QString actionName, QObject *parent) : AbstractTableAction(actionName, parent)
{
 //super(actionName);
 blockList = QList<Block*>();
 blockTableModel = NULL;
 entryPointTableModel = NULL;
    sectionManager = NULL;
    blockManager = ((BlockManager*)InstanceManager::getDefault("BlockManager"));
    editMode = false;
    curSection = NULL;
    addCreateActive = true;
    lePanelList = NULL;
    curLayoutEditor = NULL;
    blockBoxList = QList<Block*>();
    beginBlock = NULL;
    endBlock = NULL;
    fSensor = NULL;
    rSensor = NULL;
    fStopSensor = NULL;
    rStopSensor = NULL;
    entryPointList = QList<EntryPoint*>();
    manualEntryPoints = true;
    frame = NULL;
    panel = NULL;
    log = new Logger("SectionTableAction");

    // add/create variables
    addFrame = NULL;
    sysName = new JTextField(5);
    sysNameFixed = new QLabel("");
    userName = new JTextField(17);
    sysNameLabel = new QLabel(tr("System Name:"));
    userNameLabel = new QLabel(tr("User Name:"));
    _autoSystemName = new QCheckBox(tr("Auto Sys Name"));
    create = NULL;
    update = NULL;
    blockBox = new QComboBox();
    addBlock = NULL;
    deleteBlocks = NULL;
    layoutEditorBox = new QComboBox();
    forwardSensorField = new JTextField(12);
    reverseSensorField = new JTextField(12);
    forwardStopSensorField = new JTextField(12);
    reverseStopSensorField = new JTextField(12);
    manually = new QRadioButton(tr("Set Manually")/*,true*/);
 manually->setChecked(true);
 automatic = new QRadioButton(tr("Set Using Connectivity from Layout Editor Panel:")/*,false*/);
 entryPointOptions = NULL;
 systemNameAuto = "SectionTableAction.AutoSystemName";

 // set manager - no need to use InstanceManager here
 sectionManager = ((SectionManager*)InstanceManager::getDefault("SectionManager"));
 // disable ourself if there is no Section manager available
 if (sectionManager==NULL)
 {
  setEnabled(false);
 }
}

void SectionTableAction::setEnabled(bool b) { enabled = b;}

//    /*public*/ SectionTableAction() { this(tr("TitleSectionTable"));}

//    static final ResourceBundle rbx = ResourceBundle
//            .getBundle("jmri.jmrit.beantable.SectionTransitTableBundle");


/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of Section objects
 */
/*protected*/ void SectionTableAction::createModel()
{
 m = new SectionTableDataModel(this);
}

SectionTableDataModel::SectionTableDataModel(SectionTableAction *act)
 : BeanTableDataModel(act)
{
 this->act = act;
 log = new Logger("SectionTableAction");
 setManager(act->sectionManager);
 connect(act->sectionManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 init();
}

/*public*/ QString SectionTableDataModel::getValue(QString /*name*/) const
{
    return "";
}
/*public*/ Manager* SectionTableDataModel::getManager() { return ((SectionManager*)InstanceManager::getDefault("SectionManager")); }
/*public*/ NamedBean* SectionTableDataModel::getBySystemName(QString name) const
{
    return ((SectionManager*)InstanceManager::getDefault("SectionManager"))->getBySystemName(name);
}
/*public*/ NamedBean* SectionTableDataModel::getByUserName(QString name) {
    return ((SectionManager*)InstanceManager::getDefault("SectionManager"))->getByUserName(name);
}

/*public int getDisplayDeleteMsg() { return InstanceManager::getDefault(jmri.UserPreferencesManager.class).getMultipleChoiceOption(getClassName(),"delete"); }
public void setDisplayDeleteMsg(int boo) { ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->setMultipleChoiceOption(getClassName(), "delete", boo); }*/
/*protected*/ QString SectionTableDataModel::getMasterClassName() { return act->getClassName(); }

/*public*/ void SectionTableDataModel::clickOn(NamedBean* /*t*/) {
}

/*public*/ int SectionTableDataModel::columnCount(const QModelIndex &/*parent*/) const
{
    return EDITCOL+1;
}

/*public*/ QVariant SectionTableDataModel::data(const QModelIndex &index, int role) const
{
 int row = index.row();
 int col = index.column();

 // some error checking
 if (row >= sysNameList.size())
 {
  log->debug("row is greater than name list");
  return QVariant();
 }
 if(role == Qt::DisplayRole)
 {
    if (col==BEGINBLOCKCOL) {
        Section* z = (Section*)getBySystemName(sysNameList.at(row));
        if (z != NULL) {
            return z->getBeginBlockName();
        }
        return "  ";
    }
    else if (col==ENDBLOCKCOL) {
        Section* z = (Section*)getBySystemName(sysNameList.at(row));
        if (z != NULL) {
            return z->getEndBlockName();
        }
        return "  ";
    }
    else if (col==VALUECOL) {
        Section* z = (Section*)getBySystemName(sysNameList.at(row));
        if (z == NULL) {
            return "";
        }
        else {
            int state = z->getState();
            if (state==Section::FREE) return (tr("FREE"));
            else if (state==Section::FORWARD) return (tr("FORWARD"));
            else if (state==Section::REVERSE) return (tr("REVERSE"));
        }
    }
    else if (col==EDITCOL) return tr("Edit");
 }
  return BeanTableDataModel::data(index, role);
}

/*public*/ bool SectionTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int col = index.column();
 int row = index.row();
 if(role == Qt::EditRole)
 {
  if ( (col==BEGINBLOCKCOL) || (col==ENDBLOCKCOL) )
  {
   return true;
  }
  else if (col == EDITCOL)
  {
//        class WindowMaker implements Runnable {
//            int row;
//            WindowMaker(int r){
//                row = r;
//            }
//            /*public*/ void run() {
                QString sName = data(this->index(row, SYSNAMECOL), Qt::DisplayRole).toString();
                act->editPressed(sName);
//            }
//        };
//        WindowMaker t = new WindowMaker(row);
//        javax.swing.SwingUtilities.invokeLater(t);
    return true;
  }
  else if (col == DELETECOL)
  {
   // act->deleteSectionPressed (sysNameList.at(row)); // will be handled by PBItemDelegate!
   return true;
  }
 }
  return BeanTableDataModel::setData(index, value, role);
}

/*public*/ QVariant SectionTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
     int col = section;
    if (col==BEGINBLOCKCOL) return (tr("First Block"));
    if (col==ENDBLOCKCOL) return (tr("Last Block"));
    if (col==EDITCOL) return "";   // no namne on Edit column
 }
 return BeanTableDataModel::headerData(section,orientation,role);
}

///*public*/ Class<?> getColumnClass(int col) {
//    if (col==VALUECOL) return String.class;  // not a button
//    if (col==BEGINBLOCKCOL) return String.class;  // not a button
//    if (col==ENDBLOCKCOL) return String.class;  // not a button
//    if (col==EDITCOL) return JButton.class;
//    else return super.getColumnClass(col);
//}

 /*public*/ Qt::ItemFlags SectionTableDataModel::flags(const QModelIndex &index) const
 {
    int col = index.column();
    if (col == BEGINBLOCKCOL) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (col == ENDBLOCKCOL) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (col == VALUECOL) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (col == EDITCOL) return Qt::ItemIsEnabled |  Qt::ItemIsEditable;
    else return BeanTableDataModel::flags(index);
}

/*public*/ int SectionTableDataModel::getPreferredWidth(int col) {
    // override default value for SystemName and UserName columns
    if (col == SYSNAMECOL)return  JTextField(9).getPreferredSize().width();
    if (col == USERNAMECOL)return  JTextField(17).getPreferredSize().width();
    if (col == VALUECOL)return  JTextField(6).getPreferredSize().width();
    // new columns
    if (col==BEGINBLOCKCOL) return  JTextField(15).getPreferredSize().width();
    if (col==ENDBLOCKCOL) return  JTextField(15).getPreferredSize().width();
    if (col==EDITCOL) return  JTextField(6).getPreferredSize().width();
    else return BeanTableDataModel::getPreferredWidth(col);
}

/*public*/ void SectionTableDataModel::configValueColumn(JTable* /*table*/) {
    // value column isn't button, so config is NULL
}

/*public*/ void SectionTableDataModel::configureTable(JTable *table)
{
 setColumnToHoldButton(table, EDITCOL);
 BeanTableDataModel::configureTable(table);
}

/*protected*/ bool SectionTableDataModel::matchPropertyName(PropertyChangeEvent* /*e*/) {
    return true;
    // return (e.getPropertyName().indexOf("alue")>=0);
}

/*protected*/ QString SectionTableDataModel::getBeanType(){
    return "Section";
}
//};
//}

/*protected*/ void SectionTableAction::setTitle() {
    f->setTitle(tr("Section Table"));
}

/*protected*/ QString SectionTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SectionTable";
}


/**
 * Responds to the Add... button and the Edit buttons in Section Table
 */
/*protected*/ void SectionTableAction::addPressed() {
    editMode = false;
    if ((blockManager->getSystemNameList().size()) > 0) {
        addEditPressed();
    }
    else {
//        javax.swing.JOptionPane.showMessageDialog(NULL, rbx
//                .getString("Message1"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(NULL, tr("Error"), tr("Sections require Blocks and Paths. Please define them before creating Sections."));
    }
}
void SectionTableAction::editPressed(QString sName) {
    curSection = (Section*)sectionManager->getBySystemName(sName);
    if (curSection==NULL) {
        // no section - should never happen, but protects against a $%^#@ exception
        return;
    }
    sysNameFixed->setText(sName);
    editMode = true;
    addEditPressed();
}
void SectionTableAction::addEditPressed()
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 if (addFrame==NULL)
 {
  addFrame = new JmriJFrameX(tr("Add Section"));
  addFrame->addHelpMenu("package.jmri.jmrit.beantable.SectionAddEdit", true);
  addFrame->resize(650,800);
  //addFrame.getContentPane().setLayout(new BoxLayout(addFrame.getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* addFrameLayout = new QVBoxLayout(addFrame->getContentPane());
//        JPanel p = new JPanel();
//        p.setLayout(new FlowLayout());
  FlowLayout* pLayout = new FlowLayout;
  pLayout->addWidget(sysNameLabel);
  pLayout->addWidget(sysNameFixed);
  pLayout->addWidget(sysName);
  pLayout->addWidget(_autoSystemName);
//        _autoSystemName.addActionListener(new ActionListener(){
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    autoSystemName();
//                }
//            });
  connect(_autoSystemName, SIGNAL(clicked()), this, SLOT(autoSystemName()));
  if(pref->getSimplePreferenceState(systemNameAuto))
   _autoSystemName->setChecked(true);
  sysName->setToolTip(tr("Enter system name for new Section, e.g.IY13"));
  pLayout->addWidget (new QLabel("     "));
  pLayout->addWidget(userNameLabel);
  pLayout->addWidget(userName);
  userName->setToolTip(tr("Enter user name for Section, e.g. Sloan to Baxter"));
  addFrameLayout->addLayout(pLayout);
  QFrame* separator = new QFrame;
  separator->setFrameStyle(QFrame::HLine);
  separator->setLineWidth(2);
  addFrameLayout->addWidget(/*new JSeparator()*/separator);
//        JPanel p1 = new JPanel();
//        p1.setLayout(new BoxLayout(p1, BoxLayout.Y_AXIS));
  QVBoxLayout* p1Layout = new QVBoxLayout;
//        JPanel p11 = new JPanel();
//        p11.setLayout(new FlowLayout());
  FlowLayout* p11Layout = new FlowLayout;
  p11Layout->addWidget(new QLabel(tr("Blocks in Section (at least 1 is required)")));
  p1Layout->addLayout(p11Layout);
//        JPanel p12 = new JPanel();
  // initialize table of blocks
  blockTableModel = new BlockTableModel(this);
  QTableView* blockTable = new QTableView(/*blockTableModel*/);
  blockTable->setModel(blockTableModel);
  blockTable->resizeColumnsToContents();
  blockTable->setMinimumSize(350,100);
//        blockTable.setRowSelectionAllowed(false);
//        blockTable.setPreferredScrollableViewportSize(new java.awt.Dimension(350,100));
//        TableColumnModel blockColumnModel = blockTable.getColumnModel();
//        TableColumn sNameColumn = blockColumnModel.getColumn(BlockTableModel.SNAME_COLUMN);
//        sNameColumn.setResizable(true);
//        sNameColumn.setMinWidth(90);
  blockTable->setColumnWidth(BlockTableModel::SNAME_COLUMN,90);
//        sNameColumn.setMaxWidth(130);
//        TableColumn uNameColumn = blockColumnModel.getColumn(BlockTableModel.UNAME_COLUMN);
//        uNameColumn.setResizable(true);
//        uNameColumn.setMinWidth(210);
//        uNameColumn.setMaxWidth(260);
//        JScrollPane blockTableScrollPane = new JScrollPane(blockTable);
//        p12.add(blockTableScrollPane, BorderLayout.CENTER);
  p1Layout->addWidget(blockTable);
//        JPanel p13 = new JPanel();
//        p13.setLayout(new FlowLayout());
  FlowLayout* p13Layout = new FlowLayout();
  p13Layout->addWidget( deleteBlocks = new QPushButton(tr("Delete All Blocks")));
//        deleteBlocks.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                deleteBlocksPressed(e);
//            }
//        });
  connect(deleteBlocks, SIGNAL(clicked()),this, SLOT(deleteBlocksPressed()));
  deleteBlocks->setToolTip(tr("Press to delete all Blocks in the above table and start again."));
  p13Layout->addWidget(new QLabel("     "));
  p13Layout->addWidget(blockBox);
  blockBox->setToolTip(tr("BlockBoxHint"));
  p13Layout->addWidget(addBlock = new QPushButton(tr("Add Selected Block")));
//        addBlock.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addBlockPressed(e);
//            }
//        });
  connect(addBlock, SIGNAL(clicked()), this, SLOT(addBlockPressed()));
  addBlock->setToolTip(tr("Press to add the Block selected at the left."));
  p1Layout->addLayout(p13Layout);
  addFrameLayout->addLayout(p1Layout);
  separator = new QFrame;
  separator->setFrameStyle(QFrame::HLine);
  separator->setLineWidth(2);
  addFrameLayout->addWidget(/*new JSeparator()*/separator);
//        JPanel p31 = new JPanel();
//        p31.setLayout(new FlowLayout());
  FlowLayout* p31Layout = new FlowLayout();
  p31Layout->addWidget(new QLabel(tr("Table of Entry Points")));
  addFrameLayout->addLayout(p31Layout);
//        JPanel p32 = new JPanel();
//        p32.setLayout(new FlowLayout());
  FlowLayout* p32Layout = new FlowLayout();
  entryPointOptions = new QButtonGroup();
  p32Layout->addWidget(manually);
  entryPointOptions->addButton(manually);
//        manually.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                manualEntryPoints = true;
//            }
//        });
  connect(manually, SIGNAL(clicked()), this, SLOT(OnManually_Clicked()));
  manually->setToolTip(tr("Select this radio button to allow manual editing of Entry Point direction."));
  p32Layout->addWidget(new QLabel("   "));
  p32Layout->addWidget(automatic);
  entryPointOptions->addButton(automatic);
//        automatic.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                manualEntryPoints = false;
//            }
//        });
  connect(automatic, SIGNAL(clicked()), this, SLOT(OnAutomatic_Clicked()));
  automatic->setToolTip(tr("Select this radio button for automatic setting of Entry Point direction."));
  p32Layout->addWidget(layoutEditorBox);
  layoutEditorBox->setToolTip(tr("Select a Layout Editor panel, then select radio button to use it."));
//        layoutEditorBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                layoutEditorSelectionChanged();
//            }
//        });
  connect(layoutEditorBox, SIGNAL(currentIndexChanged(int)), this, SLOT(layoutEditorSelectionChanged()));
// djd debugging - temporarily hide these items until the automatic setting of entry point direction is ready
//			addFrameLayout->add(p32);
  addFrameLayout->addLayout(p32Layout);
// end djd debugging
//        JPanel p33 = new JPanel();
  // initialize table of entry points
  entryPointTableModel = new EntryPointTableModel(this);
  JTable* entryPointTable = new JTable(/*entryPointTableModel*/);
  entryPointTable->setModel(entryPointTableModel);
//        entryPointTable.setRowSelectionAllowed(false);
//        entryPointTable.setPreferredScrollableViewportSize(new java.awt.Dimension(550,100)); // GT - 12-Oct-2009
  entryPointTable->setMinimumSize(550,100);
//        TableColumnModel entryPointColumnModel = entryPointTable.getColumnModel();
//        TableColumn fromBlockColumn = entryPointColumnModel.getColumn(EntryPointTableModel.BLOCK_COLUMN);
//        fromBlockColumn.setResizable(true);
//        fromBlockColumn.setMinWidth(250);
//        fromBlockColumn.setMaxWidth(310);
//// GT - 12-Oct-2009 - start
//        TableColumn toBlockColumn = entryPointColumnModel.getColumn(EntryPointTableModel.TO_BLOCK_COLUMN);
//        toBlockColumn.setResizable(true);
//        toBlockColumn.setMinWidth(150);
//        toBlockColumn.setMaxWidth(210);
// GT - 12-Oct-2009 - end
//  QComboBox* directionCombo = new QComboBox();
//  directionCombo->addItem(tr("FORWARD"));
//  directionCombo->addItem(tr("REVERSE"));
//  directionCombo->addItem(tr("UNKNOWN"));
  QStringList dirList;
  dirList << tr("FORWARD") << tr("REVERSE") << tr("UNKNOWN");
//        TableColumn directionColumn = entryPointColumnModel.getColumn(EntryPointTableModel.DIRECTION_COLUMN);
//        directionColumn.setCellEditor(new DefaultCellEditor(directionCombo));
//        entryPointTable.setRowHeight(directionCombo.getPreferredSize().height);
//        directionColumn.setPreferredWidth(directionCombo.getPreferredSize().width);
//        directionColumn.setResizable(false);
//        JScrollPane entryPointTableScrollPane = new JScrollPane(entryPointTable);
//        p33.add(entryPointTableScrollPane, BorderLayout.CENTER);
//        addFrameLayout->add(p33);
//        p33->setVisible(true);
  addFrameLayout->addWidget(entryPointTable);
  entryPointTable->setItemDelegateForColumn(EntryPointTableModel::DIRECTION_COLUMN, new JComboBoxEditor(dirList,this));
  entryPointTable->resizeColumnsToContents();
//        JPanel p34 = new JPanel();
//        p34.setLayout(new FlowLayout());
  FlowLayout* p34Layout = new FlowLayout;
  p34Layout->addWidget(new QLabel(tr("Note: FORWARD direction is from the top Block toward the bottom Block.")));
  addFrameLayout->addLayout(p34Layout);
        separator = new QFrame;
                separator->setFrameStyle(QFrame::HLine);
                separator->setLineWidth(2);addFrameLayout->addWidget(/*new JSeparator()*/separator);
        // set up for direction sensors
//        JPanel p20 = new JPanel();
//        p20.setLayout(new FlowLayout());
        FlowLayout* p20Layout = new FlowLayout;
        p20Layout->addWidget(new QLabel(tr("Direction Sensors (Optional)")));
        addFrameLayout->addLayout(p20Layout);
//        JPanel p21 = new JPanel();
//        p21.setLayout(new FlowLayout());
        FlowLayout* p21Layout = new FlowLayout;
        p21Layout->addWidget(new QLabel(tr("Forward Sensor:")));
        p21Layout->addWidget(forwardSensorField);
        forwardSensorField->setToolTip(tr("Enter forward sensor name (system or user)."));
        p21Layout->addWidget (new QLabel("     "));
        p21Layout->addWidget(new QLabel(tr("Reverse Sensor:")));
        p21Layout->addWidget(reverseSensorField);
        reverseSensorField->setToolTip(tr("Enter reverse sensor name (system or user)."));
        addFrameLayout->addLayout(p21Layout);
        separator = new QFrame;
                separator->setFrameStyle(QFrame::HLine);
                separator->setLineWidth(2);addFrameLayout->addWidget(/*new JSeparator()*/ separator);
        // set up for stopping sensors
//        JPanel p40 = new JPanel();
//        p40.setLayout(new FlowLayout());
        FlowLayout* p40Layout = new FlowLayout;
        p40Layout->addWidget(new QLabel(tr("Stopping Sensors (Optional)")));
        addFrameLayout->addLayout(p40Layout);
//        JPanel p41 = new JPanel();
//        p41.setLayout(new FlowLayout());
        FlowLayout* p41Layout = new FlowLayout;
        p41Layout->addWidget(new QLabel(tr("Forward Stopping Sensor:")));
        p41Layout->addWidget(forwardStopSensorField);
        forwardStopSensorField->setToolTip(tr("Enter forward stopping sensor name (system or user)."));
        p41Layout->addWidget (new QLabel("     "));
        p41Layout->addWidget(new QLabel(tr("Reverse Stopping Sensor:")));
        p41Layout->addWidget(reverseStopSensorField);
        reverseStopSensorField->setToolTip(tr("Enter reverse stopping sensor name (system or user)."));
        addFrameLayout->addLayout(p41Layout);
        separator = new QFrame;
                separator->setFrameStyle(QFrame::HLine);
                separator->setLineWidth(2);addFrameLayout->addWidget(separator);
        // set up bottom buttons
        QPushButton* cancel = NULL;
//        JPanel pb = new JPanel();
//        pb.setLayout (new FlowLayout());
        FlowLayout* pbLayout = new FlowLayout;
        pbLayout->addWidget(cancel = new QPushButton(tr("Cancel")));
//        cancel.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                cancelPressed(e);
//            }
//        });
        connect(cancel, SIGNAL(clicked()), this, SLOT(cancelPressed()));
        cancel->setToolTip(tr("Press to cancel without creating or updating."));
        pbLayout->addWidget(create = new QPushButton(tr("Create")));
//        create.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                createPressed(e);
//            }
//        });
        connect(create, SIGNAL(clicked()), this, SLOT(createPressed()));
        create->setToolTip(tr("SectionCreateButtonHint"));
        pbLayout->addWidget(update = new QPushButton(tr("Update")));
//        update.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updatePressed(e);
//            }
//        });
        connect(update, SIGNAL(clicked()), this, SLOT(updatePressed()));
        update->setToolTip(tr("SectionUpdateButtonHint"));
        addFrameLayout->addLayout(pbLayout);
    }
    if (editMode) {
        // setup for edit window
        _autoSystemName->setVisible(false);
        sysNameLabel->setEnabled(true);
        create->setVisible(false);
        update->setVisible(true);
        sysName->setVisible(false);
        sysNameFixed->setVisible(true);
        initializeEditInformation();
    }
    else {
        // setup for create window
        _autoSystemName->setVisible(true);
        create->setVisible(true);
        update->setVisible(false);
        sysName->setVisible(true);
        sysNameFixed->setVisible(false);
        autoSystemName();
        clearForCreate();
    }
    // initialize layout editor panels
    if (initializeLayoutEditorCombo(layoutEditorBox)) {
        manually->setVisible(true);
        automatic->setVisible(true);
        layoutEditorBox->setVisible(true);
    }
    else {
        manually->setVisible(false);
        automatic->setVisible(false);
        layoutEditorBox->setVisible(false);
    }
    // initialize block combo - first time
    initializeBlockCombo();
    addFrame->pack();
    addFrame->setVisible(true);
}
void SectionTableAction::OnManually_Clicked() // SLOT
{
  manualEntryPoints = manually->isChecked();
}
void SectionTableAction::OnAutomatic_Clicked() // SLOT
{
  manualEntryPoints = automatic->isChecked();
}

/*private*/ void SectionTableAction::initializeEditInformation()
{
 userName->setText(curSection->getUserName());
 deleteBlocksPressed();
 int i = 0;
 while (curSection->getBlockBySequenceNumber(i)!=NULL)
 {
  Block* b = curSection->getBlockBySequenceNumber(i);
  blockList.append(b);
  i++;
  if (blockList.size()==1)
  {
   beginBlock = b;
  }
  endBlock = b;
 }
 forwardSensorField->setText(curSection->getForwardBlockingSensorName());
 reverseSensorField->setText(curSection->getReverseBlockingSensorName());
 forwardStopSensorField->setText(curSection->getForwardStoppingSensorName());
 reverseStopSensorField->setText(curSection->getReverseStoppingSensorName());
 QList<EntryPoint*>* list =  curSection->getForwardEntryPointList();
    if (list->size()>0) {
        for (int j = 0; j<list->size(); j++) {
            entryPointList.append(list->at(j));
        }
    }
    list = (QList<EntryPoint*>*)curSection->getReverseEntryPointList();
    if (list->size()>0) {
        for (int j = 0; j<list->size(); j++) {
            entryPointList.append(list->at(j));
        }
    }
}
/*private*/ void SectionTableAction::clearForCreate() {
    deleteBlocksPressed();
    curSection =  NULL;
    forwardSensorField->setText("");
    reverseSensorField->setText("");
    forwardStopSensorField->setText("");
    reverseStopSensorField->setText("");
}

void SectionTableAction::createPressed() {
    if (!checkSectionInformation()) {
        return;
    }
    QString uName = userName->text();
    if (uName==("")) uName="";

    // attempt to create the new Section
    if (_autoSystemName->isChecked()) {
        curSection = sectionManager->createNewSection(uName);
    } else {
        QString sName = sysName->text().toUpper();
        curSection = sectionManager->createNewSection(sName, uName);
    }
    if (curSection==NULL) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message2"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Error - Cannot create a new Section. System name or user name is not unique."));
        return;
    }
    sysName->setText(curSection->getSystemName());
    setSectionInformation();
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = NULL;
    pref->setSimplePreferenceState(systemNameAuto, _autoSystemName->isChecked());
}
void SectionTableAction::cancelPressed() {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = NULL;
}
void SectionTableAction::updatePressed() {
    if (!checkSectionInformation()) {
        return;
    }
    // check if user name has been changed
    QString uName = userName->text();
    if (uName==("")) uName="";
    if ( (uName!=NULL) && (uName!=(curSection->getUserName())) ) {
        // check that new user name is unique
        Section* tSection = (Section*)sectionManager->getByUserName(uName);
        if (tSection!=NULL) {
//            javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message2"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addFrame, tr("Error"), tr("Error - Cannot create a new Section. System name or user name is not unique."));
            return;
        }
    }
    curSection->setUserName(uName);
    if (setSectionInformation()) {
        // successful update
        addFrame->setVisible(false);
        addFrame->dispose();
        addFrame = NULL;
    }
}
/*private*/ bool SectionTableAction::checkSectionInformation() {
    if (blockList.size()==0) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message6"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Error - A Section must have at least one block. Please add blocks and try again."));
        return false;
    }
    // check entry points
    bool unknownPresent = false;
    for (int i = 0; i<entryPointList.size(); i++) {
        if (entryPointList.at(i)->isUnknownType() ) {
            unknownPresent = true;
        }
    }
    if (unknownPresent) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message10"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Error - Entry point direction is UNKNOWN. Please assign direction of all Entry Points."));
        return false;
    }
    // check direction sensors
    QString txt = forwardSensorField->text();
    if ( (txt==NULL) || (txt==("")) ) {
        fSensor = NULL;
    }
    else {
        fSensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(txt);
        if (fSensor==NULL) {
//            javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message7"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addFrame, tr("Error"), tr("Error - Could not provide forward sensor. Please correct forward sensor name and try again."));
            return false;
        }
        else {
            if (txt!=(((AbstractSensor*)fSensor)->getUserName())) {
                forwardSensorField->setText(((AbstractSensor*)fSensor)->getSystemName());
            }
        }
    }
    txt = reverseSensorField->text();
    if ( (txt==NULL) || (txt==("")) ) {
        rSensor = NULL;
    }
    else {
        rSensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(txt);
        if (rSensor==NULL) {
//            javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message8"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addFrame, tr("Error"), tr("Error - Could not provide reverse sensor. Please correct reverse sensor name and try again."));
            return false;
        }
        else {
            if (txt!=(((AbstractSensor*)rSensor)->getUserName())) {
                reverseSensorField->setText(((AbstractSensor*)rSensor)->getSystemName());
            }
        }
    }
    if ( (fSensor!=NULL) && (fSensor==rSensor) ) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message9"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Forward and reverse sensors must be different. Please try again."));

        return false;
    }
    // check stopping sensors
    txt = forwardStopSensorField->text();
    if ( (txt==NULL) || (txt==("")) ) {
        fStopSensor = NULL;
    }
    else {
        fStopSensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(txt);
        if (fStopSensor==NULL) {
//            javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message7"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addFrame, tr("Error"), tr("Error - Could not provide forward sensor. Please correct forward sensor name and try again."));
            return false;
        }
        else {
            if (txt!=(((AbstractSensor*)fStopSensor)->getUserName())) {
                forwardStopSensorField->setText(((AbstractSensor*)fStopSensor)->getSystemName());
            }
        }
    }
    txt = reverseStopSensorField->text();
    if ( (txt==NULL) || (txt==("")) ) {
        rStopSensor = NULL;
    }
    else {
        rStopSensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(txt);
        if (rStopSensor==NULL) {
//            javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message8"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addFrame, tr("Error"), tr("Error - Could not provide reverse sensor. Please correct reverse sensor name and try again."));
            return false;
        }
        else {
            if (txt!=(((AbstractSensor*)rStopSensor)->getUserName())) {
                reverseStopSensorField->setText(((AbstractSensor*)rStopSensor)->getSystemName());
            }
        }
    }
    return true;
}

/*private*/ bool SectionTableAction::setSectionInformation() {
    curSection->removeAllBlocksFromSection();
    for (int i = 0; i<blockList.size(); i++) {
        if (!curSection->addBlock(blockList.at(i))) {
//            javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message4"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(addFrame, tr("Error"), tr("Error adding block to Section. Please press Cancel and try again."));

        }
    }
    curSection->setForwardBlockingSensorName(forwardSensorField->text());
    curSection->setReverseBlockingSensorName(reverseSensorField->text());
    curSection->setForwardStoppingSensorName(forwardStopSensorField->text());
    curSection->setReverseStoppingSensorName(reverseStopSensorField->text());
    for (int j = 0; j<entryPointList.size(); j++) {
        EntryPoint* ep = entryPointList.at(j);
        if (ep->isForwardType()) curSection->addToForwardList(ep);
        else if (ep->isReverseType()) curSection->addToReverseList(ep);
    }
    return true;
}
void SectionTableAction::deleteBlocksPressed() {
    for (int j=blockList.size(); j>0; j--) blockList.removeAt(j-1);
    beginBlock = NULL;
    endBlock = NULL;
    initializeBlockCombo();
    initializeEntryPoints();
    blockTableModel->fireTableDataChanged();
}
void SectionTableAction::addBlockPressed() {
    if (blockBoxList.size()==0) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message5"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Error - No block to add."));
        return;
    }
    int index = blockBox->currentIndex();
    Block* b = blockBoxList.at(index);
    if (b!=NULL) {
        blockList.append(b);
        if (blockList.size()==1) {
            beginBlock = b;
        }
        endBlock = b;
        initializeBlockCombo();
        initializeEntryPoints();
        blockTableModel->fireTableDataChanged();
    }
}
/*private*/ bool SectionTableAction::initializeLayoutEditorCombo(QComboBox* box) {
    // get list of Layout Editor panels
    lePanelList = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
    if (lePanelList->size()==0) return false;
    box->clear();
    box->addItem(tr("None"));
    for (int i=0; i<lePanelList->size(); i++) {
        box->addItem(lePanelList->at(i)->getTitle());
    }
    box->setCurrentIndex(1);
    return true;
}
/*private*/ void SectionTableAction::layoutEditorSelectionChanged()
{
 int i = layoutEditorBox->currentIndex();
 if ( (i<=0) || (i>lePanelList->size()) ) curLayoutEditor = NULL;
 else curLayoutEditor = lePanelList->at(i-1);
}
/*private*/ void SectionTableAction::initializeBlockCombo()
{
 QStringList allBlocks = (QStringList)blockManager->getSystemNameList();
 blockBox->clear();
 for (int j=blockBoxList.size(); j>0; j--) blockBoxList.removeAt(j-1);
 if (blockList.size()==0)
 {
  // No blocks selected, all blocks are eligible
  for (int i=0; i<allBlocks.size(); i++)
  {
   QString bName = allBlocks.at(i);
   Block* b = (Block*)blockManager->getBySystemName(bName);
   if (b!=NULL)
   {
    if ( (b->getUserName()!=NULL) && (b->getUserName()!=("")) )
     bName = bName+"( "+b->getUserName()+" )";
    blockBox->addItem(bName);
    blockBoxList.append(b);
   }
  }
 }
 else
 {
  // limit to Blocks bonded to the current block that are not already in the Section
  for (int i=0; i<allBlocks.size(); i++)
  {
   QString bName = allBlocks.at(i);
   Block* b = (Block*)blockManager->getBySystemName(bName);
   if (b!=NULL)
   {
    if ( (!inSection(b)) && connected(b,endBlock) )
    {
     if ( (b->getUserName()!=NULL) && (b->getUserName()!=("")) )
     bName = bName+"( "+b->getUserName()+" )";
     blockBox->addItem(bName);
     blockBoxList.append(b);
    }
   }
  }
 }
}
/*private*/ bool SectionTableAction::inSection(Block* b) {
    for (int i = 0; i<blockList.size(); i++) {
        if (blockList.at(i) == b) return true;
    }
    return false;
}
/*private*/ bool SectionTableAction::connected(Block* b1, Block* b2)
{
 if ( (b1!=NULL) && (b2!=NULL) )
 {
  QList<Path*> paths = b1->getPaths()->toList();
  for (int i = 0; i<paths.size(); i++)
  {
   if (paths.at(i)->getBlock() == b2) return true;
  }
 }
 return false;
}
/*private*/ void SectionTableAction::initializeEntryPoints()
{
 // Copy old Entry Point List, if there are entries, and clear it.
 QList<EntryPoint*> oldList =  QList<EntryPoint*>();
 for (int i = 0; i<entryPointList.size(); i++)
     oldList.append(entryPointList.at(i));
 entryPointList.clear();
 if (blockList.size()>0)
 {
  // cycle through Blocks to find Entry Points
  for (int i = 0; i<blockList.size(); i++)
  {
   Block* sb = blockList.at(i);
   QList<Path*> paths = sb->getPaths()->toList();
   for (int j = 0; j<paths.size(); j++)
   {
    Path* p = paths.at(j);
    if (!inSection(p->getBlock()))
    {
     // this is path to an outside block, so need an Entry Point
     QString pbDir = Path::decodeDirection(p->getFromBlockDirection());
     EntryPoint* ep = getEntryPointInList(oldList, sb, p->getBlock(), pbDir);
     if (ep==NULL) ep = new EntryPoint(sb, p->getBlock(), pbDir);
      entryPointList.append(ep);
    }
   }
  }
  // Set directions where possible
  QList<EntryPoint*> epList = getBlockEntryPointsList(beginBlock);
  if ( (epList.size()==2) && (blockList.size()==1) )
  {
   if ( ((epList.at(0))->isUnknownType()) &&
                        ((epList.at(1))->isUnknownType()) )
   {
    (epList.at(0))->setTypeForward();
    (epList.at(1))->setTypeReverse();
   }
  }
  else if (epList.size()==1)
  {
   (epList.at(0))->setTypeForward();
  }
  epList = getBlockEntryPointsList(endBlock);
  if (epList.size()==1)
  {
   (epList.at(0))->setTypeReverse();
  }
 }
// djd debugging
// here add code to use Layout Editor connectivity if desired in the future
/*		if (!manualEntryPoints) {
        // use Layout Editor connectivity to set directions of Entry Points that have UNKNOWN direction
        // check entry points for first Block
        ArrayList<EntryPoint> tEPList = getSubEPListForBlock(beginBlock);
        EntryPoint firstEP = NULL;
        int numUnknown = 0;
        for (int i = 0; i<tEPList.size(); i++) {
            if (tEPList.get(i).getDirection==EntryPoint.UNKNOWN) numUnknown ++;
            else if (firstEP==NULL) firstEP = tEPList.get(i);
        }
        if (numUnknown>0) {
            // first Block has unknown entry point(s)
            if ( (firstEP!=NULL) && (blockList.getSize()==1) ) {
                firstEP = tEPList.get(0);
                firstEP.setTypeForward();
            }
            else if (firstEP==NULL) {
                // find connection from the second Block
        }
    }   */
 entryPointTableModel->fireTableDataChanged();
}
/*	private ArrayList<EntryPoint> getSubEPListForBlock(Block b) {
    ArrayList<EntryPoint> tList = new ArrayList<EntryPoint>0;
    for (int i=0; i<eplist.size(); i++) {
        EntryPoint tep = epList.get(i);
        if (epList.getBlock()==b) {
            tList.add(tep);
        }
    }
    return tList;
} */
// end djd debugging

/*private*/ EntryPoint* SectionTableAction::getEntryPointInList(QList<EntryPoint*> list, Block* b, Block* pb, QString pbDir) {
    for (int i = 0; i<list.size(); i++) {
        EntryPoint* ep = list.at(i);
        if ( (ep->getBlock()==b) && (ep->getFromBlock()==pb) &&
                        (pbDir==(ep->getFromBlockDirection())) ) return ep;
    }
    return NULL;
}
/*private*/ QList<EntryPoint*> SectionTableAction::getBlockEntryPointsList(Block* b) {
    QList<EntryPoint*> list = QList<EntryPoint*>();
    for (int i = 0; i<entryPointList.size(); i++) {
        EntryPoint* ep = entryPointList.at(i);
        if (ep->getBlock()==b) list.append(ep);
    }
    return list;
}

/**
 * Special processing when user requests deletion of a Section
 *     Standard BeanTable processing results in misleading information
 */
/*private*/ void SectionTableAction::deleteSectionPressed(QString sName)
{
#if 1
 /*final*/ Section* s = (Section*)((SectionManager*)InstanceManager::getDefault("SectionManager"))->getBySystemName(sName);
 QString fullName = sName;
 if (s->getUserName().length()>0)
 {
  fullName = fullName+"("+s->getUserName()+")";
 }
 QList<Transit*>* affectedTransits = ((TransitManager*)InstanceManager::getNullableDefault("transitManger"))->getListUsingSection(s);
 /*final*/ JDialog* dialog = new JDialog();
 QString msg = "";
 dialog->setTitle(tr("Warning Title"));
//  TODO: dialog->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
 //dialog.getContentPane().setLayout(new BoxLayout(dialog.getContentPane(), BoxLayout.Y_AXIS));
 QVBoxLayout* contentLayout = (QVBoxLayout*)dialog->getContentPane()->layout();
//    JPanel p1 = new JPanel();
//    p1.setLayout(new FlowLayout());
 FlowLayout* p1Layout = new FlowLayout;
 if (affectedTransits->size() > 0)
 {
  // special warning if Section is used in Transits
  QLabel* iLabel = new QLabel(tr("The Section - \"%1\" - is in use by the following Transits - ").arg(fullName));
  p1Layout->addWidget(iLabel);
  contentLayout->addLayout(p1Layout);
  for (int i=0; i<affectedTransits->size(); i++)
  {
   Transit* aTransit = affectedTransits->at(i);
   QString tFullName = aTransit->getSystemName();
   if (aTransit->getUserName().length()>0)
   {
    tFullName = tFullName+"("+aTransit->getUserName()+")";
   }
//    p1 = new JPanel();
//    p1.setLayout(new FlowLayout());
   p1Layout = new FlowLayout;
   iLabel = new QLabel("   "+tFullName);
   p1Layout->addWidget(iLabel);
   contentLayout->addLayout(p1Layout);
  }
  contentLayout->addLayout(p1Layout);
//  JPanel p3 = new JPanel();
//  p3.setLayout(new FlowLayout());
//  FlowLayout* p3Layout = new FlowLayout;
  QLabel* question = new QLabel(tr("Deleting this Section will break the Transits. "));
//  JPanel p4 = new JPanel();
//  p4.setLayout(new FlowLayout());
  FlowLayout* p4Layout = new FlowLayout;
  question = new QLabel(tr("Recommend deleting affected Transits first. "));
  p4Layout->addWidget(question);
  contentLayout->addLayout(p4Layout);
 }
 else
 {
  msg = tr("Recommend deleting affected Transits first. ")/*, fullName)*/;
  QLabel* question = new QLabel(msg);
  p1Layout->addWidget(question);
  contentLayout->addLayout(p1Layout);
 }
// JPanel p6 = new JPanel();
// p6.setLayout(new FlowLayout());
 FlowLayout* p6Layout = new FlowLayout;
 QLabel* quest = new QLabel(tr("Do you still want to delete this Section?"));
 p6Layout->addWidget(quest);
 contentLayout->addLayout(p6Layout);
 QPushButton* yesButton = new QPushButton(tr("Yes Delete It"));
 QPushButton* noButton = new QPushButton(tr("No Cancel"));
 //JPanel button = new JPanel();
 FlowLayout* buttonLayout = new FlowLayout;

 buttonLayout->addWidget(yesButton);
 buttonLayout->addWidget(noButton);
 contentLayout->addLayout(buttonLayout);

    //    noButton.addActionListener(new ActionListener(){
    //        /*public*/ void actionPerformed(ActionEvent e) {
    //            // user cancelled delete request
    //            dialog.dispose();
    //        }
    //    });
 NoButtonActionListener* noButtonListener = new NoButtonActionListener(dialog);
 connect(noButton, SIGNAL(clicked()), noButtonListener, SLOT(actionPerformed()));

//    yesButton.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            jmri.((SectionManager*)InstanceManager::getDefault("SectionManager")).deregister(s);
//            s.dispose();
//            dialog.dispose();
//        }
//    });
 YesButtonActionListener* addActionListener = new YesButtonActionListener(dialog, s);
 connect(yesButton, SIGNAL(clicked()), addActionListener, SLOT(actionPerformed()));
 dialog->pack();
 dialog->setModal(true);
 dialog->setVisible(true);
#endif
}
YesButtonActionListener::YesButtonActionListener(JDialog* dlg, Section *s)
{
 this->dlg = dlg;
 this->s = s;
}

void YesButtonActionListener::actionPerformed(JActionEvent* )
{
 ((SectionManager*)InstanceManager::getDefault("SectionManager"))->deregister(s);
 s->dispose();
 dlg->close();
}
NoButtonActionListener::NoButtonActionListener(JDialog* dlg)
{
 this->dlg = dlg;
}

void NoButtonActionListener::actionPerformed(JActionEvent*)
{
 dlg->close();
}
#if 1
/**
 * Add the Tools menu item
 */
/*public*/ void SectionTableAction::setMenuBar(BeanTableFrame* f)
{
 frame = f;
 QMenuBar* menuBar = f->menuBar();

 QMenu* toolsMenu = createToolsMenu();
 menuBar->addMenu(toolsMenu);
}
/*public*/ QMenu* SectionTableAction::createToolsMenu()
{
 QMenu* toolsMenu = new QMenu(tr("Tools"));
 QAction* validate = new QAction(tr("Validate All Sections")+"...",this);
 toolsMenu->addAction(validate);
//    validate.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (sectionManager!=NULL) {
//                    initializeLayoutEditor(false);
//                    int n = sectionManager->validateAllSections(frame, panel);
//                    if (n>0) {
//                        JOptionPane.showMessageDialog(frame,java.text.MessageFormat.format(
//                                tr("Message14"),new Object[] {""+n}),
//                                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
//                    }
//                    else if (n==-2) {
//                        JOptionPane.showMessageDialog(frame, tr("Message16"),
//                                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
//                    }
//                    else if (n==0) {
//                        JOptionPane.showMessageDialog(frame, tr("Message15"),
//                                tr("MessageTitle"),JOptionPane.INFORMATION_MESSAGE);
//                    }
//                }
//            }
//        });
 connect(validate, SIGNAL(triggered()), this, SLOT(OnValidate()));

 QAction* setDirSensors = new QAction(tr("Setup Direction Sensors")+"...",this);
 toolsMenu->addAction(setDirSensors);
//    setDirSensors.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (sectionManager!=NULL) {
//                    if (initializeLayoutEditor(true)) {
//                        int n = sectionManager->setupDirectionSensors(panel);
//                        if (n>0) {
//                            JOptionPane.showMessageDialog(frame,java.text.MessageFormat.format(
//                                tr("Message27"),new Object[] {""+n}),
//                                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
//                        }
//                        else if (n==-2) {
//                            JOptionPane.showMessageDialog(frame, tr("Message30"),
//                                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
//                        }
//                        else if (n==0) {
//                            JOptionPane.showMessageDialog(frame, tr("Message28"),
//                                tr("MessageTitle"),JOptionPane.INFORMATION_MESSAGE);
//                        }
//                    }
//                }
//            }
//        });
    connect(setDirSensors, SIGNAL(triggered()), this, SLOT(OnSetDirSensors()));

    QAction* removeDirSensors = new QAction(tr("RemoveDirectionSensors")+"...",this);
    toolsMenu->addAction(removeDirSensors);
//    removeDirSensors.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (sectionManager!=NULL) {
//                    if (initializeLayoutEditor(true)) {
//                        int n = sectionManager->removeDirectionSensorsFromSSL(panel);
//                        if (n>0) {
//                            JOptionPane.showMessageDialog(frame,java.text.MessageFormat.format(
//                                tr("Message33"),new Object[] {""+n}),
//                                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
//                        }
//                        else if (n==-2) {
//                            JOptionPane.showMessageDialog(frame, tr("Message32"),
//                                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
//                        }
//                        else if (n==0) {
//                            JOptionPane.showMessageDialog(frame, tr("Message31"),
//                                tr("MessageTitle"),JOptionPane.INFORMATION_MESSAGE);
//                        }
//                    }
//                }
//            }
//        });
    connect(removeDirSensors,SIGNAL(triggered()), this, SLOT(OnRemoveDirSensors()));
 return toolsMenu;
}
void SectionTableAction::OnValidate()
{
 if (sectionManager!=NULL)
 {
  if (initializeLayoutEditor(true))
  {
   int n = sectionManager->setupDirectionSensors(panel);
   if (n>0)
   {
//    JOptionPane.showMessageDialog(frame,java.text.MessageFormat.format(
//                tr("Message27"),new Object[] {""+n}),
//                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(frame, tr("Error"),tr("%1 error or warning messages issued when placing direction sensors in\nsignal logic. See error log for details.").arg(n));
   }
   else if (n==-2)
   {
//            JOptionPane.showMessageDialog(frame, tr("Message30"),
//                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(frame, tr("Error"),tr("Cannot place direction sensors because there are no sections defined."));
   }
   else if (n==0)
   {
//            JOptionPane.showMessageDialog(frame, tr("Message28"),
//                tr("MessageTitle"),JOptionPane.INFORMATION_MESSAGE);
    QMessageBox::information(frame, tr("Information"), tr("Directions sensors placed in signal logic with no errors or warnings issued."));
   }
  }
 }
}

void SectionTableAction::OnSetDirSensors()
{
 if (sectionManager!=NULL)
 {
  if (initializeLayoutEditor(true))
  {
   int n = sectionManager->setupDirectionSensors(panel);
   if (n>0)
   {
//    JOptionPane.showMessageDialog(frame,java.text.MessageFormat.format(
//                tr("Message27"),new Object[] {""+n}),
//                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(frame, tr("Error"), tr("%1 error or warning messages issued when placing direction sensors in\nsignal logic. See error log for details.").arg(n));
   }
   else if (n==-2)
   {
       //            JOptionPane.showMessageDialog(frame, tr("Message30"),
       //                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(frame, tr("Error"), tr("Cannot place direction sensors because there are no sections defined."));
   }
   else if (n==0)
   {
//    JOptionPane.showMessageDialog(frame, tr("Message28"),
//               tr("MessageTitle"),JOptionPane.INFORMATION_MESSAGE);
       QMessageBox::information(frame, tr("Information"), tr("Directions sensors placed in signal logic with no errors or warnings issued."));
   }
  }
 }
}

void SectionTableAction::OnRemoveDirSensors()
{
 if (sectionManager!=NULL)
 {
  if (initializeLayoutEditor(true))
  {
   int n = sectionManager->removeDirectionSensorsFromSSL(panel);
   if (n>0)
   {
//            JOptionPane.showMessageDialog(frame,java.text.MessageFormat.format(
//                tr("Message33"),new Object[] {""+n}),
//                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(frame, tr("Error"),tr("{0} error messages issued when removing direction sensors from \nsignal logic. See error log for details.").arg(n));
   }
   else if (n==-2)
   {
//            JOptionPane.showMessageDialog(frame, tr("Message32"),
//                tr("ErrorTitle"),JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(frame, tr("Error"),tr("Cannot remove direction sensors because there are no sections defined."));
   }
   else if (n==0)
   {
//            JOptionPane.showMessageDialog(frame, tr("Message31"),
//                tr("MessageTitle"),JOptionPane.INFORMATION_MESSAGE);
    QMessageBox::information(frame, tr("Information"), tr("Directions sensors placed in signal logic with no errors or warnings issued."));

   }
  }
 }
}

//@SuppressWarnings("NULL")
/*private*/ bool SectionTableAction::initializeLayoutEditor(bool required)
{
 // Get a Layout Editor panel. Choose Layout Editor panel if more than one.
 QList<LayoutEditor*>* layoutEditorList =
                ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
 if ( (panel==NULL) || (layoutEditorList->size()>1) )
 {
  if (layoutEditorList->size()>1)
  {
   // initialize for choosing between layout editors
   QList<QVariant> choices =  QList<QVariant>();
   int index = 0;
   for (int i = 0; i<layoutEditorList->size(); i++)
   {
    QString txt = layoutEditorList->at(i)->getTitle();
    //choices[i] = txt;
    choices.append(txt);
    if (panel==layoutEditorList->at(i)) index = i;
   }
   // choose between Layout Editors
   QString panelName;
//    Object panelName = JOptionPane.showInputDialog(frame,
//        (tr("Message11")), tr("ChoiceTitle"),
//        JOptionPane.QUESTION_MESSAGE, NULL, choices, choices[index]);
   InputDialog* dlg = new InputDialog(tr("Please choose a Layout Editor panel to define connectivity."),choices, index,tr("Choose Panel"));
   if(dlg->exec() == QDialog::Accepted)
      panelName = dlg->value();
   if ( (panelName==NULL) && required)
   {
//        JOptionPane.showMessageDialog(frame, tr("Message12"));
    QMessageBox::warning(frame, tr("Warning"), tr("Warning - Tool request cancelled because you cancelled\ninstead of choosing a Layout Editor panel as required."));
    panel = NULL;
    return false;
   }
   if(panelName==NULL)
        log->error("panelName is NULL!");
   for (int j = 0; j<layoutEditorList->size(); j++)
   {
    if (panelName==(choices[j]))
    {
     panel = layoutEditorList->at(j);
     return true;
    }
   }
   return false;
  }
  else if (layoutEditorList->size() == 1)
  {
   panel = layoutEditorList->at(0);
   return true;
  }
  else
  {
   if (required)
   {
//            JOptionPane.showMessageDialog(frame, tr("Message13"));
            QMessageBox::warning(frame, tr("Warning"), tr("Request cancelled. This tool requires a Layout Editor panel\nto define connectivity.  Please create or load one and try again."));
            panel = NULL;
   }
   return false;
  }
 }
 return true;
}
#endif
//private void validateAllSections(ActionEvent e) {
//}
/**
 * Table model for Blocks in Create/Edit Section window
 */
///*public*/ class BlockTableModel extends javax.swing.table.AbstractTableModel implements
//        java.beans.PropertyChangeListener {

//    /*public*/ static final int SNAME_COLUMN = 0;

//    /*public*/ static final int UNAME_COLUMN = 1;

/*public*/ BlockTableModel::BlockTableModel(SectionTableAction *act)
{
    //super();
this->act = act;
    act->blockManager->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(act->blockManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void BlockTableModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("length")) {
        // a new NamedBean is available in the manager
        fireTableDataChanged();
    }
}

//    /*public*/ Class<?> getColumnClass(int c) {
//        return String.class;
//    }

/*public*/ int BlockTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

/*public*/ int BlockTableModel::rowCount(const QModelIndex &/*parent*/) const{
    return (act->blockList.size());
}

/*public*/ Qt::ItemFlags BlockTableModel::flags(const QModelIndex &/*index*/) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*public*/ QVariant BlockTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(Qt::DisplayRole == role && orientation == Qt::Horizontal)
 {
    switch (section) {
    case SNAME_COLUMN:
        return tr("System Name");
    case UNAME_COLUMN:
        return tr("User Name");
    default:
        break;
    }
 }
 return QVariant();
}

/*public*/ int BlockTableModel::getPreferredWidth(int col) {
    switch (col) {
    case SNAME_COLUMN:
        return  JTextField(8).getPreferredSize().width();
    case UNAME_COLUMN:
        return  JTextField(17).getPreferredSize().width();
    default:
        return  JTextField(5).getPreferredSize().width();
    }
}

/*public*/ QVariant BlockTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
    int rx = index.row();
    if (rx > act->blockList.size()) {
        return QVariant();
    }
    switch (index.column()) {
        case SNAME_COLUMN:
            return act->blockList.at(rx)->getSystemName();
        case UNAME_COLUMN: //
            return act->blockList.at(rx)->getUserName();
        default:
        break;
    }
 }
 return QVariant();
}

/*public*/ bool BlockTableModel::setData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/)
{
    return false;
}
//};


/*private*/ void SectionTableAction::autoSystemName(){
    if (_autoSystemName->isChecked()){
        sysName->setEnabled(false);
        sysName->setText("");
        sysNameLabel->setEnabled(false);
    }
    else {
        sysName->setEnabled(true);
        sysNameLabel->setEnabled(true);
    }
}

/**
 * Table model for Entry Points in Create/Edit Section window
 */
///*public*/ class EntryPointTableModel extends javax.swing.table.AbstractTableModel {

///*public*/ static final int BLOCK_COLUMN = 0;

///*public*/ static final int TO_BLOCK_COLUMN = 1;	// GT - 12-Oct-2009

///*public*/ static final int DIRECTION_COLUMN = 2;	// GT - 12-Oct-2009

/*public*/ EntryPointTableModel::EntryPointTableModel(SectionTableAction *act) {
    //super();
    this->act = act;
}

/*public*/ QString EntryPointTableModel::getColumnClass(int c) {
    if (c == DIRECTION_COLUMN)
        return "JComboBox";
    return "String";
}

/*public*/ int EntryPointTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;	// GT - 12-Oct-2009
}

/*public*/ int EntryPointTableModel::rowCount(const QModelIndex &/*parent*/) const{
    return (act->entryPointList.size());
}

/*public*/ Qt::ItemFlags EntryPointTableModel::flags(const QModelIndex &index) const
{
 int r = index.row();
 if (index.column()==DIRECTION_COLUMN)
 {
  if ( !act->manualEntryPoints )
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  else if (r < act->entryPointList.size())
  {
   return (!act->entryPointList.at(r)->isFixed())?Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable:Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
 }
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*public*/ QVariant EntryPointTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
    switch (section) {
    case BLOCK_COLUMN:
        return tr("From Block");

    case TO_BLOCK_COLUMN:					// GT - 12-Oct-2009
        return tr("To Block");	// GT - 12-Oct-2009

    case DIRECTION_COLUMN:
        return tr("Travel Direction");
    default:
        break;
    }
 }
 return QVariant();
}

/*public*/ int EntryPointTableModel::getPreferredWidth(int col) {
    if (col == BLOCK_COLUMN || col == TO_BLOCK_COLUMN)		// GT - 12-Oct-2009
        return  JTextField(37).getPreferredSize().width(); // GT - 12-Oct-2009
    if (col == DIRECTION_COLUMN)
        return  JTextField(9).getPreferredSize().width();
    return  JTextField(5).getPreferredSize().width();
}

/*public*/ QVariant EntryPointTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int rx = index.row();
  if (rx >= act->entryPointList.size())
  {
   return QVariant();
  }
  switch (index.column())
  {
   case BLOCK_COLUMN:
    return act->entryPointList.at(rx)->getFromBlockName();

// GT - 12-Oct-2009 - start
   case TO_BLOCK_COLUMN:
   {
    QString s = act->entryPointList.at(rx)->getBlock()->getSystemName();
    QString u = act->entryPointList.at(rx)->getBlock()->getUserName();
    if ((u!=NULL) && (u!=("")))
    {
     s = s+"( "+u+" )";
    }
    return s;
   }
// GT - 12-Oct-2009 - end

   case DIRECTION_COLUMN: //
   {
    if (act->entryPointList.at(rx)->isForwardType())
    {
     return tr("FORWARD");
    }
    else if (act->entryPointList.at(rx)->isReverseType())
    {
     return tr("REVERSE");
    }
    else
    {
     return tr("UNKNOWN");
    }
   }
  }
 }
 return QVariant();
}

/*public*/ bool EntryPointTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
  if (col==DIRECTION_COLUMN)
  {
   if ((value.toString())==(tr("FORWARD")))
   {
    act->entryPointList.at(row)->setTypeForward();
   }
   else if ((value.toString())==(tr("REVERSE")))
   {
    act->entryPointList.at(row)->setTypeReverse();
   }
   else if ((value.toString())==(tr("UNKNOWN")))
   {
    act->entryPointList.at(row)->setTypeUnknown();
   }
  }
  return true;
 }
 return false;
}

//};

/*protected*/ QString SectionTableAction::getClassName() { return "jmri.jmrit.beantable.SectionTableAction"; }

/*public*/ QString SectionTableAction::getClassDescription() { return tr("Section Table"); }

