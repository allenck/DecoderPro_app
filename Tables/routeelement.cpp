#include "routeelement.h"


/**
 * Base class Route Table RouteElements.
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
//abstract class RouteElement {


    RouteElement::RouteElement(QString sysName, QString userName, QObject* parent) {
        _sysName = sysName;
        _userName = userName;
        _included = false;
        _setToState = Sensor::INACTIVE;
    }

    QString RouteElement::getSysName() {
        return _sysName;
    }

    QString RouteElement::getUserName() {
        return _userName;
    }

    bool RouteElement::isIncluded() {
        return _included;
    }

    QString RouteElement::getDisplayName() {
        QString name = getUserName();
        if (name != "" && name.length() > 0) {
            return name;
        } else {
            return getSysName();
        }

    }

    void RouteElement::setIncluded(bool include) {
        _included = include;
    }

//    abstract String getSetToState();

//    abstract void setSetToState(String state);

    int RouteElement::getState() {
        return _setToState;
    }

    void RouteElement::setState(int state) {
        _setToState = state;
    }
