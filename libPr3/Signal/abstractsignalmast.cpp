#include "abstractsignalmast.h"
#include "defaultsignalappearancemap.h"
#include "instancemanager.h"
#include "signalsystemmanager.h"
#include "defaultsignalsystemmanager.h"
#include "defaultsignalsystem.h"

//AbstractSignalMast::AbstractSignalMast(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * Abstract class providing the basic logic of the SignalMast interface.
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version     $Revision: 19974 $
 */
///*public*/ abstract class AbstractSignalMast extends AbstractNamedBean
//    implements SignalMast, java.io.Serializable {

/*public*/ AbstractSignalMast::AbstractSignalMast(QString systemName, QString userName, QObject *parent)
 : SignalMast(systemName, userName, parent)
{
    //super(systemName, userName);
 common();
}

/*public*/ AbstractSignalMast::AbstractSignalMast(QString systemName, QObject *parent)
 : SignalMast(systemName, parent)
{
    //super(systemName);
 common();
}

void AbstractSignalMast::common()
{
 log = new Logger("AbstractSignalMast");
 mLit = true;
 mHeld = false;
 disabledAspects = new QStringList();
 *disabledAspects << "";

}

//@edu.umd.cs.findbugs.annotations.OverrideMustInvoke
/*public*/ void AbstractSignalMast::setAspect(QString aspect)
{
 QString oldAspect = this->aspect;
 this->aspect = aspect;
 if(getSignalSystem() == NULL) return; // added ACK
 this->speed = ((DefaultSignalSystem*)getSignalSystem())->getProperty(aspect, "speed").toString();
 firePropertyChange("Aspect", QVariant(oldAspect), QVariant(aspect));
    //emit propertyChange(new PropertyChangeEvent(this,"Aspect", QVariant(oldAspect), QVariant(aspect)));
}

/*public*/ QString AbstractSignalMast::getAspect() { return aspect; }

/*public*/ QString AbstractSignalMast::getSpeed() { return speed; }

/**
 * The state is the index of the current aspect
 * in the list of possible aspects.
 */
/*public*/ int AbstractSignalMast::getState() {
    return -1;
}
/*public*/ void AbstractSignalMast::setState(int /*i*/) {
}

/**
 * By default, signals are lit.
 */
/**
 * Default behavior for "lit" parameter is
 * to track value and return it.
 */
/*public*/ bool AbstractSignalMast::getLit() {return mLit;}

/**
 * By default, signals are not held.
 */

/**
 * "Held" parameter is just tracked and notified.
 */
/*public*/ bool AbstractSignalMast::getHeld() {return mHeld;}

/**
 * Set the lit parameter.
 *
 * This acts on all the SignalHeads included
 * in this SignalMast
 */
//@edu.umd.cs.findbugs.annotations.OverrideMustInvoke
/*public*/ void AbstractSignalMast::setLit(bool newLit) {
    bool oldLit = mLit;
    mLit = newLit;
    if (oldLit != newLit) {
        //updateOutput();
        // notify listeners, if any
        firePropertyChange("Lit", QVariant(oldLit), QVariant(newLit));
    }

}

/**
 * Set the held parameter.
 * <P>
 * Note that this does not directly effect the output on the layout;
 * the held parameter is a local variable which effects the aspect
 * only via higher-level logic.
 */
//@edu.umd.cs.findbugs.annotations.OverrideMustInvoke
/*public*/ void AbstractSignalMast::setHeld(bool newHeld) {
    bool oldHeld = mHeld;
    mHeld = newHeld;
    if (oldHeld != newHeld) {
        // notify listeners, if any
        firePropertyChange("Held", QVariant(oldHeld), QVariant(newHeld));
    }

}

void AbstractSignalMast::configureSignalSystemDefinition(QString name) {
    systemDefn = static_cast<SignalSystemManager*>( InstanceManager::getDefault("SignalSystemManager"))->getSystem(name);
    if (systemDefn == NULL) {
        log->error("Did not find signal definition: "+name);
        throw  IllegalArgumentException("Signal definition not found: "+name);
    }
}

void AbstractSignalMast::configureAspectTable(QString signalSystemName, QString aspectMapName) {
    map = DefaultSignalAppearanceMap::getMap(signalSystemName, aspectMapName);
}

/*public*/ SignalSystem* AbstractSignalMast::getSignalSystem() {
    return systemDefn;
}

/*public*/ SignalAppearanceMap* AbstractSignalMast::getAppearanceMap() {
    return map;
}

/**
* returns a list of all the valid aspects, that have not been disabled
*/
/*public*/ QVector<QString> AbstractSignalMast::getValidAspects() {
    QStringListIterator e (map->getAspects());
    QVector<QString> v =  QVector<QString>();
    while (e.hasNext()) {
        QString aspect = e.next();
        if(!disabledAspects->contains(aspect))
            v.append(aspect);
    }
    return v;
}

/**
  * {@inheritDoc }
  */
 /*public*/ QString AbstractSignalMast::getMastType() { return mastType; }
 /*public*/ void AbstractSignalMast::setMastType(/*@Nonnull*/ QString type) {
     //Objects.requireNonNull(type, "MastType cannot be null");
     mastType = type;
 }

/**
* returns a list of all the known aspects for this mast, including those that have been disabled
*/
/*public*/ QVector<QString> AbstractSignalMast::getAllKnownAspects(){
    QStringListIterator e (map->getAspects());
    QVector<QString> v =  QVector<QString>();
    while (e.hasNext()) {
        v.append(e.next());
    }
    return v;
}

/*public*/ void AbstractSignalMast::setAspectDisabled(QString aspect){
    if(aspect==NULL || aspect==(""))
        return;
    if(!map->checkAspect(aspect)){
        log->warn("attempting to disable an aspect: " + aspect + " that is not on the mast " + getDisplayName());
        return;
    }
    if(!disabledAspects->contains(aspect)){
        disabledAspects->append(aspect);
        firePropertyChange("aspectDisabled", QVariant(), QVariant(aspect));
    }
}

/*public*/ void AbstractSignalMast::setAspectEnabled(QString aspect){
    if(aspect==NULL || aspect==(""))
        return;
    if(!map->checkAspect(aspect)){
        log->warn("attempting to disable an aspect: " + aspect + " that is not on the mast " + getDisplayName());
        return;
    }
    if(disabledAspects->contains(aspect)) {
        disabledAspects->removeAt(disabledAspects->indexOf(aspect));
        firePropertyChange("aspectEnabled", QVariant(), QVariant(aspect));
    }
}

/*public*/QStringList* AbstractSignalMast::getDisabledAspects(){
    return disabledAspects;
}

/*public*/ bool AbstractSignalMast::isAspectDisabled(QString aspect){
    return disabledAspects->contains(aspect);
}

/*public*/ void AbstractSignalMast::setAllowUnLit(bool boo)
{
 _allowUnLit = boo;
}

/*public*/ bool AbstractSignalMast::allowUnLit() {
    return _allowUnLit;
}

/*public*/ void AbstractSignalMast::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException)
{
}

/*public*/ QString AbstractSignalMast::getBeanType()
{
 return tr("Signal Mast");
}
