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
#include "guilafpreferencesmanager.h"
#include "storemenu.h"
#include "transferactionlistener.h"
#include "portal.h"
#include "portalmanager.h"
#include "borderlayout.h"
#include "tablerowsorter.h"
#include "oblockeditaction.h"
#include "blockmanager.h"
#include "blockpatheditframe.h"
#include "borderfactory.h"
#include "jbutton.h"
#include "turnout.h"
#include "box.h"
#include "loggerfactory.h"
#include <QHeaderView>
#include "pathturnouttablemodel.h"
#include "defaulttablemodel.h"
/**
 * GUI to define OBlocks.
 * <p>
 * Core code can be used with two interfaces:
 * <ul>
 *     <li>original "desktop" InternalFrames (displays as InternalJFrames inside a JmriJFrame)
 *     <li>JMRI standard Tabbed tables (displays as Js inside a ListedTableFrame)
 * </ul>
 * The _tabbed field decides, it is set in prefs (restart required). TableFrames itself has no UI.
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 *
 * @author Pete Cressman (C) 2010
 * @author Egbert Broerse (C) 2020
 */
///*public*/ class TableFrames implements InternalFrameListener {
 /*private*/ /*static*/ QString  TableFrames::_oblockPrefix = "";
/*public*/ /*static*/ /*final*/ int TableFrames::ROW_HEIGHT = 20;//( JButton("X").sizeHint().height())*9/10;

/*private*/ /*final*/ /*static*/ QString  TableFrames::portalPrefix;// = "IP";
/*protected*/ /*static*/ /*final*/ QString TableFrames::SET_CLOSED = InstanceManager::turnoutManagerInstance()->getClosedText();
/*protected*/ /*static*/ /*final*/ QString TableFrames::SET_THROWN = InstanceManager::turnoutManagerInstance()->getThrownText();

/*public*/ TableFrames::TableFrames(QWidget* parent) : JmriJFrame(parent){
    common("OBlock Tables");
} // NOI18N, title will be updated during init

/*public*/ TableFrames::TableFrames(QString actionName, QWidget* parent) : JmriJFrame(parent){
    common(actionName);
}

/*private*/ void TableFrames::common(QString actionName)
{
    _tabbed = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isOblockEditTabbed();
    _title = actionName;
    if (!_tabbed) {
        desktopframe = new JmriJFrameX(actionName);
    }
    // create the tables
    _oBlockModel = new OBlockTableModel(this);
    _portalModel = new PortalTableModel(this);
    _blockPortalXRefModel = new BlockPortalTableModel(_oBlockModel);
    _signalModel = new SignalTableModel(this);
    _signalModel->init();
    ROW_HEIGHT = ( JButton("X").sizeHint().height())*9/10;
}

/*public*/ OBlockTableModel* TableFrames::getOblockTableModel() {
    return _oBlockModel;
}
/*public*/ PortalTableModel* TableFrames::getPortalTableModel() {
    return _portalModel;
}
/*public*/ BlockPortalTableModel* TableFrames::getPortalXRefTableModel() {
    return _blockPortalXRefModel;
}
/*public*/ BlockPathTableModel* TableFrames::getBlockPathTableModel(OBlock* block) {
    return new BlockPathTableModel(block, this);
}
/*public*/ SignalTableModel* TableFrames::getSignalTableModel() {
    return _signalModel;
}

/*public*/ void TableFrames::initComponents() {
    // build and display the classic floating "OBlock and its..." desktop interface
    if (!_tabbed) { // just to be sure
        setTitle(tr("Occupancy Blocks, their Portals and Paths"));

        // build tables
        _blockTableFrame = buildFrame(_oBlockModel, tr("Occupancy Block Table"), tr("Enter a Block System or User Name into the blank (last) row of the table to add an Occupancy Block"));
        _blockTableFrame->setVisible(true);

        _portalTableFrame = buildFrame(_portalModel, tr("Portal Table"), tr("Enter a Portal Name into the blank (last) row of the table to add a Portal"));
        _portalTableFrame->setVisible(true);

        _signalTableFrame = buildFrame(_signalModel, tr("Signal Table"), tr("Enter a SignalMast or SignalHead Name into the blank (last) row of the table to add a Signal"));
        _signalTableFrame->setVisible(false);

        _blockPortalXRefFrame = buildFrame(_blockPortalXRefModel, tr("Block-Portal Cross Reference"), tr("(table not editable)"));
        _blockPortalXRefFrame->setVisible(false); // start with frame hidden

        // build the print menu after the tables have been created
        desktopframe->setTitle(getTitle());
        desktopframe->setMenuBar(addMenus(desktopframe->menuBar()));
        desktopframe->addHelpMenu("package.jmri.jmrit.logix.OBlockTable", true);

        createDesktop(); // adds tables as windows on desktopframe._desktop
        desktopframe->setLocation(10, 30);
        desktopframe->setVisible(true);
        desktopframe->pack();
        addCloseListener(desktopframe);

        // finally check table contents for errors
        WarrantTableAction::getDefault()->errorCheck();
    }
}

/*public*/ QMenuBar* TableFrames::addMenus(QMenuBar* mBar) {
    if (mBar == nullptr) {
        mBar = new QMenuBar();
    }
    // create and add the menus
    if (!_tabbed) { // _tabbed Print is handled via getPrintItem() in OBlockTablePanel
        // File menu
        QMenu* fileMenu = new QMenu(tr("File"));
        fileMenu->addMenu(new StoreMenu());
        fileMenu->addMenu(getPrintMenuItems(_oBlockTable, _portalTable, _signalTable, _blockPortalTable)); // add the print items
        mBar->addMenu(fileMenu);

        // Edit menu
        QMenu* editMenu = new QMenu(tr("Edit&E"));
        //editMenu->setMnemonic(KeyEvent.VK_E);
        TransferActionListener* actionListener = new TransferActionListener(this);

        QAction* menuItem = new QAction(tr("Cut"), this);
#if 0
        menuItem->setActionCommand( TransferHandler::getCutAction().getValue(Action.NAME));
        menuItem.addActionListener(actionListener);
        if (SystemType.isMacOSX()) {
            menuItem->setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X, InputEvent.META_DOWN_MASK));
        } else {
            menuItem->setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X, InputEvent.CTRL_DOWN_MASK));
        }
        menuItem->setMnemonic(KeyEvent.VK_T);
#endif
        editMenu->addAction(menuItem);

        menuItem = new QAction(tr("Copy&C"));
#if 0
        menuItem->setActionCommand((String) TransferHandler.getCopyAction().getValue(Action.NAME));
        menuItem.addActionListener(actionListener);
        if (SystemType.isMacOSX()) {
            menuItem->setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C, InputEvent.META_DOWN_MASK));
        } else {
            menuItem->setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C, InputEvent.CTRL_DOWN_MASK));
        }

        //menuItem->setMnemonic(KeyEvent.VK_C);
#endif
        editMenu->addAction(menuItem);

        menuItem = new QAction(tr("Paste&P"));
#if 0
        menuItem->setActionCommand((String) TransferHandler.getPasteAction().getValue(Action.NAME));
        menuItem.addActionListener(actionListener);
        if (SystemType.isMacOSX()) {
            menuItem->setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_V, InputEvent.META_DOWN_MASK));
        } else {
            menuItem->setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_V, InputEvent.CTRL_DOWN_MASK));
        }
        //menuItem->setMnemonic(KeyEvent.VK_P);
#endif
        editMenu->addAction(menuItem);
        mBar->addMenu(editMenu);
    }

    mBar->addMenu(getOptionMenu());
    mBar->addMenu(getTablesMenu());
    return mBar;
}

/*public*/ QMenu* TableFrames::getPrintMenuItems(JTable* oBlockTable, JTable* portalTable, JTable* signalTable, JTable* blockPortalTable) {
    QMenu* print = new QMenu(tr("Print Table"));
    QAction* printItem = new QAction(tr("Print OBlock Table"), this);
    print->addAction(printItem);
//    printItem.addActionListener(e -> {
    connect(printItem, &QAction::triggered, [=]{
        try {
#if 1
            QString headerFormat = tr("OBlock Table");
            QString footerFormat = QString(getTitle() + " page {0,number}");
            oBlockTable->print(JTable::PrintMode::FIT_WIDTH, headerFormat, footerFormat);
#endif
        } catch (PrinterException e1) {
            log->warn(tr("error printing: %1").arg(e1.getMessage()), e1);
        }
    });
    printItem = new QAction(tr("Print Portal Table"),this);
    print->addAction(printItem);
//    printItem.addActionListener(e -> {
    connect(printItem, &QAction::triggered, [=]{
        try {
#if 1
            QString headerFormat = tr("Portal Table");
            QString footerFormat = QString(getTitle() + " page {0,number}");
            portalTable->print(JTable::PrintMode::FIT_WIDTH, headerFormat, footerFormat);
#endif
        } catch (PrinterException e1) {
            log->warn(tr("error printing: %1").arg(e1.getMessage()), e1);
        }
    });
    printItem = new QAction(tr("Print Signal Table"), this);
    print->addAction(printItem);
//    printItem.addActionListener(e -> {
    connect(printItem, &QAction::triggered, [=]{
        try {
#if 1
            QString headerFormat = tr("Signal Table");
            QString footerFormat = QString(getTitle() + " page {0,number}");
            signalTable->print(JTable::PrintMode::FIT_WIDTH, headerFormat, footerFormat);
#endif
        } catch (PrinterException e1) {
      log->warn(tr("error printing: %1").arg(e1.getMessage()), e1);
        }
    });
    printItem = new QAction(tr("PrintXRef"));
    print->addAction(printItem);
//    printItem.addActionListener(e -> {
    connect(printItem, &QAction::triggered, [=]{
        try {
#if 1
            QString headerFormat = tr("%1 Block-Portal Cross Reference").arg("");
            QString footerFormat = QString(getTitle() + " page {0,number}");
            blockPortalTable->print(JTable::PrintMode::FIT_WIDTH, headerFormat, footerFormat);
#endif
        } catch (PrinterException e1) {
      log->warn(tr("error printing: %1").arg(e1.getMessage()), e1);
        }
    });
    return print;
}

// for desktop style interface, ignored for _tabbed
/*private*/ void TableFrames::createDesktop() {
    _desktop = new JDesktopPane();
    _desktop->putClientProperty("JDesktopPane.dragMode", "outline"); // slower or faster?
    _desktop->resize(QSize(1100, 600));
    _desktop->setBackground(QColor(180,180,180));
    desktopframe->setContentPane(_desktop);

    // placed at 0,0
    _desktop->addWidget(_blockTableFrame);
    _portalTableFrame->setLocation(0, 320);
    _desktop->addWidget(_portalTableFrame);
    _signalTableFrame->setLocation(350, 400);
    _desktop->addWidget(_signalTableFrame);
    _blockPortalXRefFrame->setLocation(700, 20);
    _desktop->addWidget(_blockPortalXRefFrame);
}

/*public*/ QMenu* TableFrames::getOptionMenu() {
    // Options menu
    QMenu* optionMenu = new QMenu(tr("Options"));
    _showWarnItem = new QAction(tr("Suppress Warnings and Error Messages"));
    //_showWarnItem.addActionListener(event -> {
    connect(_showWarnItem, &QAction::triggered, [=]{
        QString cmd = ((QAction*)QObject::sender())->text();//event.getActionCommand();
        setShowWarnings(cmd);
    });
    optionMenu->addAction(_showWarnItem);
    setShowWarnings("ShowWarning");

    QAction* importBlocksItem = new QAction(tr("ImportBlocksMenu"));
//    importBlocksItem.addActionListener((ActionEvent event) -> importBlocks());
    connect(importBlocksItem, &QAction::triggered, [=]{
     optionMenu->addAction(importBlocksItem);
     // disable ourself if there is no primary Block manager available
     if (((BlockManager*)InstanceManager::getNullableDefault("BlockManager")) == nullptr) { // means Block list is empty
         importBlocksItem->setEnabled(false);
     }
    });
    return optionMenu;
}

/*public*/ QMenu* TableFrames::getTablesMenu() {
    // Tables menu
    tablesMenu = new QMenu(tr("Tables"));
    updateOBlockTablesMenu(); // replaces the last 2 menu items with appropriate submenus
    return tablesMenu;
}

/*private*/ QString TableFrames::oblockPrefix() {
    if (_oblockPrefix == nullptr) {
        _oblockPrefix = ((BlockManager*)InstanceManager::getDefault("OBlockManager"))->getSystemNamePrefix();
    }
    return _oblockPrefix;
}

/**
 * Get the JFrame containig all UI windows.
 *
 * @return the contentframe
 */
/*protected*/ JmriJFrame* TableFrames::getDesktopFrame() {
    return desktopframe;
}

/**
 * Convert a copy of your current JMRI Blocks to OBlocks and connect them with Portals and Paths.
 * Accessed from the Options menu.
 *
 * @author Egbert Broerse 2019
 */
/*protected*/ void TableFrames::importBlocks() throw (IllegalArgumentException) {
    BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
    OBlockManager* obm = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
    PortalManager* pom = (PortalManager*)InstanceManager::getDefault("PortalManager");
    QSet</*Block*/NamedBean*> blkList = bm->getNamedBeanSet();
    // don't return an element if there are no Blocks to include
    if (blkList.isEmpty()) {
        log->warn("no Blocks to convert"); // NOI18N
        JOptionPane::showMessageDialog(desktopframe, tr("No Blocks to convert"),
                tr("Informational note:"), JOptionPane::INFORMATION_MESSAGE);
        return;
    } else {
        if (_showWarnings) {
            int reply = JOptionPane::showOptionDialog(nullptr,
                    tr("Default OBlock system name prefix: %1.\nImport all %2 Blocks to OBlocks?").arg(oblockPrefix()).arg(blkList.size()),
                    tr("Question"),
                    JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(),
                    QVariantList({tr("Yes"),
                            tr("Cancel")}),
                    tr("Yes")); // standard JOptionPane can't be found in Jemmy log4J
            if (reply > 0) {
                return;
            }
        }
    }
    for (/*Block*/NamedBean* nb : blkList) {
     Block* b = (Block*)nb;
        try {
            // read Block properties
            QString sName = b->getSystemName();
            QString uName = b->getUserName();
            QString blockNumber = sName.mid(sName.startsWith("IB:AUTO:") ? 8 : 3);
            QString oBlockName = oblockPrefix() + blockNumber;
            QString sensor = "";
            Sensor* s = b->getSensor();
            if (s != nullptr) {
                sensor = s->getDisplayName();
            }
            float length = b->getLengthMm(); // length is stored in Mm in oBlock->setLength(float)
            int curve = b->getCurvature();
            QVector<Path*>* blockPaths = b->getPaths();
            QString toBlockName;
            Portal* port = nullptr;
            int n = 0;
            Portal* prevPortal = nullptr;

            log->debug(tr("start creating OBlock %1 from Block %2").arg(oBlockName).arg(sName));
            if ((uName != "") && (obm->getOBlock(uName) != nullptr)) {
                log->warn(tr("an OBlock with this user name already exists, replacing %1").arg(uName));
            }
            // create the OBlock by systemName
            OBlock* oBlock = obm->provideOBlock(oBlockName);
            oBlock->setUserName(uName);
            if (!sensor.isEmpty()) {
                oBlock->setSensor(sensor);
            }
            oBlock->setMetricUnits(true); // length always stored in Mm in Block, so copy that for OBlock
            oBlock->setLength(length);
            oBlock->setCurvature(curve);

            for (Path* pa : *blockPaths) {
                log->debug(tr("Start loop: Path %1 on Block %2").arg(n).arg(oBlockName));
                QString toBlockNumber = pa->getBlock()->getSystemName().mid(sName.startsWith("IB:AUTO:") ? 8 : 3);
                toBlockName = oblockPrefix() + toBlockNumber;
                QString portalName = portalPrefix + toBlockNumber + "-" + blockNumber; // reversed name for new Portal
                port = pom->getPortal(portalName);
                if (port == nullptr) {
                    portalName = portalPrefix + blockNumber + "-" + toBlockNumber; // normal name for new Portal
                    log->debug(tr("new Portal %1 on block %2, path #%3").arg(portalName).arg(toBlockName).arg(n));
                    port = pom->providePortal(portalName); // normally, will create a new Portal
                    port->setFromBlock(oBlock, false);
                    port->setToBlock(obm->provideOBlock(toBlockName), false); // create one if required
                } else {
                    log->debug(tr("duplicate Portal %1 on block %2, path #%3").arg(portalName).arg(toBlockName).arg(n));
                    // Portal port already set
                }
                oBlock->addPortal(port);

                // create OPath from this Path
                OPath* opa = new OPath(oBlock, "IP" + n++); // only needs to be unique within oBlock
                opa->setLength(oBlock->getLengthMm()); // simple assumption, works for default OBlock/OPath
                log->debug(tr("new OPath #%1 - %2 on OBlock %3").arg(n).arg(opa->getName()).arg(opa->getBlock()->getDisplayName()));
                oBlock->addPath(opa); // checks for duplicates, will add OPath to any Portals on oBlock as well
                log->debug(tr("number of paths: %1").arg(oBlock->getPaths()->size()));

                // set _fromPortal and _toPortal for each OPath in OBlock
                if (opa->getFromPortal() == nullptr) {
                    opa->setFromPortal(port);
                }
                for (BeanSetting* bs : pa->getSettings()) {
                    opa->addSetting(bs);
                }
                if ((opa->getToPortal() == nullptr) && (prevPortal != nullptr)) {
                    opa->setToPortal(prevPortal);
                    // leaves ToPortal in previously (first) created OPath n-1 empty
                }
                prevPortal = port; // remember the new portal for use as ToPortal in opposing OPath
                // user must remove nonsense manually unless...
            }
            // we use the last FromPortal as ToPortal in OPath P0
            OPath* p0 = oBlock->getPathByName("IP0");
            if ((p0 != nullptr) && (n > 1) && (p0->getToPortal() == nullptr)) {
                p0->setToPortal(port);
            }
        } catch (IllegalArgumentException iae) {
            log->error(iae.toString());
        }
        // finished setting up 1 OBlock
    }
    // add recursive Path elements to FromBlock/ToBlock
    QSet</*OBlock*/NamedBean*> oblkList = obm->getNamedBeanSet();
    for (NamedBean* nb : oblkList) {
        OBlock* oblk = (OBlock*)nb;
        for (Portal* po : oblk->getPortals()) {
            OBlock* oob = (OBlock*)obm->getByUserName(po->getFromBlockName());
            if (oob !=nullptr) {
                oob->addPortal(po);
            }
            oob = (OBlock*)obm->getByUserName(po->getToBlockName());
            if (oob !=nullptr) {
                oob->addPortal(po);
            }
        }
    }
    // storing and reloading will add in these items
    WarrantTableAction::getDefault()->errorCheck();
    if (_showWarnings) {
        JOptionPane::showMessageDialog(nullptr,
                tr("Finished importing %1 Blocks to %2 Occupancy Blocks, Portals and Paths.\nPlease review and complete the OPaths, especially around turnouts.").arg(blkList.size()).arg(oblkList.size()),
                tr("Message"),
                JOptionPane::INFORMATION_MESSAGE); // standard JOptionPane can't be found in Jemmy log4J
    }
}
// End of importBlocks() menu method

/*protected*/ void TableFrames::setShowWarnings(QString cmd) {
    if (cmd == ("Show Warnings and Error Messages")) {
        _showWarnings = true;
//        _showWarnItem->setActionCommand("Suppress Warnings and Error Messages");
        _showWarnItem->setText(tr("Suppress Warnings and Error Messages"));
    } else {
        _showWarnings = false;
//        _showWarnItem->setActionCommand("ShowWarning");
        _showWarnItem->setText(tr("Show Warnings and Error Messages"));
    }
    log->debug(tr("setShowWarnings: _showWarnings= %1").arg(_showWarnings));
}

// listen for _desktopframe closing
void TableFrames::addCloseListener(JmriJFrame* desktop) {
//    desktop.addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(QCloseEvent* e) {
//            WarrantTableAction.getDefault().errorCheck();
//            desktop->setDefaultCloseOperation(javax.swing.WindowConstants.HIDE_ON_CLOSE);
//            // closing instead of hiding removes name from Windows menu.handle menu to read Show...
//            log.debug("windowClosing: {}", toString());
//            desktop.dispose();
//        }
//    });
 desktop->addWindowListener(new TFCloseWindowListener(desktop, this));
}

/*private*/ QString TableFrames::getTitle() {
    return _title;
}

/*private*/ void TableFrames::setTitle(QString title) {
    _title = title;
}

/**
 * Fill in the Open/Hide Tables menu on tablesMenu.
 */
/*protected*/ void TableFrames::updateOBlockTablesMenu() {
    if (tablesMenu == nullptr) {
        return;
    }
    tablesMenu->clear();
    if (!_tabbed) { // full menu in _desktop, open/show not available in _tabbed interface
        // use string tr("Hide") to correct action in menu for all table open at start
        openBlock = new QAction(tr("%1 Occupancy Block Table").arg(tr("Hide")),this);
        tablesMenu->addAction(openBlock);
        //openBlock.addActionListener(event -> showHideFrame(_blockTableFrame, openBlock, "%1 Occupancy Block Table"));
        connect(openBlock, &QAction::triggered, [=]{showHideFrame(_blockTableFrame, openBlock, "%1 Occupancy Block Table");});

        openPortal = new QAction(tr("%1 Portal Table").arg(tr("Show")),this);
        tablesMenu->addAction(openPortal);
        //openPortal.addActionListener(event -> showHideFrame(_portalTableFrame, openPortal, "%1 Portal Table"));
        connect(openPortal, &QAction::triggered, [=]{showHideFrame(_portalTableFrame, openPortal, "%1 Portal Table");});

        openXRef = new QAction(tr("%1 Block-Portal Cross Reference").arg(tr("Show")));
        tablesMenu->addAction(openXRef);
        //openXRef.addActionListener(event -> showHideFrame(_blockPortalXRefFrame, openXRef, "%1 Block-Portal Cross Reference"));
        connect(openXRef, &QAction::triggered, [=]{showHideFrame(_blockPortalXRefFrame, openXRef, "%1 Block-Portal Cross Reference");});

        openSignal = new QAction(tr("%1 Signal Table").arg(tr("Show")));
        tablesMenu->addAction(openSignal);
        //openSignal.addActionListener(event -> showHideFrame(_signalTableFrame, openSignal, "%1 Signal Table"));
        connect(openSignal, &QAction::triggered, [=]{showHideFrame(_signalTableFrame, openSignal, "%1 Signal Table");});
    }

    OBlockManager* manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");

    // Block-Path submenus
    QMenu* openBlockPath = new QMenu(tr("Block-Path Tables"));
//    ActionListener openFrameAction = e -> {
//        ActionListener* openFrameAction = [=]{
//        QString blockSystemName = ((QAction*)QObject::sender())->text();//e.getActionCommand();
//        openBlockPathPane(blockSystemName, tr("Paths")); // handles both interfaces
//    };

    if (manager->getNamedBeanSet().size() == 0) {
        QAction* mi = new QAction(tr("Add OBlocks first"));
        mi->setEnabled(false);
        openBlockPath->addAction(mi);
    } else {
        for (/*OBlock*/NamedBean* nb : manager->getNamedBeanSet())
        {
            OBlock* block = (OBlock*)nb;
            QAction* mi = new QAction(tr("Open \"%1\" Path Table").arg(block->getDisplayName()));
            mi->/*setActionCommand*/setData(block->getSystemName());
            //mi->addActionListener(openFrameAction);
            connect(mi, &QAction::triggered, [=]{
//             QString blockSystemName = ((QAction*)QObject::sender())->data().toString();//e.getActionCommand();
             QString blockSystemName = mi->data().toString();
             openBlockPathPane(blockSystemName, tr("Paths")); // handles both interfaces

            });
            openBlockPath->addAction(mi);
        }
    }
    tablesMenu->addMenu(openBlockPath);

    // Path-Turnout submenus
    QMenu* openTurnoutPath = new QMenu(tr("Block-Path-Turnout Tables"));
    if (manager->getNamedBeanSet().size() == 0) {
        QAction* mi = new QAction(tr("Add Paths first"));
        mi->setEnabled(false);
        openTurnoutPath->addAction(mi);
    } else {
        for (/*OBlock*/NamedBean* nb  : manager->getNamedBeanSet()) {
            OBlock* block = (OBlock*)nb;
            QMenu* openTurnoutMenu = new QMenu(tr("Open \"%1\" Path-Turnout Tables").arg(block->getDisplayName()));
            openTurnoutPath->addMenu(openTurnoutMenu);
//            openFrameAction = [=]/*e ->*/ {
//                QString pathTurnoutName = ((QAction*)QObject::sender())->text();//e.getActionCommand();
//                openPathTurnoutEditPane(pathTurnoutName); // handles both interfaces
//            };
            for (Path* p : *block->getPaths()) {
                if (qobject_cast<OPath*>(p)) {
                    OPath* path = (OPath*) p;
                    QAction* mi = new QAction(tr("Open \"%1\" Turnout Table").arg(path->getName()));
                    mi->setData(makePathTurnoutName(block->getSystemName(), path->getName()));
                    //mi.addActionListener(openFrameAction);
                    connect(mi, &QAction::triggered, [=]{
                     QString blockSystemName = mi->data().toString();//e.getActionCommand();
                     openBlockPathPane(blockSystemName, tr("Paths")); // handles both interfaces
                   });
                    openTurnoutMenu->addAction(mi);
                }
            }
        }
    }
    tablesMenu->addMenu(openTurnoutPath);
}

/*public*/ void TableFrames::openPathTurnoutEditPane(QString pathTurnoutName) {
    if (_tabbed) {
        log->debug(tr("openPathTurnoutEditPane for %1").arg(pathTurnoutName));
        openPathTurnoutEditor(pathTurnoutName);
    } else { // stand alone frame only used for _desktop, created from/stored in Portal
        openPathTurnoutFrame(pathTurnoutName);
    }
}

/**
 * Show or hide a table in the _desktop interface.
 *
 * @param frame JInternalFrame to show (or hide, name property value contains {} var handled by frame)
 * @param menu menu item object
 * @param menuName base i18n string containing table name
 */
/*private*/ void TableFrames::showHideFrame(JInternalFrame* frame, QAction* menu, QString menuName) {
    if (!frame->isVisible()) {
        frame->setVisible(true);
        try {
            frame->setIcon(false);
        } catch (PropertyVetoException* pve) {
            log->warn(tr("%1 Frame vetoed setIcon %1").arg(frame->getTitle()).arg(pve->toString()));
        }
        frame->moveToFront();
    } else {
        frame->setVisible(false);
    }
    menu->setText(tr(menuName.toLocal8Bit()).arg(
            (frame->isVisible() ? tr("Hide") : tr("Show"))));
}

/**
 * Wrapper for shared code around each Table in a JInternal window on _desktop interface.
 *
 * @param tableModel underlying model for the table
 * @param title text displayed as title of frame
 * @param prompt text below bottom line
 * @return iframe to put on _desktop interface
 */
/*protected*/ JInternalFrame* TableFrames::buildFrame(AbstractTableModel* tableModel, QString title, QString prompt) {
    JInternalFrame* iframe = new JInternalFrame(title, true, false, false, true);

    // specifics for table
    JTable* table = new JTable();
    if (qobject_cast<OBlockTableModel*>(tableModel)) {
        table = makeOBlockTable((OBlockTableModel*) tableModel);
    } else if (qobject_cast<PortalTableModel*>(tableModel)) {
        table = makePortalTable((PortalTableModel*) tableModel);
    } else if (qobject_cast<BlockPortalTableModel*>(tableModel)) {
        table = makeBlockPortalTable((BlockPortalTableModel*) tableModel);
    } else if (qobject_cast<SignalTableModel*>(tableModel)) {
        table = makeSignalTable((SignalTableModel*) tableModel);
    } // no case here for BlockPathTableModel, it is handled directly from OBlockTable
    table->setMinimumHeight(100);

    //JScrollPane scroll = new JScrollPane(table);
    JPanel* contentPane = new JPanel();
    //BorderLayout* contentPaneLayout;
    QVBoxLayout* contentPaneLayout;
    //contentPane->setLayout(contentPaneLayout= new BorderLayout(/*5, 5*/));
    contentPane->setLayout(contentPaneLayout = new QVBoxLayout());
    JLabel* _prompt = new JLabel(prompt);
    //contentPaneLayout->addWidget(_prompt, BorderLayout::North);
    contentPaneLayout->addWidget(_prompt, 0, Qt::AlignTop);
    //contentPaneLayout->addWidget(/*scroll*/table, BorderLayout::Center);
    FlowLayout* fl = new FlowLayout();
    contentPaneLayout->addWidget(/*scroll*/table, 1);
    iframe->setContentPane(contentPane);
    iframe->pack();
    return iframe;
}

/*
 * ********************* OBlock Table for _desktop ****************
 */
/*protected*/ JTable* TableFrames::makeOBlockTable(OBlockTableModel* model) {
    _oBlockTable = new JTable(model);
    TableRowSorter/*<OBlockTableModel*>*/* sorter = new TableRowSorter(_oBlockModel);
    // use NamedBean's built-in Comparator interface for sorting
    _oBlockTable->setRowSorter(sorter);
#if 0
    _oBlockTable->setTransferHandler(new jmri.util.DnDTableImportExportHandler(new int[]{OBlockTableModel::EDIT_COL,
        OBlockTableModel::DELETE_COL, OBlockTableModel::REPORT_CURRENTCOL, OBlockTableModel::SPEEDCOL,
        OBlockTableModel::PERMISSIONCOL, OBlockTableModel::UNITSCOL}));
#endif
    _oBlockTable->setDragEnabled(true);

    // Use XTableColumnModel so we can control which columns are visible
    XTableColumnModel* tcm = new XTableColumnModel(_oBlockTable);
    _oBlockTable->setColumnModel(tcm);
//    _oBlockTable->getTableHeader()->setReorderingAllowed(true);
    _oBlockTable->createDefaultColumnsFromModel();
    _oBlockModel->addHeaderListener(_oBlockTable);

//    _oBlockTable->setDefaultEditor("JComboBox", new ValueEditor());
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::EDIT_COL)->setCellEditor(new ButtonEditor());
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::EDIT_COL)->setCellRenderer(new ButtonRenderer());
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::DELETE_COL)->setCellEditor(new ButtonEditor());
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::DELETE_COL)->setCellRenderer(new ButtonRenderer());
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::UNITSCOL)->setCellRenderer(
            new ToggleButtonRenderer(tr("cm"), tr("in")));
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::UNITSCOL)->setCellEditor(
            new ToggleButtonEditor(tr("cm"), tr("in")));
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::REPORT_CURRENTCOL)->setCellRenderer(
            new ToggleButtonRenderer(tr("Current"), tr("Last")));
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::REPORT_CURRENTCOL)->setCellEditor(
            new ToggleButtonEditor(tr("Current"), tr("Last")));
    model->configSpeedColumn(_oBlockTable); // use real combo
    //        JComboBox<String> box = new JComboBox<>(OBlockTableModel::curveOptions);
            _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::CURVECOL)->setCellEditor(new /*DefaultCellEditor(box))*/JComboBoxEditor(OBlockTableModel::curveOptions));
    model->configCurveColumn(_oBlockTable); // use real combo
    //        box = new JComboBox<>(jmri.InstanceManager.getDefault(SignalSpeedMap.class).getValidSpeedNames());
//        box.addItem("");
//        _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::SPEEDCOL)->setCellRenderer(new DefaultCellRenderer(new _oBlockModel.SpeedComboBoxPanel()));
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::SPEEDCOL)->setCellEditor(new /*DefaultCellEditor(box)*/JComboBoxEditor(((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames().toList()));
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::PERMISSIONCOL)->setCellRenderer(
            new ToggleButtonRenderer(tr("Permissive"), tr("Absolute")));
    _oBlockTable->getColumnModel()->getColumn(OBlockTableModel::PERMISSIONCOL)->setCellEditor(
            new ToggleButtonEditor(tr("Permissive"), tr("Absolute")));
#if 0
    _oBlockTable->addMouseListener(new MouseAdapter() {
        @Override
        /*public*/ void mousePressed(MouseEvent me) { // for macOS, Linux
            showPopup(me);
        }

        @Override
        /*public*/ void mouseReleased(MouseEvent me) { // for Windows
            showPopup(me);
        }
    });
    /*public*/ void mousePressed(QMouseEvent* me) { // for macOS, Linux
        showPopup(me);
    }

#endif
    for (int i = 0; i < _oBlockModel->getColumnCount(); i++) {
        int width = _oBlockModel->getPreferredWidth(i);
        _oBlockTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
    _oBlockTable->doLayout();
    _oBlockTable->setAutoResizeMode(JTable::AUTO_RESIZE_OFF);
    _oBlockTable->setRowHeight(ROW_HEIGHT);
//    _oBlockTable->setPreferredScrollableViewportSize(QSize(maxWidth,
//            qMin(TableFrames.ROW_HEIGHT * 10, maxHeight)));
    _oBlockTable->resize(QSize(maximumWidth(),
            qMin(TableFrames::ROW_HEIGHT * 10, maximumHeight())));


    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::REPORTERCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::REPORT_CURRENTCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::PERMISSIONCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::WARRANTCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::ERR_SENSORCOL), false);
    tcm->setColumnVisible(tcm->getColumnByModelIndex(OBlockTableModel::CURVECOL), false);

    return _oBlockTable;
}
/*public*/ void TableFrames::mousePressEvent(QMouseEvent* me) { // for macOS, Linux
    showPopup(me);
}
#if 1
/*private*/ void TableFrames::showPopup(QMouseEvent* me) {
    QPoint p = me->pos();//getPoint();
    bool bMeta = me->modifiers()&Qt::MetaModifier;
    bool bAlt = me->modifiers()&Qt::AltModifier;
    bool bShift =  me->modifiers()&Qt::ShiftModifier;
    bool bPopupTrigger = me->button() & Qt::RightButton;
    bool bControl = me->modifiers()&Qt::ControlModifier;

    int col = _oBlockTable->columnAtPoint(p);
    if (!/*me.isPopupTrigger()*/bPopupTrigger && !/*me.isMetaDown()*/bMeta && !/*me.isAltDown()*/bAlt && col == OBlockTableModel::STATECOL) {
        int row = _oBlockTable->rowAtPoint(p);
        QString stateStr = /*(String)*/ _oBlockModel->getValueAt(row, col).toString();
        //int state = Integer.parseInt(stateStr, 2);
        int state = stateStr.toInt();
        stateStr = OBlockTableModel::getValue(state);
        QMenu* popupMenu = new QMenu();
        popupMenu->addAction(new QAction(stateStr));
        //popupMenu.show(_oBlockTable, me.getX(), me.getY());
        popupMenu->exec(p);
    }
}
#endif
// Opens the Edit OBlock panel for _tabbed
/*protected*/ bool TableFrames::openOBlockEditor(QString blockSystemName, QString tabname) {
    bool result = false;
    if (blockSystemName != nullptr) {
        // this is for Edit (new OBlocks are created from [Add oBlock->..] button in table)
        OBlock* oblock = (OBlock*)((BlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(blockSystemName);
        if (oblock != nullptr) {
            BlockPathJPanel* panel = makeBlockPathEditPanel(oblock);
            // BeanEdit UI, adapted from jmri.jmrit.beantable.BlockTableAction
#if 1
            OBlockEditAction* beanEdit = new OBlockEditAction(new JActionEvent((QObject*)this, JActionEvent::ACTION_PERFORMED, tabname));
            beanEdit->setBean(oblock);
            beanEdit->setTablePanel(panel);
            beanEdit->actionPerformed(nullptr);
#endif
            // run on separate thread? does not update new Paths in table!
            //                class WindowMaker implements Runnable {
            //                    final OBlock ob;
            //                    final BlockPathJPanel panel;
            //                    WindowMaker(OBlock oblock, BlockPathJPanel panel) {
            //                        ob = oblock;
            //                        this.panel = panel;
            //                    }
            //                    @Override
            //                    /*public*/ void run() {
            //                        jmri.jmrit.beantable.beanedit.OBlockEditAction beanEdit = new jmri.jmrit.beantable.beanedit.OBlockEditAction();
            //                        beanEdit->setBean(oblock);
            //                        beanEdit->setTablePanel(panel);
            //                        beanEdit.actionPerformed(null);
            //                    }
            //                }
            //                WindowMaker t = new WindowMaker(oblock, panel);
            //                javax.swing.SwingUtilities.invokeLater(t);
            log->debug(tr("path table created for oblock %1").arg(blockSystemName));
            result = true;
        }
    }
    return result;
}

/**
 * Open the Edit Path panel for _tabbed.
 * Compare with openOBlockEditor(block, selectedtabname) and OBlockTableAction.
 *
 * @param blockName system or user name of the owning oblock
 * @param pathName name of the path under edit, or null to create a new path
 * @param bpmodel blockpathtablemodel that should be informed about changes
 * @return true if successful
 */
/*protected*/ bool TableFrames::openPathEditor(/*@Nonnull*/ QString blockName, /*@CheckForNull*/ QString pathName, BlockPathTableModel* bpmodel) {
    OBlock* block = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(blockName);
    if (block == nullptr) {
        log->error(tr("OBlock %1 not found").arg(blockName));
        return false;
    }
    OPath* path;
    QString title;
    PathTurnoutJPanel* turnouttable = makePathTurnoutPanel(block, pathName); // shows the turnouts on path, includes Add Turnout button, checks for null path
    if (pathName == nullptr) { // new Path, empty TurnoutTable
        // a new Path is created from [Add Path...] button in Path table on OBlock Editor pane.
        path = nullptr;
        title = tr("Create New Path on OBlock %1").arg(blockName);
    } else {
        path = block->getPathByName(pathName);
        title = tr("Edit Path %1 on OBlock %2").arg(pathName).arg(blockName);
    }
    BlockPathEditFrame* bpef = new BlockPathEditFrame(title, block, path, turnouttable, bpmodel, this);
    bpef->setVisible(true);
    // run on separate thread? combos are final, difficult to store Partals in Path/see them show up in the table
    //        class WindowMaker implements Runnable {
    //            final String title;
    //            final OBlock ob;
    //            final OPath path;
    //            final PathTurnoutTableModel tomodel;
    //            final BlockPathTableModel bpmodel;
    //            final TableFrames parent;
    //            WindowMaker(String title, OBlock ob, OPath path, PathTurnoutTableModel turnoutmodel, BlockPathTableModel blockpathmodel, TableFrames tf) {
    //                this.title = title;
    //                this.ob = ob;
    //                this.path = path;
    //                this.tomodel = turnoutmodel;
    //                this.bpmodel = blockpathmodel;
    //                parent = tf;
    //            }
    //            @Override
    //            /*public*/ void run() {
    //                BlockPathEditFrame bpef = new BlockPathEditFrame(title, block, path, turnouttable, bpmodel, parent);
    //                bpef->setVisible(true);
    //            }
    //        }
    //        WindowMaker t = new WindowMaker(title, block, path, turnouttable.getModel(), bpmodel, this);
    //        javax.swing.SwingUtilities.invokeLater(t);

    log->debug(tr("Path editor created for path %1 on block %2").arg(pathName).arg(blockName));
    return true;
}

/*
 * ********************* PortalTable for _desktop *****************************
 */
/*protected*/ JTable* TableFrames::makePortalTable(PortalTableModel* model) {
    _portalTable = new JTable(model);
    TableRowSorter/*<PortalTableModel*>*/* sorter = new TableRowSorter(model);
    _portalTable->setRowSorter(sorter);
#if 0
    _portalTable->setTransferHandler(new jmri.util.DnDTableImportExportHandler(new int[]{PortalTableModel::DELETE_COL}));
#endif
    _portalTable->setDragEnabled(true);

    _portalTable->getColumnModel()->getColumn(PortalTableModel::DELETE_COL)->setCellEditor(new ButtonEditor(new JButton()));
    _portalTable->getColumnModel()->getColumn(PortalTableModel::DELETE_COL)->setCellRenderer(new ButtonRenderer());
    for (int i = 0; i < model->getColumnCount(); i++) {
        int width = model->getPreferredWidth(i);
        _portalTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
    _portalTable->doLayout();
    int tableWidth = _portalTable->sizeHint().width();
    _portalTable->setRowHeight(ROW_HEIGHT);
//    _portalTable->setPreferredScrollableViewportSize(QSize(tableWidth, TableFrames.ROW_HEIGHT * 10));
    _portalTable->resize(QSize(tableWidth, TableFrames::ROW_HEIGHT * 10));
    return _portalTable;
}

/*
 * ********************* Block-Portal (XRef) Table for _desktop *****************************
 */
/*protected*/ JTable* TableFrames::makeBlockPortalTable(BlockPortalTableModel* model) {
    _blockPortalTable = new JTable(model);
#if 0
    _blockPortalTable->setTransferHandler(new jmri.util.DnDTableExportHandler());
#endif
    _blockPortalTable->setDragEnabled(true);

    _blockPortalTable->setDefaultRenderer("String", new ValueRenderer());
//    _blockPortalTable->setDefaultEditor("String", new ValueEditor()); // useful on non-editable cell?
    for (int i = 0; i < model->getColumnCount(); i++) {
        int width = model->getPreferredWidth(i);
        _blockPortalTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
    _blockPortalTable->doLayout();
    _blockPortalTable->setRowHeight(ROW_HEIGHT);
//    _blockPortalTable->setPreferredScrollableViewportSize(QSize(maxWidth/3,
//            qMin(TableFrames.ROW_HEIGHT * 20, maxHeight)));
    _blockPortalTable->resize(QSize(maximumWidth()/3,
            qMin(TableFrames::ROW_HEIGHT * 20, maximumHeight())));

    return _blockPortalTable;
}

/*
 * ********************* Signal Table for _desktop *****************************
 */
/*protected*/ JTable* TableFrames::makeSignalTable(SignalTableModel* model) {
    _signalTable = new JTable(model);
    TableRowSorter/*<SignalTableModel>*/* sorter = new TableRowSorter(model);
    _signalTable->setRowSorter(sorter);
#if 0
    _signalTable->setTransferHandler(new jmri.util.DnDTableImportExportHandler(
            new int[]{SignalTableModel::UNITSCOL, SignalTableModel::DELETE_COL}));
#endif
    _signalTable->setDragEnabled(true);

    _signalTable->getColumnModel()->getColumn(SignalTableModel::UNITSCOL)->setCellRenderer(
            new ToggleButtonRenderer(tr("cm"), tr("in")));
    _signalTable->getColumnModel()->getColumn(SignalTableModel::UNITSCOL)->setCellEditor(
            new ToggleButtonEditor(tr("cm"), tr("in")));
    _signalTable->getColumnModel()->getColumn(SignalTableModel::DELETE_COL)->setCellEditor(new ButtonEditor());
    _signalTable->getColumnModel()->getColumn(SignalTableModel::DELETE_COL)->setCellRenderer(new ButtonRenderer());
    for (int i = 0; i < model->getColumnCount(); i++) {
        int width = SignalTableModel::getPreferredWidth(i);
        _signalTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
    _signalTable->doLayout();
    int tableWidth = _signalTable->sizeHint().width();
    _signalTable->setRowHeight(ROW_HEIGHT);
    _signalTable->resize(QSize(tableWidth*2/3,
            qMin(TableFrames::ROW_HEIGHT * 8, maximumHeight())));
    return _signalTable;
}

/*
 * ***************** end of permanent Tables + InternalFrame definitions *****************
 */


/*
 * ***************** On Demand Tables + InternalFrame definitions *****************
 */

/*
 * ********************* Block-Path Frame *****************************
 */

// called from Tables menu and the OBlockTable EDIT buttons
/*public*/ void TableFrames::openBlockPathPane(QString blockSystemName, QString editorTabName) {
    if (_tabbed) {
        if (!openOBlockEditor(blockSystemName, editorTabName)) {
            // pass on to Per OBlock Edit panel, includes a BlockPath table
            log->error(tr("Failed to open OBlock Path table for %1").arg(blockSystemName));
        }
    } else {
        openBlockPathFrame(blockSystemName); // an editable table of all paths on this block
    }
}

// ***************** Block-Path Frame for _desktop **************************
/**
 * Open a block-specific Block-Path table in _desktop interface.
 *
 * @param blockSystemName of the OBlock
 */
/*protected*/ void TableFrames::openBlockPathFrame(QString blockSystemName) {
    BlockPathFrame* frame = (BlockPathFrame*)_blockPathMap.value(blockSystemName);
    if (frame == nullptr) {
        OBlock* block = (OBlock*)((BlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(blockSystemName);
        if (block == nullptr) {
            return;
        }
        frame = makeBlockPathFrame(block);
        // store frame in Map
        _blockPathMap.insert(blockSystemName, frame);
        frame->setVisible(true);
        //desktopframe->getContentPane()->layout()->addWidget(frame);
        _desktop->addWidget(frame);
    } else {
        frame->setVisible(true);
        try {
            frame->setIcon(false);
        } catch (PropertyVetoException pve) {
            log->warn(tr("BlockPath Table Frame for \"%1\" vetoed setIcon %2").arg(blockSystemName).arg(pve.getMessage()));
        }
    }
    frame->moveToFront();
}

// common dispose
/*protected*/ void TableFrames::disposeBlockPathFrame(OBlock* block) {
    if (!_tabbed) {
        //BlockPathFrame frame = _blockPathMap.get(block.getSystemName());
        // TODO frame.getModel().removeListener();
        //_blockPathMap.remove(block.getSystemName()); // block not stored in map, required to remove listener?
        // frame.dispose(); not required (closeable window)
        //} else {
        BlockPathFrame* frame = (BlockPathFrame*)_blockPathMap.value(block->getSystemName());
        frame->getModel()->removeListener();
        _blockPathMap.remove(block->getSystemName());
        frame->dispose();
    }
}

// *************** Block-Path InternalFrame for _desktop ***********************

/*protected*/ TableFrames::BlockPathFrame* TableFrames::makeBlockPathFrame(OBlock* block) {
    QString title = tr("Paths in Block \"%1\"").arg(block->getDisplayName());
    // create table
    BlockPathTableModel* model = new BlockPathTableModel(block, this);
    JPanel* contentPane = makeBlockPathTablePanel(model);

    BlockPathFrame* frame = new BlockPathFrame(title, true, true, false, true);
    frame->setModel(model, block->getSystemName());
    frame->addInternalFrameListener((InternalFrameListener*)this);
    frame->setContentPane(contentPane);
    //frame->setClosable(true); // set in ctor
    frame->setLocation(50, 30);
    frame->pack();
    return frame;
}

// *************** Block-Path Edit Panel for _tabbed ***********************

/*protected*/ TableFrames::BlockPathJPanel* TableFrames::makeBlockPathEditPanel(OBlock* block) {
    // Path Table placed on jmri.jmrit.beanedit OBlockEditAction - Paths tab
    QString title = tr("Edit Paths in Block \"%1\"").arg(block->getDisplayName());
    // create table
    BlockPathTableModel* model = new BlockPathTableModel(block, this);
    JPanel* bpTablePane = makeBlockPathTablePanel(model);
    BlockPathJPanel* panel = new BlockPathJPanel(title);
    panel->setModel(model, block->getSystemName());
    panel->setLayout(new QVBoxLayout());//panel, BoxLayout.PAGE_AXIS));
    panel->layout()->addWidget(bpTablePane);

    // Add Path Button
    JPanel* tblButtons = new JPanel();
    tblButtons->setLayout(new BorderLayout(/*10, 10*/));
    tblButtons->setBorder(BorderFactory::createEmptyBorder(2, 10, 2, 10));
    tblButtons->setLayout(new QVBoxLayout());//tblButtons, BoxLayout.Y_AXIS));

    JButton* addPathButton = new JButton(tr("Add Path"));
    //ActionListener addPathAction = e -> {
    connect(addPathButton, &JButton::clicked, [=]{
        // New Path uses the same editor pane as Edit Path
        if (!isPathEdit()) {
            setPathEdit(true);
            log->debug("makeBlockPathEditPanel pathEdit=True");
            openPathEditor(block->getDisplayName(), nullptr, model);
        } else {
            log->warn("Close BlockPath Editor to reopen");
        }
    });
    //addPathButton->addActionListener(addPathAction);
    //connect(addPathButton, SIGNAL(clicked(bool)), addPathAction, SLOT(actionPerformed()));


    addPathButton->setToolTip(tr("Click Add to create a Path"));
    tblButtons->layout()->addWidget(addPathButton);
    panel->layout()->addWidget(tblButtons);

    //panel.pack();
    return panel;
}

// prevent more than 1 edit pane being opened at the same time
/*protected*/ void TableFrames::setPathEdit(bool edit) {
    pathEdit = edit;
}

/*protected*/ bool TableFrames::isPathEdit() {
    return pathEdit;
}




// ***************** Block-Path JPanel class for _tabbed **************************

/*
 * ********************* Block-Path Table Panel for _desktop and _tabbed ***********************
 */
/*protected*/ JPanel* TableFrames::makeBlockPathTablePanel(BlockPathTableModel* _model) {
    JTable* blockPathTable = makeBlockPathTable(_model); // styled

    // get table
    //JScrollPane tablePane = new JScrollPane(blockPathTable);
    JPanel* contentPane = new JPanel();
    contentPane->setLayout(new QVBoxLayout());//BorderLayout(/*5, 5*/));
    if (_tabbed) {
        // a bit more styling
        blockPathTable->resize(QSize(600, 100));
    } else {
        JLabel* prompt = new JLabel(tr("Enter a Path Name into the blank (last) row of the table to add a Path"));
        ((QVBoxLayout*)contentPane->layout())->addWidget(prompt, 0, Qt::AlignTop);//BorderLayout::North);
    }
    ((QVBoxLayout*)contentPane->layout())->addWidget(/*tablePane*/blockPathTable, 1);//BorderLayout::Center);

    return contentPane;
}

/*protected*/ JTable* TableFrames::makeBlockPathTable(BlockPathTableModel* _model) {
    JTable* blockPathTable = new JTable(_model);
    // configure DnD
#if 0
    blockPathTable->setTransferHandler(new jmri.util.DnDTableImportExportHandler(new int[]{BlockPathTableModel::EDIT_COL, BlockPathTableModel::DELETE_COL, BlockPathTableModel::UNITSCOL}));
#endif
    blockPathTable->setDragEnabled(true);
    // style table
    blockPathTable->getColumnModel()->getColumn(BlockPathTableModel::UNITSCOL)->setCellRenderer(new ToggleButtonRenderer(tr("cm"), tr("in")));
    blockPathTable->getColumnModel()->getColumn(BlockPathTableModel::UNITSCOL)->setCellEditor(new ToggleButtonEditor( tr("cm"), tr("in")));
    blockPathTable->getColumnModel()->getColumn(BlockPathTableModel::EDIT_COL)->setCellEditor(new ButtonEditor(new JButton()));
    blockPathTable->getColumnModel()->getColumn(BlockPathTableModel::EDIT_COL)->setCellRenderer(new ButtonRenderer());
    blockPathTable->getColumnModel()->getColumn(BlockPathTableModel::DELETE_COL)->setCellEditor(new ButtonEditor(new JButton()));
    blockPathTable->getColumnModel()->getColumn(BlockPathTableModel::DELETE_COL)->setCellRenderer(new ButtonRenderer());
    // units, etc renderer

    for (int i = 0; i < _model->getColumnCount(); i++) {
        int width = _model->getPreferredWidth(i);
        blockPathTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
    blockPathTable->doLayout();
    int tableWidth = blockPathTable->sizeHint().width();
    blockPathTable->setRowHeight(ROW_HEIGHT);
    blockPathTable->resize(QSize(tableWidth, qMin(TableFrames::ROW_HEIGHT * 10, maximumHeight())));

    return blockPathTable;
}






/*
 * ********************* Path-TurnoutFrame for _desktop *************************
 */
/*protected*/ TableFrames::PathTurnoutFrame* TableFrames::makePathTurnoutFrame(OBlock* block, QString pathName) {
    QString title = tr("Path \"%2\" in Block \"%1\"").arg(block->getDisplayName()).arg(pathName);
    TableFrames::PathTurnoutFrame* frame = new PathTurnoutFrame(title, true, true, false, true);
    if (log->isDebugEnabled()) {
        log->debug(tr("makePathTurnoutFrame for Block %1 and Path %2 on _desktop").arg(block->getDisplayName()).arg(pathName));
    }
    frame->setName(makePathTurnoutName(block->getSystemName(), pathName));
    OPath* path = block->getPathByName(pathName);
    if (path == nullptr) {
        return nullptr;
    }
    PathTurnoutTableModel* pathTurnoutModel = new PathTurnoutTableModel(path, frame);
    frame->setModel(pathTurnoutModel);

    JTable* pathTurnoutTable = makePathTurnoutTable(pathTurnoutModel);

    //JScrollPane tablePane = new JScrollPane(pathTurnoutTable);

    JPanel* contentPane = new JPanel();
    contentPane->setLayout(new BorderLayout(/*5, 5*/));
    JLabel* prompt = new JLabel(tr("Enter a Turnout Name into the last row"));
    ((BorderLayout*)contentPane->layout())->addWidget(prompt, BorderLayout::North);
    ((BorderLayout*)contentPane->layout())->addWidget(/*tablePane*/pathTurnoutTable, BorderLayout::Center);

    frame->addInternalFrameListener((InternalFrameListener*)this);
    frame->setContentPane(contentPane);
    //frame->setClosable(true); // is set in ctor
    frame->setLocation(10, 270);
    frame->pack();
    return frame;
}

/*
 * ********************* Path-TurnoutPanel for _tabbed *****************************
 */
/*protected*/ TableFrames::PathTurnoutJPanel* TableFrames::makePathTurnoutPanel(/*@Nonnull*/ OBlock* block, /*@CheckForNull*/ QString pathName) {
    QString title = tr("Path \"%2\" in Block \"%1\"").arg(block->getDisplayName()).arg(pathName);
    PathTurnoutJPanel* panel = new PathTurnoutJPanel(title);
    PathTurnoutTableModel* pathTurnoutModel;
    JTable* pathTurnoutTable;
    JButton* addTurnoutButton = new JButton(tr("Add Turnout"));
    addTurnoutButton->setToolTip(tr("Click to select an existing turnout and define its state for this Path"));
    JLabel* prompt = new JLabel();
    //prompt->setFont(prompt.getFont().deriveFont(0.9f * new JLabel().getFont().getSize())); // a bit smaller
    QFont f = prompt->font();
    f.setPointSizeF((new JLabel())->font().pointSizeF()*.9);
    prompt->setForeground(Qt::gray);

    if (pathName == nullptr) {
        panel->setObjectName(makePathTurnoutName(block->getSystemName(), "<new Path>"));
//        QVector<QString> columnHeaders = {tr("Turnouts")};
//        QStringList emptyTable = QStringList({tr("None")});
        QVector<QVariant> columnHeaders = {tr("Turnouts")};
        QVariantList emptyTable = {tr("None")};
        //pathTurnoutTable = new JTable(emptyTable, columnHeaders); // dummy table
        //new DefaultTableModel(QVariantList({tr("None")}), columnHeaders),); // dummy table
        pathTurnoutTable = new JTable();
        addTurnoutButton->setEnabled(false);
        prompt->setText(tr("To add Turnouts, create this Path and reselect Edit"));
    } else {
        panel->setObjectName(makePathTurnoutName(block->getSystemName(), pathName));
        /*final*/ OPath* path = block->getPathByName(pathName); // final for actionhandler
        if (path == nullptr) {
            return nullptr; // unexpected
        }
        pathTurnoutModel = new PathTurnoutTableModel(path);
        pathTurnoutTable = makePathTurnoutTable(pathTurnoutModel);
        panel->setModel(pathTurnoutModel);
//        ActionListener* addTurnoutAction= e -> addTurnoutPane(path, pathTurnoutModel);
//        addTurnoutButton.addActionListener(addTurnoutAction);
        connect(addTurnoutButton, &JButton::clicked, [=]{addTurnoutPane(path, pathTurnoutModel);});
        prompt->setText(tr("Turnouts defined on this Path"));
    }
    //JScrollPane tablePane = new JScrollPane(pathTurnoutTable);

    JPanel* tblButtons = new JPanel();
    tblButtons->setLayout(new QVBoxLayout(/*10, 10*/));
    tblButtons->setBorder(BorderFactory::createEmptyBorder(2, 10, 2, 10));
    tblButtons->setLayout(new QVBoxLayout());//tblButtons, BoxLayout.Y_AXIS));
    tblButtons->layout()->addWidget(addTurnoutButton);
    // add more to frame?

    panel->setLayout(new BorderLayout(/*5, 5*/));

    ((QVBoxLayout*)panel->layout())->addWidget(prompt, 0, Qt::AlignTop);// BorderLayout::North);
    ((QVBoxLayout*)panel->layout())->addWidget(/*tablePane*/pathTurnoutTable, 0, Qt::AlignVCenter);//BorderLayout::Center);
    ((QVBoxLayout*)panel->layout())->addWidget(tblButtons, 0, Qt::AlignBottom);//BorderLayout::South);

    return panel;
}

/*
 * ********************* Path-Turnout Table *****************************
 */
/*protected*/ JTable* TableFrames::makePathTurnoutTable(PathTurnoutTableModel* model) {
    JTable* pathTurnoutTable = new JTable(model);
#if 0
    pathTurnoutTable->setTransferHandler(new jmri.util.DnDTableImportExportHandler(
            new int[]{PathTurnoutTableModel.STATE_COL, PathTurnoutTableModel.DELETE_COL}));
#endif
    pathTurnoutTable->setDragEnabled(true);

    model->configTurnoutStateColumn(pathTurnoutTable); // use real combo
    pathTurnoutTable->getColumnModel()->getColumn(PathTurnoutTableModel::DELETE_COL)->setCellEditor(new ButtonEditor(new JButton()));
    pathTurnoutTable->getColumnModel()->getColumn(PathTurnoutTableModel::DELETE_COL)->setCellRenderer(new ButtonRenderer());
    //pathTurnoutTable->setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
    for (int i = 0; i < model->getColumnCount(); i++) {
        int width = model->getPreferredWidth(i);
        pathTurnoutTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
    pathTurnoutTable->doLayout();
    int tableWidth = pathTurnoutTable->sizeHint().width();
    pathTurnoutTable->setRowHeight(ROW_HEIGHT);
    pathTurnoutTable->resize(QSize(tableWidth,
        qMin(TableFrames::ROW_HEIGHT * 5, maximumHeight())));

    return pathTurnoutTable;
}

/**
 * Create a coded id for a path turnout.
 *
 * @param blockSysName oblock system name
 * @param pathName the path through the oblock for which to display turnouts set
 * @return name of the pathTurnout, example "%path 1-3&amp;block-1"
 */
/*protected*/ QString TableFrames::makePathTurnoutName(QString blockSysName, QString pathName) {
    return "%" + pathName + "&" + blockSysName;
}

// ********************* Open Path-Turnout Frame for _desktop *****************************
/**
 * Open a block-specific PathTurnouts table as a JInternalFrame for _desktop from BlockPathTableModel
 *
 * @param pathTurnoutName name of turnout configured on Path
 */
/*protected*/ void TableFrames::openPathTurnoutFrame(QString pathTurnoutName) {
    PathTurnoutFrame* frame = (PathTurnoutFrame*)_pathTurnoutMap.value(pathTurnoutName);
    if (frame == nullptr) {
        int index = pathTurnoutName.indexOf('&');
        QString pathName = pathTurnoutName.mid(1, index);
        QString blockName = pathTurnoutName.mid(index + 1);
        OBlock* block = (OBlock*)((BlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(blockName);
        if (block == nullptr) {
            return;
        }
        frame = makePathTurnoutFrame(block, pathName);
        if (frame == nullptr) {
            return;
        }
        _pathTurnoutMap.insert(pathTurnoutName, frame);
        frame->setVisible(true);
        desktopframe->getContentPane()->layout()->addWidget(frame);
    } else {
        frame->setVisible(true);
        try {
            frame->setIcon(false);
        } catch (PropertyVetoException pve) {
            log->warn(tr("PathTurnout Table Frame for \"%1\" vetoed setIcon %2").arg(pathTurnoutName).arg(pve.getMessage()));
        }
    }
    frame->moveToFront();
}

// *********** Open stand alone Path-Turnout Edit Panel for _tabbed *********************
/**
 * Open a block-specific PathTurnouts edit pane as a JmriJFrame for _tabbed from menu.
 * TODO fix menu access to pathturnouts on _tabbed in ListedTableView, single table menus OK
 *
 * @param pathTurnoutName name of turnout configured on Path
 */
/*protected*/ void TableFrames::openPathTurnoutEditor(QString pathTurnoutName) {
    int index = pathTurnoutName.indexOf('&');
    QString pathName = pathTurnoutName.mid(1, index);
    QString blockName = pathTurnoutName.mid(index + 1);
    OBlock* block = (OBlock*)((BlockManager*)InstanceManager::getDefault("OBlockManager"))->getBySystemName(blockName);
    if (block == nullptr) {
        return;
    }
    OPath* path = block->getPathByName(pathName);
    if (path == nullptr) {
        return;
    }
    PathTurnoutJPanel* turnouttable = makePathTurnoutPanel(block, pathName);
    // shows the turnouts on this path, already includes [Add Turnout...] button
    JmriJFrame* frame = new JmriJFrameX(tr("Path \"%2\" in Block \"%1\"").arg(block->getDisplayName()).arg(pathName));
    frame->getContentPane()->setLayout(new QVBoxLayout());//frame.getContentPane(), BoxLayout.PAGE_AXIS));
    frame->resize(370, 250);

    JPanel* p = new JPanel();
    p->setLayout(new QVBoxLayout());//p, BoxLayout.PAGE_AXIS));
    p->layout()->addWidget(turnouttable);
    JButton* ok;
    p->layout()->addWidget(ok = new JButton(tr("OK"))); // no need to save things, handled by TurnoutTable
    //ok.addActionListener((ActionEvent e) -> frame.dispose());
    connect(ok, &JButton::clicked, [=]{frame->dispose();});
    frame->getContentPane()->layout()->addWidget(p);
    frame->pack();
    frame->setVisible(true);
}

/**
 * Add new Turnout pane, called from makePathTurnoutPanel on _tabbed interface.
 *
 * @param path to link this turnout setting to
 * @param pathTurnoutModel displayed table of turnouts currently set on this path
 */
/*protected*/ void TableFrames::addTurnoutPane(OPath* path, PathTurnoutTableModel* pathTurnoutModel) {
    JmriJFrame* frame = new JmriJFrameX(tr("Add New Turnout on Path %1").arg(path->getName()));
    frame->getContentPane()->setLayout(new QVBoxLayout());//frame.getContentPane(), BoxLayout.PAGE_AXIS));
    frame->resize(200, 150);

    JPanel* p = new JPanel(new QVBoxLayout());

    /*final*/ NamedBeanComboBox/*<Turnout>*/* turnoutBox = new NamedBeanComboBox((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    JComboBox/*<String>*/* stateCombo = new JComboBox();
    JLabel* statusBar = new JLabel(tr("To create a new %1, enter its definition, then click [%2].").arg(tr("Turnout")).arg(tr("OK")), JLabel::LEADING);
    stateCombo->addItem(SET_THROWN);
    stateCombo->addItem(SET_CLOSED);
    turnoutBox->setToolTip(tr("<html>Choose a turnout from the list<br>Create it in the Turnout Table if it is not yet defined in JMRI</html>"));

    JPanel* p1 = new JPanel();
    p1->setLayout(new QHBoxLayout());//p1, BoxLayout.LINE_AXIS));
    p1->layout()->addWidget(new JLabel(tr("%1").arg(tr("Turnout"))));
    p1->layout()->addWidget(turnoutBox);
    p->layout()->addWidget(p1);

    p1 = new JPanel();
    p1->layout()->addWidget(new JLabel(tr("%1").arg(tr("Set State"))));
    p1->layout()->addWidget(stateCombo);
    p->layout()->addWidget(p1);

    p->layout()->addWidget(Box::createVerticalGlue());

    JPanel* p2 = new JPanel();
    QFont f = (new JLabel())->font();
//    statusBar->setFont(statusBar->getFont().pointSizeF()*0.9f * (new JLabel())->font().pointSizeF()); // a bit smaller
    if (turnoutBox->count() < 1) {
        statusBar->setText(tr("NotEnoughTurnouts"));
        statusBar->setForeground(Qt::red);
    } else {
        statusBar->setForeground(Qt::gray);
    }
    p2->layout()->addWidget(statusBar);
    p->layout()->addWidget(p2);

    JPanel* btns = new JPanel();
    btns->setLayout(new QHBoxLayout());//btns, BoxLayout.LINE_AXIS));
    JButton* cancel;
    btns->layout()->addWidget(cancel = new JButton(tr("Cancel")));
    //cancel.addActionListener((ActionEvent e) -> frame.dispose());
    connect(cancel, &JButton::clicked, [=]{frame->dispose();});
    JButton* ok;
    btns->layout()->addWidget(ok = new JButton(tr("OK")));
    //ok.addActionListener((ActionEvent e) -> {
    connect(ok, &JButton::clicked, [=]{
        if (turnoutBox->getSelectedItem() == nullptr || turnoutBox->getSelectedIndex() == 0) {
            statusBar->setText(tr("WarningSelectionEmpty"));
            statusBar->setForeground(Qt::red);
        } else {
            QString user = turnoutBox->getSelectedItemDisplayName();
            Turnout* t = InstanceManager::turnoutManagerInstance()->getTurnout(user);
            if (t != nullptr) {
                int s;
                if (stateCombo->getSelectedItem() != nullptr && stateCombo->getSelectedItem() ==(TableFrames::SET_CLOSED)) {
                    s = Turnout::CLOSED;
                } else {
                    s = Turnout::THROWN;
                }
                BeanSetting* bs = new BeanSetting(t, user, s);
                path->addSetting(bs);
                if (pathTurnoutModel != nullptr) {
                    pathTurnoutModel->fireTableDataChanged();
                }
            } else {
                log->error(tr("PathTurnout %1 not found").arg(user));
            }
            frame->dispose();
        }
    });
    ((QVBoxLayout*)p->layout())->addWidget(btns, 0, Qt::AlignBottom);//BorderLayout::South);

    frame->getContentPane()->layout()->addWidget(p);
    frame->pack();
    frame->setVisible(true);
}

/*
 * ********************* End of tables and frames methods *****************************
 */

// Shared warning dialog method. Store user pref to suppress further mentions.
/*protected*/ int TableFrames::verifyWarning(QString message) {
    int val = 0;
    if (_showWarnings) {
        // verify deletion
        val = JOptionPane::showOptionDialog(nullptr,
                message, tr("Warning"),
                JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(),
                QVariantList ({tr("Yes"),
                    tr("YesPlus"),
                    tr("No")}),
                tr("No")); // default choice = No
        if (val == 1) { // suppress future warnings
            _showWarnings = false;
        }
    }
    return val;
}

/*
 * ********************* InternalFrameListener implementation for _desktop *****************
 */
//@Override
/*public*/ void TableFrames::internalFrameClosing(InternalFrameEvent* e) {
    JInternalFrame* frame = (JInternalFrame*)e->getSource();
    log->debug(tr("Internal frame closing: %1").arg(frame->getTitle()));
    if (frame->getTitle() == (tr("Block Table"))) {
        showHideFrame(_blockTableFrame, openBlock, "%1 Occupancy Block Table");
    }
}

// clean up on close on _desktop
// for _tabbed this is handled in the Edit pane applyPressed() method
//@Override
/*public*/ void TableFrames::internalFrameClosed(InternalFrameEvent* e) {
    JInternalFrame* frame = (JInternalFrame*) e->getSource();
    QString name = frame->getName();
    if (log->isDebugEnabled()) {
        log->debug(tr("Internal frame closed: %1, name= %2 size (%3, %4)").arg(
                frame->getTitle()).arg(name).arg(
                frame->size().width(), frame->size().height()));
    }
    if (name != nullptr && name.startsWith("OB")) {
        _blockPathMap.remove(name);
        if (static_cast<BlockPathFrame*>(frame)) {
            QString msg = WarrantTableAction::getDefault()->checkPathPortals(((BlockPathFrame*) frame)->getModel()->getBlock());
            if (!msg.isEmpty()) {
                JOptionPane::showMessageDialog(desktopframe, msg,
                        tr("Info"), JOptionPane::INFORMATION_MESSAGE);
            }
            ((BlockPathFrame*) frame)->getModel()->removeListener();
        }
    } else {
        if (static_cast<PathTurnoutFrame*>(frame)) {
            ((PathTurnoutFrame*) frame)->getModel()->removeListener();
        _pathTurnoutMap.remove(name);
        }
    }
}

//@Override
/*public*/ void TableFrames::internalFrameOpened(InternalFrameEvent* e) {
    /*  JInternalFrame frame = (JInternalFrame)e.getSource();
     if (log.isDebugEnabled()) {
         log.debug("Internal frame Opened: {}, name= {} size ({}, {})",
                frame.getTitle(), frame.getName(),
                frame.getSize().getWidth(), frame.getSize().getHeight());
      }*/
}

//@Override
/*public*/ void TableFrames::internalFrameIconified(InternalFrameEvent* e) {
    JInternalFrame* frame = (JInternalFrame*) e->getSource();
    QString name = frame->getName();
    if (log->isDebugEnabled()) {
        log->debug(tr("Internal frame Iconified: %1, name= %2 size (%3, %4)").arg(
                frame->getTitle()).arg(name).arg(
                frame->size().width()).arg(frame->size().height()));
    }
    if (name != nullptr && name.startsWith(oblockPrefix())) {
        if (static_cast<BlockPathFrame*>(frame)) {
            QString msg = WarrantTableAction::getDefault()->checkPathPortals(((BlockPathFrame*) frame)->getModel()->getBlock());
            JOptionPane::showMessageDialog(desktopframe, msg,
                tr("Info"), JOptionPane::INFORMATION_MESSAGE);
        }
    }
}

//@Override
/*public*/ void TableFrames::internalFrameDeiconified(InternalFrameEvent* e) {
    //JInternalFrame frame = (JInternalFrame)e.getSource();
    //log.debug("Internal frame deiconified: {}", frame.getTitle());
}

//@Override
/*public*/ void TableFrames::internalFrameActivated(InternalFrameEvent* e) {
    //JInternalFrame frame = (JInternalFrame)e.getSource();
    //log.debug("Internal frame activated: {}", frame.getTitle());
}

//@Override
/*public*/ void TableFrames::internalFrameDeactivated(InternalFrameEvent* e) {
    //JInternalFrame frame = (JInternalFrame)e.getSource();
    //log.debug("Internal frame deactivated: {}", frame.getTitle());
}

/*private*/ /*final*/ /*static*/ Logger* TableFrames::log = LoggerFactory::getLogger("TableFrames");
