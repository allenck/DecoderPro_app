#include "importlogix.h"
#include "loggerfactory.h"
#include "../../libPr3/logix.h"
#include "logixng.h"
#include "defaultlogixngmanager.h"
#include "instancemanager.h"
#include "importconditional.h"
#include "defaultconditionalngmanager.h"

/**
 * Imports Logixs to LogixNG
 *
 * @author Daniel Bergqvist 2019
 */
// /*public*/  class ImportLogix {


/*public*/  ImportLogix::ImportLogix(Logix* logix, QObject* parent) : QObject(parent) {
    common(logix, false);
}

/*public*/  ImportLogix::ImportLogix(Logix* logix, bool allowSystemImport, QObject* parent) : QObject(parent) {
    common(logix, allowSystemImport, false);
}

/**
 * Create instance of ImportConditional
 * @param logix             the parent Logix of the conditional to import
 * @param allowSystemImport true if system logixs is allowed to be imported,
 *                          false otherwise
 * @param dryRun            true if import without creating any new beans,
 *                          false if to create new beans
 */
/*public*/  ImportLogix::ImportLogix(Logix* logix, bool allowSystemImport, bool dryRun, QObject* parent) : QObject(parent) {
 common(logix, allowSystemImport, dryRun);
}

void ImportLogix::common(Logix* logix, bool allowSystemImport, bool dryRun)
{

    _dryRun = dryRun;
    LogixNG* logixNG = nullptr;

    if (!_dryRun) {
        int counter = 0;
        while ((logixNG == nullptr) && counter < 100) {
            QString name = counter > 0 ? " - " + QString::number(counter) : "";
            logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                    ->createLogixNG("Logix: " + logix->getDisplayName() + name);
            counter++;
        }

        if (logixNG == nullptr) throw new RuntimeException("Cannot create new LogixNG with name: \"Logix: " + logix->getDisplayName()+"\"");

        log->debug(tr("Import Logix %1 to LogixNG %2").arg(logix->NamedBean::getSystemName(), logixNG->NamedBean::getSystemName()));
    }

    _logix = logix;
    _logixNG = logixNG;
}

/*public*/  void ImportLogix::doImport() /*throws JmriException*/ {
    for (int i=0; i < _logix->getNumConditionals(); i++) {
        Conditional* c = _logix->getConditional(_logix->getConditionalByNumberOrder(i));

        if (!_dryRun) {
            log->warn(tr("Import Conditional '%1' to LogixNG '%2'").arg(c->getSystemName(), _logixNG->NamedBean::getSystemName()));
        }


        ImportConditional* ic = new ImportConditional(
                _logix, c, _logixNG,
                ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->AbstractManager::getAutoSystemName(),
                _dryRun);

        try {
            ic->doImport();
        } catch (SocketAlreadyConnectedException* ex) {
            if (!_dryRun) {
                log->warn(tr("Exception during import of Conditional %1 to ConditionalNG %2").arg(
                        c->getSystemName(), _logixNG->NamedBean::getSystemName()), ex);
            }
        }
        if (!_dryRun) ic->getConditionalNG()->setEnabled(true);
    }

}

/*public*/  LogixNG* ImportLogix::getLogixNG() {
    return _logixNG;
}

/*private*/ /*final*/ /*static*/ Logger* ImportLogix::log = LoggerFactory::getLogger("ImportLogix");
