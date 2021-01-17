#include "defaultroutemanager.h"
#include "decimalformat.h"

DefaultRouteManager::DefaultRouteManager(InternalSystemConnectionMemo* memo, QObject *parent) : AbstractRouteManager((SystemConnectionMemo*)memo, parent)
{
 setObjectName("DefaultRouteManager");
 setProperty("JavaClassName", "jmri.managers.DefaultRouteManager");
 //lastAutoRouteRef = 0;
 //_instance = NULL;
 this->parent = parent;
 log = new Logger("DefaultRouteManager");
 paddedNumber = new DecimalFormat("0000");
 registerSelf();

 InstanceManager::turnoutManagerInstance()->addVetoableChangeListener((VetoableChangeListener*)this);
 InstanceManager::sensorManagerInstance()->addVetoableChangeListener((VetoableChangeListener*)this);

}
/**
 * Basic Implementation of a RouteManager.
 * <P>
 * Note that this does not enforce any particular system naming convention
 *
 * @author      Dave Duchamp Copyright (C) 2004
 * @version	$Revision: 18102 $
 */
///*public*/ class DefaultRouteManager extends AbstractManager
//    implements RouteManager, java.beans.PropertyChangeListener {

//    /*public*/ DefaultRouteManager() {
//        super();
//    }

/*public*/ int DefaultRouteManager::getXMLOrder() const{
    return Manager::ROUTES;
}

///*public*/ QString DefaultRouteManager::getSystemPrefix() const { return "I"; }
/*public*/ char DefaultRouteManager::typeLetter() const { return 'O'; }

/**
 * Method to provide a  Route
 * whether or not it already exists.
 */
/*public*/ Route* DefaultRouteManager::provideRoute(QString systemName, QString userName) const
{
 DefaultRoute* r;
 r = (DefaultRoute*)getByUserName(systemName);
 if (r!=NULL) return r;
 r = (DefaultRoute*)getBySystemName(systemName);
 if (r!=NULL) return r;
 // Route does not exist, create a new route
 r = new DefaultRoute(systemName,userName);
 // save in the maps
 AbstractManager::Register((NamedBean*)r);

 updateAutoNumber(systemName);

 return r;
}

/*public*/ Route* DefaultRouteManager::newRoute(QString userName)
{
    return provideRoute(getAutoSystemName(), userName);
}

//int DefaultRouteManager::getLastAutoRouteRef()
//{ return lastAutoRouteRef;}

/**
 * Remove an existing route. Route must have been deactivated
 * before invoking this.
 */
/*public*/ void DefaultRouteManager::deleteRoute(Route* r) {
    AbstractManager::deregister((NamedBean*)r);
}

/**
 * Method to get an existing Route.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ Route* DefaultRouteManager::getRoute(QString name) {
    Route* r = (Route*)getByUserName(name);
    if (r!=NULL) return r;
    return (Route*)getBySystemName(name);
}

///*public*/ Route* DefaultRouteManager::getBySystemName(QString name) {
//    return (Route*)_tsys->value(name);
//}

///*public*/ Route* DefaultRouteManager::getByUserName(QString key) {
//    return (Route*)_tuser->value(key);
//}

/*static*/ /*public*/ DefaultRouteManager* DefaultRouteManager::instance()
{
 return (DefaultRouteManager*)InstanceManager::getDefault("DefaultRouteManager");
}

//@Nonnull
//@Override
/*public*/ QString DefaultRouteManager::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "Routes" : "Route");
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString DefaultRouteManager::getNamedBeanClass()const {
    return "Route";
}
//@Override
/*public*/ Route* DefaultRouteManager::provide(QString name) throw (IllegalArgumentException) {
    return provideRoute(name, "");
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultRouteManager.class.getName());
//}
