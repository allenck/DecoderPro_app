#include "routeaddframe.h"
#include "jbutton.h"
#include "routesensormodel.h"
#include "routeturnoutmodel.h"
#include "userpreferencesmanager.h"
#include "routemanager.h"
/**
 * Add frame for the Route Table.
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
///*public*/ class RouteAddFrame extends AbstractRouteAddEditFrame {


/*public*/ RouteAddFrame::RouteAddFrame(QWidget* parent) : AbstractRouteAddEditFrame(tr("Add"), false, true, parent) {
    //this(Bundle.getMessage("TitleAddRoute"));
    initComponents();
}

/*public*/ RouteAddFrame::RouteAddFrame(QString name, QWidget* parent) : AbstractRouteAddEditFrame(name, false, true, parent) {
    //this(name,false,true);
    initComponents();
}

/*public*/ RouteAddFrame::RouteAddFrame(QString name, bool saveSize, bool savePosition, QWidget* parent) : AbstractRouteAddEditFrame(name, false, true, parent)  {
    //super(name, saveSize, savePosition);
    initComponents();
}

//@Override
/*protected*/ JPanel* RouteAddFrame::getButtonPanel() {
    /*final*/ JButton* createButton = new JButton(tr("Create"));
    /*final*/ JButton* editButton = new JButton(tr("Edit"));
    /*final*/ JButton* cancelButton = new JButton(tr("Cancel"));
    /*final*/ JButton* updateButton = new JButton(tr("Update"));
    // add Buttons panel
    JPanel* pb = new JPanel();
    pb->setLayout(new FlowLayout(/*FlowLayout.TRAILING*/));
    // Cancel (Add) button
    pb->layout()->addWidget(cancelButton);

    //cancelButton.addActionListener(this::cancelAddPressed);
    connect(cancelButton, &JButton::clicked, [=]{cancelAddPressed();});
    // Create button
    pb->layout()->addWidget(createButton);
    //createButton.addActionListener(this::createPressed);
    connect(createButton, &JButton::clicked, [=]{createPressed();});
    createButton->setToolTip(tr("Add a new Route using the data entered above"));

    // Show the initial buttons, and hide the others
    cancelButton->setVisible(true); // show CancelAdd button
    updateButton->setVisible(true);
    editButton->setVisible(true);
    createButton->setVisible(true);

    return pb;
}

/**
 * Respond to the CancelAdd button.
 *
 * @param e the action event
 */
/*private*/ void RouteAddFrame::cancelAddPressed(/*ActionEvent e*/) {
    cancelAdd();
}

/**
 * Cancel Add mode.
 */
/*private*/ void RouteAddFrame::cancelAdd() {
    if (routeDirty) {
        showReminderMessage();
    }
    curRoute = nullptr;
    finishUpdate();
    status1->setText(tr("To create a new Route, enter its definition, then click [%1].").arg(tr("Create"))); // I18N to include original button name in help string
    //status2.setText(tr("RouteAddStatusInitial2", tr("ButtonEdit")));
    routeDirty = false;
    // hide addFrame
    setVisible(false);
    _routeSensorModel->dispose();
    _routeTurnoutModel->dispose();
    closeFrame();
}

/**
 * Respond to the Create button.
 *
 * @param e the action event
 */
/*private*/ void RouteAddFrame::createPressed(/*ActionEvent e*/) {
    if (!_autoSystemName->isChecked()) {
        if (!checkNewNamesOK()) {
            return;
        }
    }
    updatePressed(true); // close pane after creating
    //status2.setText(tr("RouteAddStatusInitial2", tr("ButtonEdit")));
    pref->setSimplePreferenceState(systemNameAuto, _autoSystemName->isChecked());
    // activate the route
    if (curRoute != nullptr) {
        curRoute->activateRoute();
    }
    closeFrame();
}

/**
 * Check name for a new Route object using the _systemName field on the addFrame pane.
 *
 * @return whether name entered is allowed
 */
/*private*/ bool RouteAddFrame::checkNewNamesOK() {
    // Get system name and user name from Add Route pane
    QString sName = _systemName->text();
    QString uName = _userName->text();
    if (sName.length() == 0) {
        status1->setText(tr("Enter a System Name and (optional) User Name."));
        status1->setForeground(Qt::red);
        return false;
    }
    Route* g;
    // check if a Route with the same user name exists
    if (uName != ("")) {
        g = (Route*)routeManager->getByUserName(uName);
        if (g != nullptr) {
            // Route already exists
            status1->setText(tr("Error: an element with this User Name already exists."));
            return false;
        }
    }
    // check if a Route with this system name already exists
    sName = routeManager->makeSystemName(sName);
    g = (Route*)routeManager->getBySystemName(sName);
    if (g != nullptr) {
        // Route already exists
        status1->setText(tr("Error: an element with this System Name already exists."));
        return false;
    }
    return true;
}

