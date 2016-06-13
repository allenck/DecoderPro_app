#include "signalmastrepeater.h"
#include "instancemanager.h"
#include "signalmast.h"
#include "signalmastmanager.h"
#include "defaultsignalmastmanager.h"
#include "namedbean.h"
#include "abstractsignalmast.h"
#include "signalmastrepeater.h"

//SignalMastRepeater::SignalMastRepeater(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * A simple class that repeaters the state of one SignalMast
 * to another
 *
 * @author	Kevin Dickerson Copyright (C) 2012
 *
 * @version     $Revision$
 */
//import java.beans.PropertyChangeListener;
//import java.beans.PropertyChangeEvent;
//import jmri.SignalMast;
//import jmri.NamedBeanHandle;

///*public*/ class SignalMastRepeater {



/*public*/ SignalMastRepeater::SignalMastRepeater(SignalMast* master, SignalMast* slave, QObject *parent) : QObject(parent)
{
 init();
 _master = nbhm->getNamedBeanHandle(master->getDisplayName(), master);
 _slave = nbhm->getNamedBeanHandle(slave->getDisplayName(), slave);
}

/*public*/ SignalMastRepeater::SignalMastRepeater(QString master, QString slave, QObject *parent) : QObject(parent)
{
 init();
 SignalMast* masterMast = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getSignalMast(master);
 _master = nbhm->getNamedBeanHandle(master, masterMast);
 SignalMast* slaveMast = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->getSignalMast(slave);
 _slave = nbhm->getNamedBeanHandle(slave, slaveMast);
}
void SignalMastRepeater::init()
{
 log = new Logger("SignalMastRepeater");
 _enabled = true;
 _direction = BOTHWAY;
 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
 disposed = false;
}
/*public*/ SignalMast* SignalMastRepeater::getMasterMast(){
    return _master->getBean();
}

/*public*/ SignalMast* SignalMastRepeater::getSlaveMast(){
    return _slave->getBean();
}

/*public*/ QString SignalMastRepeater::getMasterMastName(){
    return _master->getName();
}

/*public*/ QString SignalMastRepeater::getSlaveMastName(){
    return _slave->getName();
}

/*public*/ int SignalMastRepeater::getDirection(){
    return _direction;
}

/*public*/ void SignalMastRepeater::setDirection(int dir){
    if(dir==_direction)
        return;
    _direction = dir;
    //getMasterMast().removePropertyChangeListener(mastListener);
    SignalMast* masterMast = getMasterMast();
    disconnect(masterMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    //getSlaveMast().removePropertyChangeListener(mastListener);
    SignalMast* slaveMast = getSlaveMast();
    disconnect(slaveMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));    initialise();
}

/*public*/ void SignalMastRepeater::setEnabled(bool en){
    if(_enabled == en){
        return;
    }
    _enabled = en;
    //getMasterMast().removePropertyChangeListener(mastListener);
    SignalMast* masterMast = getMasterMast();
    disconnect(masterMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    //getSlaveMast().removePropertyChangeListener(mastListener);
    SignalMast* slaveMast = getSlaveMast();
    disconnect(slaveMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));    initialise();
}

/*public*/ bool SignalMastRepeater::getEnabled(){
    return _enabled;
}

/*public*/ void SignalMastRepeater::initialise()
{
 if(disposed){
        log->error("Trying to initialise a repeater that has already been disposed");
 }
 if(!_enabled)
  return;
 //getMasterMast().removePropertyChangeListener(mastListener);
 SignalMast* masterMast = getMasterMast();
 disconnect(masterMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 //getSlaveMast().removePropertyChangeListener(mastListener);
 SignalMast* slaveMast = getSlaveMast();
 disconnect(slaveMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 switch(_direction)
 {
 case MASTERTOSLAVE :
  //getMasterMast().addPropertyChangeListener(mastListener);
  connect(masterMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateStatus(masterMast, slaveMast);
  break;
 case SLAVETOMASTER :
  //getSlaveMast().addPropertyChangeListener(mastListener);
  connect(slaveMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateStatus(slaveMast, masterMast);
  break;
 default :
  //getMasterMast().addPropertyChangeListener(mastListener);
  connect(masterMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  //getSlaveMast().addPropertyChangeListener(mastListener);
  connect(slaveMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateStatus(getMasterMast(), getSlaveMast());
 }
}

//PropertyChangeListener mastListener = new PropertyChangeListener() {
    /*public*/ void SignalMastRepeater::propertyChange(PropertyChangeEvent* e) { // SLOT[]
        if(disposed)
            return;
        if(e->getSource()==getMasterMast())
            updateStatus(getMasterMast(), getSlaveMast());
        else
            updateStatus(getSlaveMast(), getMasterMast());
    }
//};

void SignalMastRepeater::updateStatus(SignalMast* mastFrom, SignalMast* mastTo)
{
 if(log->isDebugEnabled()) log->debug("Updating from mast " + ((AbstractSignalMast*)mastFrom)->getDisplayName() + ":" + ((AbstractSignalMast*)mastFrom)->getAspect() + " to mast " + ((AbstractSignalMast*)mastTo)->getDisplayName());
 if(((AbstractSignalMast*)mastFrom)->getAspect()!="")
        ((AbstractSignalMast*)mastTo)->setAspect(((AbstractSignalMast*)mastFrom)->getAspect());
}


/*public*/ void SignalMastRepeater::dispose()
{
 disposed = true;
 //getMasterMast().removePropertyChangeListener(mastListener);
 SignalMast* masterMast = getMasterMast();
 disconnect(masterMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 //getSlaveMast().removePropertyChangeListener(mastListener);
 SignalMast* slaveMast = getSlaveMast();
 disconnect(slaveMast, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 _master = NULL;
_slave = NULL;
}
