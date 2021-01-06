#include "blockbosslogic.h"
#include "namedbeanhandlemanager.h"
#include "instancemanager.h"
#include "proxysensormanager.h"
#include "namedbeanhandle.h"
#include "abstractsignalhead.h"
#include "defaultsignalhead.h"
#include "configxmlmanager.h"
#include "abstractsensor.h"
#include "abstractsignalheadmanager.h"
#include "signalhead.h"

//BlockBossLogic::BlockBossLogic(QObject *parent) :
//    Siglet(parent)
//{
//}
/*static*/  QHash<QString,BlockBossLogic*>* BlockBossLogic::umap = NULL;
/*static*/ QHash<QString,BlockBossLogic*>* BlockBossLogic::smap = NULL;

/**
 * Drives the "simple signal" logic for one signal.
 *<P>
 * Signals "protect" by telling the engineer
 * about the conditions ahead.  The engineer
 * controls the speed of the train based on
 * what the signals show, and the signals in turn
 * react to whether the track ahead is occupied,
 * what signals further down the line show, etc.
 * <P>
 * There are four situations that this logic can handle:
 * <OL>
 * <LI>SINGLEBLOCK - A simple block, without a turnout.
 *<P>In this case, there is only a single
 * set of sensors and a single
 * next signal to protect.
 * <LI>TRAILINGMAIN - This signal is protecting a trailing point turnout,
 * which can only be passed when the turnout is closed. It can also be used
 * for the upper head of a two head signal on the facing end of the turnout.
 *<P>In this case, the signal is forced red if the specified turnout is
 * THROWN.  When the turnout is CLOSED, there is a single
 * set of sensors and next signal(s) to protect.
 * <LI>TRAILINGDIVERGING - This signal is protecting a trailing point turnout,
 * which can only be passed when the turnout is thrown. It can also be used
 * for the lower head of a two head signal on the facing end of the turnout.
 *<P>In this case, the signal is forced red if the specified turnout is
 * CLOSED.  When the turnout is THROWN, there is a single
 * set of sensors and next signal(s) to protect.
 * <LI>FACING - This single head signal protects a facing point turnout, which
 * may therefore have two next signals and two sets of next sensors for the
 * closed and thrown states of the turnout.
 *<P>If the turnout is THROWN, one set of sensors and next signal(s)
 * is protected.  If the turnout is CLOSED, another set of sensors and next signal(s)
 * is protected.
 * </OL><P>
 * Note that these four possibilities logically require that certain
 * information be configured consistently; e.g. not specifying a turnout
 * in TRAILINGMAIN doesn't make any sense. That's not enforced explicitly,
 * but violating it can result in confusing behavior.
 *
 * <P>
 * The protected sensors should cover the track to the next signal.
 * If any of the protected sensors show ACTIVE, the signal will be dropped to red.
 * Normally, the protected sensors cover the occupancy of the track to the next signal.
 * In this case, the signal will show red to prevent trains from entering
 * an occupied stretch of track (often called a "block").
 * But the actual source of the sensors can be anything useful, for example
 * a microswitch on a local turnout, etc.
 * <P>
 * There are several varients to how a next signal is protected. In the
 * simplest form, the controlled signal provides a warning to the engineer
 * of what the signal being protected will show when it becomes visible:
 * <UL>
 *<LI>If the next signal is red, the engineer needs to be told to slow down;
 * this signal will be set to yellow.
 *<LI>If the next signal is green, the engineer can proceed at track speed;
 * this signal will be set to green.
 *</UL>
 * If the next signal is yellow, there are two possible varients that can be
 * configured:
 * <UL>
 * <LI>For the common "three-aspect" signaling system, an engineer doesn't
 * need any warning before a yellow signal.  In this case, this signal
 * is set to green when the protected signal is yellow.
 * <LI>For lines where track speed is very fast or braking distances are
 * very long, it can be useful to give engineers warning that the
 * next signal is yellow (and the one after that is red) so that
 * slowing the train can start early.  Usually flashing yellow preceeds
 * the yellow signal, and the system is called "four-aspect" signaling.
 *</UL>
 *
 *<P>
 * In some cases, you want a signal to show <i>exactly</I> what the next
 * signal shows, instead of one speed faster.  E.g. if the (protected) next
 * signal is red, this one should be red, instead of yellow.
 * In this case, this signal is called a "distant signal", as it
 * provides a "distant" view of the protected signal's appearance.  Note
 * that when in this mode, this signal still protects the interveneing track, etc.
 * <P>
 * The "hold" unbound parameter can be used to set this
 * logic to show red, regardless of input.  That's intended for
 * use with CTC logic, etc.
 * <P>
 * "Approach lit" signaling sets the signal head to dark (off) unless the
 * specified sensor(s) are ACTIVE.  Normally, those sensors are
 * in front  of (before) the signal head. The signal heads then only light
 * when a train is approaching.  This is used to preserve bulbs and batteries
 * (and sometimes to reduce engineer workload) on prototype railroads, but is
 * uncommon on model railroads; once the layout owner has gone to the trouble
 * and expense of installing signals, he usually wants them lit up.
 * <P>
 * Two signal heads can be protected.  For example, if the next signal
 * has two heads to control travel onto a main track or siding, then both
 * heads should be provided here.  The <i>faster</i> signal aspect will control
 * the appearance of this head.  For example, if the next signal is showing a
 * green head and a red head, this signal will be green, because the
 * train will be able to proceed at track speed when it reaches that next
 * signal (along the track with the green signal).
 *
 * @author	Bob Jacobsen    Copyright (C) 2003, 2005
 * @version     $Revision: 18058 $
 *
 * Revisions to add facing point sensors, approach lighting, and check box
 * to limit speed. Dick Bronosn (RJB) 2006
 */

// /*public*/ class BlockBossLogic extends Siglet {

/**
 * Create a default object, without contents.
 */
/*public*/ BlockBossLogic::BlockBossLogic(QObject *parent) : Siglet(parent)
{
 setObjectName("BlockBossLogic");
 setProperty("JavaClassName", "jmri.jmrit.blockboss.BlockBossLogic");

 mode = 0;
 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
 log = new Logger("BlockBossLogic");
 log->setDebugEnabled(true);
 setName("BlockBossLogic");
 mHold = false;
 driveSignal = NULL;
 watchSensor1 = NULL;
 watchSensor2 = NULL;
 watchSensor3 = NULL;
 watchSensor4 = NULL;
 watchSensor5 = NULL;
 watchTurnout = NULL;
 watchedSignal1 = NULL;
 watchedSignal1Alt = NULL;
 watchedSignal2 = NULL;
 watchedSignal2Alt = NULL;
 watchedSensor1 = NULL;
 watchedSensor1Alt = NULL;
 watchedSensor2 = NULL;
 watchedSensor2Alt = NULL;
 approachSensor1 = NULL;

 limitSpeed1 = false;
 limitSpeed2 = false;
 protectWithFlashing = false;
 distantSignal = false;
//    umap = smap = NULL;
}
BlockBossLogic::~BlockBossLogic()
{
 delete log;
}

/**
 * Create an object to drive a specific signal.
 * @param name System or user name of the driven signal.
 */
/*public*/ BlockBossLogic::BlockBossLogic(QString name, QObject *parent) : Siglet(name+tr("BlockBossLogic"), parent)
{
 //super(name+tr("BlockBossLogic"));
 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
 log = new Logger("BlockBossLogic");
 log->setDebugEnabled(true);
 mHold = false;
 this->name = name;
 mHold = false;
 driveSignal = NULL;
 watchSensor1 = NULL;
 watchSensor2 = NULL;
 watchSensor3 = NULL;
 watchSensor4 = NULL;
 watchSensor5 = NULL;
 watchTurnout = NULL;
 watchedSignal1 = NULL;
 watchedSignal1Alt = NULL;
 watchedSignal2 = NULL;
 watchedSignal2Alt = NULL;
 watchedSensor1 = NULL;
 watchedSensor1Alt = NULL;
 watchedSensor2 = NULL;
 watchedSensor2Alt = NULL;
 approachSensor1 = NULL;

 limitSpeed1 = false;
 limitSpeed2 = false;
 protectWithFlashing = false;
 distantSignal = false;
// umap = smap = NULL;

 //if (log->isTraceEnabled()) log->trace("Create BBL "+name);
 ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
 InstanceManager::turnoutManagerInstance()->addVetoableChangeListener((VetoableChangeListener*)this);
 InstanceManager::sensorManagerInstance()->addVetoableChangeListener((VetoableChangeListener*)this);
 SignalHead* driveHead = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
 if (driveHead == nullptr) {
     log->warn(tr("%1 \"%2\" was not found").arg(tr("SignalHead")).arg(name));
     throw IllegalArgumentException("SignalHead \"" + name + "\" does not exist");
 }
 driveSignal = new NamedBeanHandle<SignalHead*> (name, static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name));
 if (driveSignal->getBean() == nullptr) log->warn(tr("Signal_")+name+tr(" was not found!"));
 driveSignal = nbhm->getNamedBeanHandle(name, driveHead);
//          java.util.Objects.requireNonNull(driveSignal, "driveSignal should not have been null");
}

/**
 * The "driven signal" is controlled by this
 * element.
 * @return system name of the driven signal
 */
/*public*/ QString BlockBossLogic::getDrivenSignal() {
    return driveSignal->getName();
}

/*public*/ /*@Nonnull*/ NamedBeanHandle<SignalHead*>* BlockBossLogic::getDrivenSignalNamedBean() {
    //java.util.Objects.requireNonNull(driveSignal, "driveSignal should have been null");
    return driveSignal;
}

/*public*/ void BlockBossLogic::setSensor1(QString name)
{
 if (name == NULL || name==(""))
 {
  watchSensor1 = NULL;
  return;
 }
 watchSensor1 = nbhm->getNamedBeanHandle (name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
 if (watchSensor1 == NULL || watchSensor1->getBean() == NULL) log->warn(tr("Sensor1")+name+tr(" was not found!"));
 else
 {
  AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
  connect(sensor->pcs,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
 }
}

/*public*/ void BlockBossLogic::setSensor2(QString name)
{
 if (name == NULL || name==(""))
 {
  watchSensor2 = NULL;
  return;
 }
 watchSensor2 = nbhm->getNamedBeanHandle (name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
 if (watchSensor2 == NULL || watchSensor2->getBean() == NULL) log->warn(tr("Sensor2")+name+tr(" was not found!"));
 else
 {
  AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
  connect(sensor->pcs,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
 }
}

/*public*/ void BlockBossLogic::setSensor3(QString name)
{
 if (name == NULL || name==(""))
 {
  watchSensor3 = NULL;
  return;
 }
 watchSensor3 = nbhm->getNamedBeanHandle (name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
 if (watchSensor3 == NULL || watchSensor3->getBean() == NULL) log->warn(tr("Sensor3")+name+tr(" was not found!"));
    else
    {
     AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
     connect(sensor->pcs,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
    }
}

/*public*/ void BlockBossLogic::setSensor4(QString name)
{
 if (name == NULL || name==(""))
 {
  watchSensor4 = NULL;
  return;
 }
 watchSensor4 = nbhm->getNamedBeanHandle (name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
 if (watchSensor4 == NULL || watchSensor4->getBean() == NULL) log->warn(tr("Sensor4")+name+tr(" was not found!"));
    else
    {
     AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
     connect(sensor->pcs,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
    }
}

/*public*/ void BlockBossLogic::setSensor5(QString name)
{
 if (name == NULL || name==(""))
 {
  watchSensor5 = NULL;
  return;
 }
 watchSensor5 = nbhm->getNamedBeanHandle (name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
 if (watchSensor5 == NULL || watchSensor5->getBean() == NULL) log->warn(tr("Sensor5")+name+tr(" was not found!"));
 else
    {
     AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
     connect(sensor->pcs,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
    }
}

/**
 * Return the system name of the sensor being monitored
 * @return system name; NULL if no sensor configured
 */
/*public*/ QString BlockBossLogic::getSensor1() {
    if (watchSensor1 == NULL) return NULL;
    return watchSensor1->getName();
}
/*public*/ QString BlockBossLogic::getSensor2() {
    if (watchSensor2 == NULL) return NULL;
    return watchSensor2->getName();
}
/*public*/ QString BlockBossLogic::getSensor3() {
    if (watchSensor3 == NULL) return NULL;
    return watchSensor3->getName();
}
/*public*/ QString BlockBossLogic::getSensor4() {
    if (watchSensor4 == NULL) return NULL;
    return watchSensor4->getName();
}
/*public*/ QString BlockBossLogic::getSensor5() {
    if (watchSensor5 == NULL) return NULL;
    return watchSensor5->getName();
}

/*public*/ void BlockBossLogic::setTurnout(QString name)
{
 if (name == NULL || name==(""))
 {
  watchTurnout = NULL;
  return;
 }
 watchTurnout = nbhm->getNamedBeanHandle(name, ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(name));
 if (watchTurnout == NULL || watchTurnout->getBean() == NULL) log->warn(tr("Turnout_")+name+tr(" was not found!"));
    else
    {
     AbstractTurnout* turnout = (AbstractTurnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(name);
     connect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(turnoutChange(PropertyChangeEvent*)));
    }
}

/**
 * Return the system name of the turnout being monitored
 * @return system name; NULL if no turnout configured
 */
/*public*/ QString BlockBossLogic::getTurnout() {
    if (watchTurnout == NULL) return NULL;
    return watchTurnout->getName();
}
/*public*/ void BlockBossLogic::setMode(int mode) {
    this->mode = mode;
}
/*public*/ int BlockBossLogic::getMode() {
    return mode;
}

/*public*/ void BlockBossLogic::setComment(QString comment) { this->comment = comment; }
/*public*/ QString BlockBossLogic::getComment() { return this->comment; }

/*public*/ void BlockBossLogic::setWatchedSignal1(QString name, bool useFlash)
{
 if (name == NULL || name==(""))
 {
  watchedSignal1 = NULL;
  return;
 }
 watchedSignal1 = new NamedBeanHandle<SignalHead*>(name,  static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name));
 if (watchedSignal1 == NULL || watchedSignal1->getBean() == NULL)
 {
  log->warn(tr("Signal \"")+name+tr("\" was not found!"));
  watchedSignal1 = NULL;
 }
 else
 {
  AbstractSignalHead* head = (AbstractSignalHead*)static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
  connect(head->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(signalChange(PropertyChangeEvent*)));
 }
 protectWithFlashing = useFlash;
}
/**
 * Return the system name of the signal being monitored for first route
 * @return system name; NULL if no primary signal configured
 */
/*public*/ QString BlockBossLogic::getWatchedSignal1()
{
 if (watchedSignal1 == NULL) return NULL;
 return watchedSignal1->getName();
}

/*public*/ void BlockBossLogic::setWatchedSignal1Alt(QString name)
{
 if (name == NULL || name==(""))
 {
  watchedSignal1Alt = NULL;
  return;
 }
 watchedSignal1Alt = new NamedBeanHandle<SignalHead*>(name, static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name));
 if (watchedSignal1Alt == NULL || watchedSignal1Alt->getBean() == NULL) log->warn(tr("Signal")+name+tr(" was not found!"));
}
/**
 * Return the system name of the alternate signal being monitored for first route
 * @return system name; NULL if no signal configured
 */
/*public*/ QString BlockBossLogic::getWatchedSignal1Alt() {
    if (watchedSignal1Alt == NULL) return NULL;
    return watchedSignal1Alt->getName();
}

/*public*/ void BlockBossLogic::setWatchedSignal2(QString name)
{
 if (name == NULL || name==(""))
 {
  watchedSignal2 = NULL;
  return;
 }
 watchedSignal2 = new NamedBeanHandle<SignalHead*>(name, static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name));
 if (watchedSignal2 == NULL || watchedSignal2->getBean() == NULL) log->warn(tr("Signal_")+name+tr("_was not found!"));
}
/**
 * Return the system name of the signal being monitored for the 2nd route
 * @return system name; NULL if no signal configured
 */
/*public*/ QString BlockBossLogic::getWatchedSignal2() {
    if (watchedSignal2 == NULL) return NULL;
    return watchedSignal2->getName();
}

/*public*/ void BlockBossLogic::setWatchedSignal2Alt(QString name)
{
 if (name == NULL || name==(""))
 {
  watchedSignal2Alt = NULL;
  return;
 }
 watchedSignal2Alt = new NamedBeanHandle<SignalHead*>(name, static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name));
 if (watchedSignal2Alt == NULL || watchedSignal2Alt->getBean() == NULL) log->warn(tr("Signal_")+name+tr(" was not found!"));
}
/**
 * Return the system name of the secondary signal being monitored for the 2nd route
 * @return system name; NULL if no secondary signal configured
 */
/*public*/ QString BlockBossLogic::getWatchedSignal2Alt() {
    if (watchedSignal2Alt == NULL) return NULL;
    return watchedSignal2Alt->getName();
}

/*public*/ void BlockBossLogic::setWatchedSensor1(QString name)
{
 if (name == NULL || name==(""))
 {
  watchedSensor1 = NULL;
  return;
 }
 watchedSensor1 = nbhm->getNamedBeanHandle(name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
 if (watchedSensor1 == NULL || watchedSensor1->getBean() == NULL) log->warn(tr("Sensor1 ")+name+tr(" was not found!"));
 else
 {
  AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
  connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
 }
}
void BlockBossLogic::sensorChange(PropertyChangeEvent */*e*/)
{
 //AbstractAutomaton::sensorChange(e);
 setOutput();
}
void BlockBossLogic::signalChange(PropertyChangeEvent */*e*/)
{
 setOutput();
}
void BlockBossLogic::turnoutChange(PropertyChangeEvent */*e*/)
{
 setOutput();
}

/**
 * Return the original name of the sensor being monitored
 * @return original name; NULL if no sensor configured
 */
/*public*/ QString BlockBossLogic::getWatchedSensor1() {
    if (watchedSensor1 == NULL) return NULL;
    return watchedSensor1->getName();
}

/*public*/ void BlockBossLogic::setWatchedSensor1Alt(QString name) {
    if (name == NULL || name==("")) {
        watchedSensor1Alt = NULL;
        return;
    }
 watchedSensor1Alt = nbhm->getNamedBeanHandle(name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
 if (watchedSensor1Alt == NULL || watchedSensor1Alt->getBean() == NULL) log->warn(tr("Sensor1Alt_")+name+tr("_was not found!"));
 else
 {
    AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
  connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
 }
}
/**
 * Return the system name of the sensor being monitored
 * @return system name; NULL if no sensor configured
 */
/*public*/ QString BlockBossLogic::getWatchedSensor1Alt() {
    if (watchedSensor1Alt == NULL) return NULL;
    return watchedSensor1Alt->getName();
}

/*public*/ void BlockBossLogic::setWatchedSensor2(QString name) {
    if (name == NULL || name==("")) {
        watchedSensor2 = NULL;
        return;
    }
    watchedSensor2 = nbhm->getNamedBeanHandle(name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
    if (watchedSensor2 == NULL || watchedSensor2->getBean() == NULL) log->warn(tr("Sensor2_")+name+tr("_was not found!"));
    else
    {
    AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
    connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
    }
}
/**
 * Return the system name of the sensor being monitored
 * @return system name; NULL if no sensor configured
 */
/*public*/ QString BlockBossLogic::getWatchedSensor2() {
    if (watchedSensor2 == NULL) return NULL;
    return watchedSensor2->getName();
}

/*public*/ void BlockBossLogic::setWatchedSensor2Alt(QString name) {
    if (name == NULL || name==("")) {
        watchedSensor2Alt = NULL;
        return;
    }
    watchedSensor2Alt = nbhm->getNamedBeanHandle(name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
    if (watchedSensor2Alt == NULL || watchedSensor2Alt->getBean() == NULL) log->warn(tr("Sensor2Alt_")+name+tr("_was not found!"));
    else
    {
    AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
    connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
  }
}
/**
 * Return the system name of the sensor being monitored
 * @return system name; NULL if no sensor configured
 */
/*public*/ QString BlockBossLogic::getWatchedSensor2Alt() {
    if (watchedSensor2Alt == NULL) return NULL;
    return watchedSensor2Alt->getName();
}
/*public*/ void BlockBossLogic::setLimitSpeed1(bool d) { limitSpeed1 = d; }
/*public*/ bool BlockBossLogic::getLimitSpeed1() {
    return limitSpeed1;
}
/*public*/ void BlockBossLogic::setLimitSpeed2(bool d) { limitSpeed2 = d; }
/*public*/ bool BlockBossLogic::getLimitSpeed2() {
    return limitSpeed2;
}

/*public*/ bool BlockBossLogic::getUseFlash() {
    return protectWithFlashing;
}

/*public*/ void BlockBossLogic::setDistantSignal(bool d) { distantSignal = d; }
/*public*/ bool BlockBossLogic::getDistantSignal() { return distantSignal; }

/**
 * Provide the current value of the "hold" parameter.
 * If true, the output is forced to a RED "stop" aspect.
 * This allows CTC and other higher-level functions to
 * control permission to enter this section of track.
 */
/*public*/ bool BlockBossLogic::getHold() {return mHold;}
/*
 * Set the current value of the "hold" parameter.
 * If true, the output is forced to a RED "stop" aspect.
 * This allows CTC and other higher-level functions to
 * control permission to enter this section of track.
 */
/*public*/ void BlockBossLogic::setHold(bool m) {
    mHold = m;
    setOutput();  // to invoke the new state
}



/*public*/ void BlockBossLogic::setApproachSensor1(QString name)
{
 if (name == NULL || name==(""))
 {
  approachSensor1 = NULL;
  return;
 }
 approachSensor1 = nbhm->getNamedBeanHandle(name, ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name));
 if (approachSensor1->getBean() == NULL) log->warn(tr("Approach_Sensor1_")+name+tr("_was not found!"));
 else
 {
  AbstractSensor* sensor = (AbstractSensor*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
  connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
 }
}
/**
 * Return the system name of the sensor being monitored
 * @return system name; NULL if no sensor configured
 */
/*public*/ QString BlockBossLogic::getApproachSensor1() {
    if (approachSensor1 == NULL) return NULL;
    return approachSensor1->getName();
}

/**
 * Define the siglet's input and output.
 */
/*public*/ void BlockBossLogic::defineIO() {
    QVector<NamedBean*>* tempArray = new QVector<NamedBean*>(10);
    int n = 0;

    if (watchTurnout!=NULL ) {
        tempArray->replace(n,  watchTurnout->getBean());
        n++;
    }
    if (watchSensor1 != NULL) {
        tempArray->replace(n,  watchSensor1->getBean());
        n++;
    }
    if (watchSensor2 != NULL) {
        tempArray->replace(n,  watchSensor2->getBean());
        n++;
    }
    if (watchSensor3 != NULL) {
        tempArray->replace(n,  watchSensor3->getBean());
        n++;
    }
    if (watchSensor4 != NULL) {
        tempArray->replace(n,  watchSensor4->getBean());
        n++;
    }
    if (watchSensor5 != NULL) {
        tempArray->replace(n,  watchSensor5->getBean());
        n++;
    }
    if (watchedSignal1 != NULL) {
        tempArray->replace(n,  watchedSignal1->getBean());
        n++;
    }
    if (watchedSignal1Alt != NULL) {
        tempArray->replace(n,  watchedSignal1Alt->getBean());
        n++;
    }
    if (watchedSignal2 != NULL) {
        tempArray->replace(n,  watchedSignal2->getBean());
        n++;
    }
    if (watchedSignal2Alt != NULL) {
        tempArray->replace(n,  watchedSignal2Alt->getBean());
        n++;
    }
    if (watchedSensor1 != NULL) {
        tempArray->replace(n,  watchedSensor1->getBean());
        n++;
    }
    if (watchedSensor1Alt != NULL) {
        tempArray->replace(n,  watchedSensor1Alt->getBean());
        n++;
    }
    if (watchedSensor2 != NULL) {
        tempArray->replace(n,  watchedSensor2->getBean());
        n++;
    }
    if (watchedSensor2Alt != NULL) {
        tempArray->replace(n,  watchedSensor2Alt->getBean());
        n++;
    }
    if (approachSensor1 != NULL) {
        tempArray->replace(n,  approachSensor1->getBean());
        n++;
    }

    // copy temp to definitive inputs
    inputs =  QVector<NamedBean*>(n);
    for (int i = 0; i< inputs.size(); i++)
        inputs.replace(i, tempArray->at(i));

    outputs = QVector<NamedBean*>() << driveSignal->getBean();

    // also need to act if the _signal's_ "held"
    // parameter changes, but we don't want to
    // act if the signals appearance changes (to
    // avoid a loop, or avoid somebody changing appearance
    // manually and having it instantly recomputed & changed back
    DefaultSignalHead* head = (DefaultSignalHead*)driveSignal->getBean();
    if(head == NULL) return;
//    connect(head->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    driveSignal->getBean()->addPropertyChangeListener( (PropertyChangeListener*)this);
//    {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                if (e.getPropertyName()==(tr("Held")))
//                    setOutput();
//            }
//        });
}
/*public*/ void BlockBossLogic::propertyChange(PropertyChangeEvent* e) // SLOT[]
{
 if (e->getPropertyName()==(tr("Held"))) 
  setOutput();
}

/**
 * Recompute new output state
 * and apply it.
 */
/*public*/ void BlockBossLogic::setOutput()
{
 //if (log->isTraceEnabled()) log->trace("setOutput for "+name);
 // make sure init is complete
 if ( (outputs.isEmpty() || (outputs.at(0)==NULL) )) return;

 // if "hold" is true, must show red
 if (getHold()) {
     ((DefaultSignalHead*)outputs.at(0))->setAppearance(SignalHead::RED);
     if (log->isDebugEnabled()) log->debug("setOutput red due to held for "+name);
     return;
 }

 // otherwise, process algorithm
 switch (mode) {
 case SINGLEBLOCK:
     doSingleBlock();
     break;
 case TRAILINGMAIN:
     doTrailingMain();
     break;
 case TRAILINGDIVERGING:
     doTrailingDiverging();
     break;
 case FACING:
     doFacing();
     break;
 default:
     log->error(tr("Unexpected_mode:_")+mode+"_Signal_"+getDrivenSignal());
 }
}

int BlockBossLogic::fastestColor1()
{
 int result = SignalHead::RED;
 // special case:  GREEN if no next signal
 if (watchedSignal1==NULL && watchedSignal1Alt==NULL )
     result = SignalHead::GREEN;

 int val = result;
 if (watchedSignal1!=NULL) val = ((DefaultSignalHead*)watchedSignal1->getBean())->getAppearance();
 if (watchedSignal1!=NULL && ((AbstractSignalHead*)watchedSignal1->getBean())->getHeld())
     val =  SignalHead::RED;  // if Held, act as if Red

 int valAlt = result;
 if (watchedSignal1Alt!=NULL) valAlt = ((AbstractSignalHead*)watchedSignal1Alt->getBean())->getAppearance();
 if (watchedSignal1Alt!=NULL && ((AbstractSignalHead*)watchedSignal1Alt->getBean())->getHeld())
     valAlt =  SignalHead::RED; // if Held, act as if Red

 return fasterOf(val, valAlt);
}

int BlockBossLogic::fastestColor2()
{
 int result = SignalHead::RED;
 // special case:  GREEN if no next signal
 if (watchedSignal2==NULL && watchedSignal2Alt==NULL )
     result = SignalHead::GREEN;

 int val = result;
 if (watchedSignal2!=NULL) val = ((DefaultSignalHead*)watchedSignal2->getBean())->getAppearance();
 if (watchedSignal2!=NULL && ((DefaultSignalHead*)watchedSignal2->getBean())->getHeld())
     val =  SignalHead::RED;

 int valAlt = result;
 if (watchedSignal2Alt!=NULL) valAlt = ((DefaultSignalHead*)watchedSignal2Alt->getBean())->getAppearance();
 if (watchedSignal2Alt!=NULL && ((DefaultSignalHead*)watchedSignal2Alt->getBean())->getHeld())
     valAlt =  SignalHead::RED;

 return fasterOf(val, valAlt);
}

/**
 * Given two {@link SignalHead} color constants, returns the one corresponding
 * to the slower speed.
 */
/*static*/ int BlockBossLogic::slowerOf(int a, int b)
{
    // DARK is smallest, FLASHING GREEN is largest
    return qMin(a, b);
}

/**
 * Given two {@link SignalHead} color constants, returns the one corresponding
 * to the faster speed.
 */
/*static*/ int BlockBossLogic::fasterOf(int a, int b)
{
    // DARK is smallest, FLASHING GREEN is largest
    return qMax(a, b);
}

void BlockBossLogic::doSingleBlock() {
    int appearance = SignalHead::GREEN;
    int oldAppearance = ((AbstractSignalHead*)outputs.at(0))->getAppearance();
    // check for yellow, flashing yellow overriding green
    if (protectWithFlashing && fastestColor1()==SignalHead::YELLOW)
        appearance = SignalHead::FLASHYELLOW;
    if (fastestColor1()==SignalHead::RED || fastestColor1()==SignalHead::FLASHRED)
        appearance = SignalHead::YELLOW;

    // if distant signal, show exactly what the home signal does
    if (distantSignal)
        appearance = fastestColor1();

    // if limited speed and green, reduce to yellow
    if (limitSpeed1)
        appearance = slowerOf(appearance, SignalHead::YELLOW);

    // check for red overriding yellow or green
    if (watchSensor1!=nullptr && watchSensor1->getBean()->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor2!=nullptr && watchSensor2->getBean()->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor3!=nullptr && watchSensor3->getBean()->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor4!=nullptr && watchSensor4->getBean()->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor5!=nullptr && watchSensor5->getBean()->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;

    // check if signal if held, forcing a red aspect by this calculation
    if (((DefaultSignalHead*)outputs.at(0))->getHeld())
        appearance = SignalHead::RED;

    // handle approach lighting
    doApproach();

    // show result if changed
    if (appearance != oldAppearance) {
        ((DefaultSignalHead*)outputs.at(0))->setAppearance(appearance);
        if (log->isDebugEnabled()) log->debug("Change appearance of "+name+" to "+QString::number(appearance) + " ("+((DefaultSignalHead*)outputs.at(0))->getDefaultStateName(appearance)+ ")");
    }
}

void BlockBossLogic::doTrailingMain() {
    int appearance = SignalHead::GREEN;
    int oldAppearance = ((DefaultSignalHead*)outputs.at(0))->getAppearance();
    // check for yellow, flashing yellow overriding green
    if (protectWithFlashing && fastestColor1()==SignalHead::YELLOW)
        appearance = SignalHead::FLASHYELLOW;
    if (fastestColor1()==SignalHead::RED || fastestColor1()==SignalHead::FLASHRED)
        appearance = SignalHead::YELLOW;

    // if distant signal, show exactly what the home signal does
    if (distantSignal)
        appearance = fastestColor1();

    // if limited speed and green, reduce to yellow
    if (limitSpeed1)
        appearance = slowerOf(appearance, SignalHead::YELLOW);

    // check for red overriding yellow or green
    if (watchSensor1!=nullptr && ((AbstractSensor*)watchSensor1->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor2!=nullptr && ((AbstractSensor*)watchSensor2->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor3!=nullptr && ((AbstractSensor*)watchSensor3->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor4!=nullptr && ((AbstractSensor*)watchSensor4->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor5!=nullptr && ((AbstractSensor*)watchSensor5->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;

    if (watchTurnout!=nullptr && watchTurnout->getBean()->getKnownState() != Turnout::CLOSED)
        appearance = SignalHead::RED;
    if (watchTurnout!=nullptr && watchTurnout->getBean()->getCommandedState() != Turnout::CLOSED)
        appearance = SignalHead::RED;

    // check if signal if held, forcing a red aspect by this calculation
    if (((DefaultSignalHead*)outputs.at(0))->getHeld())
        appearance = SignalHead::RED;

    // handle approach lighting
    doApproach();

    // show result if changed
    if (appearance != oldAppearance) {
        ((DefaultSignalHead*)outputs.at(0))->setAppearance(appearance);
        if (log->isDebugEnabled()) log->debug("Change appearance of "+name+" to "+ QString::number(appearance) + " ("+((DefaultSignalHead*)outputs.at(0))->getDefaultStateName(appearance)+ ")");
    }
}

void BlockBossLogic::doTrailingDiverging() {
    int appearance = SignalHead::GREEN;
    int oldAppearance = ((DefaultSignalHead*)outputs.at(0))->getAppearance();
    // check for yellow, flashing yellow overriding green
    if (protectWithFlashing && fastestColor1()==SignalHead::YELLOW)
        appearance = SignalHead::FLASHYELLOW;
    if (fastestColor1()==SignalHead::RED || fastestColor1()==SignalHead::FLASHRED)
        appearance = SignalHead::YELLOW;

    // if distant signal, show exactly what the home signal does
    if (distantSignal)
        appearance = fastestColor1();

    // if limited speed and green, reduce to yellow
    if (limitSpeed2)
        appearance = slowerOf(appearance, SignalHead::YELLOW);

    // check for red overriding yellow or green
    if (watchSensor1!=nullptr && ((AbstractSensor*)watchSensor1->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor2!=nullptr && ((AbstractSensor*)watchSensor2->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor3!=nullptr && ((AbstractSensor*)watchSensor3->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor4!=nullptr && ((AbstractSensor*)watchSensor4->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor5!=nullptr && ((AbstractSensor*)watchSensor5->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;

    if (watchTurnout!=nullptr && watchTurnout->getBean()->getKnownState() != Turnout::THROWN)
        appearance = SignalHead::RED;
    if (watchTurnout!=nullptr && watchTurnout->getBean()->getCommandedState() != Turnout::THROWN)
        appearance = SignalHead::RED;

    // check if signal if held, forcing a red aspect by this calculation
    if (((DefaultSignalHead*)outputs.at(0))->getHeld())
        appearance = SignalHead::RED;

    // handle approach lighting
    doApproach();

    // show result if changed
    if (appearance != oldAppearance) {
        ((DefaultSignalHead*)outputs.at(0))->setAppearance(appearance);
        if (log->isDebugEnabled()) log->debug("Change appearance of "+name+" to "+QString::number(appearance) + " ("+((DefaultSignalHead*)outputs.at(0))->getDefaultStateName(appearance)+ ")");
    }
}

void BlockBossLogic::doFacing() {
    int appearance = SignalHead::GREEN;
    int oldAppearance = ((DefaultSignalHead*)outputs.at(0))->getAppearance();

    // find downstream appearance, being pessimistic if we're not sure of the state
    int s = SignalHead::GREEN;
    if (watchTurnout!=nullptr && watchTurnout->getBean()->getKnownState() != Turnout::THROWN)
        s = slowerOf(s, fastestColor1());
    if (watchTurnout!=nullptr && watchTurnout->getBean()->getKnownState() != Turnout::CLOSED)
        s = slowerOf(s, fastestColor2());

    // check for yellow, flashing yellow overriding green
    if (protectWithFlashing && s==SignalHead::YELLOW)
        appearance = SignalHead::FLASHYELLOW;
    if (s==SignalHead::RED  || s==SignalHead::FLASHRED)
        appearance = SignalHead::YELLOW;
    // if distant signal, show exactly what the home signal does
    if (distantSignal)
        appearance = s;

    // if limited speed and green or flashing yellow, reduce to yellow
    if (watchTurnout!=nullptr && limitSpeed1 && watchTurnout->getBean()->getKnownState()!=Turnout::THROWN)
        appearance = slowerOf(appearance, SignalHead::YELLOW);

    if (watchTurnout!=nullptr && limitSpeed2 && watchTurnout->getBean()->getKnownState()!=Turnout::CLOSED)
        appearance = slowerOf(appearance, SignalHead::YELLOW);


    // check for red overriding yellow or green
    if (watchSensor1!=nullptr && ((AbstractSensor*)watchSensor1->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor2!=nullptr && ((AbstractSensor*)watchSensor2->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor3!=nullptr && ((AbstractSensor*)watchSensor3->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor4!=nullptr && ((AbstractSensor*)watchSensor4->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;
    if (watchSensor5!=nullptr && ((AbstractSensor*)watchSensor5->getBean())->getKnownState() != Sensor::INACTIVE)
        appearance = SignalHead::RED;

    if ((watchTurnout!=nullptr && watchTurnout->getBean()->getKnownState() == Turnout::CLOSED)
            && ((watchedSensor1!=nullptr && ((AbstractSensor*)watchedSensor1->getBean())->getKnownState() != Sensor::INACTIVE)))
        appearance = SignalHead::RED;
    if ((watchTurnout!=nullptr && watchTurnout->getBean()->getKnownState() == Turnout::CLOSED) && ((watchedSensor1Alt!=nullptr && ((AbstractSensor*)watchedSensor1Alt->getBean())->getKnownState() != Sensor::INACTIVE)))
        appearance = SignalHead::RED;
    if (watchTurnout!=nullptr && (watchTurnout->getBean()->getKnownState() == Turnout::THROWN) && ((watchedSensor2!=nullptr && ((AbstractSensor*)watchedSensor2->getBean())->getKnownState() != Sensor::INACTIVE)))
        appearance = SignalHead::RED;
    if ((watchTurnout!=nullptr && watchTurnout->getBean()->getKnownState() == Turnout::THROWN) && ((watchedSensor2Alt!=nullptr && ((AbstractSensor*)watchedSensor2Alt->getBean())->getKnownState() != Sensor::INACTIVE)))
        appearance = SignalHead::RED;

    // check if turnout in motion, if so force redwwwwwwwwwwww
    if (watchTurnout!=nullptr && (watchTurnout->getBean()->getKnownState() != watchTurnout->getBean()->getCommandedState()) )
        appearance = SignalHead::RED;
    if (watchTurnout!=nullptr && (watchTurnout->getBean()->getKnownState() != Turnout::THROWN) && (watchTurnout->getBean()->getKnownState() != Turnout::CLOSED) )  // checking for other states
        appearance = SignalHead::RED;

    // check if signal if held, forcing a red aspect by this calculation
    if (static_cast<SignalHead*>(outputs.at(0))->getHeld())
        appearance = SignalHead::RED;

    // handle approach lighting
    doApproach();

    // show result if changed
    if (appearance != oldAppearance)
        static_cast<SignalHead*>(outputs.at(0))->setAppearance(appearance);
}

/**
 * Handle the approach lighting logic for all modes
 */
void BlockBossLogic::doApproach()
{
 if ((approachSensor1 != nullptr) && (approachSensor1->getBean()->getKnownState() == Sensor::INACTIVE))
 {
  // should not be lit
  if (driveSignal->getBean()->getLit())
   driveSignal->getBean()->setLit(false);
 }
 else {
  // should be lit
  if (!driveSignal->getBean()->getLit())
   driveSignal->getBean()->setLit(true);
 }
 return;
}


/*public*/ /*static*/ QListIterator<BlockBossLogic*> BlockBossLogic::entries() {
    setup(); // ensure we've been registered
    return smap->values();
}

/*private*/ /*static*/ void BlockBossLogic::setup() {
    if (smap == nullptr) {
        smap = new QHash<QString,BlockBossLogic*>();
        umap = new QHash<QString,BlockBossLogic*>();
        static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerConfig(new BlockBossLogic(), Manager::BLOCKBOSS);
    }
}

/**
 * Ensure that this BlockBossLogic object is available for later retrieval
 */
/*public*/ void BlockBossLogic::retain()
{
 if(driveSignal->getBean() == nullptr) return;
 smap->insert(driveSignal->getBean()->getSystemName(), this);
 if (driveSignal->getBean()->getUserName()!=nullptr)
  umap->insert(driveSignal->getBean()->getUserName(), this);
}

/**
 * Return the BlockBossLogic item governing a specific signal,
 * having removed it from use.
 * @param signal
 * @return never NULL
 */
/*public*/ /*static*/ BlockBossLogic* BlockBossLogic::getStoppedObject(QString signal)
{
 BlockBossLogic* b = NULL;
 setup(); // ensure we've been registered
 if (smap->contains(signal))
 {
  b = smap->value(signal);
 }
 else if (umap->contains(signal))
 {
  b = umap->value(signal);
 }
 if (b != NULL)
 {
  // found an existing one, remove it from the map and stop its thread
  smap->remove(b->driveSignal->getBean()->getSystemName());
  if (b->driveSignal->getBean()->getUserName() != NULL)
  {
   umap->remove(b->driveSignal->getBean()->getUserName());
  }
  b->stop();
  return b;
 }
 else
 {
  // no existing one, create a new one
  return new BlockBossLogic(signal);
 }
}
/**
 * Return the BlockBossLogic item governing a specific signal.
 * <P>
 * Unlike {@link BlockBossLogic#getStoppedObject(String signal)}
 * this does not remove the object from being used.
 * @param signal system name
 * @return never NULL
 */
/*public*/ /*static*/ BlockBossLogic* BlockBossLogic::getExisting(QString signal) {
    BlockBossLogic* b;
    setup(); // ensure we've been registered
    if (smap->contains(signal)) {
        b = smap->value(signal);
    } else if (umap->contains(signal)) {
        b = umap->value(signal);
    } else {
        b = new BlockBossLogic(signal);
    }
    return b;
}

/*public*/ QList<NamedBeanUsageReport*> BlockBossLogic::getUsageReport(NamedBean* bean) {
        QList<NamedBeanUsageReport*> report = QList<NamedBeanUsageReport*>();
        SignalHead* head = driveSignal->getBean();
        if (bean != nullptr) {
            if (watchSensor1 != nullptr && bean->equals(getDrivenSignalNamedBean()->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSignal", head));  // NOI18N
            }
            if (watchSensor1 != nullptr && bean->equals(watchSensor1->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensor1", head));  // NOI18N
            }
            if (watchSensor2 != nullptr && bean->equals(watchSensor2->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensor2", head));  // NOI18N
            }
            if (watchSensor3 != nullptr && bean->equals(watchSensor3->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensor3", head));  // NOI18N
            }
            if (watchSensor4 != nullptr && bean->equals(watchSensor4->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensor4", head));  // NOI18N
            }
            if (watchSensor5 != nullptr && bean->equals(watchSensor5->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensor5", head));  // NOI18N
            }
            if (watchTurnout != nullptr && bean->equals(watchTurnout->getBean())) {
                report.append(new NamedBeanUsageReport("SSLTurnout", head));  // NOI18N
            }
            if (watchedSignal1 != nullptr && bean->equals(watchedSignal1->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSignal1", head));  // NOI18N
            }
            if (watchedSignal1Alt != nullptr && bean->equals(watchedSignal1Alt->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSignal1Alt", head));  // NOI18N
            }
            if (watchedSignal2 != nullptr && bean->equals(watchedSignal2->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSignal2", head));  // NOI18N
            }
            if (watchedSignal2Alt != nullptr && bean->equals(watchedSignal2Alt->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSignal2Alt", head));  // NOI18N
            }
            if (watchedSensor1 != nullptr && bean->equals(watchedSensor1->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensorWatched1", head));  // NOI18N
            }
            if (watchedSensor1Alt != nullptr && bean->equals(watchedSensor1Alt->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensorWatched1Alt", head));  // NOI18N
            }
            if (watchedSensor2 != nullptr && bean->equals(watchedSensor2->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensorWatched2", head));  // NOI18N
            }
            if (watchedSensor2Alt != nullptr && bean->equals(watchedSensor2Alt->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensorWatched2Alt", head));  // NOI18N
            }
            if (approachSensor1 != nullptr && bean->equals(approachSensor1->getBean())) {
                report.append(new NamedBeanUsageReport("SSLSensorApproach", head));  // NOI18N
            }
        }
        return report;
    }
