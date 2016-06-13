#include "defaultroutemanager.h"
#include "decimalformat.h"

/*static*/ DefaultRouteManager* DefaultRouteManager::_instance = NULL;

DefaultRouteManager::DefaultRouteManager(QObject *parent) : RouteManager(parent)
{
 setObjectName("DefaultRouteManager");
 lastAutoRouteRef = 0;
 //_instance = NULL;
 this->parent = parent;
 log = new Logger("DefaultRouteManager");
 paddedNumber = new DecimalFormat("0000");
 registerSelf();
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

/*public*/ int DefaultRouteManager::getXMLOrder(){
    return Manager::ROUTES;
}

/*public*/ QString DefaultRouteManager::getSystemPrefix() { return "I"; }
/*public*/ char DefaultRouteManager::typeLetter() { return 'R'; }

/**
 * Method to provide a  Route
 * whether or not it already exists.
 */
/*public*/ Route* DefaultRouteManager::provideRoute(QString systemName, QString userName)
{
 Route* r;
 r = getByUserName(systemName);
 if (r!=NULL) return r;
 r = getBySystemName(systemName);
 if (r!=NULL) return r;
 // Route does not exist, create a new route
 r = (Route*)new DefaultRoute(systemName,userName);
 // save in the maps
 AbstractManager::Register(r);
 /*The following keeps trace of the last created auto system name.
  currently we do not reuse numbers, although there is nothing to stop the
  user from manually recreating them*/
 if (systemName.startsWith("IR:AUTO:"))
 {
  try
  {
   bool bOk;
   int autoNumber = systemName.mid(8).toInt(&bOk);
   if(!bOk) throw new NumberFormatException();
   if (autoNumber > lastAutoRouteRef)
   {
    lastAutoRouteRef = autoNumber;
   }
  }
  catch (NumberFormatException e)
  {
   log->warn("Auto generated SystemName "+ systemName + " is not in the correct format");
  }
 }
 emit newRouteCreated((Route*)r);
 return r;
}

/*public*/ Route* DefaultRouteManager::newRoute(QString userName)
{
 int nextAutoRouteRef = lastAutoRouteRef+1;
 QString b = "IR:AUTO:";
 QString nextNumber = paddedNumber->format(nextAutoRouteRef);
    b.append(nextNumber);
    return provideRoute(b, userName);
}

int DefaultRouteManager::getLastAutoRouteRef()
{ return lastAutoRouteRef;}

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
    Route* r = getByUserName(name);
    if (r!=NULL) return r;
    return getBySystemName(name);
}

/*public*/ Route* DefaultRouteManager::getBySystemName(QString name) {
    return (Route*)_tsys->value(name);
}

/*public*/ Route* DefaultRouteManager::getByUserName(QString key) {
    return (Route*)_tuser->value(key);
}

/*static*/ /*public*/ DefaultRouteManager* DefaultRouteManager::instance()
{
 if (_instance == NULL)
 {
  _instance = new DefaultRouteManager();
 }
 return (_instance);
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultRouteManager.class.getName());
//}
