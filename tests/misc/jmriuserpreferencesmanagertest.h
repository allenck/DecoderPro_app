#ifndef JMRIUSERPREFERENCESMANAGERTEST_H
#define JMRIUSERPREFERENCESMANAGERTEST_H

#include <QObject>
#include "propertychangelistener.h"
#include "exceptions.h"
#include "jmriuserpreferencesmanager.h"
#include "junitutil.h"
#include "propertychangeevent.h"

class TemporaryFolder;
class Logger;
class JmriUserPreferencesManagerTest : public QObject
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit JmriUserPreferencesManagerTest(QObject *parent = nullptr);
 ~JmriUserPreferencesManagerTest() {}
 JmriUserPreferencesManagerTest(const JmriUserPreferencesManagerTest&) : QObject() {}
 //@Rule
 /*public*/ TemporaryFolder* folder;// = new TemporaryFolder();
 Q_INVOKABLE /*public*/ void setUp() throw (Exception);
 Q_INVOKABLE /*public*/ void tearDown() throw (Exception);
 Q_INVOKABLE /*public*/ QString getClassDescription();

signals:

public slots:
// /*public*/ void testGetInstance();
// /*public*/ void testGetDefault();
 /*public*/ void testAllowSave();
 /*public*/ void testDisallowSave();
 /*public*/ void testSetSaveAllowed();
 /*public*/ void testIsSaveAllowed();
 /*public*/ void testGetScreen();
 /*public*/ void testSetSimplePreferenceState();
 /*public*/ void testGetSimplePreferenceState();
 /*public*/ void testGetSimplePreferenceStateList();
 /*public*/ void testSetPreferenceState();
 /*public*/ void testGetPreferenceState();
 /*public*/ void testSetPreferenceItemDetails();
 /*public*/ void testGetPreferenceList();
 /*public*/ void testGetPreferenceItemName();
 /*public*/ void testGetPreferenceItemDescription();
 /*public*/ void testSetSessionPreferenceState();
 /*public*/ void testGetSessionPreferenceState();
 /*public*/ void testShowInfoMessage_4args();
 /*public*/ void testShowErrorMessage();
 /*public*/ void testShowInfoMessage_6args();
 /*public*/ void testShowWarningMessage();
 /*public*/ void testShowMessage();
 /*public*/ void testAddComboBoxLastSelection();
 /*public*/ void testGetComboBoxLastSelection_String();
 /*public*/ void testSetComboBoxLastSelection();
 /*public*/ void testGetComboBoxSelectionSize();
 /*public*/ void testGetChangeMade();
 /*public*/ void testSetChangeMade();
 /*public*/ void testResetChangeMade();
 /*public*/ void testIsLoading();
 /*public*/ void testSetLoading();
 /*public*/ void testFinishLoading();
 /*public*/ void testDisplayRememberMsg();
 /*public*/ void testGetWindowLocation();
 /*public*/ void testGetWindowSize();
 /*public*/ void testGetSaveWindowSize();
 /*public*/ void testGetSaveWindowLocation();
 /*public*/ void testSetSaveWindowSize();
 /*public*/ void testSetSaveWindowLocation();
 /*public*/ void testSetWindowLocation();
 /*public*/ void testSetWindowSize();
 /*public*/ void testGetWindowList();
 /*public*/ void testSetProperty();
 /*public*/ void testGetProperty();
 /*public*/ void testGetPropertyKeys();
 /*public*/ void testHasProperties();
 /*public*/ void testGetClassDescription_String();
 /*public*/ void testGetPreferencesClasses();
 /*public*/ void testSetClassDescription();
 /*public*/ void testSetMessageItemDetails();
 /*public*/ void testGetChoiceOptions();
 /*public*/ void testGetMultipleChoiceSize();
 /*public*/ void testGetMultipleChoiceList();
 /*public*/ void testGetChoiceName() ;
 /*public*/ void testGetChoiceDescription();
 /*public*/ void testGetMultipleChoiceOption();
 /*public*/ void testGetMultipleChoiceDefaultOption();
 /*public*/ void testSetMultipleChoiceOption_3args_String() ;
 /*public*/ void testSetMultipleChoiceOption_3args_int();
 /*public*/ void testGetClassDescription_0args();
 /*public*/ void testGetClassName();
 /*public*/ void testGetClassPreferences();
 /*public*/ void testGetPreferencesSize();
 /*public*/ void testReadUserPreferences() throw (IOException);
 /*public*/ void testSaveElement() throw (IOException);
private:
 static Logger* log;
 /*private*/ /*final*/ QString strClass;// = JmriUserPreferencesManagerTest.class.getName();

};
Q_DECLARE_METATYPE(JmriUserPreferencesManagerTest)

/*private*/ /*static*/ class TestJmriUserPreferencesManager : public JmriUserPreferencesManager {
Q_OBJECT
 JmriUserPreferencesManagerTest* test;
public:
    /*public*/ QString title;// = null;
    /*public*/ QString message;// = null;
    /*public*/ QString strClass;// = null;
    /*public*/ QString item;// = null;
    // bool is nullable unlike bool, null indicates showMessage not called
    /*public*/ bool sessionOnly = false;
    /*public*/ bool alwaysRemember = false;
    /*public*/ int type = -1;
    QString getComboBoxLastSelection(QString s);
    QString getClassName();
protected:
    /*protected*/ TestJmriUserPreferencesManager(JmriUserPreferencesManagerTest* test);

    //@Override
    /*protected*/ void showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item,
      /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type);
    /*protected*/ QHash<QString, QString> *getComboBoxLastSelection() ;

    /*protected*/ bool isLoading() override;
 friend class JmriUserPreferencesManagerTest;
};

/*private*/ /*static*/ class JUPMListener : public PropertyChangeListener {
 Q_OBJECT
 JmriUserPreferencesManagerTest* test;
public:
 JUPMListener(JmriUserPreferencesManagerTest* test) {this->test = test;}
 /*public*/ PropertyChangeEvent* event = nullptr;
public slots:
 //@Override
 /*public*/ void propertyChange(PropertyChangeEvent* evt);
};

class JUPMReleaseUntil : public ReleaseUntil
{
 Q_OBJECT
 JUPMListener* l;
public:
 JUPMReleaseUntil(JUPMListener* l) {this->l = l;}
 bool ready() throw (Exception) {return l->event != nullptr && l->event->getPropertyName() == (UserPreferencesManager::PREFERENCES_UPDATED);}
};
#endif // JMRIUSERPREFERENCESMANAGERTEST_H
