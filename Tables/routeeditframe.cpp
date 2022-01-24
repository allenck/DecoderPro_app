#include "routeeditframe.h"
#include "instancemanager.h"
#include "routemanager.h"
#include "route.h"
#include "jbutton.h"
#include "routeturnoutmodel.h"
#include "routesensormodel.h"
#include <QScrollBar>
#include "routeexporttologix.h"
#include "jtable.h"
/**
 * Edit frame for the Route Table.
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
///*public*/ class RouteEditFrame extends AbstractRouteAddEditFrame {


    /*public*/ RouteEditFrame::RouteEditFrame(QString systemName, QWidget* parent)
      : AbstractRouteAddEditFrame(tr("Edit Route"), false, true, parent){
        //this(tr("TitleEditRoute"), systemName);
        this->systemName = systemName;
        initComponents();}

    /*public*/ RouteEditFrame::RouteEditFrame(QString name, QString systemName, QWidget* parent)
      : AbstractRouteAddEditFrame(name, false, true, parent)
    {
        //this(name,false,true, systemName);
        this->systemName = systemName;
        initComponents();
    }

    /*public*/ RouteEditFrame::RouteEditFrame(QString name, bool saveSize, bool savePosition, QString systemName, QWidget* parent)
      : AbstractRouteAddEditFrame(name, saveSize, savePosition, parent)
    {
        //super(name, saveSize, savePosition);
        this->systemName = systemName;
        initComponents();
    }

    //@Override
    /*public*/ void RouteEditFrame::initComponents() {
        AbstractRouteAddEditFrame::initComponents();
        resize(300, 200);
        _systemName->setText(systemName);
        // identify the Route with this name if it already exists
        QString sName = _systemName->text();
        Route* g = (Route*)((RouteManager*)InstanceManager::getDefault("RouteManager"))->getBySystemName(sName);
        if (g == nullptr) {
            sName = _userName->text();
            g = (Route*)((RouteManager*)InstanceManager::getDefault("RouteManager"))->getByUserName(sName);
            if (g == nullptr) {
                // Route does not exist, so cannot be edited
                status1->setText(tr("Route with the entered System Name or User Name was not found."));
                return;
            }
        }
        // Route was found, make its system name not changeable
        curRoute = g;
        _systemName->setVisible(true);
        _systemName->setText(sName);
        _systemName->setEnabled(false);
        nameLabel->setEnabled(true);
        _autoSystemName->setVisible(false);
        // deactivate this Route
        curRoute->deActivateRoute();
        // get information for this route
        _userName->setText(((NamedBean*)g->self())->getUserName());
        // set up Turnout list for this route
        int setRow = 0;
        for (int i = _turnoutList.size() - 1; i >= 0; i--) {
            RouteTurnout* turnout = _turnoutList.at(i);
            QString tSysName = turnout->getSysName();
            if (g->isOutputTurnoutIncluded(tSysName)) {
                turnout->setIncluded(true);
                turnout->setState(g->getOutputTurnoutSetState(tSysName));
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
#if 1
        _routeTurnoutModel->table()->verticalScrollBar()->setValue(setRow * ROW_HEIGHT);
        _routeTurnoutModel->fireTableDataChanged();
        // set up Sensor list for this route
        for (int i = _sensorList.size() - 1; i >= 0; i--) {
            RouteSensor* sensor = _sensorList.at(i);
            QString tSysName = sensor->getSysName();
            if (g->isOutputSensorIncluded(tSysName)) {
                sensor->setIncluded(true);
                sensor->setState(g->getOutputSensorSetState(tSysName));
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
        _routeSensorModel->table()->verticalScrollBar()->setValue(setRow * ROW_HEIGHT);
        _routeSensorModel->fireTableDataChanged();
        // get Sound and  Script file names
        scriptFile->setText(g->getOutputScriptName());
        soundFile->setText(g->getOutputSoundName());

        // get Turnout Aligned sensor
        turnoutsAlignedSensor->setSelectedItem(g->getTurnoutsAlgdSensor());

        // set up Sensors if there are any
        QVector<Sensor*> temNames = QVector<Sensor*>(Route::MAX_CONTROL_SENSORS);
        QVector<int> temModes = QVector<int>(Route::MAX_CONTROL_SENSORS);
        for (int k = 0; k < Route::MAX_CONTROL_SENSORS; k++) {
            temNames[k] = g->getRouteSensor(k);
            temModes[k] = g->getRouteSensorMode(k);
        }
        sensor1->setSelectedItem(temNames[0]);
        setSensorModeBox(temModes[0], sensor1mode);

        sensor2->setSelectedItem(temNames[1]);
        setSensorModeBox(temModes[1], sensor2mode);

        sensor3->setSelectedItem(temNames[2]);
        setSensorModeBox(temModes[2], sensor3mode);

        // set up Control Turnout if there is one
        cTurnout->setSelectedItem(g->getCtlTurnout());

        setTurnoutModeBox(g->getControlTurnoutState(), cTurnoutStateBox);

        // set up Lock Control Turnout if there is one
        cLockTurnout->setSelectedItem(g->getLockCtlTurnout());

        setTurnoutModeBox(g->getLockControlTurnoutState(), cLockTurnoutStateBox);

        // set up additional route specific Delay
        timeDelay->setValue(g->getRouteCommandDelay());
        // begin with showing all Turnouts
        // set up buttons and notes
        status1->setText(tr("To change this Route, make changes above, then click [%1].").arg(tr("Update")));
        status2->setText(tr("To leave Edit mode without changing this Route, click [%1].").arg(tr("Cancel %1").arg(tr("Edit"))));
        status2->setVisible(true);
        setTitle(tr("TitleEditRoute"));
        editMode = true;
#endif
    }

    //@Override
    /*protected*/ JPanel* RouteEditFrame::getButtonPanel() {
        /*final*/ JButton* cancelEditButton = new JButton(tr("Cancel %1").arg(tr("Edit"))); // I18N for word sequence "Cancel Edit"
        /*final*/ JButton* deleteButton = new JButton(tr("Delete") + " " + tr("Route")); // I18N "Delete Route"
        /*final*/ JButton* updateButton = new JButton(tr("Update"));
        /*final*/ JButton* exportButton = new JButton(tr("Export"));
        // add Buttons panel
        JPanel* pb = new JPanel();
        pb->setLayout(new FlowLayout());//FlowLayout.TRAILING));
        // CancelEdit button
        pb->layout()->addWidget(cancelEditButton);
        //cancelEditButton.addActionListener(this::cancelPressed);
        connect(cancelEditButton, &JButton::clicked, [=]{cancelPressed();});
        cancelEditButton->setToolTip(tr("Leave Edit mode without changing the Route"));
        // Delete Route button
        pb->layout()->addWidget(deleteButton);
        //deleteButton.addActionListener(this::deletePressed);
        connect(deleteButton, &JButton::clicked, [=]{deletePressed();});
        deleteButton->setToolTip(tr("Delete the Route with this System Name"));
        // Update Route button
        pb->layout()->addWidget(updateButton);
        //updateButton.addActionListener((ActionEvent e1) -> updatePressed(false));
        connect(updateButton, &JButton::clicked, [=]{updatePressed(false);});
        updateButton->setToolTip(tr("Change this Route and leave Edit mode"));
        // Export button
        pb->layout()->addWidget(exportButton);
        //exportButton.addActionListener(this::exportButtonPressed);
        connect(exportButton, &JButton::clicked, [=]{exportButtonPressed();});
        exportButton->setToolTip(tr("Export Route to Logix Conditionals for further enhancement. The Route will be deleted from the table."));

        // Show the initial buttons, and hide the others
        deleteButton->setVisible(true);
        cancelEditButton->setVisible(true);
        updateButton->setVisible(true);
        exportButton->setVisible(true);
        return pb;
    }

    /**
     * Respond to the export button.
     *
     * @param e the action event
     */
    /*private*/ void RouteEditFrame::exportButtonPressed(/*ActionEvent e*/){
        (new RouteExportToLogix(_systemName->text()))->_export();
        status1->setText(tr("Route")
                + "\"" + _systemName->text() + "\" " +
                tr("exported to Logix") + " ("
                + QString::number(get_includedTurnoutList().size()) +
                tr("Turnouts") + ", " +
                get_includedSensorList().size() + " " + tr("Sensors") + ")");
        finishUpdate();
        closeFrame();
    }

    /**
     * Respond to the CancelEdit button.
     *
     * @param e the action event
     */
    /*private*/ void RouteEditFrame::cancelPressed(/*ActionEvent e*/) {
        cancelEdit();
    }

    /**
     * Respond to the Delete button.
     *
     * @param e the action event
     */
    /*private*/ void RouteEditFrame::deletePressed(/*ActionEvent e*/) {
        // route is already deactivated, just delete it
        routeManager->deleteRoute(curRoute);

        curRoute = nullptr;
        finishUpdate();
        closeFrame();
    }

