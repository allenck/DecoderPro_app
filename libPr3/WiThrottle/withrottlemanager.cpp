#include "withrottlemanager.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "withrottlepreferences.h"
#include "trackpowercontroller.h"
#include "turnoutcontroller.h"
#include "routecontroller.h"
#include "consistcontroller.h"

//WiThrottleManager::WiThrottleManager(QObject *parent) : QObject(parent)
//{

//}
/**
 * @author Brett Hoffman Copyright (C) 2010
 */
//@SuppressFBWarnings(value="ISC_INSTANTIATE_STATIC_CLASS", justification="False Positive (April 2016)")
        // FindBugs is flagging "This class allocates an object that is based on a class that only supplies static methods. This object does not need to be created, just access the static methods directly using the class name as a qualifier."
        // so it's confused about the access to the instance() variable.
// /*public*/ class WiThrottleManager {

/*static*/ /*private*/ WiThrottleManager* WiThrottleManager::root = NULL;


/*public*/ WiThrottleManager::WiThrottleManager(QObject *parent) : QObject(parent)
{
 consistController = NULL;
    trackPowerController = new TrackPowerController();
    turnoutController = new TurnoutController();
    routeController = new RouteController();
    if (InstanceManager::getNullableDefault("WiThrottlePreferences") == NULL) {
        InstanceManager::store(new WiThrottlePreferences(FileUtil::getUserFilesPath() + "throttle" + File::separator + "WiThrottlePreferences.xml"), "WiThrottlePreferences");
    }
    withrottlePreferences =(WiThrottlePreferences*) InstanceManager::getDefault("WiThrottlePreferences");
}

/*static*/ /*private*/ WiThrottleManager* WiThrottleManager::instance()
{
 if (root == NULL) {
     root = new WiThrottleManager();
 }
 return root;
}

/*static*/ /*public*/ TrackPowerController* WiThrottleManager::trackPowerControllerInstance() {
    return instance()->trackPowerController;
}

/*static*/ /*public*/ TurnoutController* WiThrottleManager::turnoutControllerInstance() {
    return instance()->turnoutController;
}

/*static*/ /*public*/ RouteController* WiThrottleManager::routeControllerInstance() {
    return instance()->routeController;
}

/*static*/ /*public*/ ConsistController* WiThrottleManager::consistControllerInstance()
{
 if (instance()->consistController == NULL) {
     instance()->consistController = new ConsistController();
 }
 return instance()->consistController;
}

/*static*/ /*public*/ WiThrottlePreferences* WiThrottleManager::withrottlePreferencesInstance() {
    return instance()->withrottlePreferences;
}
