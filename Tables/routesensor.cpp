#include "routesensor.h"
#include "loggerfactory.h"
/**
 * Route Table RouteSensor Elements.
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
//class RouteSensor extends RouteElement {
    /*private*/ /*static*/ /*final*/ QString RouteSensor::SET_TO_ACTIVE =  tr("Set") + " " +  tr("SensorStateActive");
    /*private*/ /*static*/ /*final*/ QString RouteSensor::SET_TO_INACTIVE =  tr("Set") + " " +  tr("SensorStateInactive");

    /*private*/ /*static*/ /*final*/ QString RouteSensor::SET_TO_TOGGLE =  tr("Set") + " " +  tr("Toggle");

    RouteSensor::RouteSensor(QString sysName, QString userName, QObject *parent) :  RouteElement(sysName, userName, parent) {
        //super(sysName, userName);
    }

    //@Override
    QString RouteSensor::getSetToState() {
        switch (_setToState) {
            case Sensor::INACTIVE:
                return SET_TO_INACTIVE;
            case Sensor::ACTIVE:
                return SET_TO_ACTIVE;
            case Route::TOGGLE:
                return SET_TO_TOGGLE;
            default:
                log->warn(tr("Unhandled route state: %1").arg(_setToState));
                break;
        }
        return "";
    }

    //@Override
    void RouteSensor::setSetToState(QString state) {
        if (SET_TO_INACTIVE == (state)) {
            _setToState = Sensor::INACTIVE;
        } else if (SET_TO_ACTIVE == (state)) {
            _setToState = Sensor::ACTIVE;
        } else if (SET_TO_TOGGLE == (state)) {
            _setToState = Route::TOGGLE;
        }
    }

    /*private*/ /*static*/ /*final*/ Logger* RouteSensor::log = LoggerFactory::getLogger("RouteSensor");
