#include "oblocktableaction.h"
#include "tableframes.h"
#include "oblocktablepanel.h"
#include "tableframes.h"
#include <QMenu>
#include <QMenuBar>
#include "addnewbeanpanel.h"
#include "userpreferencesmanager.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "guilafpreferencesmanager.h"

/**
 * GUI to define OBlocks, OPaths and Portals. Overrides some of the AbstractTableAction methods as this is a hybrid pane.
 * Relies on {@link jmri.jmrit.beantable.oblock.TableFrames}.
 *
 * @author Pete Cressman (C) 2009, 2010
 * @author Egbert Broerse (C) 2020
 */

/*public*/ OBlockTableAction::OBlockTableAction(QObject *parent)
 : AbstractTableAction(tr("OBlock Table"),parent)
{
    //this("OBlock Table");
 common();
}

/*public*/ OBlockTableAction::OBlockTableAction(QString actionName, QObject *parent) :
AbstractTableAction(actionName, parent){
    //super(actionName);
 common();
 _includeAddButton = false; // not required per se as we override the actionPerformed method
}

void OBlockTableAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * Configure managers for all tabs on OBlocks table pane.
 * @param om the manager to assign
 */
//@Override
/*public*/ void OBlockTableAction::setManager(/*@Nonnull*/ Manager/*<OBlock>*/* om) {
    oblockManager->removePropertyChangeListener((PropertyChangeListener*)this);
    if (qobject_cast<OBlockManager*>(om)) {
        oblockManager = (OBlockManager*) om;
        if (m != nullptr) { // model
            m->setManager(oblockManager);
        }
    }
    oblockManager->addPropertyChangeListener((PropertyChangeListener*)this);
}

// add the 3 buttons to add new OBlock, Portal, Signal
//@Override
/*public*/ void OBlockTableAction::addToFrame(/*@Nonnull*/ BeanTableFrame/*<OBlock>*/* f) {
    JButton* addOblockButton = new JButton(tr("Add OBlock..."));
    otp->addToBottomBox(addOblockButton);
    //addOblockButton.addActionListener(this::addOBlockPressed);
    connect(addOblockButton, &JButton::clicked, [=]{
     addOBlockPressed();
    });

    JButton* addPortalButton = new JButton(tr("Add Portal"));
    otp->addToBottomBox(addPortalButton);
    //addPortalButton.addActionListener(this::addPortalPressed);
    connect(addPortalButton, &JButton::clicked, [=]{
     addPortalPressed();
    });

    JButton* addSignalButton = new JButton(tr("Add Signal"));
    otp->addToBottomBox(addSignalButton);
    //addSignalButton.addActionListener(this::addSignalPressed);
    connect(addSignalButton, &JButton::clicked, [=]{
     addSignalPressed();
    });
}

/*public*/ void OBlockTableAction::actionPerformed(JActionEvent * /*e*/)
{
 _tabbed = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isOblockEditTabbed();
 initTableFrames();
}

/*private*/ void OBlockTableAction::initTableFrames() {
    // initialise core OBlock Edit functionality
    tf = new TableFrames(); // tf contains OBlock Edit methods and links to tableDataModels, is a JmriJFrame that must be hidden

    if (_tabbed) { // add the tables on a JTabbedPane, choose in Preferences > Display > GUI
        log->debug("Tabbed starting");
        // create the JTable model, with changes for specific NamedBean
        createModel();
        // create the frame
        otf = new OTAOBlockTableFrame(otp, helpTarget(), this);// {

//            /**
//             * Include "Add OBlock..." and "Add XYZ..." buttons
//             */
//            @Override
//            void extras() {
//                addToFrame(this); //creates multiple sets, wrong level to call
//            }
//        };
        setTitle();

        //tf->setParentFrame(otf); // needed?
        //tf->makePrivateWindow(); // prevents tf "OBlock Tables..." to show up in the Windows menu
        //tf->setVisible(false); // hide the TableFrames container when _tabbed

        otf->pack();
        otf->setVisible(true);
    } else {
        tf->initComponents();
        // original simulated desktop interface is created in tf->initComponents() and takes care of itself if !_tabbed
        // only required for _desktop, creates InternalFrames
        //tf->setVisible(true);
    }
}

/**
 * Create the JTable DataModel, along with the extra stuff for this specific NamedBean type.
 * Is directly called to prepare the Tables &gt; OBlock Table entry in the left sidebar list, bypassing actionPerformed(a)
 */
//@Override
/*protected*/ void OBlockTableAction::createModel() { // Tabbed
    if (tf == nullptr) {
        initTableFrames();
    }
    oblocks = tf->getOblockTableModel();
    portals = tf->getPortalTableModel();
    _signals = tf->getSignalTableModel();
    blockportals = tf->getPortalXRefTableModel();

    otp = new OBlockTablePanel(oblocks, portals, _signals, blockportals, tf, helpTarget());

//        if (f == null) {
//            f = new OBlockTableFrame(otp, helpTarget());
//        }
//        setMenuBar(f); // comes after the Help menu is added by f = new
    // BeanTableFrame(etc.) handled in stand alone application
//        setTitle(); // TODO see if some of this is required or should be turned off to prevent/hide the stray JFrame that opens
//        addToFrame(f);
//        f.pack();
//        f.setVisible(true); <--- another empty pane!

    init = true;
}

//@Override
/*public*/ JPanel* OBlockTableAction::getPanel() {
    createModel();
    return otp;
}

/**
 * Include the correct title.
 */
//@Override
/*protected*/ void OBlockTableAction::setTitle() {
    if (_tabbed && otf != nullptr) {
        otf->setTitle(tr("Occupancy Block Tables"));
    }
}

//@Override
/*public*/ void OBlockTableAction::setMenuBar(BeanTableFrame/*<OBlock>*/* f) {
    if (_tabbed) {
        //final JmriJFrame finalF = f;   // needed for anonymous ActionListener class on dialogs, see TurnoutTableAction ?
        QMenuBar* menuBar = f->menuBar();
        if (menuBar == nullptr) {
            log->debug("NULL MenuBar");
            return;
        }
        //MenuElement[] subElements;
        QObjectList subElements;
        QMenu* fileMenu = nullptr;
        for (int i = 0; i < menuBar->children().count(); i++) {
            if (qobject_cast<QMenu*>(menuBar->children().at(i))) {
                if (((QMenu*) menuBar->children().at(i))->title() == (tr("File"))) {
                    fileMenu = ((QMenu*) menuBar->children().at(i));//menuBar->getMenu(i);
                }
            }
        }
        if (fileMenu == nullptr) {
            log->debug("NULL FileMenu");
            return;
        }
        //subElements = fileMenu.getSubElements();
        subElements = fileMenu->children();
#if 0
        for (Object* obj : subElements) {
         QAction* subElement = (QAction*)obj;
            MenuElement[] popsubElements = subElement.getSubElements();
            for (MenuElement popsubElement : popsubElements) {
                if (popsubElement instanceof JMenuItem) {
                    if (((JMenuItem) popsubElement).getText().equals(tr("PrintTable"))) {
                        JMenuItem printMenu = (JMenuItem) popsubElement;
                        fileMenu.remove(printMenu);
                        break;
                    }
                }
            }
        }
#endif
        fileMenu->addMenu(otp->getPrintItem());

        menuBar->addMenu(otp->getOptionMenu());
        menuBar->addMenu(otp->getTablesMenu());
        log->debug("setMenuBar for OBLOCKS");

        // check for menu (copied from TurnoutTableAction)
//            boolean menuAbsent = true;
//            for (int m = 0; m < menuBar.getMenuCount(); ++m) {
//                String name = menuBar.getMenu(m).getAccessibleContext().getAccessibleName();
//                if (name.equals(tr("MenuOptions"))) {
//                    // using first menu for check, should be identical to next JMenu Bundle
//                    menuAbsent = false;
//                    break;
//                }
//            }
//            if (menuAbsent) { // create it
//                int pos = menuBar.getMenuCount() - 1; // count the number of menus to insert the TableMenu before 'Window' and 'Help'
//                int offset = 1;
//                log.debug("setMenuBar number of menu items = {}", pos);
//                for (int i = 0; i <= pos; i++) {
//                    if (menuBar.getComponent(i) instanceof JMenu) {
//                        if (((JMenu) menuBar.getComponent(i)).getText().equals(tr("MenuHelp"))) {
//                            offset = -1; // correct for use as part of ListedTableAction where the Help Menu is not yet present
//                        }
//                    }
//                }
            // add separate items, actionhandlers? next 2 menuItem examples copied from TurnoutTableAction

    //            JMenuItem item = new JMenuItem(tr("TurnoutAutomationMenuItemEdit"));
    //            opsMenu.add(item);
    //            item.addActionListener(new ActionListener() {
    //                @Override
    //                public void actionPerformed(ActionEvent e) {
    //                    new TurnoutOperationFrame(finalF);
    //                }
    //            });
    //            menuBar.add(opsMenu, pos + offset); // test
    //
    //            JMenu speedMenu = new JMenu(tr("SpeedsMenu"));
    //            item = new JMenuItem(tr("SpeedsMenuItemDefaults"));
    //            speedMenu.add(item);
    //            item.addActionListener(new ActionListener() {
    //                @Override
    //                public void actionPerformed(ActionEvent e) {
    //                    //setDefaultSpeeds(finalF);
    //                }
    //            });
    //            menuBar.add(speedMenu, pos + offset + 1); // add this menu to the right of the previous
    //    }
        f->addHelpMenu("package.jmri.jmrit.beantable.OBlockTable", true);
    }
}


// Three [Addx...] buttons on tabbed bottom box handlers

//@Override
/*protected*/ void OBlockTableAction::addPressed(/*JActionEvent *e*/) {
    log->warn("This should not have happened");
}

/*protected*/ void OBlockTableAction::addOBlockPressed(ActionEvent *e) {
    pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");

    if (addOBlockFrame == nullptr) {
        addOBlockFrame = new JmriJFrameX(tr("Add Occupancy Block"), false, true);
        addOBlockFrame->addHelpMenu("package.jmri.jmrit.beantable.OBlockTable", true);
        addOBlockFrame->getContentPane()->setLayout(new QVBoxLayout());//addOBlockFrame.getContentPane(), BoxLayout.Y_AXIS));

        //ActionListener okListener = this::createObPressed;
        ActionListener* okListener = new OTAOkActionListener(this);
        //ActionListener cancelListener = this::cancelObPressed;
        ActionListener* cancelListener = new OTACancelListener(this);

        addOBlockFrame->layout()->addWidget(new AddNewBeanPanel(startAddress, userName, numberToAddSpinner, rangeBox, autoSystemNameBox, tr("Create"), okListener, cancelListener, statusBar));
        startAddress->setToolTip(tr("<html>Enter System Name for this new item, e.g. X{0}12<br>where X = the prefix for your connection<br>and %1 = is the letter for the item type.</html>").arg("OB")); // override tooltip with bean specific letter
    }
    startAddress->setBackground(Qt::white);
    // reset status bar text
    status(tr("AddBeanStatusEnter"), false);
    if (pref->getSimplePreferenceState(systemNameAuto)) {
        autoSystemNameBox->setChecked(true);
    }
    addOBlockFrame->pack();
    addOBlockFrame->setVisible(true);
}

void OBlockTableAction::cancelObPressed(/*ActionEvent e*/) {
    addOBlockFrame->setVisible(false);
    addOBlockFrame->dispose();
    addOBlockFrame = nullptr;
}

/**
 * Respond to Create new OBlock button pressed on Add OBlock pane.
 * Adapted from {@link MemoryTableAction#addPressed(ActionEvent)}
 *
 * @param e the click event
 */
void OBlockTableAction::createObPressed(/*ActionEvent e*/) {
    int numberOfOblocks = 1;

    if (rangeBox->isChecked()) {
        numberOfOblocks =  numberToAddSpinner->getValue();
    }

    if (numberOfOblocks >= 65) { // limited by JSpinnerModel to 100
        if (JOptionPane::showConfirmDialog(addOBlockFrame,
                tr("You are about to add %1 %2 into the configuration.\nAre you sure?").arg(tr("OBlocks")).arg(numberOfOblocks),
                tr("Warning"),
                JOptionPane::YES_NO_OPTION) == 1) {
            return;
        }
    }

    QString uName = NamedBean::normalizeUserName(userName->text());
    if (!uName.isNull()  && uName.isEmpty()) {
        uName = QString();
    }
    QString sName = startAddress->text().trimmed();
    // initial check for empty entries
    if (autoSystemNameBox->isChecked()) {
        startAddress->setBackground(Qt::white);
    } else if (sName ==("")) {
        status(tr("WarningSysNameEmpty"), true);
        startAddress->setBackground(Qt::red);
        return;
    } else if (!sName.startsWith("OB")) {
        sName = "OB" + sName;
    }
    // Add some entry pattern checking, before assembling sName and handing it to the OBlockManager
    QString statusMessage = QString(tr("New %1(s) added:").arg(tr("OBlock")));
    QString errorMessage = QString();
    for (int x = 0; x < numberOfOblocks; x++) {
        if (!uName.isNull() && !uName.isEmpty() && oblockManager->getByUserName(uName) != nullptr && !pref->getPreferenceState(getClassName(), "duplicateUserName")) {
            ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                    showErrorMessage(tr("Error"), tr("The specified user name \"%1\" is already in use and therefore will not be set.").arg(uName), getClassName(), "duplicateUserName", false, true);
            // show in status bar
            errorMessage = tr("The specified user name \"%1\" is already in use and therefore will not be set.").arg(uName);
            status(errorMessage, true);
            uName = QString(); // new OBlock objects always receive a valid system name using the next free index, but uName names must not be in use so use none in that case
        }
        if (!sName.isEmpty() && oblockManager->getBySystemName(sName) != nullptr && !pref->getPreferenceState(getClassName(), "duplicateSystemName")) {
            ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                    showErrorMessage(tr("Error"), tr("The specified system name \"%1\" is already in use. Item was not created.").arg(sName), getClassName(), "duplicateSystemName", false, true);
            // show in status bar
            errorMessage = tr("The specified system name \"%1\" is already in use. Item was not created.").arg(sName);
            status(errorMessage, true);
            return; // new OBlock objects are always valid, but system names must not be in use so skip in that case
        }
        OBlock* oblk;
        QString xName = "";
        try {
            if (autoSystemNameBox->isChecked()) {
//                assert uName != null;
                oblk = oblockManager->createNewOBlock(uName);
                if (oblk == nullptr) {
                    xName = uName;
                    throw IllegalArgumentException();
                }
            } else {
                oblk = oblockManager->createNewOBlock(sName, uName);
                if (oblk == nullptr) {
                    xName = sName;
                    throw IllegalArgumentException();
                }
            }
        } catch (IllegalArgumentException ex) {
            // uName input no good
            handleCreateException(xName);
            errorMessage = tr("ErrorAddFailedCheck");
            status(errorMessage, true);
            return; // without creating
        }

        // add first and last names to statusMessage uName feedback string
        // only mention first and last of rangeBox added
        if (x == 0 || x == numberOfOblocks - 1) {
            statusMessage.append(" ").append(sName).append(" (").append(uName).append(")");
        }
        if (x == numberOfOblocks - 2) {
            statusMessage.append(" ").append(tr("ItemCreateUpTo")).append(" ");
        }

        // bump system & uName names
        if (!autoSystemNameBox->isChecked()) {
            sName = nextName(sName);
        }
        if (uName != "") {
            uName = nextName(uName);
        }
    } // end of for loop creating rangeBox of OBlocks

    // provide feedback to uName
    if (errorMessage == "") {
        status(statusMessage/*.toString()*/, false);
        // statusBar.setForeground(Qt::red); handled when errorMassage is set to differentiate urgency
    }

    pref->setSimplePreferenceState(systemNameAuto, autoSystemNameBox->isChecked());
    // Notify changes
    oblocks->fireTableDataChanged();
}

void OBlockTableAction::addPortalPressed(ActionEvent* e) {
    if (portalFrame == nullptr) {
        portalFrame = new PortalEditFrame(tr("TitleAdAdd PortaldPortal"), nullptr, portals);
    }
    //portalFrame.updatePortalList();
    portalFrame->resetFrame();
    portalFrame->pack();
    portalFrame->setVisible(true);
}

void OBlockTableAction::addSignalPressed(ActionEvent* e) {
    if (!_signals->editMode()) {
        _signals->setEditMode(true);
        if (signalFrame == nullptr) {
            signalFrame = new SignalEditFrame(tr("Add Signal"), nullptr, nullptr, _signals);
        }
        //signalFrame.updateSignalList();
        signalFrame->resetFrame();
        signalFrame->pack();
        signalFrame->setVisible(true);
    }
}

void OBlockTableAction::handleCreateException(QString sysName) {
    JOptionPane::showMessageDialog(addOBlockFrame,
            tr("Could not create OBlock \"%1\" to add it.").arg(sysName) + "\n" + tr("Check that number/name is OK and not in use."),
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}

/**
 * Create or update the blockPathTableModel. Used in EditBlockPath pane.
 *
//     * @param block to build a table for
 */
//    private void setBlockPathTableModel(OBlock block) {
//        BlockPathTableModel blockPathTableModel = tf->getBlockPathTableModel(block);
//    }

//    @Override // loops with ListedTableItem.dispose()
//    public void dispose() {
//        //jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class).setSimplePreferenceState(getClassName() + ":LengthUnitMetric", centimeterBox.isSelected());
//        f.dispose();
//        super.dispose();
//    }

//@Override
/*protected*/ QString OBlockTableAction::getClassName() {
    return /*OBlockTableAction.class.getName()*/"jmri.jmrit.beantable.OBlockTableAction" ;
}

//@Override
/*public*/ QString OBlockTableAction::getClassDescription() {
    return tr("TitleOBlockTable");
}

//    @Override
//    public void addToPanel(AbstractTableTabAction<OBlock> f) {
//        // not used (checkboxes etc.)
//    }

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void OBlockTableAction::propertyChange(PropertyChangeEvent* e) {
    QString property = e->getPropertyName();
    if (log->isDebugEnabled()) {
        log->debug(tr("PropertyChangeEvent property = %1 source= %2").arg(property).arg(e->getSource()->metaObject()->className()));
    }
//    switch (property) {
//        case "StateStored":
//            //isStateStored.setSelected(oblockManager.isStateStored());
//            break;
//        case "UseFastClock":
//        default:
//            //isFastClockUsed.setSelected(portalManager.isFastClockUsed());
//            break;
//    }
}

void OBlockTableAction::status(QString message, bool warn){
    statusBar->setText(message);
    statusBar->setForeground(warn ? Qt::red : Qt::gray);
}

//@Override
/*protected*/ QString OBlockTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.OBlockTable";
}

/*private*/ /*final*/ /*static*/ Logger* OBlockTableAction::log = LoggerFactory::getLogger("OBlockTableAction");

