#include "jmriuserpreferencesmanager.h"
#include "instancemanager.h"
#include <QScreen>
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QFont>
#include <QMessageBox>
#include "profileutils.h"
#include "profilemanager.h"
#include "profile.h"
#include "fileutil.h"
#include "nodeidentity.h"
#include "loggerfactory.h"
#include "profileutils.h"
#include "auxiliaryconfiguration.h"
#include "jmrijtablepersistencemanager.h"
#include "sortorder.h"
#include "metatypes.h"
#include "class.h"
#include "configuremanager.h"
#include "joptionpane.h"
#include "vptr.h"

/**
 * Implementation of {@link UserPreferencesManager} that saves user interface
 * preferences that should be automatically remembered as they are set.
 *
 * This class is intended to be a transitional class from a single user
 * interface preferences manager to multiple, domain-specific (windows, tables,
 * dialogs, etc) user interface preferences managers. Domain-specific managers
 * can more efficiently, both in the API and at runtime, handle each user
 * interface preference need than a single monolithic manager.
 *
 * @author Randall Wood (C) 2016
 */
// /*public*/ class JmriUserPreferencesManager extends Bean implements UserPreferencesManager {

/*public*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::SAVE_ALLOWED = "saveAllowed";

/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::CLASSPREFS_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/class-preferences-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::CLASSPREFS_ELEMENT = "classPreferences"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::COMBOBOX_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/combobox-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::COMBOBOX_ELEMENT = "comboBoxLastValue"; // NOI18N
/*private*/ /*static*/ /*final*/ QString JmriUserPreferencesManager::CHECKBOX_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/checkbox-4-21-3.xsd"; // NOI18N
/*private*/ /*static*/ /*final*/ QString JmriUserPreferencesManager::CHECKBOX_ELEMENT = "checkBoxLastValue"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::SETTINGS_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/settings-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::SETTINGS_ELEMENT = "settings"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::WINDOWS_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/window-details-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::WINDOWS_ELEMENT = "windowDetails"; // NOI18N
/*private*/ /*final*/ /*static*/ Logger* JmriUserPreferencesManager::log = LoggerFactory::getLogger("JmriUserPreferencesManager");
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::REMINDER = "reminder";
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::JMRI_UTIL_JMRI_JFRAME = "jmri.util.JmriJFrame";
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::CLASS = "class";
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::VALUE = "value";
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::WIDTH = "width";
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::HEIGHT = "height";
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::PROPERTIES = "properties";
///*public*/ /*static*/ UserPreferencesManager* JmriUserPreferencesManager::getInstance() {
//    return JmriUserPreferencesManager::getDefault();
//}

/**
 * Get the default UserPreferencesManager or create a new one if none
 * exists. Load user preferences if needed.
 *
 * @return the default UserPreferencesManager
 */
///*public*/ /*static*/ UserPreferencesManager* JmriUserPreferencesManager::getDefault() {
//    return (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
// }


/*public*/ JmriUserPreferencesManager::JmriUserPreferencesManager(QObject* parent) : UserPreferencesManager(parent)
{
 log->setDebugEnabled(true);
  dirty = false;
 loading = false;
 simplePreferenceList = new QStringList();
 //sessionList is used for messages to be suppressed for the current JMRI session only
 sessionPreferenceList = new QStringList();
 comboBoxLastSelection = new QHash<QString, QString>();
 windowDetails = new QHash<QString, WindowLocations*>();
 classPreferenceList = new QHash<QString, ClassPreferences*>();

 // prevent attempts to write during construction
 this->allowSave = false;
 //I18N in ManagersBundle.properties (this is a checkbox on prefs tab Messages|Misc items)
 this->setPreferenceItemDetails(getClassName(), REMINDER, tr("Hide Reminder Location Message")); // NOI18N
 //I18N in ManagersBundle.properties (this is the title of prefs tab Messages|Misc items)
 this->classPreferenceList->value(getClassName())->setDescription(tr("User Preferences")); // NOI18N

 // allow attempts to write
 this->allowSave = true;
 this->dirty = false;

 QMetaObject::invokeMethod((JmriUserPreferencesManager*)this, "initAfter", Qt::QueuedConnection);
 QObject::setProperty("InstanceManagerAutoInitialize", "true");
}

/*private*/ void JmriUserPreferencesManager::initAfter() // finish up after subclassed constructor has run
{
 //I18N in ManagersBundle.properties (this is a checkbox on prefs tab Messages|Misc items)
 this->setPreferenceItemDetails(getClassName(), "reminder", tr("Hide Reminder Location Message")); // NOI18N
 //I18N in ManagersBundle.properties (this is the title of prefs tab Messages|Misc items)
 this->classPreferenceList->value(getClassName())->setDescription(tr("User Preferences")); // NOI18N

 // allow attempts to write
 this->allowSave = true;
 this->dirty = false;
}

//@Override
/*public*/ /*synchronized*/ void JmriUserPreferencesManager::setSaveAllowed(bool saveAllowed)
{
 bool old = this->allowSave;
 this->allowSave = saveAllowed;
 if (saveAllowed && this->dirty) {
     this->savePreferences();
 }
 this->firePropertyChange(SAVE_ALLOWED, old, this->allowSave);
}

//@Override
/*public*/ bool JmriUserPreferencesManager::isSaveAllowed() {
    return this->allowSave;
}

//@Override
/*public*/ QSize JmriUserPreferencesManager::getScreen() {
    //return Toolkit.getDefaultToolkit().getScreenSize();
// QDesktopWidget* desktop = QApplication::desktop();
// return desktop->screen()->size();
 return QApplication::screens().at(0)->size();
}

/**
 * This is used to remember the last selected state of a checkBox and thus
 * allow that checkBox to be set to a true state when it is next
 * initialized. This can also be used anywhere else that a simple yes/no,
 * true/false type preference needs to be stored.
 *
 * It should not be used for remembering if a user wants to suppress a
 * message as there is no means in the GUI for the user to reset the flag.
 * setPreferenceState() should be used in this instance The name is
 * free-form, but to avoid ambiguity it should start with the package name
 * (package.Class) for the primary using class.
 *
 * @param name  A unique name to identify the state being stored
 * @param state simple bool.
 */
//@Override
/*public*/ void JmriUserPreferencesManager::setSimplePreferenceState(QString name, bool state)
{
 if (state)
 {
  if (!simplePreferenceList->contains(name)) {
      simplePreferenceList->append(name);
  }
 } else
 {
  simplePreferenceList->removeOne(name);
 }
 this->saveSimplePreferenceState();
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getSimplePreferenceState(QString name) {
    return simplePreferenceList->contains(name);
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getSimplePreferenceStateList() {
    return  QStringList(*simplePreferenceList);
}

//@Override
/*public*/ void JmriUserPreferencesManager::setPreferenceState(QString strClass, QString item, bool state) {
    // convert old manager preferences to new manager preferences
    if (strClass == ("jmri.managers.DefaultUserMessagePreferences")) {
        this->setPreferenceState("jmri.managers.JmriUserPreferencesManager", item, state);
        return;
    }
    if (! classPreferenceList->contains(strClass)) {
         classPreferenceList->insert(strClass, new ClassPreferences());
        setClassDescription(strClass);
    }
    QList<PreferenceList*>* a = classPreferenceList->value(strClass)->getPreferenceList();
    bool found = false;
    for (int i = 0; i < a->size(); i++) {
        if (a->at(i)->getItem() == (item)) {
            a->at(i)->setState(state);
            found = true;
        }
    }
    if (!found) {
        a->append(new PreferenceList(item, state));
    }
    displayRememberMsg();
    this->savePreferencesState();
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getPreferenceState(QString strClass, QString item) {
    if ( classPreferenceList->contains(strClass)) {
        QList<PreferenceList*>* a = classPreferenceList->value(strClass)->getPreferenceList();
        for (int i = 0; i < a->size(); i++) {
            if (a->at(i)->getItem() == (item)) {
                return a->at(i)->getState();
            }
        }
    }
    return false;
}

//@Override
/*public*/ /*final*/ void JmriUserPreferencesManager::setPreferenceItemDetails(QString strClass, QString item, QString description) {
    if (!classPreferenceList->contains(strClass)) {
         classPreferenceList->insert(strClass, new ClassPreferences());
    }
    QList<PreferenceList*>* a =  classPreferenceList->value(strClass)->getPreferenceList();
    for (int i = 0; i < a->size(); i++) {
        if (a->at(i)->getItem() == (item)) {
            a->at(i)->setDescription(description);
            return;
        }
    }
    a->append(new PreferenceList(item, description));
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getPreferenceList(QString strClass) {
    if ( classPreferenceList->contains(strClass)) {
        QList<PreferenceList*>* a =  classPreferenceList->value(strClass)->getPreferenceList();
        QStringList list =  QStringList();
        for (int i = 0; i < a->size(); i++) {
            list.append(a->at(i)->getItem());
        }
        return list;
    }
    //Just return a blank array list will save call code checking for NULL
    return QStringList();
}

//@Override
/*public*/ QString JmriUserPreferencesManager::getPreferenceItemName(QString strClass, int n) {
    if ( classPreferenceList->contains(strClass)) {
        return  classPreferenceList->value(strClass)->getPreferenceName(n);
    }
    return QString();
}

//@Override
/*public*/ QString JmriUserPreferencesManager::getPreferenceItemDescription(QString strClass, QString item) {
    if ( classPreferenceList->contains(strClass)) {
        QList<PreferenceList*>* a =  classPreferenceList->value(strClass)->getPreferenceList();
        for (int i = 0; i < a->size(); i++) {
            if (a->at(i)->getItem() == (item)) {
                return a->at(i)->getDescription();
            }
        }
    }
    return QString();

}

/**
 * Used to surpress messages for a perticular session, the information is
 * not stored, can not be changed via the GUI.
 * <p>
 * This can be used to help prevent over loading the user with repetitive
 * error messages such as turnout not found while loading a panel file due
 * to a connection failing. The name is free-form, but to avoid ambiguity it
 * should start with the package name (package.Class) for the primary using
 * class.
 *
 * @param name A unique identifer for preference.
 */
//@Override
/*public*/ void JmriUserPreferencesManager::setSessionPreferenceState(QString name, bool state) {
    if (state) {
        if (!sessionPreferenceList->contains(name)) {
            sessionPreferenceList->append(name);
        }
    } else {
        sessionPreferenceList->removeOne(name);
    }
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getSessionPreferenceState(QString name) {
    return sessionPreferenceList->contains(name);
}

/**
 * Show an info message ("don't forget ...") with a given dialog title and
 * user message. Use a given preference name to determine whether to show it
 * in the future. The combination of the classQString and item parameters
 * should form a unique value.
 *
 * @param title    message Box title
 * @param message  message to be displayed
 * @param strClass name of the calling class
 * @param item     name of the specific item this is used for
 */
//@Override
/*public*/ void JmriUserPreferencesManager::showInfoMessage(QString title, QString message, QString strClass, QString item) {
    showInfoMessage(title, message, strClass, item, false, true);
}

/**
 * Show an info message ("don't forget ...") with a given dialog title and
 * user message. Use a given preference name to determine whether to show it
 * in the future. added flag to indicate that the message should be
 * suppressed JMRI session only. The classQString {@literal &} item
 * parameters should form a unique value
 *
 * @param title          Message Box title
 * @param message        Message to be displayed
 * @param strClass       QString value of the calling class
 * @param item           QString value of the specific item this is used for
 * @param sessionOnly    Means this message will be suppressed in this JMRI
 *                       session and not be remembered
 * @param alwaysRemember Means that the suppression of the message will be
 *                       saved
 */
//@Override
/*public*/ void JmriUserPreferencesManager::showErrorMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember) {
    this->showMessage(title, message, strClass, item, sessionOnly, alwaysRemember, /*JOptionPane.ERROR_MESSAGE*/0);
}

/**
 * Show an info message ("don't forget ...") with a given dialog title and
 * user message. Use a given preference name to determine whether to show it
 * in the future. added flag to indicate that the message should be
 * suppressed JMRI session only. The classQString {@literal &} item
 * parameters should form a unique value
 *
 * @param title          Message Box title
 * @param message        Message to be displayed
 * @param strClass       QString value of the calling class
 * @param item           QString value of the specific item this is used for
 * @param sessionOnly    Means this message will be suppressed in this JMRI
 *                       session and not be remembered
 * @param alwaysRemember Means that the suppression of the message will be
 *                       saved
 */
//@Override
/*public*/ void JmriUserPreferencesManager::showInfoMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember) {
    this->showMessage(title, message, strClass, item, sessionOnly, alwaysRemember, /*JOptionPane.INFORMATION_MESSAGE*/1);
}

/**
 * Show an info message ("don't forget ...") with a given dialog title and
 * user message. Use a given preference name to determine whether to show it
 * in the future. added flag to indicate that the message should be
 * suppressed JMRI session only. The classQString {@literal &} item
 * parameters should form a unique value
 *
 * @param title          Message Box title
 * @param message        Message to be displayed
 * @param strClass       QString value of the calling class
 * @param item           QString value of the specific item this is used for
 * @param sessionOnly    Means this message will be suppressed in this JMRI
 *                       session and not be remembered
 * @param alwaysRemember Means that the suppression of the message will be
 *                       saved
 */
//@Override
/*public*/ void JmriUserPreferencesManager::showWarningMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember)
{
    this->showMessage(title, message, strClass, item, sessionOnly, alwaysRemember, /*JOptionPane.WARNING_MESSAGE*/2);
}

/*protected*/ void JmriUserPreferencesManager::showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type) {
    /*final*/ QString preference = strClass + "." + item;

    if (this->getSessionPreferenceState(preference)) {
        return;
    }
    if (!this->getPreferenceState(strClass, item)) {
        QWidget* container = new QWidget();
        //container.setLayout(new BoxLayout(container, BoxLayout.Y_AXIS));
        QVBoxLayout* containerLayout = new QVBoxLayout(container);
        containerLayout->addWidget(new QLabel(message));
        //I18N in ManagersBundle.properties
        /*final*/ QCheckBox* rememberSession = new QCheckBox(tr("Skip message for this session only?")); // NOI18N
        if (sessionOnly)
        {
         QFont f = rememberSession->font();
         f.setPointSize(10);
            rememberSession->setFont(f);
            containerLayout->addWidget(rememberSession);
        }
        //I18N in ManagersBundle.properties
        /*final*/ QCheckBox* remember = new QCheckBox(tr("Skip message in future?")); // NOI18N
        if (alwaysRemember)
        {
         QFont f = remember->font();
         f.setPointSize(10);
            remember->setFont(f);
            containerLayout->addWidget(remember);
        }
        JOptionPane::showMessageDialog(NULL, // center over parent component
                VPtr<QWidget>::asQVariant(container),
                title,
                type);
// TODO:
//        QMessageBox::information(nullptr, title, "message");  // need to add container
        if (remember->isChecked()) {
            this->setPreferenceState(strClass, item, true);
        }
        if (rememberSession->isChecked()) {
            this->setSessionPreferenceState(preference, true);
        }

    }
}

//@Override
/*public*/ QString JmriUserPreferencesManager::getComboBoxLastSelection(QString comboBoxName) {
    return this->comboBoxLastSelection->value(comboBoxName, "");
}

//@Override
/*public*/ void JmriUserPreferencesManager::setComboBoxLastSelection(QString comboBoxName, QString lastValue) {
    comboBoxLastSelection->insert(comboBoxName, lastValue);
    setChangeMade(false);
    this->saveComboBoxLastSelections();
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getCheckboxPreferenceState(QString name, bool defaultState) {
    return this->checkBoxLastSelection.value(name, defaultState);
}

//@Override
/*public*/ void JmriUserPreferencesManager::setCheckboxPreferenceState(QString name, bool state) {
    checkBoxLastSelection.insert(name, state);
    setChangeMade(false);
    this->saveCheckBoxLastSelections();
}


/*public*/ /*synchronized*/ bool JmriUserPreferencesManager::getChangeMade() {
    return dirty;
}

/*public*/ /*synchronized*/ void JmriUserPreferencesManager::setChangeMade(bool fireUpdate) {
    dirty = true;
    if (fireUpdate) {
        this->firePropertyChange(UserPreferencesManager::PREFERENCES_UPDATED, QVariant(), QVariant());
    }
}

//The reset is used after the preferences have been loaded for the first time
//@Override
/*public*/ /*synchronized*/ void JmriUserPreferencesManager::resetChangeMade() {
    dirty = false;
}

/**
 * Check if this object is loading preferences from storage.
 *
 * @return true if loading preferences; false otherwise
 */
/*protected*/ bool JmriUserPreferencesManager::isLoading() {
    return loading;
}

//@Override
/*public*/ void JmriUserPreferencesManager::setLoading() {
    loading = true;
}

//@Override
/*public*/ void JmriUserPreferencesManager::finishLoading() {
    loading = false;
    resetChangeMade();
}

/*public*/ void JmriUserPreferencesManager::displayRememberMsg() {
    if (loading) {
        return;
    }
    showInfoMessage(tr("Reminder"), tr("You can re-display this message from 'Edit|Preferences|Message' Menu."), getClassName(), "reminder"); // NOI18N
}

//@Override
/*public*/ QPoint JmriUserPreferencesManager::getWindowLocation(QString strClass) {
    if (windowDetails->contains(strClass)) {
        return windowDetails->value(strClass)->getLocation();
    }
    return QPoint();
}

//@Override
/*public*/ QSize JmriUserPreferencesManager::getWindowSize(QString strClass) {
    if (windowDetails->contains(strClass)) {
        return windowDetails->value(strClass)->getSize();
    }
    return QSize();
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getSaveWindowSize(QString strClass) {
    if (windowDetails->contains(strClass)) {
        return windowDetails->value(strClass)->getSaveSize();
    }
    return false;
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getSaveWindowLocation(QString strClass) {
    if (windowDetails->contains(strClass)) {
        return windowDetails->value(strClass)->getSaveLocation();
    }
    return false;
}

//@Override
/*public*/ void JmriUserPreferencesManager::setSaveWindowSize(QString strClass, bool b) {
    if ((strClass == "") || (strClass == (JMRI_UTIL_JMRI_JFRAME))) {
        return;
    }
    if (!windowDetails->contains(strClass)) {
        windowDetails->insert(strClass, new WindowLocations());
    }
    windowDetails->value(strClass)->setSaveSize(b);
    this->saveWindowDetails();
}

//@Override
/*public*/ void JmriUserPreferencesManager::setSaveWindowLocation(QString strClass, bool b) {
    if ((strClass == "") || (strClass == (JMRI_UTIL_JMRI_JFRAME))) {
        return;
    }
    if(strClass.endsWith(":Preferences"))
     qDebug() << "halt";
    if (!windowDetails->contains(strClass)) {
        windowDetails->insert(strClass, new WindowLocations());
    }
    windowDetails->value(strClass)->setSaveLocation(b);
    this->saveWindowDetails();
}

//@Override
/*public*/ void JmriUserPreferencesManager::setWindowLocation(QString strClass, QPoint location) {
    if ((strClass == "") || (strClass == (JMRI_UTIL_JMRI_JFRAME))) {
        return;
    }
    if(strClass.endsWith(":Preferences"))
     qDebug() << "halt";
    if (!windowDetails->contains(strClass)) {
        windowDetails->insert(strClass, new WindowLocations());
    }
    windowDetails->value(strClass)->setLocation(location);
    this->saveWindowDetails();
}

//@Override
/*public*/ void JmriUserPreferencesManager::setWindowSize(QString strClass, QSize dim) {
    if ((strClass == nullptr) || (strClass == (JMRI_UTIL_JMRI_JFRAME))) {
        return;
    }
    if(strClass.endsWith(":Preferences"))
    {
     //qDebug() << "halt";
     strClass = strClass.replace(":Preferences", "");
    }
    if (!windowDetails->contains(strClass)) {
        windowDetails->insert(strClass, new WindowLocations());
    }
    windowDetails->value(strClass)->setSize(dim);
    this->saveWindowDetails();
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getWindowList() {
    return QStringList(windowDetails->keys());
}

//@Override
/*public*/ void JmriUserPreferencesManager::setProperty(QString strClass, QString key, QVariant value) {
    if (strClass == ("JmriJFrame")) {
        return;
    }
    if(strClass.endsWith(":Preferences"))
     qDebug() << "halt";
    if (!windowDetails->contains(strClass)) {
        windowDetails->insert(strClass, new WindowLocations());
    }
    windowDetails->value(strClass)->setProperty(key, value);
    this->saveWindowDetails();
}

//@Override
/*public*/ QVariant JmriUserPreferencesManager::getProperty(QString strClass, QString key) {
    if (windowDetails->contains(strClass)) {
        return windowDetails->value(strClass)->getProperty(key);
    }
    return QVariant();
}

//@Override
/*public*/ QSet<QString> JmriUserPreferencesManager::getPropertyKeys(QString strClass) {
 if (windowDetails->contains(strClass)) {
     return windowDetails->value(strClass)->getPropertyKeys();
 }
 return QSet<QString>();
}

//@Override
/*public*/ bool JmriUserPreferencesManager::hasProperties(QString strClass) {
 bool b = windowDetails->contains(strClass);
 return b;
}

//@Override
/*public*/ QString JmriUserPreferencesManager::getClassDescription(QString strClass) {
    if ( classPreferenceList->contains(strClass)) {
        return  classPreferenceList->value(strClass)->getDescription();
    }
    return QString();
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getPreferencesClasses() {
    return QStringList(this-> classPreferenceList->keys());
}

/**
 * Given that we know the class as a string, we will try and attempt to
 * gather details about the preferences that has been added, so that we can
 * make better sense of the details in the preferences window.
 * <p>
 * This looks for specific methods within the class called
 * "getClassDescription" and "setMessagePreferencesDetails". If found it
 * will invoke the methods, this will then trigger the class to send details
 * about its preferences back to this code.
 */
#if 0
//@Override
/*public*/ void JmriUserPreferencesManager::setClassDescription(QString strClass)
{
  QObject* cl;
  try
  {
   /*Class<?>*/ cl = (QObject*)Class::forName(strClass);

//   QString clazz = strClass;
//   if(strClass.contains("."))
//    clazz = strClass.mid(strClass.lastIndexOf(".")+1);
//    int typeId = QMetaType::type(clazz.toLocal8Bit());

//    if(typeId > 0)
//    {
//   #if QT_VERSION < 0x050000
//     cl = (QObject*)QMetaType::construct(typeId);
//   #else
//     cl = (QObject*)QMetaType::create(typeId);
//   #endif
//    }
//    else
//     return;
    //Object t = cl.newInstance();
    bool classDesFound = false;
    bool classSetFound = false;
  QString desc = "";
  //Method method;
  //look through declared methods first, then all methods
  try
  {
   //method = cl.getDeclaredMethod("getClassDescription");
   int ix = cl->metaObject()->indexOfMethod(QMetaObject::normalizedSignature("getClassDescription()"));
   if(ix >= 0)
   {
      //desc = (QString) method.invoke(t);
   if(QMetaObject::invokeMethod(cl, "getClassDescription", Qt::DirectConnection, Q_RETURN_ARG(QString, desc)))
      classDesFound = true;
   else
    throw new NoSuchMethodException(tr("method %1 not found for class %2").arg("getClassDescription").arg(strClass));
//  } catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
   }
   else throw new NoSuchMethodException(tr("method %1 not found for class %2").arg("getClassDescription").arg(strClass));
  }
  catch(NoSuchMethodException* ex)
  {
   log->debug(ex->getMessage());
   classDesFound = false;
  }
//  if (!classDesFound)
//  {
   //try {
   //method = cl.getMethod("getClassDescription");
//                desc = (QString) method.invoke(t);
//            } catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
//                log->debug(ex.toQString());
//                classDesFound = false;
//            }
//  }
  if (classDesFound)
  {
   if (! classPreferenceList->contains(strClass)) {
        classPreferenceList->insert(strClass, new ClassPreferences(desc));
   } else {
        classPreferenceList->value(strClass)->setDescription(desc);
   }
   this->savePreferencesState();
  }

  try {
   //method = cl.getDeclaredMethod("setMessagePreferencesDetails");
   int ix = cl->metaObject()->indexOfMethod(QMetaObject::normalizedSignature("setMessagePreferencesDetails()"));
   if(ix >= 0)
   {
    //method.invoke(t);
    if(QMetaObject::invokeMethod(cl, "setMessagePreferencesDetails", Qt::DirectConnection))
      classSetFound = true;
     else
      throw new NoSuchMethodException(tr("method %1 not found for class %2").arg("setMessagePreferencesDetails").arg(strClass));
   }
    else throw new NoSuchMethodException(tr("method %1 not found for class %2").arg("setMessagePreferencesDetails").arg(strClass));

//  } catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
  }
  catch(NoSuchMethodException ex)
  {
      log->debug(ex->getMessage()); // *TableAction.setMessagePreferencesDetails() method is routinely not present in multiple classes
      classSetFound = false;
  }
//  if (!classSetFound) {
//      try {
//          method = cl.getMethod("setMessagePreferencesDetails");
//          method.invoke(t);
//      } catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
//          log->debug(ex.toQString());
//      }
//  }

    } catch (ClassNotFoundException* ex) {
        log->warn(tr("class name \"%1\" cannot be found, perhaps an expected plugin is missing?").arg(strClass));
  }
//     catch (IllegalAccessException ex) {
//        log->error("unable to access class \"{}\"", strClass, ex);
//    } catch (InstantiationException* ex) {
//        log->error("unable to get a class name \"{}\"", strClass, ex);
//    }
}
#else
//@Override
/*public*/ void JmriUserPreferencesManager::setClassDescription(QString strClass)
{
 try
 {
     Class* cl = Class::forName(strClass);
     QObject* t;
     try {
         t = (QObject*)cl->newInstance();
     }
     //catch (IllegalArgumentException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException | java.lang.reflect.InvocationTargetException ex)
     catch(InvocationTargetException* ex)
     {
         log->error(tr("setClassDescription(%1) failed in newInstance").arg(strClass), ex);
         //return;
         t = (QObject*)cl;
     }
     bool classDesFound;
     bool classSetFound;
     QString desc = QString();
     //Method method;
     //look through declared methods first, then all methods
     try
     {
         //method = cl.getDeclaredMethod("getClassDescription");
         //desc = (String) method.invoke(t);
         if(QMetaObject::invokeMethod(t, "getClassDescription", Qt::DirectConnection, Q_RETURN_ARG(QString, desc)))
          classDesFound = true;
         else
          throw new NoSuchMethodException(tr("method %1 not found for class %2").arg("getClassDescription").arg(strClass));
     }
     //catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex)
     catch(NoSuchMethodException* ex)
     {
      if(log->isDebugEnabled())
         log->debug(tr("Unable to call declared method \"getClassDescription\" with exception %1").arg(ex->toString()));
      classDesFound = false;
      return;
     }
#if 0
     if (!classDesFound) {
         try {
             method = cl.getMethod("getClassDescription");
             desc = (String) method.invoke(t);
         } catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
             log.debug("Unable to call undeclared method \"getClassDescription\" with exception {}", ex.toString());
             classDesFound = false;
         }
     }
#endif
     if (classDesFound) {
         if (!classPreferenceList->contains(strClass)) {
             classPreferenceList->insert(strClass, new ClassPreferences(desc));
         } else {
             classPreferenceList->value(strClass)->setDescription(desc);
         }
         this->savePreferencesState();
     }

     try {
//         method = cl.getDeclaredMethod("setMessagePreferencesDetails");
//         method.invoke(t);
      if(QMetaObject::invokeMethod(t, "setMessagePreferencesDetails", Qt::DirectConnection))
         classSetFound = true;
      else
       throw new NoSuchMethodException(tr("method %1 not found for class %2").arg("setMessagePreferencesDetails").arg(strClass));

     }
     //catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex)
     catch(NoSuchMethodException* ex)
     {
         // TableAction.setMessagePreferencesDetails() method is routinely not present in multiple classes
         log->debug(tr("Unable to call declared method \"setMessagePreferencesDetails\" with exception %1").arg(ex->toString()));
         classSetFound = false;
     }
#if 0
     if (!classSetFound) {
         try {
             method = cl.getMethod("setMessagePreferencesDetails");
             method.invoke(t);
         } catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
             log.debug("Unable to call undeclared method \"setMessagePreferencesDetails\" with exception {}", ex.toString());
         }
     }
 #endif
 } catch (ClassNotFoundException* ex) {
     log->warn(tr("class name \"%1\" cannot be found, perhaps an expected plugin is missing?").arg(strClass));
 } catch (IllegalAccessException* ex) {
     log->error(tr("unable to access class \"%1\"").arg(strClass), ex);
 } catch (InstantiationException* ex) {
     log->error(tr("unable to get a class name \"%1\"").arg(strClass), ex);
 }
}
#endif

/**
 * Add descriptive details about a specific message box, so that if it needs
 * to be reset in the preferences, then it is easily identifiable. displayed
 * to the user in the preferences GUI.
 *
 * @param strClass      QString value of the calling class/group
 * @param item          QString value of the specific item this is used for.
 * @param description   A meaningful description that can be used in a label
 *                      to describe the item
 * @param options       A map of the integer value of the option against a
 *                      meaningful description.
 * @param defaultOption The default option for the given item.
 */
//@Override
/*public*/ void JmriUserPreferencesManager::setMessageItemDetails(QString strClass, QString item, QString description, QMap<int, QString>* options, int defaultOption) {
    if (! classPreferenceList->contains(strClass)) {
         classPreferenceList->insert(strClass, new ClassPreferences());
    }
    QList<MultipleChoice*>* a =  classPreferenceList->value(strClass)->getMultipleChoiceList();
    for (int i = 0; i < a->size(); i++) {
        if (a->at(i)->getItem() == (item)) {
            a->at(i)->setMessageItems(description, options, defaultOption);
            return;
        }
    }
    a->append(new MultipleChoice(description, item, options, defaultOption));
}

//@Override
/*public*/ QMap<int, QString>* JmriUserPreferencesManager::getChoiceOptions(QString strClass, QString item) {
    if ( classPreferenceList->contains(strClass)) {
        QList<MultipleChoice*>* a =  classPreferenceList->value(strClass)->getMultipleChoiceList();
        for (int i = 0; i < a->size(); i++) {
            if (a->at(i)->getItem() == (item)) {
                return a->at(i)->getOptions();
            }
        }
    }
    return nullptr;
}

//@Override
/*public*/ int JmriUserPreferencesManager::getMultipleChoiceSize(QString strClass) {
    if ( classPreferenceList->contains(strClass)) {
        return  classPreferenceList->value(strClass)->getMultipleChoiceListSize();
    }
    return 0;
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getMultipleChoiceList(QString strClass) {
    if ( classPreferenceList->contains(strClass)) {
        QList<MultipleChoice*>* a =  classPreferenceList->value(strClass)->getMultipleChoiceList();
        QStringList list = QStringList();
        for (int i = 0; i < a->size(); i++) {
            list.append(a->at(i)->getItem());
        }
        return list;
    }
    return QStringList();
}

//@Override
/*public*/ QString JmriUserPreferencesManager::getChoiceName(QString strClass, int n) {
    if ( classPreferenceList->contains(strClass)) {
        return  classPreferenceList->value(strClass)->getChoiceName(n);
    }
    return nullptr;
}

//@Override
/*public*/ QString JmriUserPreferencesManager::getChoiceDescription(QString strClass, QString item) {
    if ( classPreferenceList->contains(strClass)) {
        QList<MultipleChoice*>* a =  classPreferenceList->value(strClass)->getMultipleChoiceList();
        for (int i = 0; i < a->size(); i++) {
            if (a->at(i)->getItem() == (item)) {
                return a->at(i)->getOptionDescription();
            }
        }
    }
    return nullptr;
}

//@Override
/*public*/ int JmriUserPreferencesManager::getMultipleChoiceOption(QString strClass, QString item) {
    if ( classPreferenceList->contains(strClass)) {
        QList<MultipleChoice*>* a =  classPreferenceList->value(strClass)->getMultipleChoiceList();
        for (int i = 0; i < a->size(); i++) {
            if (a->at(i)->getItem() == (item)) {
                return a->at(i)->getValue();
            }
        }
    }
    return 0;
}

//@Override
/*public*/ int JmriUserPreferencesManager::getMultipleChoiceDefaultOption(QString strClass, QString choice) {
    if ( classPreferenceList->contains(strClass)) {
        QList<MultipleChoice*>* a =  classPreferenceList->value(strClass)->getMultipleChoiceList();
        for (int i = 0; i < a->size(); i++) {
            if (a->at(i)->getItem() == (choice)) {
                return a->at(i)->getDefaultValue();
            }
        }
    }
    return 0;
}

//@Override
/*public*/ void JmriUserPreferencesManager::setMultipleChoiceOption(QString strClass, QString /*choice*/, QString value) {
    if (! classPreferenceList->contains(strClass)) {
         classPreferenceList->insert(strClass, new ClassPreferences());
    }
//     classPreferenceList->value(strClass)->getMultipleChoiceList().stream()
//            .filter((mc) -> (mc->getItem() == (choice))).forEachOrdered((mc) -> {
//        mc.setValue(value);
//    });
    foreach(MultipleChoice* mc, *classPreferenceList->value(strClass)->getMultipleChoiceList())
    {
     mc->setValue(value);
    }
    this->savePreferencesState();
}

//@Override
/*public*/ void JmriUserPreferencesManager::setMultipleChoiceOption(QString strClass, QString choice, int value) {
    if (! classPreferenceList->contains(strClass)) {
         classPreferenceList->insert(strClass, new ClassPreferences());
    }
    bool set = false;
    foreach (MultipleChoice* mc,  *classPreferenceList->value(strClass)->getMultipleChoiceList()) {
        if (mc->getItem() == (choice)) {
            mc->setValue(value);
            set = true;
        }
    }
    if (!set) {
         classPreferenceList->value(strClass)->getMultipleChoiceList()->append(new MultipleChoice(choice, value));
        setClassDescription(strClass);
    }
    displayRememberMsg();
    this->savePreferencesState();
}

//@Override
/*public*/ void JmriUserPreferencesManager::setTableColumnPreferences(QString table, QString column, int order, int width, SortOrder sort, bool hidden) {
#if 1
 JmriJTablePersistenceManager* manager = (JmriJTablePersistenceManager*)InstanceManager::getNullableDefault("JmriJTablePersistenceManager");
    if (manager != nullptr) {
        manager->setTableColumnPreferences(table, column, order, width, sort, hidden);
    }
#endif
}

//@Override
/*public*/ int JmriUserPreferencesManager::getTableColumnOrder(QString table, QString column) {
#if 1
 JmriJTablePersistenceManager* manager = (JmriJTablePersistenceManager*)InstanceManager::getNullableDefault("JmriJTablePersistenceManager");
 if (manager != nullptr)
 {
  TableColumnPreferences* preferences = manager->getTableColumnPreferences(table, column);
  if (preferences != nullptr) {
      return preferences->getOrder();
  }
 }
#endif
 return -1;
}

//@Override
/*public*/ int JmriUserPreferencesManager::getTableColumnWidth(QString table, QString column) {
#if 1
 JmriJTablePersistenceManager* manager = (JmriJTablePersistenceManager*)InstanceManager::getNullableDefault("JmriJTablePersistenceManager");
    if (manager != nullptr) {
        TableColumnPreferences* preferences = manager->getTableColumnPreferences(table, column);
        if (preferences != nullptr) {
            return preferences->getWidth();
        }
    }
#endif
    return -1;
}

//@Override
/*public*/ int JmriUserPreferencesManager::getTableColumnSort(QString table, QString column) {
#if 1
 JmriJTablePersistenceManager* manager = (JmriJTablePersistenceManager*)InstanceManager::getNullableDefault("JmriJTablePersistenceManager");
    if (manager != nullptr) {
        TableColumnPreferences* preferences = manager->getTableColumnPreferences(table, column);
        if (preferences != nullptr) {
            return preferences->getSort();
        }
    }
    return (int)UNSORTED;
#endif
    return 0;
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getTableColumnHidden(QString table, QString column)
{
#if 1
 JmriJTablePersistenceManager* manager = (JmriJTablePersistenceManager*)InstanceManager::getNullableDefault("JmriJTablePersistenceManager");
 if (manager != nullptr) {
     TableColumnPreferences* preferences = manager->getTableColumnPreferences(table, column);
     if (preferences != nullptr) {
         return preferences->getHidden();
     }
 }
#endif
    return false;
}

//@Override
/*public*/ QString JmriUserPreferencesManager::getTableColumnAtNum(QString table, int i) {
#if 1
    JmriJTablePersistenceManager* manager = (JmriJTablePersistenceManager*)InstanceManager::getNullableDefault("JmriJTablePersistenceManager");
    if (manager != nullptr) {
        QMap<QString, TableColumnPreferences*>* map = manager->getTableColumnPreferences(table);
        //for (Map.Entry<QString, TableColumnPreferences> entry : map.entrySet())
        QMapIterator<QString, TableColumnPreferences*> entry(*map);
        while(entry.hasNext())
        {
         entry.next();
            if ((entry.value())->getOrder() == i) {
                return entry.key();
            }
        }
    }
#endif
    return QString();
}

/**
 * Returns an empty list, since this class does not track table state.
 *
 * @return an empty list
 */
//@Override
/*public*/ QStringList JmriUserPreferencesManager::getTablesList() {
    return QStringList();
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getTablesColumnList(QString table) {
#if 1
    JmriJTablePersistenceManager* manager = (JmriJTablePersistenceManager*)InstanceManager::getNullableDefault("JmriJTablePersistenceManager");
    if (manager != nullptr) {
        QMap<QString, TableColumnPreferences*>* map = manager->getTableColumnPreferences(table);
        return QStringList(map->keys());
    }
#endif
    return QStringList();
}

/*public*/ QString JmriUserPreferencesManager::getClassDescription() {
    return "Preference Manager";
}

/*protected*/ /*final*/ QString JmriUserPreferencesManager::getClassName() {
    return "jmri.managers.JmriUserPreferencesManager";
}

/*protected*/ /*final*/ ClassPreferences* JmriUserPreferencesManager::getClassPreferences(QString strClass) {
    return this-> classPreferenceList->value(strClass);
}

//@Override
/*public*/ int JmriUserPreferencesManager::getPreferencesSize(QString strClass) {
    if ( classPreferenceList->contains(strClass)) {
        return  classPreferenceList->value(strClass)->getPreferencesSize();
    }
    return 0;
}

/*public*/ /*final*/ void JmriUserPreferencesManager::readUserPreferences()
{
 log->trace("starting readUserPreferences");
 this->allowSave = false;
 this->loading = true;
 File* perNodeConfig = nullptr;
 try {
     perNodeConfig = FileUtil::getFile(FileUtil::PROFILE + /*Profile::PROFILE*/"profile" + "/" + NodeIdentity::storageIdentity() + "/" + /*Profile::UI_CONFIG*/"user-interface.xml"); // NOI18N
     if (!perNodeConfig->canRead()) {
         perNodeConfig = nullptr;
     }
 } catch (FileNotFoundException* ex) {
     // ignore - this only means that sharedConfig does not exist.
 }
 catch (IOException* ex) {
    // ignore - this only means that sharedConfig does not exist.
 }
 if (perNodeConfig != nullptr)
 {
  file = perNodeConfig;
  this->readComboBoxLastSelections();
  this->readPreferencesState();
  this->readSimplePreferenceState();
  this->readWindowDetails();
 }
 else
 {
  try
  {
  file = FileUtil::getFile(FileUtil::PROFILE + /*Profile::UI_CONFIG_FILENAME*/"UserPrefsProfileConfig.xml");
  if (file->exists())
  {
//   log->debug(tr("start load user pref file: %1").arg(file->getPath()));
//                try {
   ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->load(file, true);
   this->allowSave = true;
   this->savePreferences(); // write new preferences format immediately
//                } catch (JmriException* e) {
//                    log->error("Unhandled problem loading configuration: " + e);
//                } catch (NullPointerException* e) {
//                    log->error("NPE when trying to load user pref " + file);
//                }
  } else {
      // if we got here, there is no saved user preferences
      log->info("No saved user preferences file");
  }
        } catch (FileNotFoundException* ex) {
            // ignore - this only means that UserPrefsProfileConfig.xml does not exist.
        }
 }
 this->loading = false;
 this->allowSave = true;
}

/*private*/ void JmriUserPreferencesManager::readComboBoxLastSelections() {
    QDomElement element = this->readElement(COMBOBOX_ELEMENT, COMBOBOX_NAMESPACE);
    if (element != QDomElement()) {
//        element.getChildren("comboBox").stream().forEach((combo) -> {
//            comboBoxLastSelection.put(combo.attribute("name"), combo.attribute("lastSelected"));
//        });
     QDomNodeList nl = element.elementsByTagName("comboBox");
     for(int i = 0; i < nl.size(); i++)
     {
      QDomNode combo = nl.at(i);
      comboBoxLastSelection->insert(combo.toElement().attribute("name"), combo.toElement().attribute("lastSelected"));
     }
    }
}

/*private*/ void JmriUserPreferencesManager::saveComboBoxLastSelections()
{
 this->setChangeMade(false);
 if (this->allowSave && !comboBoxLastSelection->isEmpty())
 {
     QDomElement element = doc.createElementNS(COMBOBOX_NAMESPACE, COMBOBOX_ELEMENT);
     // Do not store blank last entered/selected values
//        comboBoxLastSelection.entrySet().stream().
//                filter((cbls) -> (cbls.getValue() != NULL && !cbls.getValue().isEmpty())).map((cbls) -> {
//            QDomElement combo = doc.createElement("comboBox");
//     foreach()
//         combo.setAttribute("name", cbls.getKey());
//         combo.setAttribute("lastSelected", cbls.getValue());
//         return combo;
//     }).forEach((combo) -> {
//         element.addContent(combo);
//     });
     QHashIterator<QString, QString> cbls(*comboBoxLastSelection);
     while(cbls.hasNext())
     {
      cbls.next();
      QDomElement combo = doc.createElement("comboBox");
      combo.setAttribute("name", cbls.key());
      combo.setAttribute("lastSelected", cbls.value());
      element.appendChild(combo);
     }
     this->saveElement(element);
     this->resetChangeMade();
 }
}

/*private*/ void JmriUserPreferencesManager::readCheckBoxLastSelections() {
    QDomElement element = this->readElement(CHECKBOX_ELEMENT, CHECKBOX_NAMESPACE);
    if (!element.isNull()) {
//        element.getChildren("checkBox").stream().forEach(checkbox ->
//            checkBoxLastSelection.put(checkbox.getAttributeValue("name"), "yes".equals(checkbox.getAttributeValue("lastChecked"))));
     QDomNodeList list = element.elementsByTagName("checkBox");
     for(int i=0; i < list.count(); i++){
      QDomElement checkbox = list.at(i).toElement();
      checkBoxLastSelection.insert(checkbox.attribute("name"), "yes" ==(checkbox.attribute("lastChecked")));
     }
    }
}

/*private*/ void JmriUserPreferencesManager::saveCheckBoxLastSelections() {
    this->setChangeMade(false);
    if (this->allowSave && !checkBoxLastSelection.isEmpty()) {
        QDomElement element = doc.createElementNS(CHECKBOX_ELEMENT, CHECKBOX_NAMESPACE);
        // Do not store blank last entered/selected values
//        checkBoxLastSelection.entrySet().stream().
//                filter(cbls -> (cbls.getValue() != null)).map(cbls -> {
        QMapIterator<QString, bool> cbls(checkBoxLastSelection);
        while(cbls.hasNext())
        {
         cbls.next();
         if(cbls.value())
         {
            QDomElement checkbox = doc.createElement("checkBox");
            checkbox.setAttribute("name", cbls.key());
            checkbox.setAttribute("lastChecked", cbls.value() ? "yes" : "no");
//            return checkbox;
            element.appendChild(checkbox);
        };//).forEach(element::addContent);
        this->saveElement(element);
        this->resetChangeMade();
        }
    }
}

/*private*/ void JmriUserPreferencesManager::readPreferencesState()
{
#if 1
    QDomElement element = this->readElement(CLASSPREFS_ELEMENT, CLASSPREFS_NAMESPACE);
    if (element != QDomElement())
    {
//        element.getChildren("preferences").stream().forEach((preferences) -> {
     QDomNodeList pnl = element.elementsByTagName("preferences");
     for(int i = 0; i < pnl.size(); i++)
     {
      QDomElement preferences = pnl.at(i).toElement();
      QString clazz = preferences.attribute("class");
      log->debug(tr("Reading class preferences for \"%1\"").arg(clazz));
      //preferences.getChildren("multipleChoice").stream().forEach((mc) -> {
      QDomNodeList mcnl = preferences.elementsByTagName("multipleChoice");
      for(int j = 0; j < mcnl.size(); j++)
      {
       QDomElement mc = mcnl.at(j).toElement();
//          mc.getChildren("option").stream().forEach((option) -> {
       QDomNodeList onl = mc.elementsByTagName("option");
       for(int k = 0; k < onl.size(); k++)
       {
        QDomElement option = onl.at(k).toElement();
              int value = 0;
//              try {
              bool ok;
                  option.attribute("value").toInt(&ok);
              if(!ok)
              {
                  log->error("failed to convert positional attribute");
              }
              this->setMultipleChoiceOption(clazz, option.attribute("item"), value);
//          });
        }
//      });
      }
//      preferences.getChildren("reminderPrompts").stream().forEach((rp) -> {
      QDomNodeList rpnl = preferences.elementsByTagName("reminderPropmpts");
      for(int i = 0; i < rpnl.size(); i++)
      {
       QDomElement rp = rpnl.at(i).toElement();
//          rp.getChildren("reminder").stream().forEach((reminder) -> {
       QDomNodeList rnl = rp.elementsByTagName("reminder");
       for(int k = 0; k < rnl.size(); k++)
       {
        QDomElement reminder = rnl.at(k).toElement();
        log->debug(tr("Setting preferences state \"true\" for \"%1\", \"%2\"").arg(clazz).arg(reminder.text()));
        this->setPreferenceState(clazz, reminder.text(), true);
//          });
       }
//      });
      }
//   });
     }
    }
#endif
}

/*private*/ void JmriUserPreferencesManager::savePreferencesState()
{
 this->setChangeMade(true);
 if (this->allowSave)
 {
  QDomElement element = doc.createElementNS(CLASSPREFS_NAMESPACE, CLASSPREFS_ELEMENT);
  //this-> classPreferenceList->keySet().stream().forEach((name) -> {
  foreach(QString name, classPreferenceList->keys())
  {
   ClassPreferences* cp = this-> classPreferenceList->value(name);
   if (!cp->multipleChoiceList->isEmpty() || !cp->preferenceList->isEmpty())
   {
    QDomElement clazz = doc.createElement("preferences");
    clazz.setAttribute("class", name);
    if (!cp->multipleChoiceList->isEmpty()) {
        QDomElement choices = doc.createElement("multipleChoice");
        // only save non-default values
        //cp.multipleChoiceList.stream().filter((mc) -> (mc.getDefaultValue() != mc.getValue())).forEach((mc) -> {
        foreach(MultipleChoice* mc, *cp->multipleChoiceList)
        {
         QDomElement option;
            choices.appendChild(option = doc.createElement("option"));
                    option.setAttribute("item", mc->getItem());
                    option.setAttribute("value", (mc->getValue()));
        } //);
        if (!choices.childNodes().isEmpty()) {
            clazz.appendChild(choices);
        }
    }
    if (!cp->preferenceList->isEmpty()) {
        QDomElement reminders = doc.createElement("reminderPrompts");
        //cp.preferenceList.stream().filter((pl) -> (pl.getState())).forEach((pl) -> {
        foreach(PreferenceList* pl, *cp->preferenceList)
        {
            reminders.appendChild(doc.createElement("reminder").appendChild(doc.createTextNode( pl->getItem())));
        }//);
        if (!reminders.childNodes().isEmpty()) {
            clazz.appendChild(reminders);
        }
    }
    element.appendChild(clazz);
   }
  } //);
  if (!element.childNodes().isEmpty()) {
      this->saveElement(element);
  }
 }
}

/*private*/ void JmriUserPreferencesManager::readSimplePreferenceState() {
    QDomElement element = this->readElement(SETTINGS_ELEMENT, SETTINGS_NAMESPACE);
    if (element != QDomElement()) {
//        element.getChildren("setting").stream().forEach((setting) -> {
//            this->simplePreferenceList->add(setting.getText());
//        });
     QDomNodeList nl = element.elementsByTagName("setting");
     for(int i = 0; i< nl.size(); i++)
     {
      QDomNode setting = nl.at(i);
      this->simplePreferenceList->append(setting.toElement().text());
     }
    }
}

/*private*/ void JmriUserPreferencesManager::saveSimplePreferenceState() {
    this->setChangeMade(false);
    if (this->allowSave) {
        QDomElement element = doc.createElementNS(SETTINGS_NAMESPACE, SETTINGS_ELEMENT);
//        getSimplePreferenceStateList().stream().forEach((setting) -> {
//            element.addContent(doc.createElement("setting").addContent(setting));
//        });
        foreach(QString setting, getSimplePreferenceStateList())
        {
         QDomElement elem = doc.createElement("setting");
         elem.appendChild(doc.createTextNode(setting));
         element.appendChild(elem);
        }

        this->saveElement(element);
        this->resetChangeMade();
    }
}

/*private*/ void JmriUserPreferencesManager::readWindowDetails()
{
 // TODO: COMPLETE!
 QDomElement element = this->readElement(WINDOWS_ELEMENT, WINDOWS_NAMESPACE);
 if (!element.isNull())
 {
  //element.getChildren("window").stream().forEach((window) -> {
  QDomNodeList nl = element.elementsByTagName("window");
  for(int i = 0; i < nl.size(); i++)
  {
   QDomElement window = nl.at(i).toElement();
   QString reference = window.attribute("class");
   log->debug(tr("Reading window details for %1").arg(reference));
   try
   {
    bool ok;
    if (window.attribute("locX") != "" && window.attribute("locX") != "")
    {
     double x = window.attribute("locX").toDouble(&ok);
     if(!ok) throw new DataConversionException();
     double y = window.attribute("locY").toDouble(&ok);
     if(!ok) throw new DataConversionException();
     this->setWindowLocation(reference, QPoint((int) x, (int) y));
    }
    if (window.attribute("width") != "" && window.attribute("height") != "")
    {
     double width = window.attribute("width").toDouble(&ok);
     if(!ok) throw new DataConversionException();
     double height = window.attribute("height").toDouble(&ok);
     if(!ok) throw new DataConversionException();
     this->setWindowSize(reference, QSize((int) width, (int) height));
    }
   }
   catch(DataConversionException* ex)
   {
    log->error(tr("Unable to read dimensions of window \"%1\"").arg(reference));
   }
   if (window.firstChildElement(PROPERTIES) != QDomElement())
   {
//          window.getChild("properties").getChildren().stream().forEach((property) -> {
    QDomNodeList nl = window.firstChildElement(PROPERTIES).childNodes();
    for(int i = 0;  i < nl.size(); i++)
    {
     QDomElement property = nl.at(i).toElement();
     QString key = property.firstChildElement("key").text();
     if(key == "") continue; // added ACK
     QString _class = property.firstChildElement(VALUE).attribute("class");
     QString value = property.firstChildElement(VALUE).text();
     this->setProperty(reference, key, value);
#if 1
     try
     {
      //Class<?> cl = Class.forName(property.getChild("value").attribute("class"));
      QObject* cl = (QObject*)Class::forName(_class);
      if(cl != NULL)
      {
       //Constructor<?> ctor = cl.getConstructor(new Class<?>[]{QString.class});
       int cix;
       if(cix = cl->metaObject()->indexOfConstructor(QMetaObject::normalizedSignature("QString")) >= 0)
       {
        QObject* ctor = cl->metaObject()->newInstance(Q_ARG(QString,QMetaObject::normalizedSignature(property.firstChildElement("value").text().toLatin1())));
        //Object value = ctor.newInstance(new Object[]{property.getChild("value").getText()});
        QString value;
        QMetaObject::invokeMethod(ctor, QMetaObject::normalizedSignature(property.firstChildElement("value").text().toLatin1()),Qt::DirectConnection,Q_ARG(QString, value));
        if(value.isEmpty()) throw new NullPointerException();
        log->debug(tr("Setting property %1 for %2 to %3").arg(key).arg(reference).arg(value));
        this->setProperty(reference, key, value);
       }
       else throw new NoSuchMethodException();
//      catch (ClassNotFoundException* | NoSuchMethodException | SecurityException | InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException ex)
      }
     }
     catch( ClassNotFoundException* ex)
     {
       log->error(tr("Unable to retrieve property \"%1\" for window \"%2\"").arg(key).arg(reference));
     }
     catch( NoSuchMethodException* ex)
     {
       log->error(tr("Unable to retrieve property \"%1\" for window \"%2\"").arg(key).arg(reference));
     }
     catch (NullPointerException* ex)
     {
      // NULL properties do not get set
      log->debug(tr("Property \"%1\" for window \"%2\" is NULL").arg(key).arg(reference));
     }
#endif
    }//);
   }
  } // foreach window
 }
}

/*private*/ void JmriUserPreferencesManager::saveWindowDetails() {
 this->setChangeMade(false);
 if (this->allowSave)
 {
  if (!windowDetails->isEmpty())
  {
   QDomElement element = doc.createElementNS(WINDOWS_NAMESPACE, WINDOWS_ELEMENT);
   //for (Entry<QString, WindowLocations> entry : windowDetails->entrySet()) {
   QHashIterator<QString, WindowLocations*> entry(* windowDetails);
   while(entry.hasNext())
   {
    entry.next();
    QDomElement window = doc.createElement("window");
    window.setAttribute("class", entry.key());
    if(entry.key() == "jmri.jmrit.beantable.ListedTableFrame:Turnout Table" )
    {
     if(log->isDebugEnabled())
      log->debug("x=0");
    }
    if (entry.value()->saveLocation)
    {
     try
     {
         window.setAttribute("locX", entry.value()->getLocation().x());
         window.setAttribute("locY", entry.value()->getLocation().y());
     }
     catch (NullPointerException* ex) {
         // Expected if the location has not been set or the window is open
     }
    }
    if (entry.value()->saveSize) {
        try {
            double height = entry.value()->getSize().height();
            double width = entry.value()->getSize().width();
            // Do not save the width or height if set to zero
            if (!(height == 0.0 && width == 0.0)) {
                window.setAttribute("width", (width));
                window.setAttribute("height", (height));
            }
        } catch (NullPointerException* ex) {
            // Expected if the size has not been set or the window is open
        }
    }
    if (!entry.value()->parameters.isEmpty())
    {
     QDomElement properties = doc.createElement("properties");

     //entry.value().parameters.entrySet().stream().map((property) -> {
     //foreach(QVariant property , entry.value()->parameters.values())
     QMapIterator<QString, QVariant> iter(entry.value()->parameters);
     while (iter.hasNext())
     {
      iter.next();
      QString keyName = iter.key();
      QVariant value = iter.value();
      QDomElement propertyElement = doc.createElement("property");
      //propertyElement.appendChild(doc.createElement("key").appendChild(doc.createTextNode(property.typeName())));
      QDomElement key = doc.createElement("key");
      key.appendChild(doc.createTextNode(keyName));
      propertyElement.appendChild(key);
      if (value != QVariant())
      {
       QDomElement elem;
       propertyElement.appendChild(elem = doc.createElement("value"));
       QString qtClass = value.typeName();
       QString javaClass = "java.lang.String";
       if(qtClass == "QString") javaClass = "java.lang.String";
       elem.setAttribute("class", javaClass);
       //elem.setText(value.toString());
       elem.appendChild(doc.createTextNode(value.toString()));
      }
//               return propertyElement;
//           }).forEach((propertyElement) -> {
//               properties.addContent(propertyElement);
//           });
       properties.appendChild(propertyElement);
      }
     window.appendChild(properties);
    }
    element.appendChild(window);
   }
   this->saveElement(element);
   this->resetChangeMade();
  }
 }
}

/**
 *
 * @return an QDomElementor NULL if the requested element does not exist
 */
//@Nullable
/*private*/ QDomElement JmriUserPreferencesManager::readElement(/*@Nonnull*/ QString elementName, /*@Nonnull*/ QString _namespace)
{
    QDomElement element = ProfileUtils::getUserInterfaceConfiguration(ProfileManager::getDefault()->getActiveProfile())->getConfigurationFragment(elementName, _namespace, false);
 if (!element.isNull())
 {
     //return JDOMUtil.toJDOMElement(element);
  return element;
 }
 return QDomElement();
}

/*protected*/ void JmriUserPreferencesManager::saveElement(/*@NonNULL*/ QDomElement element)
{

    if(log->isDebugEnabled()) log->trace(tr("Saving %1 element.").arg(element.tagName()));
    try {
        ProfileUtils::getUserInterfaceConfiguration(ProfileManager::getDefault()->getActiveProfile())->putConfigurationFragment(/*JDOMUtil.toW3CElement*/(element), false);
    } catch (JDOMException* ex) {
        log->error("Unable to save user preferences"/*, ex*/);
    }

}

/*private*/ void JmriUserPreferencesManager::savePreferences() {
    this->saveComboBoxLastSelections();
    this->savePreferencesState();
    this->saveSimplePreferenceState();
    this->saveWindowDetails();
    this->resetChangeMade();
  JmriJTablePersistenceManager* manager =
    (JmriJTablePersistenceManager*)InstanceManager::getOptionalDefault("JmriJTablePersistenceManager");
    //->ifPresent((manager) -> {
  if(manager != nullptr)
        manager->savePreferences(ProfileManager::getDefault()->getActiveProfile());
//    });
}

//@Override
/*public*/ void JmriUserPreferencesManager::initialize() {
        this->readUserPreferences();
}
/**
 * Holds details about the specific class.
 */
///*protected*/ /*final*/ /*static*/ class ClassPreferences
//{
//private:
//    QString classDescription;

//    QList<MultipleChoice*> multipleChoiceList = new ArrayList<>();
//    QList<PreferenceList*>* preferenceList = new ArrayList<>();
//public:
    ClassPreferences::ClassPreferences() {
    }

    ClassPreferences::ClassPreferences(QString classDescription) {
        this->classDescription = classDescription;
    }

    QString ClassPreferences::getDescription() {
        return classDescription;
    }

    void ClassPreferences::setDescription(QString description) {
        classDescription = description;
    }

    QList<PreferenceList*>* ClassPreferences::getPreferenceList() {
        return preferenceList;
    }

    int ClassPreferences::getPreferenceListSize() {
        return preferenceList->size();
    }

    QList<MultipleChoice *> *ClassPreferences::getMultipleChoiceList() {
        return multipleChoiceList;
    }

    int ClassPreferences::getPreferencesSize() {
        return multipleChoiceList->size() + preferenceList->size();
    }

    /*public*/ QString ClassPreferences::getPreferenceName(int n) {
        try {
         if(n >= preferenceList->size())
          throw new IndexOutOfBoundsException();
            return preferenceList->value(n)->getItem();
        } catch (IndexOutOfBoundsException* ioob) {
            return QString();
        }
    }

    int ClassPreferences::getMultipleChoiceListSize() {
        return multipleChoiceList->size();
    }

    /*public*/ QString ClassPreferences::getChoiceName(int n) {
        try {
            return multipleChoiceList->value(n)->getItem();
        } catch (IndexOutOfBoundsException* ioob) {
            return QString();
        }
    }
//};

///*protected*/ /*final*/ /*static*/ class MultipleChoice {

//    QMap<int, QString> options;
//    QString optionDescription;
//    QString item;
//    int value = -1;
//    int defaultOption = -1;

    MultipleChoice::MultipleChoice(QString description, QString item, QMap<int, QString> *options, int defaultOption) {
     value = -1;
     defaultOption = -1;
        this->item = item;
        setMessageItems(description, options, defaultOption);
    }

    MultipleChoice::MultipleChoice(QString item, int value)
    {
     defaultOption = -1;
        this->item = item;
        this->value = value;
     options = new QMap<int, QString>();

    }

    void MultipleChoice::setValue(int value) {
        this->value = value;
    }

    void MultipleChoice::setValue(QString value) {
//        options.keySet().stream().filter((o) -> (options.get(o) == (value))).forEachOrdered((o) -> {
//            this->value = o;
//        });
     foreach(int o, options->keys())
     {
      if(options->value(o) == (value))
       this->value = o;
     }
    }

    void MultipleChoice::setMessageItems(QString description, QMap<int, QString> *options, int defaultOption) {
        optionDescription = description;
        this->options = options;
        this->defaultOption = defaultOption;
        if (value == -1) {
            value = defaultOption;
        }
    }

    int MultipleChoice::getValue() {
        return value;
    }

    int MultipleChoice::getDefaultValue() {
        return defaultOption;
    }

    QString MultipleChoice::getItem() {
        return item;
    }

    QString MultipleChoice::getOptionDescription() {
        return optionDescription;
    }

    QMap<int, QString>* MultipleChoice::getOptions() {
        return options;
    }

//};

//protected /*final*/ static class PreferenceList {

//    // need to fill this with bits to get a meaning full description.
//    bool set = false;
//    QString item = "";
//    QString description = "";

    PreferenceList::PreferenceList(QString item) {
    description = "";

        this->item = item;
    }

    PreferenceList::PreferenceList(QString item, bool state) {
     description = "";

        this->item = item;
        set = state;
    }

    PreferenceList::PreferenceList(QString item, QString description) {
        this->description = description;
        this->item = item;
    }

    void PreferenceList::setDescription(QString desc) {
        description = desc;
    }

    QString PreferenceList::getDescription() {
        return description;
    }

    bool PreferenceList::getState() {
        return set;
    }

    void PreferenceList::setState(bool state) {
        this->set = state;
    }

    QString PreferenceList::getItem() {
        return item;
    }

//};

//protected /*final*/ static class WindowLocations {

//    Point xyLocation = new Point(0, 0);
//    Dimension size = new Dimension(0, 0);
//    bool saveSize = false;
//    bool saveLocation = false;

    WindowLocations::WindowLocations() {
     parameters =  QMap<QString, QVariant>();
     xyLocation = QPoint(0, 0);
     QSize size = QSize(0, 0);
     saveSize = false;
     saveLocation = false;

    }

    QPoint WindowLocations::getLocation() {
        return xyLocation;
    }

    QSize WindowLocations::getSize() {
        return size;
    }

    void WindowLocations::setSaveSize(bool b) {
        saveSize = b;
    }

    void WindowLocations::setSaveLocation(bool b) {
        saveLocation = b;
    }

    bool WindowLocations::getSaveSize() {
        return saveSize;
    }

    bool WindowLocations::getSaveLocation() {
        return saveLocation;
    }

    void WindowLocations::setLocation(QPoint xyLocation) {
        this->xyLocation = xyLocation;
        saveLocation = true;
    }

    void WindowLocations::setSize(QSize size) {
        this->size = size;
        saveSize = true;
    }

    void WindowLocations::setProperty(QString key, QVariant value) {
     if (value == QVariant())
     {
         parameters.remove(key);
     } else {
         parameters.insert(key, value);
     }
    }

    QVariant WindowLocations::getProperty(QString key) {
        return parameters.value(key);
    }

   QSet<QString> WindowLocations::getPropertyKeys() {
        return parameters.keys().toSet();
    }

    // /*final*/ QMap<QString, QVariant> parameters =  QMap<QString, QVariant>();

//};
