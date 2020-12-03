#include "internalmetermanagerxml.h"

/**
 * Provides load and store functionality for configuring
 * InternalMeterManagers.
 * <p>
 * Uses the store method from the abstract base class, but provides a load
 * method here.
 *
 * @author Bob Jacobsen      Copyright (C) 2006
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
// /*public*/ class InternalMeterManagerXml extends jmri.managers.configurexml.AbstractMeterManagerXml {

    /*public*/ InternalMeterManagerXml::InternalMeterManagerXml(QObject *parent) : AbstractMeterManagerXml(parent){
        //super();
    }

    //@Override
    /*public*/ void InternalMeterManagerXml::setStoreElementClass(QDomElement meters) {
        meters.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrix.internal.configurexml.InternalMeterManagerXml");
    }
