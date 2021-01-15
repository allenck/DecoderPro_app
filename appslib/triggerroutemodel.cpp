#include "triggerroutemodel.h"
#include "loggerfactory.h"
#include "instancemanager.h"

TriggerRouteModel::TriggerRouteModel()
{

}
/**
 * Startup model that stores the user name of a {@link jmri.Route} so it can be
 * set at application startup.
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class TriggerRouteModel extends AbstractStartupModel {

    /*private*/ /*final*/ /*static*/ Logger* TriggerRouteModel::log = LoggerFactory::getLogger("TriggerRouteModel");

/**
 * Get the user name of the Route.
 *
 * @return the user name
 */
/*public*/ QString TriggerRouteModel::getUserName() {
    return this->getName();
}

/**
 * Set the user name of the Route.
 *
 * @param name user name to use
 */
/*public*/ void TriggerRouteModel::setUserName(QString name) {
    this->setName(name);
}

/**
 * Get the route.
 *
 * @return the route
 */
/*public*/ Route* TriggerRouteModel::getRoute() {
    return (Route*)((RouteManager*)InstanceManager::getDefault("RouteManager"))->getByUserName(this->getUserName());
}

//@Override
/*public*/ void TriggerRouteModel::performAction(QString) throw (JmriException) {
    log->info(tr("Setting route \"%1\" at startup.").arg(this->getUserName()));

    try {
        this->getRoute()->setRoute();
    } catch (NullPointerException ex) {
        log->error(tr("Unable to set route \"%1\"; it has not been defined. Is it's panel loaded?").arg(this->getUserName()));
        // it would be better to use a RouteNotFoundException if one existed
        InitializationException exception =  InitializationException(QString(/*Locale.ENGLISH, */"Unable to set route \"%1\". Route not defined.").arg(this->getUserName()),
                tr("Unable to set route \"%1\". Route not defined.").arg(this->getUserName()), &ex);
        this->addException(exception);
        throw  JmriException(exception);
    }

}
