#include "traincustomcommon.h"
#include "loggerfactory.h"
#include "trainmanagerxml.h"
#include "xml.h"
#include "traincustommanifest.h"
#include "operationsmanager.h"
#include "fileutil.h"
#include "control.h"

using namespace Operations;

TrainCustomCommon::TrainCustomCommon(QObject *parent) : QObject(parent)
{

}
///*public*/ abstract class TrainCustomCommon {


/*public*/ QString TrainCustomCommon::getFileName() {
    return mcAppName;
}

/*public*/ void TrainCustomCommon::setFileName(QString name) {
    mcAppName = name;
    Operations::TrainManagerXml::instance()->setDirty(true);
}

/*public*/ QString TrainCustomCommon::getCommonFileName() {
    return csvNamesFileName;
}

/*public*/ void TrainCustomCommon::setCommonFileName(QString name) {
    csvNamesFileName = name;
}

/*abstract*/ /*public*/ QString TrainCustomCommon::getDirectoryName() {return "";}

/*abstract*/ /*public*/ void TrainCustomCommon::setDirectoryName(QString name) {}

/*public*/ int TrainCustomCommon::getFileCount() {
    return fileCount;
}

/**
 * Adds one CSV file path to the collection of files to be processed.
 * @param csvFile The File to add.
 *
 */
//@SuppressFBWarnings(value = "UW_UNCOND_WAIT")
/*public*/ void TrainCustomCommon::addCVSFile(File* csvFile) {
    // Ignore NULL files...
    if (csvFile == NULL  || !excelFileExists()) {
        return;
    }
#if 0
    // once the process starts, we can't add files to the common file
    while (TrainCustomManifest::instance()->isProcessAlive() || TrainCustomSwitchList::instance().isProcessAlive()) {
        synchronized (this) {
            try {
                wait(1000); // 1 sec
            } catch (InterruptedException e) {
                // we don't care
            }
        }
    }
#endif
    fileCount++;
    waitTimeSeconds = getFileCount() * Control::excelWaitTime;
    alive = true;

    File* csvNamesFile = new File(Operations::OperationsManager::getInstance()->getFile(getDirectoryName()), csvNamesFileName);

    try {
        FileUtil::appendTextToFile(csvNamesFile, csvFile->getAbsolutePath());

    } catch (IOException e) {
//        e.printStackTrace();
    }
}

/**
 * Processes the CSV files using a Custom external program that reads the
 * file of file names.
 * @return True if successful.
 */
//@SuppressFBWarnings(value = "UW_UNCOND_WAIT")
/*public*/ bool TrainCustomCommon::process() {

    // check to see it the Excel program is available
    if (!excelFileExists()) {
        return false;
    }

    // Only continue if we have some files to process.
    if (getFileCount() == 0) {
        return true; // done
    }
#if 0
    // only one copy of the excel program is allowed to run.  Two copies running in parallel has issues.
    while (TrainCustomManifest.instance().isProcessAlive() || TrainCustomSwitchList.instance().isProcessAlive()) {
        synchronized (this) {
            try {
                wait(1000); // 1 sec
            } catch (InterruptedException e) {
                // we don't care
            }
        }
    }

    log.debug("Queued {} files to custom Excel program", getFileCount());

    // Build our command string out of these bits
    // We need to use cmd and start to allow launching data files like
    // Excel spreadsheets
    // It should work OK with actual programs.

    if (SystemType.isWindows()) {
        String cmd = "cmd /c start " + getFileName() + " " + mcAppArg; // NOI18N
        try {
            process = Runtime.getRuntime().exec(cmd, NULL,
                    OperationsManager.getInstance().getFile(getDirectoryName()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    } else {
        String cmd = "open " + getFileName() + " " + mcAppArg; // NOI18N
        try {
            process = Runtime.getRuntime().exec(cmd, NULL,
                    OperationsManager.getInstance().getFile(getDirectoryName()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
#endif
    fileCount = 0;
    return true;
}

/*public*/ bool TrainCustomCommon::excelFileExists() {
    File* file = new File(OperationsManager::getInstance()->getFile(getDirectoryName()), getFileName());
    return file->exists();
}
#if 0
//@SuppressFBWarnings(value = "UW_UNCOND_WAIT")
/*public*/ bool checkProcessReady() {
    if (!isProcessAlive())
        return true;
    if (alive) {
        log.debug("Wait time: {} seconds process ready", waitTimeSeconds);
        int loopCount = waitTimeSeconds; // number of seconds to wait
        while (loopCount > 0 && alive) {
            loopCount--;
            synchronized (this) {
                try {
                    wait(1000); // 1 sec
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    }
    return !alive;
}

/*public*/ bool isProcessAlive() {
    if (process != NULL) {
        return process.isAlive();
    } else {
        return false;
    }
}

/**
 *
 * @return true if process completes without a timeout, false if there's a
 *         timeout.
 * @throws InterruptedException if process thread is interrupted
 */
/*public*/ bool waitForProcessToComplete() throw (InterruptedException) {
    log.debug("Wait time: {} seconds", waitTimeSeconds);
    bool status;
    synchronized (process) {
        File file = new File(OperationsManager.getInstance().getFile(getDirectoryName()), getCommonFileName());
        if (!file.exists()) {
            log.debug("Common file not found! Normal when processing multiple files");
        }
        log.debug("Waiting for Excel program to complete");
        status = process.waitFor(waitTimeSeconds, TimeUnit.SECONDS);
        if (file.exists()) {
            log.error("Common file not deleted!");
            return false;
        }
        log.debug("Excel program complete!");
    }
    alive = false;
    return status;
}

/**
 * Checks to see if the common file exists
 * @return true if the common file exists
 */
/*public*/ bool doesCommonFileExist() {
    File file = new File(OperationsManager.getInstance().getFile(getDirectoryName()), getCommonFileName());
    return file.exists();
}
#endif
/*public*/ void TrainCustomCommon::load(QDomElement mc)
{
 if (!mc.isNull())
 {
  QString a;
  QDomElement directory = mc.firstChildElement(Xml::DIRECTORY);
  if (!directory.isNull() && (a = directory.attribute(Xml::NAME)) != NULL) {
      setDirectoryName(a);
  }
  QDomElement file = mc.firstChildElement(Xml::RUN_FILE);
  if (!file.isNull() && (a = file.attribute(Xml::NAME)) != NULL) {
      mcAppName = a;
  }
  QDomElement common = mc.firstChildElement(Xml::COMMON_FILE);
  if (!common.isNull() && (a = common.attribute(Xml::NAME)) != NULL) {
      csvNamesFileName = a;
  }
 }
}

/*public*/ void TrainCustomCommon::store(QDomElement mc) {

    QDomElement file = doc.createElement(Xml::RUN_FILE);
    file.setAttribute(Xml::NAME, getFileName());
    QDomElement directory = doc.createElement(Xml::DIRECTORY);
    directory.setAttribute(Xml::NAME, getDirectoryName());
    QDomElement common = doc.createElement(Xml::COMMON_FILE);
    common.setAttribute(Xml::NAME, getCommonFileName());
    mc.appendChild(directory);
    mc.appendChild(file);
    mc.appendChild(common);
}

    /*private*/ /*final*/ /*static*/ Logger* TrainCustomCommon::log = LoggerFactory::getLogger("TrainCustomCommon");

