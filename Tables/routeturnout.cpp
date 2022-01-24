#include "routeturnout.h"
#include "abstractrouteaddeditframe.h"

/**
 * Route Table RouteTurnout Elements.
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
//class RouteTurnout extends RouteElement {

    RouteTurnout::RouteTurnout(QString sysName, QString userName, QObject* parent) : RouteElement(sysName, userName, parent){
        //super(sysName, userName);
    }

    //@Override
    QString RouteTurnout::getSetToState() {
        switch (_setToState) {
            case Turnout::CLOSED:
                return AbstractRouteAddEditFrame::SET_TO_CLOSED;
            case Turnout::THROWN:
                return AbstractRouteAddEditFrame::SET_TO_THROWN;
            case Route::TOGGLE:
                return AbstractRouteAddEditFrame::SET_TO_TOGGLE;
            default:
                // fall through
                break;
        }
        return "";
    }

    //@Override
    void RouteTurnout::setSetToState(QString state) {
        if (AbstractRouteAddEditFrame::SET_TO_CLOSED == (state)) {
            _setToState = Turnout::CLOSED;
        } else if (AbstractRouteAddEditFrame::SET_TO_THROWN == (state)) {
            _setToState = Turnout::THROWN;
        } else if (AbstractRouteAddEditFrame::SET_TO_TOGGLE == (state)) {
            _setToState = Route::TOGGLE;
        }
    }
