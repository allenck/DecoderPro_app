#ifndef PORTALICON_H
#define PORTALICON_H
#include "positionableicon.h"

class Portal;
class PortalIcon : public PositionableIcon
{
 Q_OBJECT
public:
    /*public*/ static /*final*/ QString HIDDEN;// = "HIDDEN";
    /*public*/ static /*final*/ QString VISIBLE;// = "BLOCK";
    /*public*/ static /*final*/ QString PATH;// = "PATH";
 /*public*/ static /*final*/ QString TO_ARROW;// = "toArrow";
 /*public*/ static /*final*/ QString FROM_ARROW;// = "fromArrow";
    PortalIcon(Editor*, Portal* portal, QObject* parent = 0);
    /*public*/ PortalIcon(QString blockName, QString portalName, Editor* editor, QObject* parent = 0);
    /*public*/ Portal* getPortal();
    /*public*/ void setPortal(Portal* portal);
    /*public*/ QString getStatus();
    /*public*/ void setStatus(QString status);
    /*public*/ QString getNameString();
    /*public*/ void setArrowOrientatuon(bool set);
    /*public*/ void setHideArrows(bool set);
    /*public*/ bool getArrowSwitch();
    /*public*/ bool getArrowHide();
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ NamedBean* getNamedBean();
    /*public*/ void displayState(int state);
private:
    /*private*/ Portal* _portal;
    /*private*/ void initMap();
    Logger* log;
    /*private*/ QString _status;
    /*private*/ bool _regular;// = true;	// true when TO_ARROW shows entry into ToBlock
    /*private*/ bool _hide;// = false;	// true when arrow should NOT show entry into ToBlock
 protected:
    /*protected*/ void setIcon(QString name, NamedIcon* ic);

friend class ControlPanelEditor;
friend class PortalIconXml;
friend class EditPortalDirection;
};

#endif // PORTALICON_H
