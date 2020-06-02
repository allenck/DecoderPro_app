#include "tableframes.h"
#include "oblock.h"
#include "oblockmanager.h"
#include "instancemanager.h"
#include <QAction>
#include <QMenu>
#include <QSignalMapper>
#include "opath.h"
#include <QMenuBar>
#include "savemenu.h"
#include <QSignalMapper>
//#include "jdesktoppane.h" // see QMdiArea
#include "oblocktablemodel.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QSortFilterProxyModel>
#include "xtablecolumnmodel.h"
#include "tablecolumn.h"
#include <QComboBox>
#include "warranttableaction.h"
#include "dndjtable.h"
#include <QMdiArea>
#include "blockportaltablemodel.h"
#include "portaltablemodel.h"
#include "signaltablemodel.h"
#include "internalframelistener.h"
#include "tablecolumnmodel.h"
#include "blockpathtablemodel.h"
#include "pathturnouttablemodel.h"
#include "internalframeevent.h"
#include "signalspeedmap.h"
#include "joptionpane.h"
#include "jcombobox.h"
#include "jlabel.h"

//TableFrames::TableFrames(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * GUI to define OBlocks
 * <P>
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author  Pete Cressman (C) 2010
 * @version $Revision: 29581 $
 */

///*public*/ class TableFrames extends jmri.util.JmriJFrame implements InternalFrameListener {

/**
 *
 */
//private static /*final*/ long serialVersionUID = 5328547694482485128L;
/*static*/ int TableFrames::ROW_HEIGHT = 0;
/*public*/ /*static*/ /*final*/ int TableFrames::STRUT_SIZE = 10;
/*private*/ /*static*/ QString TableFrames::oblockPrefix;

/*public*/ TableFrames::TableFrames(QWidget *parent) :
  JmriJFrame(tr("OBlock Table"), parent)
{
 //this("OBlock Table");
 common();
}

/*public*/ TableFrames::TableFrames(QString actionName, QWidget *parent) :
  JmriJFrame(parent)
{
 //super(actionName);
 common();
}
void TableFrames::common()
{
 _showWarnings = true;
 _blockPathMap =  QMap<QString, JInternalFrame*>();
 _PathTurnoutMap = QMap<QString, JInternalFrame*>();
 log = new Logger("TableFrames");
 mdiArea = new QMdiArea();
 setCentralWidget(mdiArea);
}

//@Override
/*public*/ void TableFrames::initComponents()
{
 JmriJFrame::initComponents();
 setTitle(tr("Occupancy Blocks, their Portals and Paths"));
 QMenuBar* menuBar = new QMenuBar();
 //java.util.ResourceBundle rb = java.util.ResourceBundle.getBundle("apps.AppsBundle");
 QMenu* fileMenu = new QMenu(tr("File"));
 fileMenu->addMenu(new SaveMenu());

 QAction*  printItem = new QAction(tr("Print OBlock Table"), this);
 fileMenu->addAction(printItem);
 // TODO:
//    printItem.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            try {
//                // MessageFormat headerFormat = new MessageFormat(getTitle());  // not used below
//                MessageFormat footerFormat = new MessageFormat(getTitle() + " page {0,number}");
//                _oBlockTable.print(JTable.PrintMode.FIT_WIDTH, NULL, footerFormat);
//            } catch (java.awt.print.PrinterException e1) {
//                log->warn("error printing: " + e1, e1);
//            }
//        }
//    });
 printItem = new QAction(tr("Print Portal Table"), this );
 fileMenu->addAction(printItem);
 // TODO:
//    printItem.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            try {
//                // MessageFormat headerFormat = new MessageFormat(getTitle());  // not used below
//                MessageFormat footerFormat = new MessageFormat(getTitle() + " page {0,number}");
//                _portalTable.print(JTable.PrintMode.FIT_WIDTH, NULL, footerFormat);
//            } catch (java.awt.print.PrinterException e1) {
//                log->warn("error printing: " + e1, e1);
//            }
//        }
//    });
 printItem = new QAction(tr("Print Signal Table"),this);
 fileMenu->addAction(printItem);
 // TODO:
//    printItem.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            try {
//                // MessageFormat headerFormat = new MessageFormat(getTitle());  // not used below
//                MessageFormat footerFormat = new MessageFormat(getTitle() + " page {0,number}");
//                _signalTable.print(JTable.PrintMode.FIT_WIDTH, NULL, footerFormat);
//            } catch (java.awt.print.PrinterException e1) {
//                log->warn("error printing: " + e1, e1);
//            }
//        }
//    });
 printItem = new QAction(tr("Print OBlock/Portal Crossreference"),this);
 fileMenu->addAction(printItem);
 // TODO:
//    printItem.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            try {
//                // MessageFormat headerFormat = new MessageFormat(getTitle());  // not used below
//                MessageFormat footerFormat = new MessageFormat(getTitle() + " page {0,number}");
//                _blockPortalTable.print(JTable.PrintMode.FIT_WIDTH, NULL, footerFormat);
//            } catch (java.awt.print.PrinterException e1) {
//                log->warn("error printing: " + e1, e1);
//            }
//        }
//    });

 menuBar->addMenu(fileMenu);

 QMenu* editMenu = new QMenu(tr("Edit"));
//    editMenu.setMnemonic(KeyEvent.VK_E);
//    TransferActionListener actionListener = new TransferActionListener();

 QAction* menuItem = new QAction(tr("Cut"), this);
//    menuItem.setActionCommand((String) TransferHandler.getCutAction().getValue(Action.NAME));
//    menuItem.addActionListener(actionListener);
//    menuItem.setAccelerator(
//            KeyStroke.getKeyStroke(KeyEvent.VK_X, ActionEvent.CTRL_MASK));
//    menuItem.setMnemonic(KeyEvent.VK_T);
 editMenu->addAction(menuItem);

 menuItem = new QAction(tr("Copy"), this);
//    menuItem.setActionCommand((String) TransferHandler.getCopyAction().getValue(Action.NAME));
//    menuItem.addActionListener(actionListener);
//    menuItem.setAccelerator(
//            KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.CTRL_MASK));
//    menuItem.setMnemonic(KeyEvent.VK_C);
 editMenu->addAction(menuItem);

 menuItem = new QAction(tr("Paste"),this );
//    menuItem.setActionCommand((String) TransferHandler.getPasteAction().getValue(Action.NAME));
//    menuItem.addActionListener(actionListener);
//    menuItem.setAccelerator(
//            KeyStroke.getKeyStroke(KeyEvent.VK_V, ActionEvent.CTRL_MASK));
//    menuItem.setMnemonic(KeyEvent.VK_P);
 editMenu->addAction(menuItem);
 menuBar->addMenu(editMenu);

 QMenu* optionMenu = new QMenu(tr("Options"));
 warningMapper = new QSignalMapper;
 _showWarnItem = new QAction(tr("Suppress Warnings and Error Messages"),this);
//    _showWarnItem.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            String cmd = event.getActionCommand();
//            setShowWarnings(cmd);
//        }
//    });
 optionMenu->addAction(_showWarnItem);
 setShowWarnings("ShowWarning");
 menuBar->addMenu(optionMenu);
 connect(warningMapper, SIGNAL(mapped(QString)), this, SLOT(setShowWarnings(QString)));

 _openMenu = new QMenu(tr("OpenTables"));
 updateOpenMenu();   // replaces the last item with appropriate
 menuBar->addMenu(_openMenu);

 setMenuBar(menuBar);
 addHelpMenu("package.jmri.jmrit.logix.OBlockTable", true);

//    _desktop = new JDesktopPane(); // see QMdiArea
// TODO:   _desktop->putClientProperty("JDesktopPane.dragMode", "outline");
 //_desktop->resize( QSize(1100, 550));
 resize(QSize(1100, 550));
 //setCentralWidget(_desktop);
 _blockTableFrame = makeBlockFrame();
 _blockTableFrame->setVisible(true);
 //_desktop->addWidget(_blockTableFrame);
 mdiArea->addSubWindow(_blockTableFrame);

#if 1 // TODO:
 _portalTableFrame = makePortalFrame();
 _portalTableFrame->setVisible(true);
 //_desktop.add(_portalTableFrame);
 mdiArea->addSubWindow(_portalTableFrame);

 _signalTableFrame = makeSignalFrame();
 _signalTableFrame->setVisible(true);
 //_desktop.add(_signalTableFrame);
 mdiArea->addSubWindow(_signalTableFrame);

 _blockPortalXRefFrame = makeBlockPortalFrame();
 _blockPortalXRefFrame->setVisible(false);
 //_desktop->addWidget(_blockPortalXRefFrame);
 mdiArea->addSubWindow(_blockPortalXRefFrame);
#endif
 setLocation(10, 30);
 setVisible(true);
 adjustSize();
 WarrantTableAction::getDefault()->errorCheck();
}

///*protected*/ /*final*/ JTable* TableFrames::getBlockTablePane() {
//    return _blockTable;
//}

///*protected*/ /*final*/ JTable* TableFrames::getPortalTablePane() {
//    return _portalTable;
//}

///*protected*/ /*final*/ JTable* TableFrames::getSignalTablePane() {
//    return _signal;
//}

/*protected*/ /*final*/ OBlockTableModel* TableFrames::getBlockModel() {
    return _oBlockModel;
}

/*protected*/ /*final*/ PortalTableModel* TableFrames::getPortalModel() {
    return _portalModel;
}

/*protected*/ /*final*/ SignalTableModel* TableFrames::getSignalModel() {
    return _signalModel;
}

/*protected*/ /*final*/ BlockPortalTableModel* TableFrames::getXRefModel() {
    return _blockPortalXRefModel;
}

/*private*/ void TableFrames::setShowWarnings(QString cmd) {
    if (cmd==("ShowWarning")) {
        _showWarnings = true;
        //_showWarnItem.setActionCommand("SuppressWarning");
        warningMapper->setMapping(_showWarnItem, "Suppress Warnings and Error Messages");
        _showWarnItem->setText(tr("Suppress Warnings and Error Messages"));
        connect(_showWarnItem, SIGNAL(triggered()), warningMapper, SLOT(map()));
    } else {
        _showWarnings = false;
        //_showWarnItem.setActionCommand("ShowWarning");
        warningMapper->setMapping(_showWarnItem, "ShowWarning");
        _showWarnItem->setText(tr("Suppress Warning"));
        _showWarnItem->setText(tr("Show Warning"));
    }
    if (log->isDebugEnabled()) {
        log->debug("setShowWarnings: _showWarnings= " + _showWarnings);
    }
}
#if 1
/**
 * Add the cut/copy/paste actions to the action map.
 */
/*static*/ /*private*/ void TableFrames::setActionMappings(JTable* table) {
#if 0
    ActionMap map = table.getActionMap();
    map.put(TransferHandler.getCutAction().getValue(Action.NAME), TransferHandler.getCutAction());
    map.put(TransferHandler.getCopyAction().getValue(Action.NAME), TransferHandler.getCopyAction());
    map.put(TransferHandler.getPasteAction().getValue(Action.NAME), TransferHandler.getPasteAction());
#endif
}
//@Override
/*public*/ void TableFrames::windowClosing(QCloseEvent* e)
{
  WarrantTableAction::getDefault()->errorCheck();
  setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
  if (log->isDebugEnabled()) {
      log->debug("windowClosing: " + toString());
    }
}
#endif
///*private*/ void TableFrames::errorCheck() {
//    WarrantTableAction::initPathPortalCheck();
//    OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
//    QStringList sysNames = manager->getSystemNameArray();
//    for (int i = 0; i < sysNames.length(); i++) {
//        WarrantTableAction::checkPathPortals((OBlock*)manager->getBySystemName(sysNames[i]));
//    }
//    if (_showWarnings) {
//        WarrantTableAction::showPathPortalErrors();
//    }
//}

/*protected*/ void TableFrames::updateOpenMenu()
{
 _openMenu->clear();
 QAction* openBlock = new QAction(tr("Show Occupancy Block Table"), this);
 _openMenu->addAction(openBlock);
//    openBlock.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            _blockTableFrame.setVisible(true);
//            try {
//                _blockTableFrame.setIcon(false);
//            } catch (PropertyVetoException pve) {
//                log->warn("Block Table Frame vetoed setIcon " + pve.toString());
//            }
//            _blockTableFrame.moveToFront();
//        }
//    });
 connect(openBlock, SIGNAL(triggered()), this, SLOT(on_openBlock_triggered()));
 QAction* openPortal = new QAction(tr("Show Portal Table"), this);
 _openMenu->addAction(openPortal);
//    openPortal.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            _portalTableFrame.setVisible(true);
//            try {
//                _portalTableFrame.setIcon(false);
//            } catch (PropertyVetoException pve) {
//                log->warn("Portal Table Frame vetoed setIcon " + pve.toString());
//            }
//            _portalTableFrame.moveToFront();
//        }
//    });
 connect(openPortal, SIGNAL(triggered()), this, SLOT(on_openPortal_triggered()));
 QAction* openXRef = new QAction(tr("Show Block-Portal CrossReference"), this);
 _openMenu->addAction(openXRef);
//    openXRef.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            _blockPortalXRefFrame.setVisible(true);
//            try {
//                _blockPortalXRefFrame.setIcon(false);
//            } catch (PropertyVetoException pve) {
//                log->warn("XRef Table Frame vetoed setIcon " + pve.toString());
//            }
//            _blockPortalXRefFrame.moveToFront();
//        }
//    });
 connect(openXRef, SIGNAL(triggered()), this, SLOT(on_openXRef_triggered()));
 QAction* openSignal = new QAction(tr("Show Signal Table"),this);
 _openMenu->addAction(openSignal);
//    openSignal.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            _signalTableFrame.setVisible(true);
//            try {
//                _signalTableFrame.setIcon(false);
//            } catch (PropertyVetoException pve) {
//                log->warn("Signal Table Frame vetoed setIcon " + pve.toString());
//            }
//            _signalTableFrame.moveToFront();
//        }
//    });
 connect(openSignal, SIGNAL(triggered()), this, SLOT(on_openSignal_triggered()));
 QMenu* openBlockPath = new QMenu(tr("Open Block-Path Tables..."));
//    ActionListener openFrameAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            String sysName = e.getActionCommand();
//            openBlockPathFrame(sysName);
//        }
//    };
 QSignalMapper* mapper = new QSignalMapper;
 OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
 QStringList sysNames = manager->getSystemNameArray();
 for (int i = 0; i < sysNames.length(); i++) {
     OBlock* block = (OBlock*)manager->getBySystemName(sysNames[i]);
     QAction* mi = new QAction(tr("Open \"%1\" Path Table").arg( block->getDisplayName()),this);
     //mi.setActionCommand(sysNames[i]);
     mapper->setMapping(mi, block->getDisplayName());
     //mi.addActionListener(openFrameAction);
     connect(mi, SIGNAL(triggered()), mapper, SLOT(map()));
     openBlockPath->addAction(mi);
 }
 _openMenu->addMenu(openBlockPath);

 QMenu* openTurnoutPath = new QMenu(tr("Open Block-Path-Turnout Tables..."));
 sysNames = manager->getSystemNameArray();
 for (int i = 0; i < sysNames.length(); i++)
 {
  OBlock* block = (OBlock*)manager->getBySystemName(sysNames[i]);
  QMenu* openTurnoutMenu = new QMenu(tr("Open \"%1\" Path-Turnout Tables...").arg( block->getDisplayName()));
  openTurnoutPath->addMenu(openTurnoutMenu);
//        openFrameAction = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                String pathTurnoutName = e.getActionCommand();
//                openPathTurnoutFrame(pathTurnoutName);
//            }
//        };
  QSignalMapper* toMapper = new QSignalMapper;
  QVectorIterator<Path*> iter( *block->getPaths());
  while (iter.hasNext())
  {
   OPath* path = (OPath*) iter.next();
   QAction* mi = new QAction(tr("Open \"%1\" Turnout Table").arg( path->getName()),this);
   //mi.setActionCommand(makePathTurnoutName(sysNames[i], path.getName()));
   toMapper->setMapping(mi, makePathTurnoutName(sysNames[i], path->getName()));
   //mi.addActionListener(openFrameAction);
     connect(mi, SIGNAL(triggered()), toMapper, SLOT(map()));
   openTurnoutMenu->addAction(mi);
  }
 }
 _openMenu->addMenu(openTurnoutPath);
}

void TableFrames::on_openBlock_triggered()
{
 _blockTableFrame->setVisible(true);
 _blockTableFrame->setIcon(false);
//             } catch (PropertyVetoException pve) {
//                 log->warn("Block Table Frame vetoed setIcon " + pve.toString());
//             }
 _blockTableFrame->moveToFront();
}

void TableFrames::on_openPortal_triggered()
{
 _portalTableFrame->setVisible(true);
 //try {
     _portalTableFrame->setIcon(false);
// } catch (PropertyVetoException pve) {
//     log->warn("Portal Table Frame vetoed setIcon " + pve.toString());
// }
 _portalTableFrame->moveToFront();
}

void TableFrames::on_openXRef_triggered()
{
 _blockPortalXRefFrame->setVisible(true);
 //try {
     _blockPortalXRefFrame->setIcon(false);
// } catch (PropertyVetoException pve) {
//     log->warn("XRef Table Frame vetoed setIcon " + pve.toString());
// }
 _blockPortalXRefFrame->moveToFront();
}

void TableFrames::on_openSignal_triggered()
{
 _signalTableFrame->setVisible(true);
// try {
     _signalTableFrame->setIcon(false);
// } catch (PropertyVetoException pve) {
//     log->warn("Signal Table Frame vetoed setIcon " + pve.toString());
// }
 _signalTableFrame->moveToFront();

}


/**
 * ********************* BlockFrame *****************************
 */
/*protected*/ JInternalFrame* TableFrames::makeBlockFrame()
{
 JInternalFrame* frame = new JInternalFrame(tr("Occupancy Block Table"), true, false, false, true);
 _oBlockModel = new OBlockTableModel(this);
 QSortFilterProxyModel* sorter = new QSortFilterProxyModel;
 sorter->setSourceModel(_oBlockModel);
 _oBlockTable = new DnDJTable((TableModel*)_oBlockModel,  QList<int>() << OBlockTableModel::EDIT_COL <<
 OBlockTableModel::DELETE_COL << OBlockTableModel::REPORT_CURRENTCOL <<
 OBlockTableModel::PERMISSIONCOL << OBlockTableModel::UNITSCOL);
 _oBlockTable->setSortingEnabled(true);
//    try {   // following might fail due to a missing method on Mac Classic
//        TableSorter sorter = new TableSorter(_oBlockTable.getModel());
//        sorter.setTableHeader(_oBlockTable.getTableHeader());
//        sorter.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        _oBlockTable.setModel(sorter);
//    } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
//        log->error("makeBlockFrame: Unexpected error: " + e);
//    }
 // Use XTableColumnModel so we can control which columns are visible
 XTableColumnModel* tcm = new XTableColumnModel(_oBlockModel);
 _oBlockTable->setColumnModel(tcm);
 //_oBlockTable->getTableHeader().setReorderingAllowed(true);
 _oBlockTable->createDefaultColumnsFromModel();
 _oBlockModel->addHeaderListener(_oBlockTable);

//    _oBlockTable.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::EDIT_COL).setCellEditor(new ButtonEditor(new JButton()));
 _oBlockModel->setColumnToHoldButton(_oBlockTable, OBlockTableModel::EDIT_COL);
//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::EDIT_COL).setCellRenderer(new ButtonRenderer());
//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::DELETE_COL).setCellEditor(new ButtonEditor(new JButton()));
 _oBlockModel->setColumnToHoldButton(_oBlockTable, OBlockTableModel::DELETE_COL);
//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::DELETE_COL).setCellRenderer(new ButtonRenderer());
//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::UNITSCOL).setCellRenderer(
//            new MyBooleanRenderer(tr("cm"), tr("in")));
 _oBlockTable->setItemDelegateForColumn(OBlockTableModel::UNITSCOL,new MyBooleanRenderer(tr("cm"),tr("in"),NULL));
 //_oBlockModel->buttonMap->insert(OBlockTableModel::UNITSCOL,NULL);
//    QComboBox* box = new QComboBox(OBlockTableModel::curveOptions);
//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::CURVECOL).setCellEditor(new DefaultCellEditor(box));
 _oBlockTable->setItemDelegateForColumn(OBlockTableModel::CURVECOL, new OBSComboBoxDelegate(_oBlockModel, OBlockTableModel::curveOptions));
 _oBlockModel->buttonMap.append(OBlockTableModel::CURVECOL);
//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::REPORT_CURRENTCOL).setCellRenderer(
//            new MyBooleanRenderer(tr("Current"), tr("Last")));
//    box = new JComboBox<String>(jmri.implementation.SignalSpeedMap.getMap().getValidSpeedNames());
//    box.addItem("");
 _oBlockTable->setItemDelegateForColumn(OBlockTableModel::REPORT_CURRENTCOL,new MyBooleanRenderer(tr("Current"),tr("Last"),NULL));
 //_oBlockModel->buttonMap->insert(OBlockTableModel::REPORT_CURRENTCOL,NULL);

//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::SPEEDCOL).setCellEditor(new DefaultCellEditor(box));
 _oBlockTable->setItemDelegateForColumn(OBlockTableModel::SPEEDCOL, new OBSComboBoxDelegate(_oBlockModel, ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames().toList()));
 _oBlockModel->buttonMap.append(OBlockTableModel::SPEEDCOL);
//    _oBlockTable.getColumnModel().getColumn(OBlockTableModel::PERMISSIONCOL).setCellRenderer(
//            new MyBooleanRenderer(tr("Permissive"), tr("Absolute")));
//    _oBlockTable.addMouseListener(new MouseAdapter() {
//        @Override
//        /*public*/ void mousePressed(MouseEvent me) {
//            showPopup(me);
//        }
//        @Override
//        /*public*/ void mouseReleased(MouseEvent me) {
//            showPopup(me);
//        }
//    });
 _oBlockTable->setItemDelegateForColumn(OBlockTableModel::PERMISSIONCOL,new MyBooleanRenderer(tr("Permissive"),tr("Absolute"),NULL));
 //_oBlockModel->buttonMap->insert(OBlockTableModel::PERMISSIONCOL,NULL);

 for (int i = 0; i < _oBlockModel->columnCount(QModelIndex()); i++)
 {
     int width = _oBlockModel->getPreferredWidth(i);
     _oBlockTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
// _oBlockTable->setAutoResizeMode(JTable::AUTO_RESIZE_OFF);
 _oBlockTable->setDragEnabled(true);
 //blockTable.setDropMode(DropMode.USE_SELECTION);
 setActionMappings(_oBlockTable);
 ROW_HEIGHT = _oBlockTable->getRowHeight(0);
//        int tableWidth = blockTable.getPreferredSize().width;
//    int tableWidth = _desktop->sizeHint().width();
//    _oBlockTable.setPreferredScrollableViewportSize(new java.awt.Dimension(tableWidth, ROW_HEIGHT * 10));
//    _blockTablePane = new JScrollPane(_oBlockTable);

 tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::REPORTERCOL), false);
 tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::REPORT_CURRENTCOL), false);
 tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::PERMISSIONCOL), false);
//        tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::SPEEDCOL), false);
//        tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::ERR_SENSORCOL), false);
 tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::CURVECOL), false);

 QWidget* contentPane = new QWidget();
 //frame->setCentralWidget(contentPane);
 //contentPane.setLayout(new BorderLayout(5, 5));
 QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
 QLabel* prompt = new QLabel(tr("Enter a Block System or User Name into the blank (last) row of the table to add an Occupancy Block"));
 contentPaneLayout->addWidget(prompt, /*BorderLayout.NORTH*/0, Qt::AlignTop);
 contentPaneLayout->addWidget(_oBlockTable); //, /*BorderLayout.CENTER*/0, Qt::AlignCenter);

 frame->setContentPane(contentPane);
 frame->pack();
 return frame;
}

void TableFrames::showPopup(QMouseEvent* me)
{
 QPoint p = me->pos();
 //int col = _oBlockTable.columnAtPoint(p);
 int col = _oBlockTable->indexAt(p).column();
 //if (!me.isPopupTrigger() && !me.isMetaDown() && !me.isAltDown() && col == OBlockTableModel::STATECOL)
 if(me->button() == Qt::RightButton && !(me->modifiers() & Qt::MetaModifier == Qt::MetaModifier) &&(me->modifiers() == Qt::AltModifier) && col == OBlockTableModel::STATECOL)
 {
  int row = _oBlockTable->rowAtPoint(p);
  QString stateStr =  _oBlockModel->data(_oBlockModel->index(row, col), Qt::DisplayRole).toString();
  int state = (stateStr.toInt(0,2));
  stateStr = OBlockTableModel::getValue(state);
  QMenu* popupMenu = new QMenu();
  popupMenu->addAction(new QAction(stateStr, this));
  //popupMenu.show(_oBlockTable, me.getX(), me.getY());
  popupMenu->exec(QCursor::pos());
 }
}

/**
 * ********************* PortalFrame *****************************
 */
/*protected*/ JInternalFrame* TableFrames::makePortalFrame()
{
 JInternalFrame* frame = new JInternalFrame(tr("Portal Table"), true, false, false, true);
 _portalModel = new PortalTableModel(this);
//        _portalModel.init();
 QSortFilterProxyModel* sorter = new QSortFilterProxyModel();
 sorter->setSourceModel(_portalModel);
 _portalTable = new DnDJTable(sorter,  QList<int>() << PortalTableModel::DELETE_COL);
//        _portalModel.makeSorter(portalTable);
//    try {   // following might fail due to a missing method on Mac Classic
//        TableSorter sorter = new TableSorter(_portalTable.getModel());
//        sorter.setTableHeader(_portalTable.getTableHeader());
////            sorter.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        _portalTable.setModel(sorter);
//    } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
//        log->error("makePortalFrame: Unexpected error: " + e);
//    }
_portalTable->setSortingEnabled(true);
//    _portalTable->getColumnModel()->getColumn(PortalTableModel::DELETE_COL).setCellEditor(new ButtonEditor(new JButton()));
 _portalModel->setColumnToHoldButton(_portalTable, PortalTableModel::DELETE_COL);

//    _portalTable->getColumnModel()->getColumn(PortalTableModel.DELETE_COL).setCellRenderer(new ButtonRenderer());
//    for (int i = 0; i < _portalModel.getColumnCount(); i++) {
//        int width = _portalModel.getPreferredWidth(i);
//        _portalTable.getColumnModel().getColumn(i).setPreferredWidth(width);
//    }
 _portalTable->resizeColumnsToContents();
 _portalTable->setDragEnabled(true);
 //_portalTable.setDropMode(DropMode.USE_SELECTION);
//    setActionMappings(_portalTable);
//    int tableWidth = _portalTable.getPreferredSize().width;
//    _portalTable.setPreferredScrollableViewportSize(new java.awt.Dimension(tableWidth, ROW_HEIGHT * 10));
//    _portalTablePane = new JScrollPane(_portalTable);

 QWidget* contentPane = new QWidget();
 //contentPane.setLayout(new BorderLayout(5, 5));
 QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
 QLabel* prompt = new QLabel(tr("Enter a Portal Name into the blank (last) row of the table to add a Portal"));
 contentPaneLayout->addWidget(prompt, /*BorderLayout.NORTH*/0, Qt::AlignTop);
 //contentPane.add(_portalTablePane, BorderLayout.CENTER);
 contentPaneLayout->addWidget(_portalTable, 0, Qt::AlignVCenter);

 frame->setContentPane(contentPane);
 frame->setLocation(0, 200);
 frame->pack();
 return frame;
}

/**
 * ********************* BlockPortalFrame *****************************
 */
/*protected*/ JInternalFrame* TableFrames::makeBlockPortalFrame()
{
 JInternalFrame* frame = new JInternalFrame(tr("Block-Portal Cross Reference"), true, false, false, true);
 _blockPortalXRefModel = new BlockPortalTableModel(_oBlockModel);
 _blockPortalTable = new DnDJTable(_blockPortalXRefModel, QList<int>() << BlockPortalTableModel::BLOCK_NAME_COLUMN <<
     BlockPortalTableModel::PORTAL_NAME_COLUMN);
//    _blockPortalTable.setDefaultRenderer(String.class, new jmri.jmrit.symbolicprog.ValueRenderer());
//    _blockPortalTable.setDefaultEditor(String.class, new jmri.jmrit.symbolicprog.ValueEditor());

 _blockPortalTable->createDefaultColumnsFromModel(); // added ACK

 for (int i = 0; i < _blockPortalXRefModel->columnCount(QModelIndex()); i++)
 {
  int width = _blockPortalXRefModel->getPreferredWidth(i);
  _blockPortalTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
 _blockPortalTable->resizeColumnsToContents();
 _blockPortalTable->setDragEnabled(true);
 setActionMappings(_blockPortalTable);
 int tableWidth = _blockPortalTable->sizeHint().width();
//    _blockPortalTable.setPreferredScrollableViewportSize(new java.awt.Dimension(tableWidth, ROW_HEIGHT * 25));
//          _blockPortalTable.setPreferredScrollableViewportSize( new java.awt.Dimension(275, ROW_HEIGHT*25));
//    JScrollPane tablePane = new JScrollPane(_blockPortalTable);

 QWidget* contentPane = new QWidget();
 //contentPane.setLayout(new BorderLayout(5, 5));
 QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
 contentPaneLayout->addWidget(/*tablePane*/_blockPortalTable,/* BorderLayout.CENTER*/0, Qt::AlignVCenter);

 frame->addInternalFrameListener((InternalFrameListener*)this);
 frame->setContentPane(contentPane);
 frame->setLocation(700, 30);
 frame->pack();
 return frame;
}

/**
 * ********************* SignalFrame *****************************
 */
/*protected*/ JInternalFrame* TableFrames::makeSignalFrame()
{
 JInternalFrame* frame = new JInternalFrame(tr("Signal Table"), true, false, false, true);
 _signalModel = new SignalTableModel(this);
 _signalModel->init();
 QSortFilterProxyModel* sorter = new QSortFilterProxyModel;
 sorter->setSourceModel(_signalModel);
 _signalTable = new DnDJTable(sorter, QList<int>() << SignalTableModel::UNITSCOL << SignalTableModel::DELETE_COL);
//    try {   // following might fail due to a missing method on Mac Classic
//        TableSorter sorter = new TableSorter(_signalTable.getModel());
//        sorter.setTableHeader(_signalTable.getTableHeader());
////            sorter.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        _signalTable.setModel(sorter);
//    } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
//        log->error("makeSignalFrame: Unexpected error: " + e);
//    }
 _signalTable->setSortingEnabled(true);
//    _signalTable.getColumnModel().getColumn(SignalTableModel.UNITSCOL).setCellRenderer(
//            new MyBooleanRenderer(tr("cm"), tr("in")));
 _signalTable->setItemDelegateForColumn(SignalTableModel::UNITSCOL, new MyBooleanRenderer("cm", "in", NULL));
//    _signalTable.getColumnModel().getColumn(SignalTableModel.DELETE_COL).setCellEditor(new ButtonEditor(new JButton()));
//    _signalTable.getColumnModel().getColumn(SignalTableModel.DELETE_COL).setCellRenderer(new ButtonRenderer());

 _signalModel->setColumnToHoldButton(_signalTable, SignalTableModel::DELETE_COL);

 _signalTable->createDefaultColumnsFromModel(); // added ACK

 for (int i = 0; i < _signalModel->columnCount(QModelIndex()); i++)
 {
  int width = SignalTableModel::getPreferredWidth(i);
  _signalTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
 _signalTable->resizeColumnsToContents();
 _signalTable->setDragEnabled(true);
 setActionMappings(_signalTable);
 int tableWidth = _signalTable->sizeHint().width();
//    _signalTable.setPreferredScrollableViewportSize(new java.awt.Dimension(tableWidth, ROW_HEIGHT * 8));
//    _signalTablePane = new JScrollPane(_signalTable);

 QWidget* contentPane = new QWidget();
 //contentPane.setLayout(new BorderLayout(5, 5));
 QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
 QLabel* prompt = new QLabel(tr("Name into the blank (last) row of the table to add a Signal"));
 contentPaneLayout->addWidget(prompt, /*BorderLayout.NORTH*/ 0, Qt::AlignTop);
 contentPaneLayout->addWidget(_signalTable, /*BorderLayout.CENTER*/ 0, Qt::AlignVCenter);

 frame->setContentPane(contentPane);
 frame->setLocation(200, 350);
 frame->pack();
 return frame;
}
#if 1
/**
 * ********************* BlockPathFrame *****************************
 */
//static class BlockPathFrame extends JInternalFrame {

    /**
     *
     */
    //private static /*final*/ long serialVersionUID = 1917299755191589427L;
//    BlockPathTableModel blockPathModel;

/*public*/ BlockPathFrame::BlockPathFrame(QString title, bool resizable, bool closable,
        bool maximizable, bool iconifiable)
: JInternalFrame(title, resizable, closable, maximizable, iconifiable)
{
    //super(title, resizable, closable, maximizable, iconifiable);
}

/*public*/ void BlockPathFrame::init(OBlock* block, TableFrames* parent)
{
#if 1 // TODO:
 blockPathModel = new BlockPathTableModel(block, parent);
#endif
}

/*public*/ BlockPathTableModel* BlockPathFrame::getModel() {
    return blockPathModel;
}
//};
#endif
/**
 * ********************* BlockPathFrame *****************************
 */
/*protected*/ BlockPathFrame* TableFrames::makeBlockPathFrame(OBlock* block)
{
 QString title = tr("Path Table for Block \"%1\"").arg(block->getDisplayName());
 BlockPathFrame* frame = new BlockPathFrame(title, true, true, false, true);
 if (log->isDebugEnabled())
 {
  log->debug("makeBlockPathFrame for Block " + block->getDisplayName());
 }

 frame->setName(block->getSystemName());
 frame->init(block, this);

 BlockPathTableModel* blockPathModel = frame->getModel();
 blockPathModel->init();
 JTable* blockPathTable = new DnDJTable(blockPathModel, QList<int>() << BlockPathTableModel::EDIT_COL <<
     BlockPathTableModel::DELETE_COL << BlockPathTableModel::UNITSCOL);
 //blockPathTable.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
//    blockPathTable->getColumnModel()->getColumn(BlockPathTableModel::UNITSCOL).setCellRenderer(
//            new MyBooleanRenderer(tr("cm"), tr("in")));
 blockPathTable->setItemDelegateForColumn(BlockPathTableModel::UNITSCOL, new MyBooleanRenderer(tr("cm"), tr("in"), NULL));
//    blockPathTable.getColumnModel().getColumn(BlockPathTableModel.EDIT_COL).setCellEditor(new ButtonEditor(new JButton()));
//    blockPathTable.getColumnModel().getColumn(BlockPathTableModel.EDIT_COL).setCellRenderer(new ButtonRenderer());
 blockPathModel->setColumnToHoldButton(blockPathTable, BlockPathTableModel::EDIT_COL);
//    blockPathTable.getColumnModel().getColumn(BlockPathTableModel.DELETE_COL).setCellEditor(new ButtonEditor(new JButton()));
//    blockPathTable.getColumnModel().getColumn(BlockPathTableModel.DELETE_COL).setCellRenderer(new ButtonRenderer());
 blockPathModel->setColumnToHoldButton(blockPathTable, BlockPathTableModel::DELETE_COL);
 //blockPathTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
 blockPathTable->setDragEnabled(true);
 //blockPathTable.setDropMode(DropMode.USE_SELECTION);
 setActionMappings(blockPathTable);

 blockPathTable->createDefaultColumnsFromModel();

 for (int i = 0; i < blockPathModel->columnCount(QModelIndex()); i++)
 {
     int width = blockPathModel->getPreferredWidth(i);
     blockPathTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
 blockPathTable->resizeColumnsToContents();
// int tableWidth = blockPathTable.getPreferredSize().width;
// blockPathTable.setPreferredScrollableViewportSize(new java.awt.Dimension(tableWidth, ROW_HEIGHT * 10));
//          blockPathTable.setPreferredScrollableViewportSize( new java.awt.Dimension(766, ROW_HEIGHT*10));
// JScrollPane tablePane = new JScrollPane(blockPathTable);

 QWidget* contentPane = new QWidget();
 //contentPane.setLayout(new BorderLayout(5, 5));
 QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
 QLabel* prompt = new QLabel(tr("Enter a Path Name into the blank (last) row of the table to add a Path"));
 contentPaneLayout->addWidget(prompt, /*BorderLayout.NORTH*/ 0, Qt::AlignTop);
 contentPaneLayout->addWidget(blockPathTable, /*BorderLayout.CENTER*/ 0, Qt::AlignVCenter);


 frame->addInternalFrameListener((InternalFrameListener*)this);
 frame->setContentPane(contentPane);
 frame->setLocation(50, 30);
 frame->pack();
 return frame;
}



/*protected*/ void TableFrames::openBlockPathFrame(QString sysName)
{
 JInternalFrame* frame = _blockPathMap.value(sysName);
 if (frame == NULL)
 {
  OBlock* block = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(sysName);
  if (block == NULL)
  {
   return;
  }
  frame = makeBlockPathFrame(block);
  _blockPathMap.insert(sysName, frame);
  //_desktop->add(frame);
  mdiArea->addSubWindow(frame);
  frame->setVisible(true);
  frame->moveToFront();
 }
 else
 {
  frame->setVisible(true);
//     try {
      //frame->setIcon(false);
  frame->showMinimized();
//     } catch (PropertyVetoException pve) {
//         log->warn("BlockPath Table Frame for \"" + sysName + "\" vetoed setIcon " + pve.toString());
//     }
  frame->moveToFront();
 }
}

/*protected*/ QString TableFrames::makePathTurnoutName(QString blockSysName, QString pathName)
{
 return "%" + pathName + "&" + blockSysName;
}

/*protected*/ void TableFrames::openPathTurnoutFrame(QString pathTurnoutName)
{
 JInternalFrame* frame = _PathTurnoutMap.value(pathTurnoutName);
 log->debug("openPathTurnoutFrame for " + pathTurnoutName);
 if (frame == NULL)
 {
  int index = pathTurnoutName.indexOf('&');
  QString pathName = pathTurnoutName.mid(1, index-1);
  QString sysName = pathTurnoutName.mid(index + 1);
  OBlock* block = (OBlock*)((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->getBySystemName(sysName);
  if (block == NULL)
  {
   return;
  }
  frame = makePathTurnoutFrame(block, pathName);
  if (frame == NULL)
  {
   return;
  }
  _PathTurnoutMap.insert(pathTurnoutName, frame);
  frame->setVisible(true);
  //_desktop.add(frame);
  mdiArea->addSubWindow(frame);
  frame->moveToFront();
  } else {
  frame->setVisible(true);
 // try {
      //frame->setIcon(false);
  frame->showNormal();
 // } catch (PropertyVetoException pve) {
 //     log->warn("PathTurnout Table Frame for \"" + pathTurnoutName
 //             + "\" vetoed setIcon " + pve.toString());
 // }
  frame->moveToFront();
 }
}
#if 0
static class MyBooleanRenderer extends javax.swing.table.DefaultTableCellRenderer {
    private static /*final*/ long serialVersionUID = 934007494903837404L;
    String _trueValue;
    String _falseValue;

    MyBooleanRenderer(String trueValue, String falseValue) {
        _trueValue = trueValue;
        _falseValue = falseValue;
    }

    /*public*/ java.awt.Component getTableCellRendererComponent(JTable table,
            Object value, boolean isSelected,
            boolean hasFocus, int row, int column) {

        JLabel val;
        if (value instanceof Boolean) {
            if (((Boolean) value).booleanValue()) {
                val = new JLabel(_trueValue);
            } else {
                val = new JLabel(_falseValue);
            }
        } else {
            val = new JLabel("");
        }
        val.setFont(table.getFont().deriveFont(java.awt.Font.PLAIN));
        return val;
    }
}
#endif


 /*
  * ********************* PathTurnoutFrame *****************************
  */
 /*protected*/ PathTurnoutFrame* TableFrames::makePathTurnoutFrame(OBlock* block, QString pathName) {
     QString title = tr("Path \"%2\" in Block \"%1\"").arg(block->getDisplayName()).arg(pathName);
     PathTurnoutFrame* frame = new PathTurnoutFrame(title, true, true, false, true);
     if (log->isDebugEnabled()) {
         log->debug(tr("makePathTurnoutFrame for Block %1 and Path %2").arg(block->getDisplayName()).arg(pathName));
     }
     frame->setName(makePathTurnoutName(block->getSystemName(), pathName));
     OPath* path = block->getPathByName(pathName);
     if (path == nullptr) {
         return nullptr;
     }
     frame->init(path);
     PathTurnoutTableModel* PathTurnoutModel = frame->getModel();
     JTable* pathTurnoutTable = new JTable(PathTurnoutModel);
#if 0
     PathTurnoutTable.setTransferHandler(new jmri.util.DnDTableImportExportHandler(
             new int[]{PathTurnoutTableModel.SETTINGCOLUMN, PathTurnoutTableModel.DELETE_COL}));
#endif
     pathTurnoutTable->setDragEnabled(true);

     JComboBox* box = new JComboBox(PathTurnoutTableModel::turnoutStates);
#if 0
     pathTurnoutTable.getColumnModel()->getColumn(PathTurnoutTableModel::SETTINGCOLUMN).setCellEditor(new DefaultCellEditor(box));
     pathTurnoutTable.getColumnModel().getColumn(PathTurnoutTableModel.DELETE_COL).setCellEditor(new ButtonEditor(new JButton()));
     pathTurnoutTable.getColumnModel().getColumn(PathTurnoutTableModel.DELETE_COL).setCellRenderer(new ButtonRenderer());
#endif
     //PathTurnoutTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
     for (int i = 0; i < PathTurnoutModel->getColumnCount(); i++) {
         int width = PathTurnoutModel->getPreferredWidth(i);
         pathTurnoutTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
     }
     pathTurnoutTable->resizeColumnsToContents();//sizeColumnsToFit(-1);
     int tableWidth = pathTurnoutTable->sizeHint().width();
//     pathTurnoutTable.setPreferredScrollableViewportSize(new java.awt.Dimension(tableWidth, TableFrames.ROW_HEIGHT * 5));
//     JScrollPane tablePane = new JScrollPane(pathTurnoutTable);

     JPanel* contentPane = new JPanel();
     contentPane->setLayout(new QVBoxLayout());//new BorderLayout(5, 5));
     JLabel* prompt = new JLabel(tr("Enter a Turnout Name into the last row"));
     ((QVBoxLayout*)contentPane->layout())->addWidget(prompt, 0, Qt::AlignTop);//BorderLayout.NORTH);
     ((QVBoxLayout*)contentPane->layout())->addWidget(/*tablePane*/pathTurnoutTable, 0, Qt::AlignCenter);// BorderLayout.CENTER);
#if 0
     frame->layout()->addInternalFrameListener(this);
#endif
     frame->setContentPane(contentPane);
     frame->setLocation(10, 270);
     frame->pack();
     return frame;
 }


/**
 * ********************* InternalFrameListener implementatiom
 * *****************
 */
/*public*/ void TableFrames::internalFrameClosing(InternalFrameEvent* e)
{
 JInternalFrame* frame = (JInternalFrame*)e->getSource();
 log->debug("Internal frame closing: "+frame->getTitle());
}

/*public*/ void TableFrames::internalFrameClosed(InternalFrameEvent* e)
{
 JInternalFrame* frame = (JInternalFrame*) e->getSource();
 QString name = frame->getName();
 if (log->isDebugEnabled())
 {
  log->debug("Internal frame closed: "
          + frame->getTitle() + ", name= " + name + " size ("
          + QString::number(frame->size().width()) + ", " + QString::number(frame->size().height()) + ")");
 }
 if (name != "" && name.startsWith("OB"))
 {
     _blockPathMap.remove(name);
     if (qobject_cast<BlockPathFrame*>(frame)) {
         QString msg = WarrantTableAction::getDefault()->checkPathPortals(((BlockPathFrame*) frame)->getModel()->getBlock());
         if (msg != "") {
             JOptionPane::showMessageDialog(this, msg,
                     tr("Info"), JOptionPane::INFORMATION_MESSAGE);
         }
         ((BlockPathFrame*) frame)->getModel()->removeListener();
     }
 } else {
     if (qobject_cast<PathTurnoutFrame*>(frame)) {
#if 0
         ((PathTurnoutFrame*) frame)->getModel()->removeListener();
#endif
     }
     _PathTurnoutMap.remove(name);
 }
}

/*public*/ void TableFrames::internalFrameOpened(InternalFrameEvent* e) {
    /*  JInternalFrame frame = (JInternalFrame)e.getSource();
     if (log->isDebugEnabled()) log->debug("Internal frame Opened: "+
     frame.getTitle()+", name= "+frame.getName()+" size ("+
     frame.getSize().getWidth()+", "+frame.getSize().getHeight()+")"); */
}

/*public*/ void TableFrames::internalFrameIconified(InternalFrameEvent* e)
{
 JInternalFrame* frame = (JInternalFrame*) e->getSource();
 QString name = frame->getName();
 if (log->isDebugEnabled()) {
     log->debug("Internal frame Iconified: "
             + frame->getTitle() + ", name= " + name + " size ("
             + QString::number(frame->size().width()) + ", " + QString::number(frame->size().height()) + ")");
 }
 if (name != "" && name.startsWith(oblockPrefix)) {
             if (qobject_cast<BlockPathFrame*>(frame)) {
                 QString msg = WarrantTableAction::getDefault()->checkPathPortals(((BlockPathFrame*) frame)->getModel()->getBlock());
                 if (msg != "" ){
                     JOptionPane::showMessageDialog(this, msg,
                     tr("Info"), JOptionPane::INFORMATION_MESSAGE);
                 }
             }
         }
}

/*public*/ void TableFrames::internalFrameDeiconified(InternalFrameEvent* e) {
    //JInternalFrame frame = (JInternalFrame)e.getSource();
    //log->debug("Internal frame deiconified: "+frame.getTitle());
}

/*public*/ void TableFrames::internalFrameActivated(InternalFrameEvent* e) {
    //JInternalFrame frame = (JInternalFrame)e.getSource();
    //log->debug("Internal frame activated: "+frame.getTitle());
}

/*public*/ void TableFrames::internalFrameDeactivated(InternalFrameEvent* e) {
    //JInternalFrame frame = (JInternalFrame)e.getSource();
    //log->debug("Internal frame deactivated: "+frame.getTitle());
}

/*public*/ QString TableFrames::toString()
{
 return QString(this->metaObject()->className());
}
/*public*/ QString TableFrames::getClassName()
{
 return "jmri.jmrit.beantable.oblock.TableFrames";
}
