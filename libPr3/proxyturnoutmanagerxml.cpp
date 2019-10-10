#include "proxyturnoutmanagerxml.h"

/**
 * Handle XML persistance of ProxyTurnoutManager
 * <p>
 * This class is named as being the persistant form of the ProxyTurnoutManager
 * class, but there's no object of that form created or used.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 */
// /*public*/ class ProxyTurnoutManagerXml extends AbstractXmlAdapter {

    /*public*/ ProxyTurnoutManagerXml::ProxyTurnoutManagerXml(QObject *parent) :AbstractXmlAdapter(parent) {
    }

    /**
     * Default implementation for storing the static contents of a
     * PositionableLabel
     *
     * @param o Object to store, of type PositionableLabel
     * @return QDomElementcontaining the complete info
     */
    //@Override
    /*public*/ QDomElement ProxyTurnoutManagerXml::store(QObject* /*o*/) {
        return QDomElement();
    }

    //@Override
    /*public*/ bool ProxyTurnoutManagerXml::load(QDomElement /*shared*/, QDomElement /*perNode*/) {
        return true;
    }

    /**
     * Doesn't need to do anything, shouldn't get invoked
     *
     * @param QDomElementTop level QDomElementto unpack.
     * @param o       PanelEditor as an Object
     */
    //@Override
    /*public*/ void ProxyTurnoutManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    }
