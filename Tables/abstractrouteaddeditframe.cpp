#include "abstractrouteaddeditframe.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include "routesensormodel.h"
#include "routeturnoutmodel.h"
#include <QButtonGroup>
#include "borderfactory.h"
#include "jspinner.h"
#include "spinnernumbermodel.h"
#include "stringutil.h"
#include "fileutil.h"
#include "jbutton.h"
#include "box.h"
#include "alphanumcomparator.h"
#include "jtable.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "rowsorterutil.h"
#include "tablerowsorter.h"

/**
 * Base class for Add/Edit frame for the Route Table.
 *
 * Split from {@link jmri.jmrit.beantable.RouteTableAction}
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Simon Reader Copyright (C) 2008
 * @author Pete Cressman Copyright (C) 2009
 * @author Egbert Broerse Copyright (C) 2016
 * @author Paul Bender Copyright (C) 2020
 */
// /*public*/ abstract class AbstractRouteAddEditFrame extends JmriJFrame {


    /*static*/ /*final*/ QStringList AbstractRouteAddEditFrame::COLUMN_NAMES = {tr("SystemName"),
            tr("UserName"),
            tr("Include"),
            tr("SetState")};
    /*private*/ /*static*/ /*final*/ QString AbstractRouteAddEditFrame::SET_TO_ACTIVE = tr("Set") + " " + tr("Active");
    /*private*/ /*static*/ /*final*/ QString AbstractRouteAddEditFrame::SET_TO_INACTIVE = tr("Set") + " " + tr("SensorStateInactive");
    /*static*/ /*final*/ QString AbstractRouteAddEditFrame::SET_TO_TOGGLE = tr("Set") + " " + tr("Toggle");
    /*private*/ /*static*/ /*final*/ QStringList AbstractRouteAddEditFrame::sensorInputModes = {
            tr("On") + " " + tr("Active"),
            tr("On") + " " + tr("SensorStateInactive"),
            tr("On Change"),
            "Veto " + tr("WhenCondition") + " " + tr("Active"),
            "Veto " + tr("WhenCondition") + " " + tr("SensorStateInactive")
    };
    /*private*/ /*static*/ /*final*/ QVector<int> AbstractRouteAddEditFrame::sensorInputModeValues = {Route::ONACTIVE, Route::ONINACTIVE, Route::ONCHANGE,
                                                                                                      Route::VETOACTIVE, Route::VETOINACTIVE};

    // safe methods to set the above 4 static field values
    /*private*/ /*static*/ /*final*/ QVector<int> AbstractRouteAddEditFrame::turnoutInputModeValues = {Route::ONCLOSED, Route::ONTHROWN, Route::ONCHANGE,
                                                                                                   Route::VETOCLOSED, Route::VETOTHROWN};

    /*private*/ /*static*/ /*final*/ Logger* AbstractRouteAddEditFrame::log = LoggerFactory::getLogger("AbstractRouteAddEditFrame");

    /*static*/ int AbstractRouteAddEditFrame::ROW_HEIGHT = 0;
    // This group will get runtime updates to system-specific contents at
    // the start of buildModel() above.  This is done to prevent
    // invoking the TurnoutManager at class construction time,
    // when it hasn't been configured yet
    /*static*/ QString AbstractRouteAddEditFrame::SET_TO_CLOSED = tr("Set") + " "
            + tr("Closed");
    /*static*/ QString AbstractRouteAddEditFrame::SET_TO_THROWN = tr("Set") + " "
            + tr("Thrown");
    /*private*/ /*static*/ QStringList AbstractRouteAddEditFrame::turnoutInputModes ={
            tr("On") + " " + tr("Closed"),
            tr("On") + " " + tr("Thrown"),
            tr("On Change"),
            "Veto " + tr("WhenCondition") + " " + tr("Closed"),
            "Veto " + tr("WhenCondition") + " " + tr("Thrown")
    };
    /*private*/ /*static*/ QStringList AbstractRouteAddEditFrame::lockTurnoutInputModes = {
            tr("On") + " " + tr("Closed"),
            tr("On") + " " + tr("Thrown"),
            tr("On Change")
    };


    /*public*/ AbstractRouteAddEditFrame::AbstractRouteAddEditFrame(QString name, bool saveSize, bool savePosition, QWidget *parent)
      : JmriJFrameX(name, saveSize, savePosition)
    {
        //super(name, saveSize, savePosition);

        setClosedString(tr("Set") + " "
                + InstanceManager::turnoutManagerInstance()->getClosedText());
        setThrownString(tr("Set") + " "
                + InstanceManager::turnoutManagerInstance()->getThrownText());
        setTurnoutInputModes(QStringList{
                tr("On") + " " + InstanceManager::turnoutManagerInstance()->getClosedText(),
                tr("On") + " " + InstanceManager::turnoutManagerInstance()->getThrownText(),
                tr("On Change"),
                "Veto " + tr("WhenCondition") + " " + tr("Closed"),
                "Veto " + tr("WhenCondition") + " " + tr("Thrown")
        });
        setLockTurnoutModes(QStringList{
                tr("On") + " " + InstanceManager::turnoutManagerInstance()->getClosedText(),
                tr("On") + " " + InstanceManager::turnoutManagerInstance()->getThrownText(),
                tr("On Change")
        });

        routeManager = (RouteManager*)InstanceManager::getDefault("RouteManager");

    }

    /*protected*/ /*static*/ void AbstractRouteAddEditFrame::setClosedString(/*@Nonnull */QString newVal) {
        SET_TO_CLOSED = newVal;
    }

    /*protected*/ /*static*/ void AbstractRouteAddEditFrame::setThrownString(/*@Nonnull*/ QString newVal) {
        SET_TO_THROWN = newVal;
    }

    /*protected*/ /*static*/ void AbstractRouteAddEditFrame::setTurnoutInputModes(/*@Nonnull*/ QStringList newArray) {
        turnoutInputModes = newArray;
    }

    /*protected*/ /*static*/ void AbstractRouteAddEditFrame::setLockTurnoutModes(/*@Nonnull*/ QStringList newArray) {
        lockTurnoutInputModes = newArray;
    }

    /*private*/ /*static*/ /*synchronized*/ void AbstractRouteAddEditFrame::setRowHeight(int newVal) {
        ROW_HEIGHT = newVal;
    }

    //@Override
    /*public*/ void AbstractRouteAddEditFrame::initComponents() {
        JmriJFrameX::initComponents();

        pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
        if (editMode) {
            cancelEdit();
        }
        TurnoutManager* tm = InstanceManager::turnoutManagerInstance();
        _turnoutList = QList<RouteTurnout*>();
        for (NamedBean* nb : tm->getNamedBeanSet()) {
         Turnout* t = (Turnout*)nb;
            QString systemName = t->getSystemName();
            QString userName = t->getUserName();
            _turnoutList.append(new RouteTurnout(systemName, userName));
        }

        SensorManager* sm = InstanceManager::sensorManagerInstance();
        _sensorList = QList<RouteSensor*>();
        for (NamedBean* nb: sm->getNamedBeanSet()) {
         Sensor* s  = (Sensor*) nb;
            QString systemName = s->getSystemName();
            QString userName = s->getUserName();
            _sensorList.append(new RouteSensor(systemName, userName));
        }
        initializeIncludedList();

        turnoutsAlignedSensor = new NamedBeanComboBox(InstanceManager::sensorManagerInstance());
        sensor1 = new NamedBeanComboBox(InstanceManager::sensorManagerInstance());
        sensor2 = new NamedBeanComboBox(InstanceManager::sensorManagerInstance());
        sensor3 = new NamedBeanComboBox(InstanceManager::sensorManagerInstance());
        cTurnout = new NamedBeanComboBox(InstanceManager::turnoutManagerInstance());
        cLockTurnout = new NamedBeanComboBox(InstanceManager::turnoutManagerInstance());

        // Set combo max rows
//        JComboBoxUtil->setupComboBoxMaxRows(turnoutsAlignedSensor);
//        JComboBoxUtil->setupComboBoxMaxRows(sensor1);
//        JComboBoxUtil->setupComboBoxMaxRows(sensor2);
//        JComboBoxUtil->setupComboBoxMaxRows(sensor3);
//        JComboBoxUtil->setupComboBoxMaxRows(cTurnout);
//        JComboBoxUtil->setupComboBoxMaxRows(cLockTurnout);

        addHelpMenu("package.jmri.jmrit.beantable.RouteAddEdit", true);
        setLocation(100, 30);

        JPanel* contentPanel = new JPanel();
        contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));
        // add system name
        JPanel* ps = new JPanel();
        ps->setLayout(new FlowLayout());
        ps->layout()->addWidget(nameLabel);
        nameLabel->setLabelFor(_systemName);
        ps->layout()->addWidget(_systemName);
        ps->layout()->addWidget(_autoSystemName);
        //_autoSystemName->layout()->addWidgetActionListener((ActionEvent e1) -> autoSystemName());
        connect(_autoSystemName, &JCheckBox::clicked, [=]{
         if (pref->getSimplePreferenceState(systemNameAuto)) {
             _autoSystemName->setChecked(true);
             _systemName->setEnabled(false);
         }
        });
        _systemName->setToolTip(tr("TooltipRouteSystemName"));
        contentPanel->layout()->addWidget(ps);
        // add user name
        JPanel* p = new JPanel();
        p->setLayout(new FlowLayout());
        p->layout()->addWidget(userLabel);
        userLabel->setLabelFor(_userName);
        p->layout()->addWidget(_userName);
        _userName->setToolTip(tr("Enter User Name for the new Route, e.g. 'Clear Mainline'"));
        contentPanel->layout()->addWidget(p);

        // add Turnout Display Choice
        JPanel* py = new JPanel(new FlowLayout());
        py->layout()->addWidget(new JLabel(tr("Show") + ":"));
        QButtonGroup* selGroup = new QButtonGroup(this);
        allButton = new QRadioButton(tr("All")/*, true*/);
        allButton->setChecked(true);
        selGroup->addButton(allButton);
        py->layout()->addWidget(allButton);
//        allButton->layout()->addWidgetActionListener((ActionEvent e1) -> {
        connect(allButton, &QRadioButton::clicked, [=]{
            // Setup for display of all Turnouts, if needed
            if (!showAll) {
                showAll = true;
                _routeTurnoutModel->fireTableDataChanged();
                _routeSensorModel->fireTableDataChanged();
            }
        });
        QRadioButton* includedButton = new QRadioButton(tr("Included")/*, false*/);
        includedButton->setChecked(false);
        selGroup->addButton(includedButton);
        py->layout()->addWidget(includedButton);
//        includedButton->layout()->addWidgetActionListener((ActionEvent e1) -> {
        connect(includedButton, &QRadioButton::clicked, [=]{
            // Setup for display of included Turnouts only, if needed
            if (showAll) {
                showAll = false;
                initializeIncludedList();
                _routeTurnoutModel->fireTableDataChanged();
                _routeSensorModel->fireTableDataChanged();
            }
        });
        py->layout()->addWidget(new JLabel(tr("%1 and %2").arg(tr("Turnouts")).arg(tr("Sensors"))));
        // keys are in jmri.jmrit.Bundle
        contentPanel->layout()->addWidget(py);
        contentPanel->layout()->addWidget(getTurnoutPanel());
        contentPanel->layout()->addWidget(getSensorPanel());
        contentPanel->layout()->addWidget(getFileNamesPanel());
        contentPanel->layout()->addWidget(getAlignedSensorPanel());
        contentPanel->layout()->addWidget(getControlsPanel());
        contentPanel->layout()->addWidget(getLockPanel());
        contentPanel->layout()->addWidget(getNotesPanel());
        contentPanel->layout()->addWidget(getButtonPanel());

        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidget(contentPanel);
        if(getContentPane()->layout() == nullptr)
         getContentPane()->setLayout(new QVBoxLayout());
        getContentPane()->layout()->addWidget(scrollArea);//new JScrollPane(contentPanel), BorderLayout.CENTER);

        pack();

        // set listener for window closing
//        addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                closeFrame();
//            }
//        });
          addWindowListener(new ARAEFWindowListener(this));
    }

    ///*protected*/ abstract JPanel* getButtonPanel();
#if 1
    /*private*/ JPanel* AbstractRouteAddEditFrame::getNotesPanel() {
        // add notes panel
        JPanel* pa = new JPanel();
        pa->setLayout(new QVBoxLayout());//pa, BoxLayout.Y_AXIS));
        JPanel* p1 = new JPanel();
        p1->setLayout(new FlowLayout());
        status1->setText(tr("To create a new Route, enter its definition, then click [%1].").arg(tr("Create"))); // I18N to include original button name in help string
        QFont f =status1->font();
        f.setPointSizeF(0.9f * nameLabel->getFont().pointSizeF());
        status1->setFont(f); // a bit smaller
        status1->setForeground(Qt::gray);
        p1->layout()->addWidget(status1);
        JPanel* p2 = new JPanel();
        p2->setLayout(new FlowLayout());
        status2->setText(tr("To exit without changes or additions, click [%1].").arg(tr("Cancel","")));
        status2->setFont(f);//status1.getFont().deriveFont(0.9f * nameLabel.getFont().getSize())); // a bit smaller
        status2->setForeground(Qt::gray);
        p2->layout()->addWidget(status2);
        pa->layout()->addWidget(p1);
        pa->layout()->addWidget(p2);
        Border* pBorder = BorderFactory::createEtchedBorder();
        pa->setBorder(pBorder);
        return pa;
    }

    /*private*/ JPanel* AbstractRouteAddEditFrame::getLockPanel() {
        // add lock control table
        JPanel* p4 = new JPanel();
        p4->setLayout(new QVBoxLayout());//p4, BoxLayout.Y_AXIS));
        // add lock control turnout
        JPanel* p43 = new JPanel(new FlowLayout());
        p43->layout()->addWidget(new JLabel(tr("Turnout that controls the Lock for this Route (optional)")));
        p4->layout()->addWidget(p43);
        JPanel* p44 = new JPanel(new FlowLayout);
        p44->layout()->addWidget(new JLabel(tr("%1").arg(tr("Turnout"))));
        p44->layout()->addWidget(cLockTurnout);
        cLockTurnout->setAllowNull(true);
        cLockTurnout->setSelectedItem(nullptr);
        cLockTurnout->setToolTip(tr("Select a Turnout (real or internal)"));
        p44->layout()->addWidget(new JLabel("   " + tr("%1").arg(tr("Condition"))));
        cLockTurnoutStateBox->setToolTip(tr("Setting the control Turnout to the state selected here will lock this Route"));
        p44->layout()->addWidget(cLockTurnoutStateBox);
        p4->layout()->addWidget(p44);
        // complete this panel
        Border* p4Border = BorderFactory::createEtchedBorder();
        p4->setBorder(p4Border);
        return p4;
    }

    /*private*/ JPanel* AbstractRouteAddEditFrame::getControlsPanel() {
        // add Control Sensor table
        JPanel* p3 = new JPanel();
        p3->setLayout(new QVBoxLayout());//p3, BoxLayout.Y_AXIS));
        JPanel* p31 = new JPanel(new FlowLayout());
        p31->layout()->addWidget(new JLabel(tr("LabelEnterSensors")));
        p3->layout()->addWidget(p31);
        JPanel* p32 = new JPanel(new FlowLayout());
        //Sensor 1
        JPanel* pS = new JPanel(new FlowLayout());
        pS->setBorder(BorderFactory::createTitledBorder(tr("Sensor") + " 1"));
        pS->layout()->addWidget(sensor1);
        pS->layout()->addWidget(sensor1mode);
        p32->layout()->addWidget(pS);
        //Sensor 2
        pS = new JPanel(new FlowLayout());
        pS->setBorder(BorderFactory::createTitledBorder(tr("Sensor") + " 2"));
        pS->layout()->addWidget(sensor2);
        pS->layout()->addWidget(sensor2mode);
        p32->layout()->addWidget(pS);
        //Sensor 3
        pS = new JPanel(new FlowLayout());
        pS->setBorder(BorderFactory::createTitledBorder(tr("Sensor") + " 3"));
        pS->layout()->addWidget(sensor3);
        pS->layout()->addWidget(sensor3mode);
        p32->layout()->addWidget(pS);

        sensor1->setAllowNull(true);
        sensor2->setAllowNull(true);
        sensor3->setAllowNull(true);
        sensor1->setSelectedItem(nullptr);
        sensor2->setSelectedItem(nullptr);
        sensor3->setSelectedItem(nullptr);
        QString sensorHint = tr("Select a Sensor (or empty row)");
        sensor1->setToolTip(sensorHint);
        sensor2->setToolTip(sensorHint);
        sensor3->setToolTip(sensorHint);
        p3->layout()->addWidget(p32);
        // add control turnout
        JPanel* p33 = new JPanel(new FlowLayout());
        p33->layout()->addWidget(new JLabel(tr("Turnout that triggers this Route (optional)")));
        p3->layout()->addWidget(p33);
        JPanel* p34 = new JPanel(new FlowLayout());
        p34->layout()->addWidget(new JLabel(tr("%1").arg(tr("Turnout"))));
        p34->layout()->addWidget(cTurnout);
        cTurnout->setAllowNull(true);
        cTurnout->setSelectedItem(nullptr);
        cTurnout->setToolTip(tr("Select a Turnout (real or internal)"));
        p34->layout()->addWidget(new JLabel("   " + tr("%1").arg(tr("Condition"))));
        cTurnoutStateBox->setToolTip(tr("Setting control Turnout to the state selected here will trigger this Route"));
        p34->layout()->addWidget(cTurnoutStateBox);
        p3->layout()->addWidget(p34);
        // add additional route-specific delay
        JPanel* p36 = new JPanel(new FlowLayout());
        p36->layout()->addWidget(new JLabel(tr("%1").arg(tr("Additional delay between Turnout Commands (optional)"))));
        timeDelay->setModel(new SpinnerNumberModel(0, 0, 1000, 1));
        // timeDelay->setValue(0); // reset from possible previous use
        timeDelay->resize(JTextField(5).getPreferredSize());
        p36->layout()->addWidget(timeDelay);
        timeDelay->setToolTip(tr("Enter time in milliseconds to add to the connection-specific minimum interval between Turnout commands"));
        p36->layout()->addWidget(new JLabel(tr("Milliseconds")));
        p3->layout()->addWidget(p36);
        // complete this panel
        Border* p3Border = BorderFactory::createEtchedBorder();
        p3->setBorder(p3Border);
        return p3;
    }

    /*private*/ JPanel* AbstractRouteAddEditFrame::getAlignedSensorPanel() {
        //add turnouts aligned Sensor
        JPanel* p27 = new JPanel();
        p27->setLayout(new FlowLayout());
        p27->layout()->addWidget(new JLabel(tr("LabelEnterSensorAligned")));
        p27->layout()->addWidget(turnoutsAlignedSensor);
        turnoutsAlignedSensor->setAllowNull(true);
        turnoutsAlignedSensor->setSelectedItem(nullptr);
        turnoutsAlignedSensor->setToolTip(tr("Select a Sensor (or empty row)"));
        return p27;
    }

    /*private*/ JPanel* AbstractRouteAddEditFrame::getFileNamesPanel() {
        // Enter filenames for sound, script
        JPanel* p25 = new JPanel();
        p25->setLayout(new FlowLayout());
        p25->layout()->addWidget(new JLabel(tr("LabelPlaySound")));
        p25->layout()->addWidget(soundFile);
        JButton* ss = new JButton("..."); //NO18N
        //ss->layout()->addWidgetActionListener((ActionEvent e1) -> setSoundPressed());
        connect(ss, &JButton::clicked, [=]{setSoundPressed();});
        ss->setToolTip(tr("Select %1 file from disk").arg(tr("Audio")));
        p25->layout()->addWidget(ss);
        p25->layout()->addWidget(new JLabel(tr("Run Script")));
        p25->layout()->addWidget(scriptFile);
        ss = new JButton("..."); //NO18N
        //ss->layout()->addWidgetActionListener((ActionEvent e1) -> setScriptPressed());
        connect(ss, &JButton::clicked, [=]{setScriptPressed();});
        ss->setToolTip(tr("Select %1 file from disk").arg(tr("Script")));
        p25->layout()->addWidget(ss);
        return p25;
    }

    /*private*/ JPanel* AbstractRouteAddEditFrame::getTurnoutPanel(){
        // add Turnout table
        // Turnout list table
        JPanel* p2xt = new JPanel(new FlowLayout());
        JPanel* p2xtSpace = new JPanel();
        p2xtSpace->setLayout(new QVBoxLayout());//p2xtSpace, BoxLayout.Y_AXIS));
        p2xtSpace->layout()->addWidget(Box::createRigidArea(QSize(30,0)));
        p2xt->layout()->addWidget(p2xtSpace);

        JPanel* p21t = new JPanel();
        p21t->setLayout(new QVBoxLayout());//p21t, BoxLayout.Y_AXIS));
        p21t->layout()->addWidget(new JLabel(tr("<html>Select %1<br>to be included<br>in this Route:</html>").arg(tr("Turnouts"))));
        p2xt->layout()->addWidget(p21t);
        _routeTurnoutModel = new RouteTurnoutModel(this);
        JTable* routeTurnoutTable = new JTable(_routeTurnoutModel);
//        TableRowSorter/*<RouteTurnoutModel*>*/* rtSorter = new TableRowSorter(_routeTurnoutModel);

//        // Use AlphanumComparator for SNAME and UNAME columns.  Start with SNAME sort.
//        rtSorter->setComparator(RouteOutputModel::SNAME_COLUMN, (Comparator*)new AlphanumComparator());
//        rtSorter->setComparator(RouteOutputModel::UNAME_COLUMN, (Comparator*)new AlphanumComparator());
//        RowSorterUtil::setSortOrder(rtSorter, RouteOutputModel::SNAME_COLUMN, SortOrder::ASCENDING);

//        routeTurnoutTable->setRowSorter(rtSorter);
        routeTurnoutTable->setRowSelectionAllowed(false);
//        routeTurnoutTable->setPreferredScrollableViewportSize(QSize(480, 80));
        routeTurnoutTable->resize(QSize(480, 80));

        setRowHeight(routeTurnoutTable->getRowHeight());
        JComboBox* stateTCombo = new JComboBox();
        stateTCombo->addItem(SET_TO_CLOSED);
        stateTCombo->addItem(SET_TO_THROWN);
        stateTCombo->addItem(SET_TO_TOGGLE);
        TableColumnModel* routeTurnoutColumnModel = routeTurnoutTable->getColumnModel();
        TableColumn* includeColumnT = routeTurnoutColumnModel->
                getColumn(RouteOutputModel::INCLUDE_COLUMN);
        includeColumnT->setResizable(false);
        includeColumnT->setMinWidth(50);
        includeColumnT->setMaxWidth(60);
        TableColumn* sNameColumnT = routeTurnoutColumnModel->
                getColumn(RouteOutputModel::SNAME_COLUMN);
        sNameColumnT->setResizable(true);
        sNameColumnT->setMinWidth(75);
        sNameColumnT->setMaxWidth(95);
        TableColumn* uNameColumnT = routeTurnoutColumnModel->
                getColumn(RouteOutputModel::UNAME_COLUMN);
        uNameColumnT->setResizable(true);
        uNameColumnT->setMinWidth(210);
        uNameColumnT->setMaxWidth(260);
        TableColumn* stateColumnT = routeTurnoutColumnModel->
                getColumn(RouteOutputModel::STATE_COLUMN);
        stateColumnT->setCellEditor(new /*DefaultCellEditor(stateTCombo)*/JComboBoxEditor(stateTCombo));
        stateColumnT->setResizable(false);
        stateColumnT->setMinWidth(90);
        stateColumnT->setMaxWidth(100);
//        _routeTurnoutScrollPane = new JScrollPane(routeTurnoutTable);
        p2xt->layout()->addWidget(/*_routeTurnoutScrollPane*/routeTurnoutTable);//, BorderLayout.CENTER);
        p2xt->setVisible(true);
        return p2xt;
    }

    /*private*/ JPanel* AbstractRouteAddEditFrame::getSensorPanel(){
        // add Sensor table
        // Sensor list table
        JPanel* p2xs = new JPanel(new FlowLayout());
        JPanel* p2xsSpace = new JPanel();
        p2xsSpace->setLayout(new QVBoxLayout());//p2xsSpace, BoxLayout.Y_AXIS));
        p2xsSpace->layout()->addWidget(Box::createRigidArea(QSize(30,0)));
        p2xs->layout()->addWidget(p2xsSpace);

        JPanel* p21s = new JPanel();
        p21s->setLayout(new QVBoxLayout());//p21s, BoxLayout.Y_AXIS));
        p21s->layout()->addWidget(new JLabel(tr("<html>Select %1<br>to be included<br>in this Route:</html>").arg(tr("Sensors"))));
        p2xs->layout()->addWidget(p21s);
        _routeSensorModel = new RouteSensorModel(this);
        JTable* routeSensorTable = new JTable(_routeSensorModel);
//        TableRowSorter/*<RouteSensorModel>*/* rsSorter = new TableRowSorter(_routeSensorModel);

//        // Use AlphanumComparator for SNAME and UNAME columns.  Start with SNAME sort.
//        rsSorter->setComparator(RouteOutputModel::SNAME_COLUMN, (Comparator*)new AlphanumComparator());
//        rsSorter->setComparator(RouteOutputModel::UNAME_COLUMN, (Comparator*)new AlphanumComparator());
//        RowSorterUtil::setSortOrder(rsSorter, RouteOutputModel::SNAME_COLUMN, SortOrder::ASCENDING);
        //routeSensorTable->setRowSorter(rsSorter);
        routeSensorTable->setRowSelectionAllowed(false);
        //routeSensorTable->setPreferredScrollableViewportSize(QSize(480, 80));
        routeSensorTable->resize(QSize(480, 80));
        JComboBox* stateSCombo = new JComboBox();
        stateSCombo->addItem(SET_TO_ACTIVE);
        stateSCombo->addItem(SET_TO_INACTIVE);
        stateSCombo->addItem(SET_TO_TOGGLE);
        TableColumnModel* routeSensorColumnModel = routeSensorTable->getColumnModel();
        TableColumn* includeColumnS = routeSensorColumnModel->
                getColumn(RouteOutputModel::INCLUDE_COLUMN);
        includeColumnS->setResizable(false);
        includeColumnS->setMinWidth(50);
        includeColumnS->setMaxWidth(60);
        TableColumn* sNameColumnS = routeSensorColumnModel->
                getColumn(RouteOutputModel::SNAME_COLUMN);
        sNameColumnS->setResizable(true);
        sNameColumnS->setMinWidth(75);
        sNameColumnS->setMaxWidth(95);
        TableColumn* uNameColumnS = routeSensorColumnModel->
                getColumn(RouteOutputModel::UNAME_COLUMN);
        uNameColumnS->setResizable(true);
        uNameColumnS->setMinWidth(210);
        uNameColumnS->setMaxWidth(260);
        TableColumn* stateColumnS = routeSensorColumnModel->
                getColumn(RouteOutputModel::STATE_COLUMN);
        stateColumnS->setCellEditor(new /*DefaultCellEditor(stateSCombo)*/JComboBoxEditor(stateSCombo->itemList()));
        stateColumnS->setResizable(false);
        stateColumnS->setMinWidth(90);
        stateColumnS->setMaxWidth(100);
        //_routeSensorScrollPane = new JScrollPane(routeSensorTable);
        //p2xs->layout()->addWidget(_routeSensorScrollPane, BorderLayout.CENTER);
        p2xs->layout()->addWidget(routeSensorTable);
        p2xs->setVisible(true);
        return p2xs;
    }
#endif
    /**
     * Initialize list of included turnout positions.
     */
    /*protected*/ void AbstractRouteAddEditFrame::initializeIncludedList() {
        _includedTurnoutList = QList<RouteTurnout*>();
        for (RouteTurnout* routeTurnout : _turnoutList) {
            if (routeTurnout->isIncluded()) {
                _includedTurnoutList.append(routeTurnout);
            }
        }
        _includedSensorList = QList<RouteSensor*>();
        for (RouteSensor* routeSensor : _sensorList) {
            if (routeSensor->isIncluded()) {
                _includedSensorList.append(routeSensor);
            }
        }
    }

    /*private*/ void AbstractRouteAddEditFrame::autoSystemName() {
        if (_autoSystemName->isChecked()) {
            _systemName->setEnabled(false);
            nameLabel->setEnabled(false);
        } else {
            _systemName->setEnabled(true);
            nameLabel->setEnabled(true);
        }
    }

    /*protected*/ void AbstractRouteAddEditFrame::showReminderMessage() {
        ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                showInfoMessage(tr("Reminder"),  // NOI18N
                        tr("<html>Remember to save your %1 information in your Configuration.<br>(choose Store &gt; Store Configuration... from the File menu)</html>").arg(tr("Route Table")),  // NOI18N
                        getClassName(), "remindSaveRoute"); // NOI18N
    }

    /*private*/ int AbstractRouteAddEditFrame::sensorModeFromBox(JComboBox* box) {
        QString mode =  box->getSelectedItem();
        return sensorModeFromString(mode);
    }

    int AbstractRouteAddEditFrame::sensorModeFromString(QString mode) {
        int result = StringUtil::getStateFromName(mode, sensorInputModeValues, sensorInputModes.toVector());

        if (result < 0) {
            log->warn(tr("unexpected mode string in sensorMode: %1").arg(mode));
            throw  IllegalArgumentException();
        }
        return result;
    }

    void AbstractRouteAddEditFrame::setSensorModeBox(int mode, JComboBox* box) {
        QString result = StringUtil::getNameFromState(mode, sensorInputModeValues, sensorInputModes);
        box->setSelectedItem(result);
    }

    /*private*/ int AbstractRouteAddEditFrame::turnoutModeFromBox(JComboBox* box) {
        QString mode =  box->getSelectedItem();
        int result = StringUtil::getStateFromName(mode, turnoutInputModeValues, turnoutInputModes.toVector());

        if (result < 0) {
            log->warn(tr("unexpected mode string in turnoutMode: %1").arg(mode));
            throw  IllegalArgumentException();
        }
        return result;
    }

    void AbstractRouteAddEditFrame::setTurnoutModeBox(int mode, JComboBox* box) {
        QString result = StringUtil::getNameFromState(mode, turnoutInputModeValues, turnoutInputModes);
        box->setSelectedItem(result);
    }

    /**
     * Set the Turnout information for adding or editing.
     *
     * @param g the route to add the turnout to
     */
    /*protected*/ void AbstractRouteAddEditFrame::setTurnoutInformation(Route* g) {
        for (RouteTurnout* t : _includedTurnoutList) {
            g->addOutputTurnout(t->getDisplayName(), t->getState());
        }
    }

    /**
     * Sets the Sensor information for adding or editing.
     *
     * @param g the route to add the sensor to
     */
    /*protected*/ void AbstractRouteAddEditFrame::setSensorInformation(Route* g) {
        for (RouteSensor* s : _includedSensorList) {
            g->addOutputSensor(s->getDisplayName(), s->getState());
        }
    }

    /**
     * Set the Sensor, Turnout, and delay control information for adding or editing.
     *
     * @param g the route to configure
     */
    /*protected*/ void AbstractRouteAddEditFrame::setControlInformation(Route* g) {
        // Get sensor control information if any
        Sensor* sensor = (Sensor*)sensor1->getSelectedItem();
        if (sensor != nullptr) {
            if ((!g->addSensorToRoute(sensor->getSystemName(), sensorModeFromBox(sensor1mode)))) {
                log->error(tr("Unexpected failure to add Sensor '%1' to route '%2'.").arg(sensor->getSystemName()).arg(g->getSystemName()));
            }
        }

        if (sensor2->getSelectedItem() != nullptr) {
            if ((!g->addSensorToRoute(sensor2->getSelectedItemDisplayName(), sensorModeFromBox(sensor2mode)))) {
                log->error(tr("Unexpected failure to add Sensor '%1' to Route '%2'.").arg(sensor2->getSelectedItemDisplayName()).arg(g->getSystemName()));
            }
        }

        if (sensor3->getSelectedItem() != nullptr) {
            if ((!g->addSensorToRoute(sensor3->getSelectedItemDisplayName(), sensorModeFromBox(sensor3mode)))) {
                log->error(tr("Unexpected failure to add Sensor '%1' to Route '%2'.").arg(sensor3->getSelectedItemDisplayName()).arg(g->getSystemName()));
            }
        }

        //Turnouts Aligned sensor
        if (turnoutsAlignedSensor->getSelectedItem() != nullptr) {
            g->setTurnoutsAlignedSensor(turnoutsAlignedSensor->getSelectedItemDisplayName());
        } else {
            g->setTurnoutsAlignedSensor("");
        }

        // Set turnout information if there is any
        if (cTurnout->getSelectedItem() != nullptr) {
            g->setControlTurnout(cTurnout->getSelectedItemDisplayName());
            // set up Control Turnout state
            g->setControlTurnoutState(turnoutModeFromBox(cTurnoutStateBox));
        } else {
            // No Control Turnout was entered
            g->setControlTurnout("");
        }
        // set route specific Delay information, see jmri.implementation.DefaultRoute#SetRouteThread()
        int addDelay = timeDelay->value(); // from a JSpinner with 0 set as minimum
        g->setRouteCommandDelay(addDelay);

        // Set Lock Turnout information if there is any
        if (cLockTurnout->getSelectedItem() != nullptr) {
            g->setLockControlTurnout(cLockTurnout->getSelectedItemDisplayName());
            // set up control turnout state
            g->setLockControlTurnoutState(turnoutModeFromBox(cLockTurnoutStateBox));
        } else {
            // No Lock Turnout was entered
            g->setLockControlTurnout("");
        }
    }

    /**
     * Set the sound file.
     */
    /*private*/ void AbstractRouteAddEditFrame::setSoundPressed() {
        if (soundChooser == nullptr) {
            soundChooser = new JFileChooser(FileUtil::getUserFilesPath());
//            soundChooser->setFileFilter(new NoArchiveFileFilter());
        }
//        soundChooser->rescanCurrentDirectory();
        int retVal = soundChooser->showOpenDialog(nullptr);
        // handle selection or cancel
        if (retVal == JFileChooser::APPROVE_OPTION) {
            try {
                soundFile->setText(soundChooser->getSelectedFile()->getCanonicalPath());
            } catch (IOException e) {
                log->error("exception setting sound file: ", e);
            }
        }
    }

    /**
     * Set the script file.
     */
    /*private*/ void AbstractRouteAddEditFrame::setScriptPressed() {
        if (scriptChooser == nullptr) {
            scriptChooser = XmlFile::userFileChooser("Python script files", "py");
        }
//        scriptChooser->rescanCurrentDirectory();
        int retVal = scriptChooser->showOpenDialog(nullptr);
        // handle selection or cancel
        if (retVal == JFileChooser::APPROVE_OPTION) {
            try {
                scriptFile->setText(scriptChooser->getSelectedFile()->getCanonicalPath());
            } catch (IOException e) {
                log->error("exception setting script file: ", e);
            }
        }
    }


    /*protected*/ void AbstractRouteAddEditFrame::finishUpdate() {
#if 1
        // move to show all Turnouts if not there
        cancelIncludedOnly();
        // Provide feedback to user
        // switch GUI back to selection mode
        //status2->setText(tr("To edit an existing Route, enter its System Name, then click [%1].").arg(tr("ButtonEdit")));
        status2->setVisible(true);
        autoSystemName();
        setTitle(tr("TitleAddRoute"));
        clearPage();
        // reactivate the Route
        routeDirty = true;
        // get out of edit mode
        editMode = false;
        if (curRoute != nullptr) {
            curRoute->activateRoute();
        }
#endif
    }

    /*private*/ void AbstractRouteAddEditFrame::clearPage() {
        _systemName->setText("");
        _userName->setText("");
        sensor1->setSelectedItem(nullptr);
        sensor2->setSelectedItem(nullptr);
        sensor3->setSelectedItem(nullptr);
        cTurnout->setSelectedItem(nullptr);
        cLockTurnout->setSelectedItem(nullptr);
        turnoutsAlignedSensor->setSelectedItem(nullptr);
        soundFile->setText("");
        scriptFile->setText("");
        for (int i = _turnoutList.size() - 1; i >= 0; i--) {
            _turnoutList.at(i)->setIncluded(false);
        }
        for (int i = _sensorList.size() - 1; i >= 0; i--) {
            _sensorList.at(i)->setIncluded(false);
        }
    }


    /**
     * Cancel included Turnouts only option
     */
    /*private*/ void AbstractRouteAddEditFrame::cancelIncludedOnly() {
        if (!showAll) {
            allButton->click();
        }
    }

    /*private*/ QString AbstractRouteAddEditFrame::getClassName() {
        return /*this.getClass().getName()*/QString("jmri.jmrit.beantable.") + metaObject()->className();
    }

    QList<RouteTurnout*> AbstractRouteAddEditFrame::get_turnoutList() {
        return _turnoutList;
    }

    QList<RouteTurnout*> AbstractRouteAddEditFrame::get_includedTurnoutList() {
        return _includedTurnoutList;
    }

    QList<RouteSensor*> AbstractRouteAddEditFrame::get_sensorList() {
        return _sensorList;
    }

    QList<RouteSensor*> AbstractRouteAddEditFrame::get_includedSensorList() {
        return _includedSensorList;
    }

    /*public*/ bool AbstractRouteAddEditFrame::isShowAll() {
        return showAll;
    }

    /**
     * Cancels edit mode
     */
    /*protected*/ void AbstractRouteAddEditFrame::cancelEdit() {
        if (editMode) {
            status1->setText(tr("To create a new Route, enter its definition, then click [#1].").arg(tr("Create"))); // I18N to include original button name in help string
            //status2->setText(tr("RouteAddStatusInitial2", tr("ButtonEdit")));
            finishUpdate();
            // get out of edit mode
            editMode = false;
            curRoute = nullptr;
        }
        closeFrame();
    }

    /**
     * Respond to the Update button - update to Route Table.
     *
     * @param newRoute true if a new route; false otherwise
     */
    /*protected*/ void AbstractRouteAddEditFrame::updatePressed(bool newRoute) {
        // Check if the User Name has been changed
        QString uName = _userName->text();
        Route* g = checkNamesOK();
        if (g == nullptr) {
            return;
        }
        // User Name is unique, change it
        g->setUserName(uName);
        // clear the current Turnout information for this Route
        g->clearOutputTurnouts();
        g->clearOutputSensors();
        // clear the current Sensor information for this Route
        g->clearRouteSensors();
        // add those indicated in the panel
        initializeIncludedList();
        setTurnoutInformation(g);
        setSensorInformation(g);
        // set the current values of the file names
        g->setOutputScriptName(scriptFile->text());
        g->setOutputSoundName(soundFile->text());
        // add Control Sensors and a Control Turnout if entered in the panel
        setControlInformation(g);
        curRoute = g;
        finishUpdate();
        status1->setForeground(Qt::gray);
        status1->setText((newRoute ? tr("New Route created") :
                tr("Route updated")) + ": \"" + uName + "\" (" + _includedTurnoutList.size() + " "
                + tr("Turnouts") + ", " + _includedSensorList.size() + " " + tr("Sensors") + ")");
    }

    /**
     * Check name and return a new or existing Route object with the name as entered in the _systemName field on the
     * addFrame pane.
     *
     * @return the new/updated Route object
     */
    /*private*/ Route* AbstractRouteAddEditFrame::checkNamesOK() {
        // Get system name and user name
        QString sName = _systemName->text();
        QString uName = _userName->text();
        Route* g;
        if (_autoSystemName->isChecked() && !editMode) {
            log->debug("checkNamesOK new autogroup");
            // create new Route with auto system name
            g = routeManager->newRoute(uName);
        } else {
            if (sName.length() == 0) {
                status1->setText(tr("Enter a System Name and (optional) User Name."));
                status1->setForeground(Qt::red);
                return nullptr;
            }
            try {
                sName = routeManager->makeSystemName(sName);
                g = routeManager->provideRoute(sName, uName);
            } catch (IllegalArgumentException ex) {
                g = nullptr; // for later check:
            }
        }
        if (g == nullptr) {
            // should never get here
            log->error(tr("Unknown failure to create Route with System Name: %1").arg(sName)); // NOI18N
        } else {
            g->deActivateRoute();
        }
        return g;
    }

    /*protected*/ void AbstractRouteAddEditFrame::closeFrame(){
        // remind to save, if Route was created or edited
        if (routeDirty) {
            showReminderMessage();
            routeDirty = false;
        }
        // hide addFrame
        setVisible(false);

        // if in Edit, cancel edit mode
        if (editMode) {
            cancelEdit();
        }

        _routeSensorModel->dispose();
        _routeTurnoutModel->dispose();

        this->dispose();
    }

