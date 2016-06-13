#include "autosave.h"
#include "setup.h"
#include "operationsxml.h"
#include "logger.h"
#include "trainmanager.h"
#include "sleeperthread.h"

namespace Operations
{
/**
 * Auto Save. When enabled will automatically save operation files.
 *
 * @author Daniel Boudreau Copyright (C) 2012
 * @version $Revision: 17977 $
 */
///*public*/ class AutoSave {

 /*static*/ QThread* AutoSave::autoSave = NULL;

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "SC_START_IN_CTOR")
 /*public*/ AutoSave::AutoSave(QObject* parent) : QObject(parent)
 {
  log = new Logger("AutoSave");
     /*synchronized (this)*/
  if (Setup::isAutoSaveEnabled() && autoSave == NULL)
  {
//             autoSave = new Thread(new Runnable() {
//                 /*public*/ void run() {
//                     saveFiles();
//                 }
//             });
    autoSave = new QThread();
    Worker* worker = new Worker(this);
    worker->moveToThread(autoSave);
    connect(autoSave, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), autoSave, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(autoSave, SIGNAL(finished()), autoSave, SLOT(deleteLater()));
    autoSave->setObjectName("Operations Auto Save"); // NOI18N
    autoSave->start();
  }
 }

 Worker::Worker(AutoSave *autoSave)
 {
  this->autoSave = autoSave;
 }

 void Worker::process()
 {
  autoSave->saveFiles();
 }

 /*private*/ /*synchronized*/ void AutoSave::saveFiles() {
     while (true) {
         try {
//             wait(60000);	// check every minute
             SleeperThread:: sleep(60);
         } catch (InterruptedException e) {
         }
         if (!Setup::isAutoSaveEnabled()) {
             break;
         }
         if (OperationsXml::areFilesDirty()) {
             log->debug("Detected dirty operation files");
             try {
                 //wait(60000);	// wait another minute before saving
              SleeperThread::sleep(60);
             } catch (InterruptedException e) {
             }
             if (TrainManager::instance()->isAnyTrainBuilding()) {
                 log->debug("Detected trains being built");
                 continue;
             }
             if (OperationsXml::areFilesDirty()) {
                 OperationsXml::save();
                 log->info("Operation files automatically saved");
             }
         }
     }
     autoSave = NULL;	// done
 }

}
