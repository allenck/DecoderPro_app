#ifndef EDITSIGNALFRAME_H
#define EDITSIGNALFRAME_H
#include "editframe.h"

class ListSelectionEvent;
class NamedBean;
class PositionableIcon;
class PortalIcon;
class JTextField;
class PortalList;
class Portal;
class LengthPanel;
class OpenPickListButton;
class SignalMast;
class SignalHead;
class EditSignalFrame : public EditFrame
{
 Q_OBJECT

public:
 EditSignalFrame(QString title, CircuitBuilder* parent, OBlock* block);
 /*public*/ void valueChanged(ListSelectionEvent* e);

private:
 static Logger* log;
 /*private*/ PortalIcon* _portalIcon;

 /*private*/ JTextField* _mastName;
 /*private*/ PortalList* _portalList;
 /*private*/ LengthPanel* _lengthPanel;
 /*private*/ Portal* _currentPortal;
 OpenPickListButton/*<SignalMast*>*/* _pickMast;
 OpenPickListButton/*<SignalHead*>*/* _pickHead;

 QString getClassName() {return"jmri.jmrir.display.controlPanelEditor.EditSignalFrame";}
 /*private*/ void setMastNameAndIcon(NamedBean* mast);
 /*private*/ void setPortalSelected(Portal* portal, PositionableIcon* icon);
 /*private*/ bool replaceQuestion(/*@Nonnull*/ NamedBean* mast, /*@Nonnull*/ Portal* homePortal);
 /*private*/ NamedBean* getSignal();
 /*private*/ void addMast(/*@Nonnull*/ Portal* portal, /*@Nonnull*/ NamedBean *newMast);
 /*private*/ void setMastIcon(NamedBean* newMast,  Portal* portal);
 /*private*/ void removeMast();
 /*private*/ QString checkMastForSave();

protected:
 /*protected*/ JPanel* makeContentPanel();
 /*protected*/ void setSelected(PositionableIcon* icon);

 /*protected*/ void closingEvent(bool close);

 friend class CircuitBuilder;
};

#endif // EDITSIGNALFRAME_H
