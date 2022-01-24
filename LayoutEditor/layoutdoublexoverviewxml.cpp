#include "layoutdoublexoverviewxml.h"

/**
 * This module handles configuration for display.LayoutTurnoutView objects for a
 * LayoutEditor.
 *
 * @author Bob Jacobsen Copyright (c) 2020
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 */
// /*public*/ class LayoutDoubleXOverViewXml extends LayoutXOverViewXml {

//    static final EnumIO<LayoutTurnout.LinkType> linkEnumMap = new EnumIoOrdinals<>(LayoutTurnout.LinkType.class);
//    static final EnumIO<LayoutTurnout.TurnoutType> tTypeEnumMap = new EnumIoOrdinals<>(LayoutTurnout.TurnoutType.class);

    /*public*/ LayoutDoubleXOverViewXml::LayoutDoubleXOverViewXml(QObject* parent) : LayoutXOverViewXml(parent){
    }

    //@Override
    /*protected*/ void LayoutDoubleXOverViewXml::addClass(QDomElement element) {
        element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutDoubleXOverXml");
    }
