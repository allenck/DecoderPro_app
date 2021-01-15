#include "routetableaction.h"
#include "instancemanager.h"
#include "routetabledatamodel.h"
#include "routeaddframe.h"
#include "userpreferencesmanager.h"

/**
 * Swing action to create and register a Route Table.
 *
 * Based in part on {@link SignalHeadTableAction} by Bob Jacobsen
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Simon Reader Copyright (C) 2008
 * @author Pete Cressman Copyright (C) 2009
 * @author Egbert Broerse Copyright (C) 2016
 * @author Paul Bender Colyright (C) 2020
 */
// /*public*/ class RouteTableAction extends AbstractTableAction<Route> {

    /**
     * Create an action with a specific title.
     * <p>
     * Note that the argument is the Action title, not the title of the
     * resulting frame. Perhaps this should be changed?
     *
     * @param s title of the action
     */
    /*public*/ RouteTableAction::RouteTableAction(QString s, QObject* parent) : AbstractTableAction(s, parent){
        //super(s);
        // disable ourself if there is no primary Route manager available
        if (InstanceManager::getNullableDefault("RouteManager") == nullptr) {
            setEnabled(false);
        }
    }

    /*public*/ RouteTableAction::RouteTableAction(QObject* parent) : AbstractTableAction(tr("Route Table"), parent){
        //this(Bundle.getMessage("TitleRouteTable"));
        if (InstanceManager::getNullableDefault("RouteManager") == nullptr) {
           setEnabled(false);
        }
    }

    /**
     * Create the JTable DataModel, along with the changes for the specific case
     * of Routes.
     */
    //@Override
    /*protected*/ void RouteTableAction::createModel() {
        m = new RouteTableDataModel();
    }

    //@Override
    /*protected*/ void RouteTableAction::setTitle() {
        f->setTitle(tr("Route Table"));
    }

    //@Override
    /*protected*/ QString RouteTableAction::helpTarget() {
        return "package.jmri.jmrit.beantable.RouteTable";
    }


    //@Override
    /*protected*/ void RouteTableAction::addPressed(/*ActionEvent e*/) {

        /*final*/ JmriJFrame* addFrame = new RouteAddFrame();
        // display the window
        addFrame->setVisible(true);
    }

    //@Override
    /*public*/ void RouteTableAction::setMessagePreferencesDetails() {
        ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))
                ->setPreferenceItemDetails(getClassName(), "remindSaveRoute", tr("Hide Save Message reminder"));
        AbstractTableAction::setMessagePreferencesDetails();
    }

    //@Override
    /*protected*/ QString RouteTableAction::getClassName() {
        return /*RouteTableAction.class.getName()*/"jmri.jmrit.beantable.RouteTableAction.";
    }

    //@Override
    /*public*/ QString RouteTableAction::getClassDescription() {
        return tr("Route Table");
    }
