#include "consistpreferencesmanager.h"
#include "loggerfactory.h"
#include "profile.h"
#include "profileutils.h"
#include "preferences.h"

ConsistPreferencesManager::ConsistPreferencesManager(QObject* parent)
{

}
/**
 *
 * @author Paul Bender (C) 2019
 */
//@ServiceProvider(service = PreferencesManager.class)
// /*public*/ class ConsistPreferencesManager extends AbstractPreferencesManager {

    /*private*/ /*final*/ /*static*/ Logger* ConsistPreferencesManager::log = LoggerFactory::getLogger("ConsistPreferencesManager");
    /*public*/ /*final*/ /*static*/ QString ConsistPreferencesManager::UPDATE_CV19 = "updateCV19";

    ////@Override
    /*public*/ void ConsistPreferencesManager::initialize(Profile* profile) throw (InitializationException) {
        if (!this->isInitialized(profile)) {
            Preferences* preferences = ProfileUtils::getPreferences(profile, /*this.getClass()*/"jmri.jmrit.consisttool.ConsistPreferencesManager", true);
            this->setUpdateCV19(preferences->getBoolean(UPDATE_CV19, this->isUpdateCV19()));
            this->setInitialized(profile, true);
        }
    }

    //@Override
    /*public*/ void ConsistPreferencesManager::savePreferences(Profile* profile) {
        Preferences* preferences = ProfileUtils::getPreferences(profile, /*this.getClass()*/"jmri.jmrit.consisttool.ConsistPreferencesManager", true);
        preferences->putBoolean(UPDATE_CV19, this->updateCV19);
        try {
            preferences->sync();
        } catch (BackingStoreException* ex) {
            log->error("Unable to save preferences.", ex);
        }
    }

    /**
     * @return updateCV19
     */
    /*public*/ bool ConsistPreferencesManager::isUpdateCV19() {
        return updateCV19;
    }

    /**
     * @param update the value to set updateCV19 to.
     */
    /*public*/ void ConsistPreferencesManager::setUpdateCV19(bool update) {
        bool oldUpdateCV19 = this->updateCV19;
        updateCV19 = update;
        firePropertyChange(UPDATE_CV19, oldUpdateCV19, updateCV19);
    }
