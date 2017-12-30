#include "programmerconfigmanager.h"
#include "preferences.h"
#include "profileutils.h"
#include <QSet>
#include "logger.h"
#include "paneprogframe.h"
#include "progdefault.h"

ProgrammerConfigManager::ProgrammerConfigManager()
{
 setObjectName("ProgrammerConfigmanager");
  log = new Logger("ProgrammerConfigmanager");
 defaultFile = "";
 showEmptyPanes = true;
 showCvNumbers = false;

}
/**
 *
 * @author Randall Wood (C) 2015
 */
// /*public*/ class ProgrammerConfigManager extends AbstractPreferencesManager {

//    /*private*/ /*final*/ static Logger log = LoggerFactory.getLogger(ProgrammerConfigManager.class);
    /*public*/ /*final*/ /*static*/ QString ProgrammerConfigManager::DEFAULT_FILE = "defaultFile";
    /*public*/ /*final*/ /*static*/ QString ProgrammerConfigManager::SHOW_EMPTY_PANES = "showEmptyPanes";
    /*public*/ /*final*/ /*static*/ QString ProgrammerConfigManager::SHOW_CV_NUMBERS = "showCvNumbers";

//@Override
/*public*/ void ProgrammerConfigManager::initialize(Profile* profile) throw (InitializationException)
{
    if (!this->isInitialized(profile)) {
        Preferences* preferences = ProfileUtils::getPreferences(profile, "jmri/jmrit/symbolicprog/ProgrammerConfigManager", true);
        if (preferences->get(DEFAULT_FILE, this->getDefaultFile()) != NULL) {
            this->setDefaultFile(preferences->get(DEFAULT_FILE, this->getDefaultFile()));
            ProgDefault::setDefaultProgFile(this->getDefaultFile());
        }
        this->setShowEmptyPanes(preferences->getBoolean(SHOW_EMPTY_PANES, this->isShowEmptyPanes()));
        PaneProgFrame::setShowEmptyPanes(this->isShowEmptyPanes());
        this->setShowCvNumbers(preferences->getBoolean(SHOW_CV_NUMBERS, this->isShowCvNumbers()));
        PaneProgFrame::setShowCvNumbers(this->isShowCvNumbers());
        this->setInitialized(profile, true);
    }
}

//@Override
/*public*/ /*Set<Class<? extends PreferencesManager>>*/ QSet<QString>* ProgrammerConfigManager::getRequires() {
    //Set<Class<? extends PreferencesManager>> requires = super.getRequires();
 QSet<QString>* requires = new QSet<QString>();
    requires->insert("FileLocationsPreferences");
    return requires;
}

//@Override
/*public*/ /*Set<Class<?>>*/ QSet<QString>* ProgrammerConfigManager::getProvides() {
    //Set<Class<?>> provides = super.getProvides();
    QSet<QString>* provides = AbstractPreferencesManager::getProvides();
    //provides.stream().forEach((provide) -> {
    foreach(QString provide, *provides )
    {
        log->debug(tr("ProgammerConfigManager provides %1").arg(provide));
    }//);
    return provides;
}

//@Override
/*public*/ void ProgrammerConfigManager::savePreferences(Profile* profile) {
    Preferences* preferences = ProfileUtils::getPreferences(profile, "jmri/jmrit/symbolicprog/ProgrammerConfigManager", true);
    if (this->defaultFile != NULL) {
        preferences->put(DEFAULT_FILE, this->defaultFile);
    } else {
        preferences->remove(DEFAULT_FILE);
    }
    preferences->putBoolean(SHOW_EMPTY_PANES, this->showEmptyPanes);
    preferences->putBoolean(SHOW_CV_NUMBERS, this->showCvNumbers);
//    try {
        preferences->sync();
//    } catch (BackingStoreException ex) {
//        log.error("Unable to save preferences.", ex);
//    }
}

/**
 * @return the defaultFile
 */
/*public*/ QString ProgrammerConfigManager::getDefaultFile() {
    return defaultFile;
}

/**
 * @param defaultFile the defaultFile to set
 */
/*public*/ void ProgrammerConfigManager::setDefaultFile(QString defaultFile) {
    QString oldDefaultFile = this->defaultFile;
    this->defaultFile = defaultFile;
    firePropertyChange(DEFAULT_FILE, oldDefaultFile, defaultFile);
}

/**
 * @return the showEmptyPanes
 */
/*public*/ bool ProgrammerConfigManager::isShowEmptyPanes() {
    return showEmptyPanes;
}

/**
 * @param showEmptyPanes the showEmptyPanes to set
 */
/*public*/ void ProgrammerConfigManager::setShowEmptyPanes(bool showEmptyPanes) {
    bool oldShowEmptyPanes = this->showEmptyPanes;
    this->showEmptyPanes = showEmptyPanes;
    firePropertyChange(SHOW_EMPTY_PANES, oldShowEmptyPanes, showEmptyPanes);
}

/**
 * @return the showCvNumbers
 */
/*public*/ bool ProgrammerConfigManager::isShowCvNumbers() {
    return showCvNumbers;
}

/**
 * @param showCvNumbers the showCvNumbers to set
 */
/*public*/ void ProgrammerConfigManager::setShowCvNumbers(bool showCvNumbers) {
    bool oldShowCvNumbers = this->showCvNumbers;
    this->showCvNumbers = showCvNumbers;
    firePropertyChange(SHOW_CV_NUMBERS, oldShowCvNumbers, showCvNumbers);
}
