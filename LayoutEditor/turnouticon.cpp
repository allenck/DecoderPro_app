#include "turnouticon.h"
#include "instancemanager.h"
#include <QAction>
#include "namedicon.h"
#include <QMenu>
#include "editor.h"
#include "tableitempanel.h"

//TurnoutIcon::TurnoutIcon(QObject *parent) :
//    PositionableIcon(parent)
//{
//}
/**
 * An icon to display a status of a turnout.<P>
 * This responds to only KnownState, leaving CommandedState to some other
 * graphic representation later.
 * <P>
 * A click on the icon will command a state change. Specifically, it
 * will set the CommandedState to the opposite (THROWN vs CLOSED) of
 * the current KnownState.
 *<P>
 * The default icons are for a left-handed turnout, facing point
 * for east-bound traffic.
 * @author Bob Jacobsen  Copyright (c) 2002
 * @author PeteCressman Copyright (C) 2010, 2011
 * @version $Revision: 22576 $
 */

//public class TurnoutIcon extends PositionableIcon implements java.beans.PropertyChangeListener {


/*public*/ TurnoutIcon::TurnoutIcon(Editor* editor, QObject */*parent*/) : PositionableIcon(new NamedIcon(":/resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif",
                                                                                          "resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif"), editor, (Positionable*)this)
{
    // super ctor call to make sure this is an icon label
    //super(new NamedIcon("resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif",
//                        "resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif"), editor);
 log = new Logger("TurnoutIcon");
 //log->setDebugEnabled(true);
 _control = true;
 namedTurnout = NULL;
 _iconStateMap = new QHash <int, NamedIcon*>();
 _name2stateMap = new QHash <QString, int>();
 _name2stateMap->insert("BeanStateUnknown", (Turnout::UNKNOWN));
 _name2stateMap->insert("BeanStateInconsistent", (Turnout::INCONSISTENT));
 _name2stateMap->insert("TurnoutStateClosed", (Turnout::CLOSED));
 _name2stateMap->insert("TurnoutStateThrown", (Turnout::THROWN));
 _state2nameMap = new QHash <int, QString>();
 _state2nameMap->insert((Turnout::UNKNOWN), "BeanStateUnknown");
 _state2nameMap->insert((Turnout::INCONSISTENT), "BeanStateInconsistent");
 _state2nameMap->insert((Turnout::CLOSED), "TurnoutStateClosed");
 _state2nameMap->insert((Turnout::THROWN), "TurnoutStateThrown");
 _type = 0;
 tristate = false;
 setPopupUtility(NULL);
 setObjectName("TurnoutIcon");
 momentary = false;
 directControl = false;
 momentaryItem = new QAction(tr("Momentary"),this);
 momentaryItem->setCheckable(true);
 directControlItem = new QAction(tr("Direct control"), this);
 directControlItem->setCheckable(true);

}

/*public*/ Positionable* TurnoutIcon::deepClone()
{
 TurnoutIcon* pos = new TurnoutIcon(_editor);
 return finishClone((Positionable*)pos);
}

/*public*/ Positionable* TurnoutIcon::finishClone(Positionable* p)
{
 TurnoutIcon* pos = (TurnoutIcon*)p;
 if(getNamedTurnout()!= NULL)
  pos->setTurnout(getNamedTurnout()->getName());
 pos->_iconStateMap = cloneMap(_iconStateMap, pos);
 pos->setTristate(getTristate());
 pos->_iconFamily = _iconFamily;
 return PositionableIcon::finishClone((Positionable*)pos);
}


/**
 * Attached a named turnout to this display item
 * @param pName Used as a system/user name to lookup the turnout object
 */
 /*public*/ void TurnoutIcon::setTurnout(QString pName)
{
 if (InstanceManager::turnoutManagerInstance() != NULL)
 {
  Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(pName);
  if (turnout != NULL)
  {
   setTurnout(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, turnout));
  }
  else
  {
   log->error("Turnout '"+pName+"' not available, icon won't see changes");
   }
  }
  else
  {
   log->error("No TurnoutManager for this protocol, icon won't see changes");
  }
 }

/*public*/ void TurnoutIcon::setTurnout(NamedBeanHandle<Turnout*>* to)
{
    Q_ASSERT(to != NULL);
 if (namedTurnout != NULL)
 {
//  ((AbstractTurnout*)getTurnout())->removePropertyChangeListener((PropertyChangeListener*)this);
     AbstractTurnout* t = (AbstractTurnout*)getTurnout();
     disconnect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 }
 namedTurnout = to;
 if (namedTurnout != NULL)
 {
  _iconStateMap = new QHash <int, NamedIcon*>();
  _name2stateMap = new QHash <QString, int>();
  _name2stateMap->insert("BeanStateUnknown", (Turnout::UNKNOWN));
  _name2stateMap->insert("BeanStateInconsistent", (Turnout::INCONSISTENT));
  _name2stateMap->insert("TurnoutStateClosed", (Turnout::CLOSED));
  _name2stateMap->insert("TurnoutStateThrown", (Turnout::THROWN));
  _state2nameMap = new QHash <int, QString>();
  _state2nameMap->insert((Turnout::UNKNOWN), "BeanStateUnknown");
  _state2nameMap->insert((Turnout::INCONSISTENT), "BeanStateInconsistent");
  _state2nameMap->insert((Turnout::CLOSED), "TurnoutStateClosed");
  _state2nameMap->insert((Turnout::THROWN), "TurnoutStateThrown");
  displayState(turnoutState());
//  ((AbstractTurnout*)getTurnout())->addPropertyChangeListener((PropertyChangeListener*)this, namedTurnout->getName(), "Panel Editor Turnout Icon");
  AbstractTurnout* t = (AbstractTurnout*)getTurnout();
  connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/*public*/ Turnout* TurnoutIcon::getTurnout() { return namedTurnout->getBean(); }

/*public*/ NamedBeanHandle<Turnout*>* TurnoutIcon::getNamedTurnout() {
    return namedTurnout;
}

/*public*/ NamedBean* TurnoutIcon::getNamedBean()
{
 return getTurnout();
}

/**
* Place icon by its bean state name key found in jmri.NamedBeanBundle.properties
* That is, by its localized bean state name
*/
/*public*/ void TurnoutIcon::setIcon(QString name, NamedIcon* icon)
{
 if (log->isDebugEnabled()) log->debug("setIcon for name \""+name+
                                        "\" state= "+QString("%1").arg(_name2stateMap->value(name)));
 _iconStateMap->insert(_name2stateMap->value(name), icon);
  displayState(turnoutState());
}

/**
* Get icon by its localized bean state name
*/
/*public*/ NamedIcon* TurnoutIcon::getIcon(QString state)
{
    return _iconStateMap->value(_name2stateMap->value(state));
}
/*public*/ NamedIcon* TurnoutIcon::getIcon(int state) {
    return _iconStateMap->value((state));
}

/*public*/ QString TurnoutIcon::getFamily() {
    return _iconFamily;
}
/*public*/ void TurnoutIcon::setFamily(QString family) {
    _iconFamily = family;
}

/*public*/ int TurnoutIcon::maxHeight()
{
 int max = 0;
 //Iterator<NamedIcon> iter = _iconStateMap.values().iterator();
 QHashIterator<int, NamedIcon*> iter(*_iconStateMap);
 while (iter.hasNext())
 {
  iter.next();
  max = qMax(iter.value()->getIconHeight(), max);
 }
 return max;
}
/*public*/ int TurnoutIcon::maxWidth()
{
 int max = 0;
 //Iterator<NamedIcon> iter = _iconStateMap.values().iterator();
 QHashIterator<int, NamedIcon*> iter(*_iconStateMap);
 while (iter.hasNext())
 {
  iter.next();
  max = qMax(iter.value()->getIconWidth(), max);
 }
 return max;
}

/**
 * Get current state of attached turnout
 * @return A state variable from a Turnout, e.g. Turnout.CLOSED
 */
int TurnoutIcon::turnoutState() {
    if (namedTurnout != NULL) return ((AbstractTurnout*)getTurnout())->getKnownState();
    else return Turnout::UNKNOWN;
}

// update icon as state of turnout changes
/*public*/ void TurnoutIcon::propertyChange(PropertyChangeEvent* e) {
 if (log->isDebugEnabled())
  log->debug("property change: " + getNameString() + " " + e->getPropertyName() + " is now "                + e->getNewValue().toString());

 // when there's feedback, transition through inconsistent icon for better
 // animation
 if (getTristate() && (((AbstractTurnout*)getTurnout())->getFeedbackMode() != Turnout::DIRECT) && (e->getPropertyName()==("CommandedState")))
 {
  if (((AbstractTurnout*)getTurnout())->getCommandedState() != ((AbstractTurnout*)getTurnout())->getKnownState())
  {
   int now = Turnout::INCONSISTENT;
   displayState(now);
  }
  // this takes care of the quick double click
  if (((AbstractTurnout*)getTurnout())->getCommandedState() == ((AbstractTurnout*)getTurnout())->getKnownState())
  {
   int now = ( e->getNewValue()).toInt();
   displayState(now);
  }
 }

 if (e->getPropertyName()==("KnownState"))
 {
  int now = ( e->getNewValue()).toInt();
  displayState(now);
 }
 //_editor->addToTarget((Positionable*)this);
}

/*public*/ QString TurnoutIcon::getStateName(int state)
{
 return _state2nameMap->value((state));
}

/*public*/ QString TurnoutIcon::getNameString()
{
 QString name;
 if (namedTurnout == NULL) name = tr("<Not connected>");
 else if (((AbstractTurnout*)getTurnout())->getUserName()!=NULL)
  name = getTurnout()->getUserName()+" ("+getTurnout()->getSystemName()+")";
 else
  name = getTurnout()->getSystemName();
 return name;
}

/*public*/ void TurnoutIcon::setTristate(bool bSet)
{
 tristate = bSet;
}
/*public*/ bool TurnoutIcon::getTristate() { return tristate; }

/*public*/ bool TurnoutIcon::getMomentary() {
    return momentary;
}

/*public*/ void TurnoutIcon::setMomentary(bool m) // SLOT[]
{
 momentary = m;
}

/*public*/ bool TurnoutIcon::getDirectControl() {
    return directControl;
}

/*public*/ void TurnoutIcon::setDirectControl(bool m) // slot []
{
 directControl = m;
}


/**
 * Pop-up displays unique attributes of turnouts
 */
/*public*/ bool TurnoutIcon::showPopUp(QMenu* popup)
{
 if (isEditable())
 {
  // add tristate option if turnout has feedback
  if (namedTurnout != NULL && ((AbstractTurnout*)getTurnout())->getFeedbackMode() != Turnout::DIRECT)
  {
   addTristateEntry(popup);
  }

  popup->addAction(momentaryItem);
  momentaryItem->setChecked(getMomentary());
//      momentaryItem.addActionListener(new ActionListener() {
//          public void actionPerformed(java.awt.event.ActionEvent e) {
//              setMomentary(momentaryItem.isSelected());
//          }
//      });
  connect(momentaryItem, SIGNAL(toggled(bool)), this, SLOT(setMomentary(bool)));
  popup->addAction(directControlItem);
  directControlItem->setChecked(getDirectControl());
//      directControlItem.addActionListener(new ActionListener() {
//          public void actionPerformed(java.awt.event.ActionEvent e) {
//              setDirectControl(directControlItem.isSelected());
//          }
//      });
  connect(directControlItem, SIGNAL(triggered(bool)), this, SLOT(setDirectControl(bool)));
 }
 else if (getDirectControl())
 {
  getTurnout()->setCommandedState(Turnout::THROWN);
 }
 return true;
}

//javax.swing.JCheckBoxMenuItem tristateItem = NULL;
void TurnoutIcon::addTristateEntry(QMenu* popup)
{
 QAction* tristateItem = new QAction(tr("Tristate"),this);
 tristateItem->setCheckable(true);
 //tristateItem = tr("Tristate");
 tristateItem->setChecked(getTristate());
 popup->addAction(tristateItem);
 connect(tristateItem, SIGNAL(toggled(bool)), this, SLOT(on_tristateItem_toggled(bool)));
//    tristateItem.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            setTristate(tristateItem.isSelected());
//        }
//    });
}
void TurnoutIcon::on_tristateItem_toggled(bool bState)
{
 setTristate(bState);
}

/******** popup AbstractAction method overrides *********/

/*protected*/ void TurnoutIcon::rotateOrthogonal()
{
   //Iterator<Entry<Integer, NamedIcon>> it = _iconStateMap.entrySet().iterator();
 QHashIterator<int, NamedIcon*> it(*_iconStateMap);
 while (it.hasNext())
 {
  //Entry<Integer, NamedIcon> entry = it.next();
  it.next();
  it.value()->setRotation(it.value()->getRotation()+1, this);
 }
 displayState(turnoutState());
 // bug fix, must repaint icons that have same width and height
 //repaint();
//_editor->addToTarget((Positionable*)this);
}

/*public*/ void TurnoutIcon::setScale(double s)
{
 //Iterator<Entry<Integer, NamedIcon>> it = _iconStateMap.entrySet().iterator();
 QHashIterator<int, NamedIcon*> it(*_iconStateMap);
 while (it.hasNext())
 {
  //Entry<Integer, NamedIcon> entry = it.next();
  it.next();
  it.value()->scale(s, this);
 }
 displayState(turnoutState());
 //_editor->addToTarget((Positionable*)this);
}

/*public*/ void TurnoutIcon::rotate(int deg) {
#if 0 // QGraphicsScene does the rotating
 //Iterator<Entry<Integer, NamedIcon>> it =   _iconStateMap.entrySet().iterator();
 QHashIterator<int, NamedIcon*> it(*_iconStateMap);
 while (it.hasNext())
 {
  //Entry<Integer, NamedIcon> entry = it.next();
  it.next();
  it.value()->rotate(deg, this);
 }
#else
 _degrees = deg;
#endif
 displayState(turnoutState());
 //_editor->addToTarget((Positionable*)this);
}

/**
 * Drive the current state of the display from the state of the turnout.
 */
/*public*/ void TurnoutIcon::displayState(int state)
{
 if (getNamedTurnout() == NULL)
 {
  if(log->isDebugEnabled()) log->debug("Display state "+QString("%1").arg(state)+", disconnected");
 }
 else
 {
  if(log->isDebugEnabled()) log->debug(getNameString() +" displayState "+_state2nameMap->value(state));
  if (isText())
  {
   PositionableIcon::setText(_state2nameMap->value(state));
  }
  if (isIcon())
  {
   NamedIcon* icon = getIcon(state);
   if (icon!=NULL)
   {

//    QList<QGraphicsItem*> l =_itemGroup->childItems();
//    foreach(QGraphicsItem* item, l)
//    {
//     _itemGroup->removeFromGroup(item);
//    }
//    PositionableIcon::setIcon(icon);
//    _itemGroup->addToGroup(new QGraphicsPixmapItem(QPixmap::fromImage(icon->getImage()),0));
    PositionableLabel::setIcon(icon);
    updateScene();
    _itemGroup->setName("TurnoutIcon");
   }
  }
 }
 updateSize();
 _itemGroup->update();
}

/*public*/ QString TurnoutIcon() { return "TurnoutIcon";}

/*public*/ bool TurnoutIcon::setEditItemMenu(QMenu* popup)
{
 QString txt = tr("Edit %1 Icon").arg(tr("Turnout"));
// popup.add(new javax.swing.AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editItem();
//            }
//        });
 QAction* act = new QAction(txt, this);
 popup->addAction(act);
 connect(act, SIGNAL(triggered()), this, SLOT(editItem()));
    return true;
}

/*protected*/ void TurnoutIcon::editItem()
{
 makePaletteFrame(tr("Edit %1 Icon").arg("Turnout"));
 _itemPanel = new TableItemPanel(_paletteFrame, "Turnout", _iconFamily, PickListModel::turnoutPickModelInstance(), _editor,this);
//    ActionListener updateAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateItem();
//        }
//    };
 UpdateTurnoutActionListener* updateAction = new UpdateTurnoutActionListener(this);
 // duplicate icon map with state names rather than int states and unscaled and unrotated
 QHash<QString, NamedIcon*>* strMap = new QHash<QString, NamedIcon*>();
 QHashIterator<int, NamedIcon*> it(*_iconStateMap);
  while (it.hasNext())
  {
   it.next();
   NamedIcon* oldIcon =it.value();
   NamedIcon* newIcon = cloneIcon(oldIcon, this);
   newIcon->rotate(0, this);
   newIcon->scale(1.0, this);
   newIcon->setRotation(4, this);
   strMap->insert(_state2nameMap->value(it.key()), newIcon);
  }
  _itemPanel->init(updateAction, strMap);
  _itemPanel->setSelection(getTurnout());
  if(_paletteFrame->centralWidget() == NULL)
  {
   QWidget* centralWidget = new QWidget();
   centralWidget->setLayout(new QVBoxLayout);
   _paletteFrame->setCentralWidget(centralWidget);
  }
  QScrollArea* scrollArea = new QScrollArea;
  scrollArea->setWidget(_itemPanel);
  scrollArea->setWidgetResizable(true);
  _paletteFrame->centralWidget()->layout()->addWidget(scrollArea);
  _paletteFrame->setMinimumSize(400,600);
  _paletteFrame->setVisible(true);
  _paletteFrame->pack();
}

void TurnoutIcon::updateItem()
{
 QHash<int, NamedIcon*>* oldMap = cloneMap(_iconStateMap, this);
 setTurnout(_itemPanel->getTableSelection()->getSystemName());
 _iconFamily = _itemPanel->getFamilyName();
 QHash <QString, NamedIcon*>* iconMap = _itemPanel->getIconMap();
 if (iconMap!=NULL)
 {
  QHashIterator<QString, NamedIcon*> it(*iconMap);
  while (it.hasNext())
  {
   it.next();
   if (log->isDebugEnabled()) log->debug("key= "+it.key());
   NamedIcon* newIcon = it.value();
   NamedIcon* oldIcon = oldMap->value(_name2stateMap->value(it.key()));
   newIcon->setLoad(oldIcon->getDegrees(), oldIcon->getScale(), this);
   newIcon->setRotation(oldIcon->getRotation(), this);
   setIcon(it.key(), newIcon);
  }
 }   // otherwise retain current map
//        jmri.jmrit.catalog.ImageIndexEditor.checkImageIndex();  _paletteFrame->dispose();
 _paletteFrame = NULL;
 _itemPanel->dispose();
 _itemPanel = NULL;
//    invalidate();
}

/*public*/ bool TurnoutIcon::setEditIconMenu(QMenu* popup)
{
 QString txt = tr("Edit %1 Icon").arg("Turnout");
// popup.add(new javax.swing.AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                edit();
//            }
//        });
 QAction* act = new QAction(txt, this);
 popup->addAction(act);
 connect(act, SIGNAL(triggered()), this, SLOT(edit()));
 return true;
}

/*protected*/ void TurnoutIcon::edit()
{
 makeIconEditorFrame(this, "Turnout", true, NULL);
 _iconEditor->setPickList(PickListModel::turnoutPickModelInstance());
 QListIterator<int> e = _iconStateMap->keys();
 int i = 0;
 while (e.hasNext())
 {
  int key = e.next();
  _iconEditor->setIcon(i++, _state2nameMap->value(key), _iconStateMap->value(key));
 }
 _iconEditor->makeIconPanel(false);

    // set default icons, then override with this turnout's icons
//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateTurnout();
//        }
//    };
 AddTurnoutIconActionListener* addIconAction = new AddTurnoutIconActionListener(this);
 _iconEditor->complete(addIconAction, true, true, true);
 _iconEditor->setSelection(getTurnout());
 _iconEditorFrame->setMinimumSize(400,600);
 _iconEditorFrame->pack();
 QTimer::singleShot(50,_iconEditorFrame, SLOT(pack()));
}
void TurnoutIcon::updateTurnout()
{
 QHash<int, NamedIcon*>* oldMap = cloneMap(_iconStateMap, this);
 setTurnout(_iconEditor->getTableSelection()->getDisplayName());
 QHash <QString, NamedIcon*>* iconMap = _iconEditor->getIconMap();

 QHashIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  it.next();
  if (log->isDebugEnabled()) log->debug("key= "+it.key());
  NamedIcon* newIcon = it.value();
  NamedIcon* oldIcon = oldMap->value(_name2stateMap->value(it.key()));
  newIcon->setLoad(oldIcon->getDegrees(), oldIcon->getScale(), this);
  newIcon->setRotation(oldIcon->getRotation(), this);
  setIcon(it.key(), newIcon);
 }
 _iconEditorFrame->dispose();
 _iconEditorFrame = NULL;
 _iconEditor = NULL;
  //invalidate();
}

/**
 * Throw the turnout when the icon is clicked
 * @param e
 */
/*public*/ void TurnoutIcon::doMouseClicked(QGraphicsSceneMouseEvent* e)
{
 if (!_editor->getFlag(Editor::OPTION_CONTROLS, isControlling())) return;
 //if (e.isMetaDown() || e.isAltDown() ) return;
 if((((e->modifiers())&Qt::MetaModifier) == Qt::MetaModifier) || (((e->modifiers())& Qt::AltModifier)==Qt::AltModifier))
  return;
 if (namedTurnout==NULL)
 {
  log->error("No turnout connection, can't process click");
  return;
 }
// if (((AbstractTurnout*)getTurnout())->getKnownState()==Turnout::CLOSED)  // if clear known state, set to opposite
//  ((AbstractTurnout*)getTurnout())->setCommandedState(Turnout::THROWN);
// else if (((AbstractTurnout*)getTurnout())->getKnownState()==Turnout::THROWN)
//  ((AbstractTurnout*)getTurnout())->setCommandedState(Turnout::CLOSED);

// else if (((AbstractTurnout*)getTurnout())->getCommandedState()==Turnout::CLOSED)
//  ((AbstractTurnout*)getTurnout())->setCommandedState(Turnout::THROWN);  // otherwise, set to opposite of current commanded state if known
// else
//  ((AbstractTurnout*)getTurnout())->setCommandedState(Turnout::CLOSED);  // just force closed.
 if (getDirectControl() && !isEditable())
 {
  getTurnout()->setCommandedState(Turnout::CLOSED);
 }
 else
 {
  alternateOnClick();
 }
}
void TurnoutIcon::alternateOnClick()
{
 if (getTurnout()->getKnownState() == Turnout::CLOSED) // if clear known state, set to opposite
 {
  getTurnout()->setCommandedState(Turnout::THROWN);
 }
 else if (getTurnout()->getKnownState() == Turnout::THROWN)
 {
  getTurnout()->setCommandedState(Turnout::CLOSED);
 }
 else if (getTurnout()->getCommandedState() == Turnout::CLOSED)
 {
  getTurnout()->setCommandedState(Turnout::THROWN);  // otherwise, set to opposite of current commanded state if known
 }
 else
 {
  getTurnout()->setCommandedState(Turnout::CLOSED);  // just force closed.
 }
}

/*public*/ void TurnoutIcon::dispose()
{
 if (namedTurnout != NULL)
 {
  //getTurnout().removePropertyChangeListener(this);
  AbstractTurnout* t = (AbstractTurnout*)getTurnout();
  disconnect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 }
 namedTurnout = NULL;
 _iconStateMap = NULL;
 _name2stateMap = NULL;
 _state2nameMap = NULL;

 PositionableIcon::dispose();
}

/*protected*/ QHash<int, NamedIcon*>* TurnoutIcon::cloneMap(QHash<int, NamedIcon*>* map,
                                                         TurnoutIcon* pos)
{
 QHash<int, NamedIcon*>* clone = new QHash<int, NamedIcon*>();
 if (map!=NULL)
 {
  //Iterator<Entry<Integer, NamedIcon>> it = map.entrySet().iterator();
  QHashIterator<int, NamedIcon*> it(*map);
  while (it.hasNext())
  {
   //Entry<Integer, NamedIcon> entry = it.next();
   it.next();
   clone->insert(it.key(), cloneIcon(it.value(), pos));
   if (pos!=NULL)
   {
    pos->setIcon(_state2nameMap->value(it.key()), _iconStateMap->value(it.key()));
   }
  }
 }
 return clone;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TurnoutIcon.class.getName());
//}
void TurnoutIcon::setType(int type) { _type = type;}
int TurnoutIcon::getType() { return _type;}

/*public*/ QString TurnoutIcon::getGroupName()
{
 return "TurnoutIcon";
}
