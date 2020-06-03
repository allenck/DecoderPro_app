#include "portalicon.h"
#include "portal.h"
#include "instancemanager.h"
#include "oblockmanager.h"
#include "oblock.h"
#include "namedicon.h"
#include "positionableicon.h"
#include "controlpaneleditor.h"
#include "circuitbuilder.h"

//PortalIcon::PortalIcon()
//{
//}
/**
 * @author PeteCressman Copyright (C) 2011
 * @version $Revision: 17977 $
 */

///*public*/ class PortalIcon extends jmri.jmrit.display.PositionableIcon {
/*public*/ /*static*/ /*final*/ QString PortalIcon::HIDDEN = tr("Hidden");
/*public*/ /*static*/ /*final*/ QString PortalIcon::VISIBLE = tr("Visible");
/*public*/ /*static*/ /*final*/ QString PortalIcon::PATH = tr("Path Editing");
/*public*/ /*static*/ /*final*/ QString PortalIcon::TO_ARROW = tr("Exit Arrow");
/*public*/ /*static*/ /*final*/ QString PortalIcon::FROM_ARROW = tr("Entry Arrow");



/*public*/ PortalIcon::PortalIcon(Editor* editor, Portal* portal, QObject* parent) : PositionableIcon("", editor, (Positionable*)parent)
{
 // super ctor call to make sure this is an icon label
 //super(editor);
 _portal = portal;
 _regular = true;	// true when TO_ARROW shows entry into ToBlock
 _hide = false;	// true when arrow should NOT show entry into ToBlock

 initMap();
}

// Config file ctor
/*public*/ PortalIcon::PortalIcon(QString blockName, QString portalName, Editor* editor, QObject* parent) : PositionableIcon("", editor, (Positionable*)parent) {
    // super ctor call to make sure this is an icon label
    //super(editor);
    OBlock* block = ((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->getOBlock(blockName);
    _portal = block->getPortalByName(portalName);
    initMap();
}


/*private*/ void PortalIcon::initMap()
{
 ControlPanelEditor* ed = (ControlPanelEditor*) _editor;
 int deg = getDegrees();
 _iconMap = PositionableIcon::cloneMap(ed->getPortalIconMap(), this);
 if (!_regular) {
     NamedIcon* a = _iconMap->value(TO_ARROW);
     NamedIcon* b = _iconMap->value(FROM_ARROW);
     _iconMap->insert(FROM_ARROW, a);
     _iconMap->insert(TO_ARROW, b);
 }
 setScale(getScale());
 rotate(deg);
 PositionableIcon::setIcon(_iconMap->value(HIDDEN));
}

/**
 * Called from EditPortalDirection frame in CircuitBuilder
 */
/*protected*/ void PortalIcon::setIcon(QString name, NamedIcon* ic)
{
    if (log->isDebugEnabled()) {
        log->debug("Icon " + getPortal()->getName() + " put icon key= \"" + name + "\" icon= " + ic->getName());
    }
    NamedIcon* icon = cloneIcon(ic, this);
    icon->scale(getScale(), this);
    icon->rotate(getDegrees(), this);
    _iconMap->insert(name, icon);
}

/**
 * Called from EditPortalDirection frame in CircuitBuilder
 */
/*public*/ void PortalIcon::setArrowOrientatuon(bool set)
{
    if (log->isDebugEnabled()) {
     log->debug("Icon " + getPortal()->getName() + " setArrowOrientatuon regular=" + (set?"true":"false") + " from " + (_regular?"true":"false"));
    }
    _regular = set;
}

/**
 * Called from EditPortalDirection frame in CircuitBuilder
 */
/*public*/ void PortalIcon::setHideArrows(bool set) {
    if (log->isDebugEnabled()) {
     log->debug("Icon " + getPortal()->getName() + " setHideArrows hide=" + (set?"true":"false") + " from " + (_hide?"true":"false"));
    }
    _hide = set;
}

/*public*/ bool PortalIcon::getArrowSwitch() {
    return _regular;
}

/*public*/ bool PortalIcon::getArrowHide() {
    return _hide;
}

/*public*/ Portal* PortalIcon::getPortal() {
    return _portal;
}
/*public*/ void PortalIcon::setPortal(Portal* portal) {
    _portal = portal;
}

/*public*/ void PortalIcon::setStatus(QString status)
{
//        if (log.isDebugEnabled()) log.debug("Icon "+getPortal().getName()+" setStatus("+status+") regular="+_regular+" icon= "+_iconMap.get(status));
        PositionableLabel::setIcon(_iconMap->value(status));
        _status = status;
        updateSize();
        repaint();
}

/*public*/ QString PortalIcon::getStatus() {
    return _status;
}

/* currently Portals do not have an instance manager - !!!todo? */
/*public*/ NamedBean* PortalIcon::getNamedBean()
{
    return (NamedBean*)getPortal();
}

/*public*/ void PortalIcon::displayState(int state) {
    switch (state) {
        case 0x02:
            if (_hide) {
                setStatus(HIDDEN);
            } else {
                setStatus(TO_ARROW);
            }
            break;
        case 0x04:
            if (_hide) {
                setStatus(HIDDEN);
            } else {
                setStatus(FROM_ARROW);
            }
            break;
        case 0x10:
            setStatus(VISIBLE);
            break;
        case 0x20:
            setStatus(PATH);
            break;
        default:
            setStatus(HIDDEN);
            break;
    }
}

/*public*/ void PortalIcon::propertyChange(PropertyChangeEvent* e)
{
    QObject* source = e->getSource();
//        if (log.isDebugEnabled()) log.debug("Icon "+getPortal().getName()+" PropertyChange= "+e.getPropertyName()+
//        		" oldValue= "+e.getOldValue().toString()+" newValue= "+e.getNewValue().toString());
    //if (source instanceof Portal) {
    if(qobject_cast<PortalIcon*>(source) != NULL)
    {
     QString propertyName = e->getPropertyName();

        if ("Direction"==(e->getPropertyName())) {
            if (_hide) {
                setStatus(HIDDEN);
                return;
            }
            switch ( e->getNewValue().toInt()) {
                case Portal::UNKNOWN:
                    setStatus(HIDDEN);
                    break;
                case Portal::ENTER_TO_BLOCK:
                    setStatus(TO_ARROW);
                    break;
                case Portal::ENTER_FROM_BLOCK:
                    setStatus(FROM_ARROW);
                    break;
            }
        } else if ("NameChange" == (propertyName)) {
                        setName((QString) e->getNewValue().toString());
                    } else if ("portalDelete" == (propertyName)) {
                        remove();
                    }
    }
}

/*public*/ QString PortalIcon::getNameString() {
    return _portal->getDescription();
}
