#include "startuppausemodel.h"
#include "loggerfactory.h"
#include "sleeperthread.h"

StartupPauseModel::StartupPauseModel(QObject* parent) :AbstractStartupModel(parent)
{
 delay = -1; // default to invalid duration

}
/**
 * Startup action that causes JMRI to pause before triggering the next startup
 * action.
 *
 * @author Randall Wood (c) 2016
 */
///*public*/ class StartupPauseModel extends AbstractStartupModel {

/*public*/ /*static*/ /*final*/ int StartupPauseModel::DEFAULT_DELAY = 10;
/*private*/ /*final*/ /*static*/ Logger* StartupPauseModel::log = LoggerFactory::getLogger("StartupPauseModel");

//@Override
/*public*/ QString StartupPauseModel::getName() {
    return tr("Pause for %1 seconds").arg(this->getDelay()); // NOI18N
}

/**
 * {@inheritDoc}
 *
 * @return true if duration greater than or equal to 0; false otherwise
 */
//@Override
/*public*/ bool StartupPauseModel::isValid() {
    return this->getDelay() >= 0;
}

/**
 * Get the delay this action will pause the startup action processing.
 *
 * @return seconds delay
 */
/*public*/ int StartupPauseModel::getDelay() {
    return this->delay;
}

/**
 * Set the delay this action will pause the startup action processing.
 *
 * @param delay delay in seconds
 */
/*public*/ void StartupPauseModel::setDelay(int delay) {
    this->delay = delay;
}

//@Override
/*public*/ void StartupPauseModel::performAction(QString) throw (JmriException) {
    if (delay > 0) {
        log->info(tr("Pausing startup actions processing for %1 seconds.").arg(delay));
        try {
            // delay is in seconds ; sleep takes long, not int
            //Thread.sleep(delay * (long) 1000);
         SleeperThread::msleep(delay * (long) 1000);
        } catch (InterruptedException ex) {
            // warn the user that the pause was not as long as expected
            // this does not throw an error displayed to the user; should it?
            log->warn("Pause in startup actions interrupted.");
        }
    }
}
