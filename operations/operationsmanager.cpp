#include "operationsmanager.h"
#include "logger.h"
#include "carmanager.h"
#include "enginemanager.h"
#include "routemanager.h"
#include "locationmanager.h"
#include "trainmanager.h"
#include "setup.h"
#include "autobackup.h"
#include "operationsxml.h"
#include "instancemanager.h"
#include "schedulemanager.h"
#include "file.h"
#include "trainschedulemanager.h"

//OperationsManager::OperationsManager(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations
{
/**
 * A manager for Operations. This manager controls the Operations ShutDownTask.
 *
 * @author Randall Wood 2014
 */
///*public*/ final class OperationsManager {


    //static private final Logger log = LoggerFactory.getLogger(OperationsManager.class);

/*public*/ OperationsManager::OperationsManager(QObject *parent) :
    QObject(parent)
{
 //this("operations"); // NOI18N
 operationsFolderName = "operations";
 setProperty("InstanceManagerAutoDefault", "true");
 setProperty("InstanceManagerAutoInitialize", "true");

 //common();
}

void OperationsManager::initialize()
{
 // ensure the default instance of all operations managers
 // are initialized by calling their instance() methods
 // Is there a different, more optimal order for this?
 ((CarManager*)InstanceManager::getDefault("CarManager"));
 ((EngineManager*)InstanceManager::getDefault("EngineManager"));
 ((TrainManager*)InstanceManager::getDefault("TrainManager"));
 ((LocationManager*)InstanceManager::getDefault("LocationManager"));
 ((Operations::RouteManager*)InstanceManager::getDefault("RouteManager"));
 ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"));
 (TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager");
 this->setShutDownTask(this->getDefaultShutDownTask());
 // auto backup?
 if (Setup::isAutoBackupEnabled()) {
     try {
         AutoBackup* backup = new AutoBackup();
         backup->autoBackup();
     } catch (Exception ex) {
         log->debug("Auto backup after enabling Auto Backup flag."/*, ex*/);
     }
 }

}


    /**
     * Get the path to the Operations folder, rooted in the User's file path, as
     * a String.
     *
     * @return A path
     * @see #getOperationsFolderName()
     */
    /*public*/ QString OperationsManager::getPath() {
        if (this->getOperationsFolderName().endsWith(File::separator)) {
            return OperationsXml::getFileLocation() + this->getOperationsFolderName();
        }
        return OperationsXml::getFileLocation() + this->getOperationsFolderName() + File::separator;
    }

    /**
     * Get the path to a file rooted in the Operations path.
     *
     * @param name The name of the file
     * @return A path
     * @see #getPath()
     */
    /*public*/ QString OperationsManager::getPath(QString name) {
        if (name != nullptr) {
            return this->getPath() + name;
        }
        return this->getPath();
    }

    /**
     * Get a {@link java.io.File} rooted in the Operations path.
     *
     * @param name The name of the file
     * @return A file
     * @see #getPath()
     */
    /*public*/ File* OperationsManager::getFile(QString name) {
        return new File(this->getPath(name));
    }

    /**
     * Register the non-default {@link jmri.ShutDownTask}.
     *
     * Replaces the existing operations ShutDownTask with the new task. Use a
     * null value to prevent an operations ShutDownTask from being run when JMRI
     * shuts down. Use {@link #getDefaultShutDownTask() } to use the default
     * operations ShutDownTask.
     *
     * @param shutDownTask The new ShutDownTask or null
     */
    /*public*/ void OperationsManager::setShutDownTask(ShutDownTask* shutDownTask) {
        if (InstanceManager::getDefault("ShutDownManager") != nullptr) {
            if (this->shutDownTask != nullptr) {
                ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->deregister(this->shutDownTask);
            }
            this->shutDownTask = shutDownTask;
            if (this->shutDownTask != nullptr) {
                ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->_register(this->shutDownTask);
            }
        }
    }

    /**
     * Get a copy of the default operations {@link jmri.ShutDownTask}. The
     * default ShutDownTask saves the operations state at shutdown without
     * prompting.
     *
     * @return A new ShutDownTask
     */
    /*public*/ ShutDownTask* OperationsManager::getDefaultShutDownTask() {
    //        return new QuietShutDownTask("Save Operations State") { // NOI18N
    //            //@Override
    //            /*public*/ bool execute() {
    //                try {
    //                    OperationsXml::save();
    //                } catch (Exception ex) {
    //                    log->warn("Error saving operations state: {}", ex);
    //                    log->debug("Details follow: ", ex);
    //                }
    //                return true;
    //            }
    //        };
     return new MyQuietShutdownTask("Save Operations State");
    }

 /**
  * @return the operationsFolderName
  */
 /*public*/ QString OperationsManager::getOperationsFolderName()
 {
    return operationsFolderName;
 }
OperationsManager::MyQuietShutdownTask::MyQuietShutdownTask(QString name) : QuietShutDownTask(name) {}
bool OperationsManager::MyQuietShutdownTask::execute()
{
    OperationsXml::save();
}

}
