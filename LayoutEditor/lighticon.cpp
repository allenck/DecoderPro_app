#include "lighticon.h"
#include "light.h"
#include "instancemanager.h"
#include "lightmanager.h"
#include "namedicon.h"
#include "QGraphicsSceneMouseEvent"
#include "abstractlight.h"
#include "editor.h"
#include "proxylightmanager.h"

//LightIcon::LightIcon(QObject *parent) :
//    PositionableLabel(parent)
//{
//}
/**
 * An icon to display a status of a light.<P>
 * <P>
 * A click on the icon will command a state change. Specifically, it
 * will set the state to the opposite (THROWN vs CLOSED) of
 * the current state.
 *<P>
 * The default icons are for a left-handed turnout, facing point
 * for east-bound traffic.
 * @author Bob Jacobsen  Copyright (c) 2002
 * @version $Revision: 22320 $
 */

//public class LightIcon extends PositionableLabel implements java.beans.PropertyChangeListener {

/*public*/ LightIcon::LightIcon(Editor* editor, QObject *parent) : PositionableIcon(new NamedIcon("resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif",  "resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif"), editor, (Positionable*)this)
{
    // super ctor call to make sure this is an icon label
    //super(new NamedIcon("resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif",
//                        "resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif"), editor);
 log = new Logger("LightIcon");
 log->setDebugEnabled(true);
 _control = true;
 light = NULL;
 _bVisible = true;
 _icon = true;

 setPopupUtility(NULL);
 offLName = "resources/icons/smallschematics/tracksegments/os-lefthand-east-closed.gif";
 off = new NamedIcon(offLName, offLName);
 onLName = "resources/icons/smallschematics/tracksegments/os-lefthand-east-thrown.gif";
 on = new NamedIcon(onLName, onLName);
 inconsistentLName = "resources/icons/smallschematics/tracksegments/os-lefthand-east-error.gif";
 inconsistent = new NamedIcon(inconsistentLName, inconsistentLName);
 unknownLName = "resources/icons/smallschematics/tracksegments/os-lefthand-east-unknown.gif";
 unknown = new NamedIcon(unknownLName, unknownLName);
 _namedIcon = unknown;
 _editor = editor;
 _icon = true;
 displayState(lightState());
}


/*public*/ Positionable* LightIcon::deepClone()
{
 LightIcon* pos = new LightIcon(_editor);
 return finishClone((Positionable*)pos);
}

/*public*/ Positionable* LightIcon::finishClone(Positionable* p)
{
    LightIcon* pos = (LightIcon*)p;
    pos->setLight(getNameString());
    pos->setOffIcon(cloneIcon(getOffIcon(), pos));
    pos->setOnIcon(cloneIcon(getOnIcon(), pos));
    pos->setInconsistentIcon(cloneIcon(getInconsistentIcon(), pos));
    pos->setUnknownIcon(cloneIcon(getUnknownIcon(), pos));
    return PositionableLabel::finishClone((Positionable*)pos);
}

/**
 * Attached a named light to this display item
 * @param pName Used as a system/user name to lookup the light object
 */
 /*public*/ void LightIcon::setLight(QString pName)
{
 if (InstanceManager::getNullableDefault("LightManager") != nullptr)
 {
  light = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->provideLight(pName);
  setLight(light);
 }
 else {
     log->error("No LightManager for this protocol, icon won't see changes");
 }
}

/*public*/ void LightIcon::setLight(Light* to)
{
 if (light != NULL)
 {
  light->removePropertyChangeListener((PropertyChangeListener*)this);
//  AbstractLight* l = (AbstractLight*)light;
//  disconnect(l->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 light = to;
 if (light != NULL)
 {
  displayState(lightState());
  light->addPropertyChangeListener((PropertyChangeListener*)this);
  //connect(light->pcs,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/*public*/ Light* LightIcon::getLight() { return light; }



/*public*/ NamedIcon* LightIcon::getOffIcon() { return off; }
/*public*/ void LightIcon::setOffIcon(NamedIcon* i) {
    off = i;
    displayState(lightState());
}

/*public*/ NamedIcon* LightIcon::getOnIcon() { return on; }
/*public*/ void LightIcon::setOnIcon(NamedIcon* i) {
    on = i;
    displayState(lightState());
}

/*public*/ NamedIcon* LightIcon::getInconsistentIcon() { return inconsistent; }
/*public*/ void LightIcon::setInconsistentIcon(NamedIcon* i) {
    inconsistent = i;
    displayState(lightState());
}

/*public*/ NamedIcon* LightIcon::getUnknownIcon() { return unknown; }
/*public*/ void LightIcon::setUnknownIcon(NamedIcon* i) {
    unknown = i;
    displayState(lightState());
}

/*public*/ int LightIcon::maxHeight()
{
    return qMax(
            qMax( (off!=NULL) ? off->getIconHeight() : 0,
                    (on!=NULL) ? on->getIconHeight() : 0),
            (inconsistent!=NULL) ? inconsistent->getIconHeight() : 0
        );
}
/*public*/ int LightIcon::maxWidth() {
    return qMax(
            qMax((off!=NULL) ? off->getIconWidth() : 0,
                    (on!=NULL) ? on->getIconWidth() : 0),
            (inconsistent!=NULL) ? inconsistent->getIconWidth() : 0
        );
}

/**
 * Get current state of attached light
 * @return A state variable from a Light, e.g. Turnout.CLOSED
 */
int LightIcon::lightState()
{
 if (light != NULL) return ((AbstractLight*)light)->getState();
 // This doesn't seem right. (Light.UNKNOWN = Light.ON = 0X01)
    //else return Light.UNKNOWN;
 else return Light::INCONSISTENT;
}

// update icon as state of light changes
/*public*/ void LightIcon::propertyChange(PropertyChangeEvent* e)
{
 //log->warn(tr("Property change %1").arg(e->toString()));
 propertyChange(e->getPropertyName(), e->getOldValue().toInt(), e->getNewValue().toInt());
}

void LightIcon::propertyChange(QString propertyName, int old, int now)
{
 if (log->isDebugEnabled())
        log->debug(tr("property change: ") + " " + propertyName + tr(" is now ")
                   + QString("%1").arg(now));

 if (propertyName == ("KnownState"))
 {

  light->setState(now);
     displayState(lightState());
//     _editor->addToTarget((Positionable*)this);
 }
}

/*public*/ QString LightIcon::getNameString()
{
 QString name;
 if (light == NULL) name = tr("<Not connected>");
 else if (light->getUserName()!=NULL)
  name = light->getUserName()+" ("+light->getSystemName()+")";
 else
  name = light->getSystemName();
 return name;
}

/******** popup AbstractAction.actionPerformed method overrides *********/

/*protected*/ void LightIcon::rotateOrthogonal() {
    off->setRotation(on->getRotation()+1, this);
    on->setRotation(off->getRotation()+1, this);
    unknown->setRotation(unknown->getRotation()+1, this);
    inconsistent->setRotation(inconsistent->getRotation()+1, this);
    displayState(lightState());
    //bug fix, must repaint icons that have same width and height
    repaint();
}


/*public*/ void LightIcon::setScale(double s) {
    off->scale(s, this);
    on->scale(s, this);
    unknown->scale(s, this);
    inconsistent->scale(s, this);
    displayState(lightState());
}

/*public*/ void LightIcon::rotate(int deg)
{
  off->rotate(deg, this);
  on->rotate(deg, this);
  unknown->rotate(deg, this);
  inconsistent->rotate(deg, this);
  displayState(lightState());
}

/*protected*/ void LightIcon::edit()
{
 makeIconEditorFrame(this, "Light", true, NULL);
 _iconEditor->setPickList(PickListModel::lightPickModelInstance());
 _iconEditor->setIcon(3, "LightStateOff", off);
 _iconEditor->setIcon(2, "LightStateOn", on);
 _iconEditor->setIcon(0, "BeanStateInconsistent", inconsistent);
 _iconEditor->setIcon(1, "BeanStateUnknown", unknown);
 _iconEditor->makeIconPanel(false);

//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateLight();
//        }
//    };
 LightIconActionListener* addIconAction = new LightIconActionListener(this);
 _iconEditor->complete(addIconAction, true, true, true);
 _iconEditor->setSelection(light);
}

LightIconActionListener::LightIconActionListener(LightIcon * icon)
{
 this->icon = icon;
}

void LightIconActionListener::actionPerformed(JActionEvent *e)
{
 icon->update();
}

void LightIcon::updateLight()
{
 setOffIcon(_iconEditor->getIcon("LightStateOff"));
 setOnIcon(_iconEditor->getIcon("LightStateOn"));
 setUnknownIcon(_iconEditor->getIcon("BeanStateUnknown"));
 setInconsistentIcon(_iconEditor->getIcon("BeanStateInconsistent"));
 setLight((Light*)_iconEditor->getTableSelection());
 _iconEditorFrame->dispose();
 _iconEditorFrame = NULL;
 _iconEditor = NULL;
 //invalidate();
}
/************* end popup action methods ****************/

/**
 * Drive the current state of the display from the state of the light.
 */
void LightIcon::displayState(int state)
{
 if (log->isDebugEnabled()) log->debug(getNameString() +" displayState "+QString("%1").arg(state));
  updateSize();
 switch (state)
 {
  case Light::OFF:
   if (isText()) PositionableLabel::setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText());
   if (isIcon()) PositionableLabel::setIcon(off);
   break;
 case Light::ON:
  if (isText()) PositionableLabel::setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText());
  if (isIcon()) PositionableLabel::setIcon(on);
  break;
 default:
  if (isText()) PositionableLabel::setText(tr("Inconsistent"));
  if (isIcon()) PositionableLabel::setIcon(inconsistent);
  break;
 }
//    _editor->repaint();
 if(light != NULL)
//    _editor->addToTarget((Positionable*)this);
  updateScene();
 return;
}

NamedIcon* LightIcon::getIcon(int state)
{
 switch(state)
 {
 case Light::ON:
  return getOnIcon();
 case Light::OFF:
  return getOffIcon();
 case /*Light::INCONSISTENT*/0X08:
  return getInconsistentIcon();
 default:
 case /*Light::UNKNOWN*/0X01:
  return getUnknownIcon();
 }
}
NamedIcon* LightIcon::getIcon(QString sState)
{
 if(sState == "ON")
     return getIcon(Light::ON);
 else
 if(sState == "OFF")
  return getIcon(Light::OFF);
 else
 if(sState == "INCONSISTENT")
  return getIcon(Light::INCONSISTENT);
 else
  if(sState == "ON")
 return getIcon(Light::UNKNOWN);
}

/**
 * Change the light when the icon is clicked
 * @param e
 */
// Was mouseClicked, changed to mouseRelease to workaround touch screen driver limitation
/*public*/ void LightIcon::doMouseClicked(QGraphicsSceneMouseEvent* e)
{
 if (!_editor->getFlag(Editor::OPTION_CONTROLS, isControlling())) return;
 //if (e->isMetaDown() || e->isAltDown() ) return;
 if (light==NULL)
 {
  log->error("No light connection, can't process click");
  return;
 }
 if (log->isDebugEnabled())
  log->debug("doMouseClicked state= " + ((AbstractLight*)light)->getState());
 if (((AbstractLight*)light)->getState()==Light::OFF)
  ((AbstractLight*)light)->setState(Light::ON);
 else
  ((AbstractLight*)light)->setState(Light::OFF);
 _editor->addToTarget((Positionable*)this);
}

/*public*/ void LightIcon::dispose()
{
 if (light != NULL)
 {
  light->removePropertyChangeListener((PropertyChangeListener*)this);
//  AbstractLight* l = (AbstractLight*)light;
//  disconnect(l, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 light = NULL;

 off = NULL;
 on = NULL;
 inconsistent = NULL;
 unknown = NULL;

 PositionableLabel::dispose();
}

/*public*/ bool LightIcon::updateScene()
{
 if(_itemGroup != NULL)
 {
  QList<QGraphicsItem*> l = _itemGroup->childItems();
  foreach(QGraphicsItem* item, l)
  {
   if(_itemGroup->scene())
    _itemGroup->scene()->removeItem(item);
   _itemGroup->removeFromGroup(item);
  }
 }
 else
   _itemGroup = new MyGraphicsItemGroup;
 _itemGroup->setName("LightIcon");

 if(getLight() != NULL)
 {
  int iState = ((AbstractLight*)getLight())->getState();
  QPixmap pixmap = QPixmap::fromImage(getIcon(iState)->getImage());
  setSize(pixmap.width(), pixmap.height());
  //   QGraphicsPixmapItem* item = g2->addPixmap(pixmap);
  QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap,_itemGroup);
  //_itemGroup->addToGroup(item);
  //item->setPos(getX(),getY());
  _itemGroup->setPos(((Positionable*)this)->getX(),((Positionable*)this)->getY());
  if(showToolTip()) _itemGroup->setToolTip(getToolTip());
  if(pixmap.isNull())
   qDebug() << "No pixmap";
  if(getDegrees() != 0)
  {
   //m->item->rotate(l->getDegrees());
   QPointF center = _itemGroup->boundingRect().center();
   _itemGroup->setTransformOriginPoint(center);
   _itemGroup->setRotation(_itemGroup->rotation()+ getDegrees());
  }
  QRectF r = getBounds();
  _itemGroup->setZValue(getDisplayLevel());
  _itemGroup->update();
  return true;
 }
 else
  log->debug(tr("Light icon '%1' missing light").arg(getName()));
 return false;
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LightIcon.class.getName());
//}
