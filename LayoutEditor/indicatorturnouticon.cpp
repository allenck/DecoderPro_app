#include "indicatorturnouticon.h"
#include "oblock.h"
#include "instancemanager.h"
#include "oblockmanager.h"
#include "namedicon.h"
#include "indicatortrackpaths.h"
#include <QHash>
#include "abstractsensor.h"
#include "indicatortoitempanel.h"
#include <QVBoxLayout>
#include "positionablelabel.h"
#include "editor.h"

//IndicatorTurnoutIcon::IndicatorTurnoutIcon(QObject *parent) :
//    TurnoutIcon(parent)
//{
//}
/**
 * An icon to display a status and state of a color coded turnout.<P>
 * This responds to only KnownState, leaving CommandedState to some other
 * graphic representation later.
 * <p>"state" is the state of the underlying turnout ("closed", "thrown", etc.)
 * <p>"status" is the operating condition of the track ("clear", "occupied", etc.)
 * <P>
 * A click on the icon will command a state change. Specifically, it
 * will set the CommandedState to the opposite (THROWN vs CLOSED) of
 * the current KnownState. This will display the setting of the turnout points.
 *<P>
 * The status is indicated by color and changes are done only done by the occupancy
 * sensing - OBlock or other sensor.
 * <p>
 * The default icons are for a left-handed turnout, facing point
 * for east-bound traffic.
 * @author Bob Jacobsen  Copyright (c) 2002
 * @author Pete Cressman  Copyright (c) 2010 2012
 * @version $Revision: 22576 $
 */

///*public*/ class IndicatorTurnoutIcon extends TurnoutIcon implements IndicatorTrack {



/*public*/ IndicatorTurnoutIcon::IndicatorTurnoutIcon(Editor* editor, QObject *parent) : TurnoutIcon(editor, parent)
{
 //super(editor);
  namedOccSensor = NULL;
  namedOccBlock = NULL;
  log = new Logger("IndicatorTurnoutIcon");

  log->debug(tr("IndicatorTurnoutIcon ctor: isIcon()= ")+(isIcon()?"true":"false")+", isText()= "+(isText()?"true":"false"));
 _pathUtil = new IndicatorTrackPaths();
 _status = "DontUseTrack";
 _iconMaps = initMaps();
 setObjectName("IndicatorTurnoutIcon");
}

QMap<QString, QHash<int, NamedIcon*>*>* IndicatorTurnoutIcon::initMaps()
{
 QMap<QString, QHash<int, NamedIcon*>*>* iconMaps = new QMap<QString, QHash<int, NamedIcon*>*>();
 iconMaps->insert("ClearTrack", new QHash <int, NamedIcon*>());
 iconMaps->insert("OccupiedTrack", new QHash <int, NamedIcon*>());
 iconMaps->insert("PositionTrack", new QHash <int, NamedIcon*>());
 iconMaps->insert("AllocatedTrack", new QHash <int, NamedIcon*>());
 iconMaps->insert("DontUseTrack", new QHash <int, NamedIcon*>());
 iconMaps->insert("ErrorTrack", new QHash <int, NamedIcon*>());
 return iconMaps;
}

QMap<QString, QHash<int, NamedIcon*>*>* IndicatorTurnoutIcon::cloneMaps(IndicatorTurnoutIcon* pos)
{
 QMap<QString, QHash<int, NamedIcon*>*>* iconMaps = initMaps();
#if 1
 QMapIterator<QString,QHash<int, NamedIcon*>*> it(*_iconMaps);
 while (it.hasNext())
 {
  /*QHash<int, NamedIcon*>* entry =*/ it.next();
  QHash<int, NamedIcon*>* clone = iconMaps->value(it.key());
  QHashIterator<int, NamedIcon*> iter( *it.value());
  while (iter.hasNext())
  {
   /*Entry<int, NamedIcon*> ent =*/ iter.next();
//                if (log->isDebugEnabled()) log->debug("key= "+ent.getKey());
   clone->insert(iter.key(), cloneIcon(iter.value(), pos));
  }
 }
#endif
 return iconMaps;
}


/*public*/ Positionable* IndicatorTurnoutIcon::deepClone() {
    IndicatorTurnoutIcon* pos = new IndicatorTurnoutIcon(_editor);
    return finishClone(pos);
}
/*public*/ Positionable* IndicatorTurnoutIcon::finishClone(Positionable* p) {
    IndicatorTurnoutIcon* pos = (IndicatorTurnoutIcon*)p;
    pos->setOccBlockHandle(namedOccBlock);
    pos->setOccSensorHandle(namedOccSensor);
    pos->_iconMaps = cloneMaps(pos);
    pos->_pathUtil = _pathUtil->deepClone();
    pos->_iconFamily = _iconFamily;
    return TurnoutIcon::finishClone(pos);
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP",
//        justification="OK until Java 1.6 allows more efficient return of copy")
/*public*/ QMap<QString, QHash<int, NamedIcon*>*>* IndicatorTurnoutIcon::getIconMaps()
{
    return _iconMaps;
}

/**
 * Attached a named sensor to display status from OBlocks
 * @param pName Used as a system/user name to lookup the sensor object
 */
/*public*/ void IndicatorTurnoutIcon::setOccSensor(QString pName)
{
 if (pName==NULL || pName.trimmed().length()==0)
 {
  setOccSensorHandle(NULL);
  return;
 }
 if (InstanceManager::sensorManagerInstance()!=NULL)
 {
  Sensor* sensor = ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->provideSensor(pName);
  if (sensor != NULL)
  {
   setOccSensorHandle(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor));
  }
  else
  {
   log->error("Occupancy Sensor '"+pName+"' not available, icon won't see changes");
  }
 }
 else
 {
  log->error("No SensorManager for this protocol, block icons won't see changes");
 }
}

/*public*/ void IndicatorTurnoutIcon::setOccSensorHandle(NamedBeanHandle<Sensor*>* sen)
{
 if (namedOccSensor != NULL)
 {
  getOccSensor()->removePropertyChangeListener((PropertyChangeListener*)this);
 }
 namedOccSensor = sen;
 if (namedOccSensor != NULL)
 {
  Sensor* sensor = getOccSensor();
  //AbstractSensor* abstractSensor = (AbstractSensor*)sensor;
  sensor->addPropertyChangeListener((PropertyChangeListener*)this, namedOccSensor->getName(), "Indicator Turnout Icon");
  //connect(abstractSensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  _status = _pathUtil->setStatus(sensor->getKnownState());
  if (_iconMaps!=NULL)
  {
   displayState(turnoutState());
  }
 }
}

/*public*/ Sensor* IndicatorTurnoutIcon::getOccSensor()
{
 if (namedOccSensor==NULL)
 {
  return NULL;
 }
 return namedOccSensor->getBean();
}
/*public*/ NamedBeanHandle <Sensor*>* IndicatorTurnoutIcon::getNamedOccSensor() { return namedOccSensor; }

/**
 * Attached a named OBlock to display status
 * @param pName Used as a system/user name to lookup the OBlock object
 */
 /*public*/ void IndicatorTurnoutIcon::setOccBlock(QString pName)
{
 if (pName==NULL || pName.trimmed().length()==0)
 {
  setOccBlockHandle(NULL);
  return;
 }

 OBlock* block = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(pName);
 if (block != NULL)
 {
  setOccBlockHandle(new NamedBeanHandle<OBlock*>(pName, block));
 }
 else
 {
  log->error("Detection OBlock '"+pName+"' not available, icon won't see changes");
 }
}

/*public*/ void IndicatorTurnoutIcon::setOccBlockHandle(NamedBeanHandle<OBlock*>* blockHandle)
{
 if (namedOccBlock != NULL)
 {
     OBlock* block = getOccBlock();
  getOccBlock()->removePropertyChangeListener((PropertyChangeListener*)this);
  //disconnect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 namedOccBlock = blockHandle;
 if (namedOccBlock != NULL)
 {
  OBlock* block = getOccBlock();
  block->addPropertyChangeListener((PropertyChangeListener*)this, namedOccBlock->getName(), "Indicator Turnout Icon");
  //connect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  setStatus(block, block->getState());
  if (_iconMaps!=NULL)
  {
   displayState(turnoutState());
  }
  setToolTip((block->getDescription()/*, 0, 0*/));
 }
}
/*public*/ OBlock* IndicatorTurnoutIcon::getOccBlock()
{
 if (namedOccBlock==NULL)
 {
  return NULL;
 }
 return namedOccBlock->getBean();
}
/*public*/ NamedBeanHandle <OBlock*>* IndicatorTurnoutIcon::getNamedOccBlock() { return namedOccBlock; }

/*public*/ void IndicatorTurnoutIcon::setShowTrain(bool set) {
    _pathUtil->setShowTrain(set);
}
/*public*/ bool IndicatorTurnoutIcon::showTrain() {
    return _pathUtil->showTrain();
}
/*public*/ QStringList IndicatorTurnoutIcon::getPaths() {
    return _pathUtil->getPaths();
}
/*public*/ void IndicatorTurnoutIcon::setPaths(QStringList paths) {
    _pathUtil->setPaths(paths);
}
/*public*/ void IndicatorTurnoutIcon::addPath(QString path) {
    _pathUtil->addPath(path);
}
/*public*/ void IndicatorTurnoutIcon::removePath(QString path) {
    _pathUtil->removePath(path);
}

/*public*/ void IndicatorTurnoutIcon::setStatus(int state) {
    _pathUtil->setStatus(state);
}

/**
* Place icon by its localized bean state name
* @param status - the track condition of the icon
* @param stateName - NamedBean name of turnout state
* @param icon - icon corresponding to status and state
*/
/*public*/ void IndicatorTurnoutIcon::setIcon(QString status,QString stateName, NamedIcon* icon)
{
 if (log->isDebugEnabled()) log->debug("setIcon for status \""+status+"\", stateName= \"" +stateName+" icom= "+icon->getURL());
//                                            ") state= "+_name2stateMap.get(stateName)+
//                                            " icon: w= "+icon.getIconWidth()+" h= "+icon.getIconHeight());
 if (_iconMaps==NULL)
 {
  initMaps();
 }
 _iconMaps->value(status)->insert(_name2stateMap->value(stateName), icon);
 PositionableIcon::setIcon(_iconMaps->value("ClearTrack")->value(_name2stateMap->value("BeanStateInconsistent")));
}

/**
* Get clear icon by its localized bean state name
*/
/*public*/ NamedIcon* IndicatorTurnoutIcon::getIcon(QString status, int state)
{
    log->debug("getIcon: status= "+status+", state= "+QString::number(state));
    QHash<int, NamedIcon*>* map = _iconMaps->value(status);
    if (map==NULL) { return NULL; }
    return map->value((state));
}

/*public*/ QString IndicatorTurnoutIcon::getStateName(int state) {
    return _state2nameMap->value(state);
}

/*public*/ QString IndicatorTurnoutIcon::getStatus() {
    return _status;
}

/*public*/ int IndicatorTurnoutIcon::maxHeight()
{
 int max = 0;
 if (_iconMaps!=NULL)
 {
  QListIterator<QHash<int, NamedIcon*>*> it(_iconMaps->values());
  while (it.hasNext())
  {
   QListIterator<NamedIcon*> iter(it.next()->values());
   while (iter.hasNext())
   {
    max = qMax(iter.next()->getIconHeight(), max);
   }
  }
 }
 return max;
}
/*public*/ int IndicatorTurnoutIcon::maxWidth()
{
 int max = 0;
 if (_iconMaps!=NULL)
 {
  QListIterator<QHash<int, NamedIcon*>*> it(_iconMaps->values());
   while (it.hasNext())
   {
    QListIterator<NamedIcon*> iter(it.next()->values());
    while (iter.hasNext())
   {
    max = qMax(iter.next()->getIconWidth(), max);
   }
  }
 }
 return max;
}

/******** popup AbstractAction.actionPerformed method overrides *********/

/*protected*/ void IndicatorTurnoutIcon::rotateOrthogonal()
{
 if (_iconMaps!=NULL)
 {
  QListIterator<QHash<int, NamedIcon*>*> it(_iconMaps->values());
  while (it.hasNext())
  {
   QListIterator< NamedIcon*> iter(it.next()->values());
   while (iter.hasNext())
   {
    NamedIcon* icon = iter.next();
    icon->setRotation(icon->getRotation()+1, this);
   }
  }
 }
 displayState(turnoutState());
}

/*public*/ void IndicatorTurnoutIcon::setScale(double s)
{
 if (_iconMaps!=NULL)
 {
  QListIterator<QHash<int, NamedIcon*>*> it(_iconMaps->values());
  while (it.hasNext())
  {
   QListIterator<NamedIcon*> iter(it.next()->values());
   while (iter.hasNext())
   {
    iter.next()->scale(s, this);
   }
  }
 }
 displayState(turnoutState());
}

/*public*/ void IndicatorTurnoutIcon::rotate(int deg)
{
 if (_iconMaps!=NULL)
 {
  QListIterator<QHash<int, NamedIcon*>*> it(_iconMaps->values());
  while (it.hasNext())
  {
   QListIterator<NamedIcon*> iter(it.next()->values());
   while (iter.hasNext())
   {
    iter.next()->rotate(deg, this);
   }
  }
 }
 displayState(turnoutState());
}

/**
 * Drive the current state of the display from the state of the turnout and status of track.
 */
/*public*/ void IndicatorTurnoutIcon::displayState(int state)
{
 if (getNamedTurnout() == NULL)
 {
  log->debug("Display state "+QString::number(state)+", disconnected");
 }
 else
 {
  if (_status!=NULL && _iconMaps!=NULL)
  {
   NamedIcon* icon = getIcon(_status, state);
   if (icon!=NULL)
   {
    PositionableLabel::setIcon(icon);
   }
  }
 }
 TurnoutIcon::displayState(state);
 updateSize();
// if(_editor != NULL)
//  _editor->addToTarget(this);
 updateScene();
 _itemGroup->setName(getGroupName());
}

/*public*/ QString IndicatorTurnoutIcon::getNameString()
{
 QString str = "";
 if (namedOccBlock!=NULL)
 {
  str = " in "+namedOccBlock->getBean()->getDisplayName();
 }
 else if (namedOccSensor!=NULL)
 {
  str = " on "+namedOccSensor->getBean()->getDisplayName();
 }
 return "ITrack "+TurnoutIcon::getNameString()+str;
}

// update icon as state of turnout changes and status of track changes
// Override
/*public*/ void IndicatorTurnoutIcon::propertyChange(PropertyChangeEvent* evt)
{
 if (log->isDebugEnabled())
  log->debug("property change: "+getNameString()+" property \""+evt->getPropertyName()+"\"= "
                +evt->getNewValue().toString()+" from "+evt->getSource()->metaObject()->className());

 QObject* source = evt->getSource();
 //if (source instanceof Turnout)
 if(qobject_cast<Turnout*>(source) != NULL)
 {
  TurnoutIcon::propertyChange(evt);
 }
 //else if (source instanceof OBlock)
 else if(qobject_cast<OBlock*>(source) != NULL)
 {
  if ("state"==(evt->getPropertyName()) || "path"==(evt->getPropertyName()))
  {
   int now = (evt->getNewValue()).toInt();
   setStatus((OBlock*)source, now);
  }
 }
 //else if (source instanceof Sensor)
 if(qobject_cast<Sensor*>(source) != NULL)
 {
  if (evt->getPropertyName()==("KnownState"))
  {
   int now = evt->getNewValue().toInt();
   if (source==(getOccSensor()))
   {
    _status = _pathUtil->setStatus(now);
   }
  }
 }
 displayState(turnoutState());
}

/*private*/ void IndicatorTurnoutIcon::setStatus(OBlock* block, int state)
{
 _status = _pathUtil->setStatus(block, state);
 _pathUtil->setLocoIcon(block->getValue().toString(), QPoint(((Positionable*)this)->getLocation().x(), ((Positionable*)this)->getLocation().y()), getSize(), _editor);
 if (_status==("DontUseTrack"))
 {
  setControlling(false);
 }
}

/*protected*/ void IndicatorTurnoutIcon::editItem()
{
 makePaletteFrame(tr("Edit %1 Icon").arg("Indicator Turnout"));
 _paletteFrame->setMinimumSize(600,800);
 _TOPanel = new IndicatorTOItemPanel(_paletteFrame, "IndicatorTO", _iconFamily, PickListModel::turnoutPickModelInstance(), _editor);
//    ActionListener updateAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateItem();
//        }
//    };
 ITOUpdateActionListener* updateAction = new ITOUpdateActionListener(this);
 // Convert _iconMaps state (ints) to Palette's bean names
 QMap<QString, QMap<QString, NamedIcon*>*>* iconMaps =
                 new QMap<QString, QMap<QString, NamedIcon*>*>();
 iconMaps->insert("ClearTrack", new QMap <QString, NamedIcon*>());
 iconMaps->insert("OccupiedTrack", new QMap <QString, NamedIcon*>());
 iconMaps->insert("PositionTrack", new QMap <QString, NamedIcon*>());
 iconMaps->insert("AllocatedTrack", new QMap <QString, NamedIcon*>());
 iconMaps->insert("DontUseTrack", new QMap <QString, NamedIcon*>());
 iconMaps->insert("ErrorTrack", new QMap <QString, NamedIcon*>());
 QMapIterator<QString, QHash<int, NamedIcon*>*> it(*_iconMaps);

 while (it.hasNext())
 {
  /*Entry<QString, QHash<int, NamedIcon*>> entry =*/ it.next();
  QMap <QString, NamedIcon*>* clone = iconMaps->value(it.key());
  QHashIterator<int, NamedIcon*> iter(*it.value());
  while (iter.hasNext())
  {
   /*Entry<int, NamedIcon*> ent =*/ iter.next();
   NamedIcon* oldIcon = iter.value();
   NamedIcon* newIcon = cloneIcon(oldIcon, this);
   newIcon->rotate(0, this);
   newIcon->scale(1.0, this);
   newIcon->setRotation(4, this);
   clone->insert(_state2nameMap->value(iter.key()), newIcon);
  }
 }

 _TOPanel->initUpdate(updateAction, iconMaps);
 _TOPanel->setSelection(getTurnout());
 if (namedOccSensor!=NULL)
 {
 _TOPanel->setOccDetector(namedOccSensor->getBean()->getDisplayName());
 }
 if (namedOccBlock!=NULL)
 {
  _TOPanel->setOccDetector(namedOccBlock->getBean()->getDisplayName());
    }
 _TOPanel->setShowTrainName(_pathUtil->showTrain());
 _TOPanel->setPaths(_pathUtil->getPaths());
 //((QVBoxLayout*)_paletteFrame->layout())->addWidget(_TOPanel);
 if(_paletteFrame->centralWidget() == NULL)
 {
  QWidget* centralWidget = new QWidget();
  centralWidget->setLayout(new QVBoxLayout);
  _paletteFrame->setCentralWidget(centralWidget);
 }
 QScrollArea* scrollArea = new QScrollArea;\
 scrollArea->setWidget(_TOPanel);
 scrollArea->setWidgetResizable(true);
 _paletteFrame->centralWidget()->layout()->addWidget(scrollArea);
 _paletteFrame->pack();
 _paletteFrame->setVisible(true);
 QTimer::singleShot(50,_paletteFrame, SLOT(pack()));
}

ITOUpdateActionListener::ITOUpdateActionListener(IndicatorTurnoutIcon *parent)
{
 this->parent = parent;
}
void ITOUpdateActionListener::actionPerformed(JActionEvent */*e*/)
{
 parent->updateItem();
}

void IndicatorTurnoutIcon::updateItem()
{
 if (log->isDebugEnabled()) log->debug("updateItem: "+getNameString()+" family= "+_TOPanel->getFamilyName());
 setTurnout(_TOPanel->getTableSelection()->getSystemName());
 setOccSensor(_TOPanel->getOccSensor());
 setOccBlock(_TOPanel->getOccBlock());
 _pathUtil->setShowTrain(_TOPanel->getShowTrainName());
 _iconFamily = _TOPanel->getFamilyName();
 _pathUtil->setPaths(_TOPanel->getPaths());
 QMap<QString, QMap<QString, NamedIcon*>*>* iconMap = _TOPanel->getIconMaps();
#if 1
 if (iconMap!=NULL)
 {
  QMapIterator<QString, QMap<QString, NamedIcon*>*> it(* iconMap);
  while (it.hasNext())
  {
   /*Entry<String, QHash<QString, NamedIcon*>*> entry =*/ it.next();
   QString status = it.key();
   QHash <int, NamedIcon*>* oldMap = _iconMaps->value(it.key());
   QMapIterator<QString, NamedIcon*> iter(*it.value() );
   while (iter.hasNext())
   {
    /*Entry<String, NamedIcon> ent =*/ iter.next();
    if (log->isDebugEnabled()) log->debug("key= "+iter.key());
    NamedIcon* newIcon = cloneIcon(iter.value(), this);
    NamedIcon* oldIcon = oldMap->value(_name2stateMap->value(iter.key()));
    newIcon->setLoad(oldIcon->getDegrees(), oldIcon->getScale(), this);
    newIcon->setRotation(oldIcon->getRotation(), this);
    setIcon(status, iter.key(), newIcon);
   }
  }
 }   // otherwise retain current map
#endif
//        jmri.jmrit.catalog->ImageIndexEditor.checkImageIndex();
 _paletteFrame->dispose();
 _paletteFrame = NULL;
 _TOPanel->dispose();
 _TOPanel = NULL;
 displayState(turnoutState());
}

/*public*/ void IndicatorTurnoutIcon::dispose() {
    if (namedOccSensor != NULL) {
        getOccSensor()->removePropertyChangeListener((PropertyChangeListener*)this);
    }
    namedOccSensor = NULL;
    namedOccSensor = NULL;
    TurnoutIcon::dispose();
}

