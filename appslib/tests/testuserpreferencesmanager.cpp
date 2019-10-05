#include "testuserpreferencesmanager.h"

/**
 * Mock Implementation for the User Preferences Manager.
 *
 * @see jmri.UserPreferencesManager
 * @see jmri.managers.JmriUserPreferencesManager
 *
 * @author Bob Jacobsen Copyright (C) 2015
 */
///*public*/ class TestUserPreferencesManager extends JmriUserPreferencesManager {

    /*public*/ TestUserPreferencesManager::TestUserPreferencesManager(QObject* parent) {
        this->setPreferenceItemDetails(getClassName(), "reminder", "Hide Reminder Location Message");
        this->getClassPreferences(getClassName())->setDescription("User Preferences");
    }

    //@Override
    /*protected*/ void TestUserPreferencesManager::showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type) {
        // Uncomment to force failure if wanting to verify that showMessage does not get called.
        //org.slf4j.LoggerFactory.getLogger(TestUserPreferencesManager.class).error("showMessage called.", new Exception());
    }
