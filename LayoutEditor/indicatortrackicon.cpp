#include "indicatortrackicon.h"
#include "indicatoritempanel.h"
#include "sensor.h"
#include "oblock.h"
#include "instancemanager.h"
#include "indicatortrackpaths.h"
#include "proxysensormanager.h"
#include "oblockmanager.h"
#include "namedicon.h"
#include <QMenu>
#include <QLayout>
#include "positionablelabel.h"
#include "abstractsensor.h"
#include "editor.h"

//IndicatorTrackIcon::IndicatorTrackIcon(QObject *parent) :
//    PositionableIcon(parent)
//{
//}
/**
 * An icon to display the status of a track segment in a block
 * <P>
 * This responds to the following conditions:
 *  1. KnownState of an occupancy sensor of the block where the track segment appears
 *  2. Allocation of a route by a Warrant where the track segment appears
 *  3. Current position of a train being run under a Warrant where the track segment appears in a block of the route
 *  4. Out of Service for a block that cannot or should not be used
 *  5. An error state of the block where the track segment appears (short/no power etc.)
 * <P>
 * A click on the icon does not change any of the above conditions..
 *<P>
 * @author Pete Cressman  Copyright (c) 2010
 * @version $Revision: 22576 $
 */

///*public*/ class IndicatorTrackIcon extends PositionableIcon
//                        implements java.beans.PropertyChangeListener, IndicatorTrack {



/*public*/ IndicatorTrackIcon::IndicatorTrackIcon(Editor* editor, QObject *parent) : PositionableIcon(editor,(Positionable*)parent)
{
 // super ctor call to make sure this is an icon label
 //super(editor);
 log = new Logger("IndicatorTrackIcon");
 namedOccSensor = NULL;
 namedOccBlock = NULL;

 _pathUtil = new IndicatorTrackPaths();
 _status = "ClearTrack";
 _iconMap = new QMap<QString, NamedIcon*>();
}

/*public*/ Positionable* IndicatorTrackIcon::deepClone() {
    IndicatorTrackIcon* pos = new IndicatorTrackIcon(_editor);
    _namedIcon = _iconMap->value(getStatus());
    return finishClone((Positionable*)pos);
}

/*public*/ Positionable* IndicatorTrackIcon::finishClone(Positionable* p) {
    IndicatorTrackIcon* pos = (IndicatorTrackIcon*)p;
    pos->setOccSensorHandle(namedOccSensor);
    pos->setOccBlockHandle(namedOccBlock);
    pos->_iconMap = cloneMap(_iconMap, pos);
    pos->_pathUtil = _pathUtil->deepClone();
    pos->_iconFamily = _iconFamily;
    return PositionableIcon::finishClone((Positionable*)pos);
}

/*public*/ QMap<QString, NamedIcon*>* IndicatorTrackIcon::getIconMap() {
    return cloneMap(_iconMap, this);
}

/**
 * Attached a named sensor to display status
 * @param pName Used as a system/user name to lookup the sensor object
 */
 /*public*/ void IndicatorTrackIcon::setOccSensor(QString pName)
{
     if (pName==NULL || pName.trimmed().length()==0) {
         setOccSensorHandle(NULL);
         return;
     }
     if (InstanceManager::sensorManagerInstance()!=NULL) {
         Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(pName);
         if (sensor != NULL) {
             setOccSensorHandle(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor));
         } else {
             log->error("Occupancy Sensor '"+pName+"' not available, icon won't see changes");
         }
     } else {
         log->error("No SensorManager for this protocol, block icons won't see changes");
     }
 }
 /*public*/ void IndicatorTrackIcon::setOccSensorHandle(NamedBeanHandle<Sensor*>* senHandle)
{
 if (namedOccSensor != NULL)
 {
  AbstractSensor* sensor = (AbstractSensor*)getOccSensor();
  sensor->removePropertyChangeListener((PropertyChangeListener*)this);
  //disconnect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 namedOccSensor = senHandle;
 if (namedOccSensor != NULL)
 {
  if (_iconMap==NULL)
  {
  _iconMap = new QMap<QString, NamedIcon*>();
  }
  AbstractSensor* sensor = (AbstractSensor*)getOccSensor();
  sensor->addPropertyChangeListener((PropertyChangeListener*)this, namedOccSensor->getName(), "Indicator Track");
  //connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   _status = _pathUtil->setStatus(sensor->getKnownState());
   displayState(_status);
  }
 }
 /*public*/ Sensor* IndicatorTrackIcon::getOccSensor() {
     if (namedOccSensor==NULL) {
         return NULL;
     }
     return namedOccSensor->getBean();
 }
 /*public*/ NamedBeanHandle <Sensor*>* IndicatorTrackIcon::getNamedOccSensor() { return namedOccSensor; }

/**
 * Attached a named OBlock to display status
 * @param pName Used as a system/user name to lookup the OBlock object
 */
 /*public*/ void IndicatorTrackIcon::setOccBlock(QString pName) {
     if (pName==NULL || pName.trimmed().length()==0) {
         setOccBlockHandle(NULL);
         return;
     }
     OBlock* block = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(pName);
     if (block != NULL) {
         setOccBlockHandle(new NamedBeanHandle<OBlock*>(pName, block));
     } else {
         log->error("Detection OBlock '"+pName+"' not available, icon won't see changes");
     }
 }
/*public*/ void IndicatorTrackIcon::setOccBlockHandle(NamedBeanHandle<OBlock*>* blockHandle)
{
 OBlock* block = getOccBlock();
 if (namedOccBlock != NULL)
 {
  getOccBlock()->removePropertyChangeListener((PropertyChangeListener*)this);
  //disconnect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 namedOccBlock = blockHandle;
 if (namedOccBlock != NULL)
 {
  if (_iconMap==NULL)
  {
   _iconMap = new QMap<QString, NamedIcon*>();
  }
  block = getOccBlock();
  block->addPropertyChangeListener((PropertyChangeListener*)this, namedOccBlock->getName(), "Indicator Track");
  //connect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  setStatus(block, block->getState());
  displayState(_status);
  //setTooltip(new ToolTip(block->getDescription(), 0, 0));
  setToolTip(block->getDescription());
 }
}
/*public*/ OBlock* IndicatorTrackIcon::getOccBlock() {
    if (namedOccBlock==NULL) {
        return NULL;
    }
    return namedOccBlock->getBean();
}
/*public*/ NamedBeanHandle <OBlock*>* IndicatorTrackIcon::getNamedOccBlock() { return namedOccBlock; }

/*public*/ void IndicatorTrackIcon::setShowTrain(bool set) {
    _pathUtil->setShowTrain(set);
}
/*public*/ bool IndicatorTrackIcon::showTrain() {
    return _pathUtil->showTrain();
}
/*public*/ QStringList IndicatorTrackIcon::getPaths() {
    return _pathUtil->getPaths();
}
/*public*/ void IndicatorTrackIcon::setPaths(QStringList paths) {
    _pathUtil->setPaths(paths);
}
/*public*/ void IndicatorTrackIcon::addPath(QString path) {
    _pathUtil->addPath(path);
}
/*public*/ void IndicatorTrackIcon::removePath(QString path) {
    _pathUtil->removePath(path);
}
/*public*/ void IndicatorTrackIcon::setStatus(int state) {
    _pathUtil->setStatus(state);
}

/**
* Place icon by its bean state name
*/
/*public*/ void IndicatorTrackIcon::setIcon(QString name, NamedIcon* icon) {
    if (log->isDebugEnabled()) log->debug("set \""+name+"\" icon= "+icon->getName());
    _iconMap->insert(name, icon);
    JLabel::setIcon(_iconMap->value(_status));
}

/*public*/ QString IndicatorTrackIcon::getStatus() {
    return _status;
}

/*public*/ void IndicatorTrackIcon::propertyChange(PropertyChangeEvent* evt)
{
 if (log->isDebugEnabled())
  log->debug("property change: " + getNameString() + " property " + evt->getPropertyName() + " is now "
                + evt->getNewValue().toString()+" from "+evt->getSource()->metaObject()->className());

 QObject* source = evt->getSource();
 //if (source instanceof OBlock)
 if(qobject_cast<OBlock*>(source)!=NULL)
 {
  if ("state"==(evt->getPropertyName()) || "path"==(evt->getPropertyName()))
  {
   int now = (evt->getNewValue()).toInt();
   setStatus((OBlock*)source, now);
  }
 }
 //else if (source instanceof Sensor)
 else if(qobject_cast<Sensor*>(source)!=NULL)
 {
  if (evt->getPropertyName()==("KnownState"))
  {
   int now = (evt->getNewValue()).toInt();
   if (source==(getOccSensor()))
   {
    _status = _pathUtil->setStatus(now);
   }
  }
 }
 displayState(_status);
}

/*private*/ void IndicatorTrackIcon::setStatus(OBlock* block, int state)
{
 _status = _pathUtil->setStatus(block, state);
 _pathUtil->setLocoIcon(block->getValue().toString(), /*getLocation()*/QPoint(((Positionable*)this)->getLocation().x(), ((Positionable*)this)->getLocation().y()), getSize(), _editor);
 if (_status==("DontUseTrack"))
 {
  setControlling(false);
 }
}

/*public*/ QString IndicatorTrackIcon::getNameString()
{
 QString str = "";
 if (namedOccBlock!=NULL)
 {
  str = "in "+namedOccBlock->getBean()->getDisplayName();
 }
 else if (namedOccSensor!=NULL)
 {
  str = "on "+namedOccSensor->getBean()->getDisplayName();
 }
 return "ITrack "+str;
}

/**
 * Pop-up displays unique attributes
 */
/*public*/ bool IndicatorTrackIcon::showPopUp(QMenu* /*popup*/) {
    return false;
}

/**
 * Drive the current state of the display from the state of the turnout.
 */
void IndicatorTrackIcon::displayState(QString status)
{
 if (log->isDebugEnabled()) log->debug(getNameString() +" displayStatus "+_status);
 _namedIcon = getIcon(status);
 if (_namedIcon!=NULL)
 {
  PositionableIcon::setIcon(_namedIcon);
 }
 updateSize();
 //_editor->addToTarget(this);
 updateScene();
}

/*public*/ bool IndicatorTrackIcon::setEditItemMenu(QMenu* popup)
{
 QString txt = tr("Edit %1 Icon").arg(tr("Indicator Track"));
//    popup.add(new javax.swing.AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editItem();
//            }
//        });
 QAction* act = new QAction(txt, this);
 popup->addAction(act);
 connect(act, SIGNAL(triggered()), this, SLOT(editItem()));
 return true;
}

/*protected*/ void IndicatorTrackIcon::editItem()
{
 makePaletteFrame(tr("Edit %1 Icon").arg(tr("Indicator Track")));

 _trackPanel = new IndicatorItemPanel(_paletteFrame, "IndicatorTrack", _iconFamily, _editor, this);

//    ActionListener updateAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            updateItem();
//        }
//    };
 ItiActionListener* updateAction = new ItiActionListener(this);

 // duplicate _iconMap map with unscaled and unrotated icons
 QMap<QString, NamedIcon*>* map = new QMap<QString, NamedIcon*>();
 //Iterator<Entry<QString, NamedIcon*>> it = _iconMap.entrySet().iterator();
 QMapIterator<QString, NamedIcon*> it(*_iconMap);
 while (it.hasNext())
 {
  it.next();
  //Entry<QString, NamedIcon*> entry = it.next();
  NamedIcon* oldIcon = it.value();
  NamedIcon* newIcon = cloneIcon(oldIcon, this);
  newIcon->rotate(0, this);
  newIcon->scale(1.0, this);
  newIcon->setRotation(4, this);
  map->insert(it.key(), newIcon);
 }
 _trackPanel->init(updateAction, map);
 if (namedOccSensor!=NULL)
 {
  _trackPanel->setOccDetector(namedOccSensor->getBean()->getDisplayName());
 }
 if (namedOccBlock!=NULL)
 {
  _trackPanel->setOccDetector(namedOccBlock->getBean()->getDisplayName());
 }
 _trackPanel->setShowTrainName(_pathUtil->showTrain());
 _trackPanel->setPaths(_pathUtil->getPaths());
 //_paletteFrame->layout()->addWidget(_trackPanel);
 _paletteFrame->setCentralWidget(_trackPanel);

//    _paletteFrame->setLocationRelativeTo(this);
 _paletteFrame->toFront();
 _paletteFrame->setVisible(true);
 _paletteFrame->setMinimumSize(300,400);
 _paletteFrame->resize(400,600);
 _paletteFrame->pack();
 QTimer::singleShot(50, _paletteFrame, SLOT(pack()));
}

ItiActionListener::ItiActionListener(IndicatorTrackIcon *self)
{
 this->self = self;
}
void ItiActionListener::actionPerformed(JActionEvent* /*a*/)
{
 self->updateItem();
}

void IndicatorTrackIcon::updateItem() {
    setOccSensor(_trackPanel->getOccSensor());
    setOccBlock(_trackPanel->getOccBlock());
    _pathUtil->setShowTrain(_trackPanel->getShowTrainName());
    _iconFamily = _trackPanel->getFamilyName();
    _pathUtil->setPaths(_trackPanel->getPaths());
    QMap<QString, NamedIcon*>* iconMap = _trackPanel->getIconMap();
    if (iconMap!=NULL) {
        QMap<QString, NamedIcon*>* oldMap = cloneMap(_iconMap, this);
        //Iterator<Entry<QString, NamedIcon*>> it = iconMap.entrySet().iterator();
        QMapIterator<QString, NamedIcon*> it(*_iconMap);
        while (it.hasNext())
        {
            it.next();
            //Entry<QString, NamedIcon*> entry = it.next();
            if (log->isDebugEnabled()) log->debug("key= "+it.key());
            NamedIcon* newIcon = it.value();
            NamedIcon* oldIcon = oldMap->value(it.key());
            newIcon->setLoad(oldIcon->getDegrees(), oldIcon->getScale(), this);
            newIcon->setRotation(oldIcon->getRotation(), this);
            setIcon(it.key(), newIcon);
        }
    }   // otherwise retain current map
//        jmri.jmrit.catalog->ImageIndexEditor.checkImageIndex();
    _paletteFrame->dispose();
    _paletteFrame = NULL;
    _trackPanel->dispose();
    _trackPanel = NULL;
    displayState(_status);
}

/*public*/ void IndicatorTrackIcon::dispose() {
    if (namedOccSensor != NULL) {
//        getOccSensor()->removePropertyChangeListener(this);
    }
    namedOccSensor = NULL;

    if (namedOccBlock != NULL) {
//        getOccBlock().removePropertyChangeListener(this);
    }
    namedOccBlock = NULL;

    _iconMap = NULL;
    PositionableIcon::dispose();
}
