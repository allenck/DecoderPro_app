#include "jmriuserpreferencesmanager.h"
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include "file.h"
#include <QApplication>
#include <QScreen>
#include "logger.h"
#include "fileutil.h"
#include "profile.h"
#include "configuremanager.h"
#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <qcheckbox.h>
#include "logger.h"
#include <QMessageBox>
#include "nodeidentity.h"
#include "defaultusermessagepreferences.h"
#include "profilemanager.h"
#include "profileutils.h"
#include "auxiliaryconfiguration.h"

/**
 * Implementation of {@link UserPreferencesManager} that saves user interface
 * preferences that should be automatically remembered as they are set.
 *
 * This class is intended to be a transitional class from a single user
 * interface preferences manager to multiple, domain-specific (windows, tables,
 * dialogs, etc) user interface preferences managers. I believe that
 * domain-specific managers could more efficiently, both in the API and at
 * runtime, handle each user interface preference need than a single monolithic
 * manager.
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JmriUserPreferencesManager extends Bean implements UserPreferencesManager {

/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::CLASSPREFS_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/class-preferences-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::CLASSPREFS_ELEMENT = "classPreferences"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::COMBOBOX_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/combobox-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::COMBOBOX_ELEMENT = "comboBoxLastValue"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::SETTINGS_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/settings-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::SETTINGS_ELEMENT = "settings"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::TABLES_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/table-details-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::TABLES_ELEMENT = "tableDetails"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::WINDOWS_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/window-details-4-3-5.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ QString JmriUserPreferencesManager::WINDOWS_ELEMENT = "windowDetails"; // NOI18N
///*private*/ /*final*/ /*static*/ Logger log = LoggerFactory.getLogger(JmriUserPreferencesManager.class);

/*public*/ /*static*/ UserPreferencesManager* JmriUserPreferencesManager::getInstance() {
    return JmriUserPreferencesManager::getDefault();
}

/**
 * Get the default UserPreferencesManager or create a new one if none
 * exists. Load user preferences if needed.
 *
 * @return the default UserPreferencesManager
 */
/*public*/ /*static*/ UserPreferencesManager* JmriUserPreferencesManager::getDefault()
{
    if (InstanceManager::getDefault("UserPreferencesManager") == NULL) {
        JmriUserPreferencesManager* manager = new JmriUserPreferencesManager();
        InstanceManager::setDefault("UserPreferencesManager", manager);
        manager->readUserPreferences();
    }
    return (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
}


/*public*/ JmriUserPreferencesManager::JmriUserPreferencesManager(QObject* parent) : Bean(parent)
{
 log = new Logger("JmriUserPreferencesManager");
 dirty = false;
 loading = false;
 simplePreferenceList = QStringList();
 //sessionList is used for messages to be suppressed for the current JMRI session only
 sessionPreferenceList = QStringList();
 _comboBoxLastSelection = QList<ComboBoxLastSelection*>();
 windowDetails = QMap<QString, WindowLocations*>();
 classPreferenceList = QMap<QString, ClassPreferences*>();
 tableColumnPrefs = QMap<QString, QMap<QString, TableColumnPreferences*> >();

 // prevent attempts to write during construction
    this->_allowSave = false;

    //I18N in ManagersBundle.properties (this is a checkbox on prefs tab Messages|Misc items)
    this->preferenceItemDetails(getClassName(), "reminder", tr("Hide Reminder Location Message")); // NOI18N
    //I18N in ManagersBundle.properties (this is the title of prefs tab Messages|Misc items)
    this->classPreferenceList.value(getClassName())->setDescription(tr("User Preferences")); // NOI18N

    // allow attempts to write
    this->_allowSave = true;
    this->dirty = false;
}

//@Override
/*public*/ /*synchronized*/ void JmriUserPreferencesManager::allowSave() {
    this->_allowSave = true;
}

//@Override
/*public*/ /*synchronized*/ void JmriUserPreferencesManager::disallowSave() {
    this->_allowSave = false;
}

//@Override
/*public*/ QSize JmriUserPreferencesManager::getScreen() {
    //return Toolkit.getDefaultToolkit().getScreenSize();
 return QApplication::screens().at(0)->size();
}

/**
 * This is used to remember the last selected state of a checkBox and thus
 * allow that checkBox to be set to a true state when it is next
 * initialised. This can also be used anywhere else that a simple yes/no,
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
/*public*/ void JmriUserPreferencesManager::setSimplePreferenceState(QString name, bool state) {
    if (state) {
        if (!simplePreferenceList.contains(name)) {
            simplePreferenceList.append(name);
        }
    } else {
        simplePreferenceList.removeOne(name);
    }
    this->saveSimplePreferenceState();
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getSimplePreferenceState(QString name) {
    return simplePreferenceList.contains(name);
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getSimplePreferenceStateList() {
    return QStringList(simplePreferenceList);
}

/**
 * Used to save the state of checkboxes which can suppress messages from
 * being displayed. This method should be used by the initiating code in
 * conjunction with the preferenceItemDetails. Here the items are stored
 * against a specific class and access to change them is made available via
 * the GUI, in the preference manager.
 * <p>
 * The strClass parameter does not have to be the exact class name of the
 * initiating code, but can be one where the information is related and
 * therefore can be grouped together with.
 * <p>
 * Both the strClass and item although free form, should make up a unique
 * reference.
 *
 * @param strClass The class that this preference should be stored or
 *                 grouped with.
 * @param item     The specific item that is to be stored
 * @param state    Boolean state of the item.
 */
//@Override
/*public*/ void JmriUserPreferencesManager::setPreferenceState(QString strClass, QString item, bool state) {
    // convert old manager preferences to new manager preferences
    if (strClass==("DefaultUserMessagePreferences")) {
        this->setPreferenceState("JmriUserPreferencesManager", item, state);
        return;
    }
    if (!classPreferenceList.contains(strClass)) {
        classPreferenceList.insert(strClass, new ClassPreferences());
        setClassDescription(strClass);
    }
    QList<PreferenceList*> a = classPreferenceList.value(strClass)->getPreferenceList();
    bool found = false;
    for (int i = 0; i < a.size(); i++) {
        if (a.at(i)->getItem()==(item)) {
            a.at(i)->setState(state);
            found = true;
        }
    }
    if (!found) {
        a.append(new PreferenceList(item, state));
    }
    displayRememberMsg();
    this->savePreferencesState();
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getPreferenceState(QString strClass, QString item) {
    if (classPreferenceList.contains(strClass)) {
        QList<PreferenceList*> a = classPreferenceList.value(strClass)->getPreferenceList();
        for (int i = 0; i < a.size(); i++) {
            if (a.at(i)->getItem()==(item)) {
                return a.at(i)->getState();
            }
        }
    }
    return false;
}

/**
 * Register details about a perticular preference, so that it can be
 * displayed in the GUI and provide a meaningful description when presented
 * to the user.
 *
 * @param strClass    A string form of the class that the preference is
 *                    stored or grouped with
 * @param item        The specific item that is being stored.
 * @param description A meaningful decription of the item that the user will
 *                    understand.
 */
//@Override
/*public*/ /*final*/ void JmriUserPreferencesManager::preferenceItemDetails(QString strClass, QString item, QString description) {
    if (!classPreferenceList.contains(strClass)) {
        classPreferenceList.insert(strClass, new ClassPreferences());
    }
    QList<PreferenceList*> a = classPreferenceList.value(strClass)->getPreferenceList();
    for (int i = 0; i < a.size(); i++) {
        if (a.at(i)->getItem()==(item)) {
            a.at(i)->setDescription(description);
            return;
        }
    }
    a.append(new PreferenceList(item, description));
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getPreferenceList(QString strClass) {
    if (classPreferenceList.contains(strClass)) {
        QList<PreferenceList*> a = classPreferenceList.value(strClass)->getPreferenceList();
        QStringList list = QStringList();
        for (int i = 0; i < a.size(); i++) {
            list.append(a.at(i)->getItem());
        }
        return list;
    }
    //Just return a blank array list will save call code checking for NULL
    return QStringList();
}
#if 0
@Override
/*public*/ String getPreferenceItemName(String strClass, int n) {
    if (classPreferenceList.containsKey(strClass)) {
        return classPreferenceList.get(strClass).getPreferenceName(n);
    }
    return NULL;
}

@Override
/*public*/ String getPreferenceItemDescription(String strClass, String item) {
    if (classPreferenceList.containsKey(strClass)) {
        ArrayList<PreferenceList> a = classPreferenceList.get(strClass).getPreferenceList();
        for (int i = 0; i < a.size(); i++) {
            if (a.get(i).getItem()==(item)) {
                return a.get(i).getDescription();
            }
        }
    }
    return NULL;

}
#endif
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
 * @param name  A unique identifer for preference.
 */
//@Override
/*public*/ void JmriUserPreferencesManager::setSessionPreferenceState(QString name, bool state) {
    if (state) {
        if (!sessionPreferenceList.contains(name)) {
            sessionPreferenceList.append(name);
        }
    } else {
        sessionPreferenceList.removeOne(name);
    }
}

//@Override
/*public*/ bool JmriUserPreferencesManager::getSessionPreferenceState(QString name) {
    return sessionPreferenceList.contains(name);
}

/**
 * Show an info message ("don't forget ...") with a given dialog title and
 * user message. Use a given preference name to determine whether to show it
 * in the future. The classString {@literal &} item parameters should form a
 * unique value
 *
 * @param title    Message Box title
 * @param message  Message to be displayed
 * @param strClass String value of the calling class
 * @param item     String value of the specific item this is used for
 */
//@Override
/*public*/ void JmriUserPreferencesManager::showInfoMessage(QString title, QString message, QString strClass, QString item) {
    showInfoMessage(title, message, strClass, item, false, true);
}

/**
 * Show an info message ("don't forget ...") with a given dialog title and
 * user message. Use a given preference name to determine whether to show it
 * in the future. added flag to indicate that the message should be
 * suppressed JMRI session only. The classString {@literal &} item
 * parameters should form a unique value
 *
 * @param title          Message Box title
 * @param message        Message to be displayed
 * @param strClass       String value of the calling class
 * @param item           String value of the specific item this is used for
 * @param sessionOnly    Means this message will be suppressed in this JMRI
 *                       session and not be remembered
 * @param alwaysRemember Means that the suppression of the message will be
 *                       saved
 */
//@Override
/*public*/ void JmriUserPreferencesManager::showErrorMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember) {
    this->showMessage(title, message, strClass, item, sessionOnly, alwaysRemember, QMessageBox::Critical);
}

/**
 * Show an info message ("don't forget ...") with a given dialog title and
 * user message. Use a given preference name to determine whether to show it
 * in the future. added flag to indicate that the message should be
 * suppressed JMRI session only. The classString {@literal &} item
 * parameters should form a unique value
 *
 * @param title          Message Box title
 * @param message        Message to be displayed
 * @param strClass       String value of the calling class
 * @param item           String value of the specific item this is used for
 * @param sessionOnly    Means this message will be suppressed in this JMRI
 *                       session and not be remembered
 * @param alwaysRemember Means that the suppression of the message will be
 *                       saved
 */
//@Override
/*public*/ void JmriUserPreferencesManager::showInfoMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember) {
    this->showMessage(title, message, strClass, item, sessionOnly, alwaysRemember, QMessageBox::Critical);
}

/**
 * Show an info message ("don't forget ...") with a given dialog title and
 * user message. Use a given preference name to determine whether to show it
 * in the future. added flag to indicate that the message should be
 * suppressed JMRI session only. The classString {@literal &} item
 * parameters should form a unique value
 *
 * @param title          Message Box title
 * @param message        Message to be displayed
 * @param strClass       String value of the calling class
 * @param item           String value of the specific item this is used for
 * @param sessionOnly    Means this message will be suppressed in this JMRI
 *                       session and not be remembered
 * @param alwaysRemember Means that the suppression of the message will be
 *                       saved
 */
//@Override
/*public*/ void JmriUserPreferencesManager::showWarningMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember) {
    this->showMessage(title, message, strClass, item, sessionOnly, alwaysRemember, QMessageBox::Critical);
}

/*protected*/ void JmriUserPreferencesManager::showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type) {
    /*final*/ QString preference = strClass + "." + item;

    if (this->getSessionPreferenceState(preference)) {
        return;
    }
    if (!this->getPreferenceState(strClass, item)) {
        QWidget* container = new QWidget();
        container->setLayout(new QVBoxLayout); //(container, BoxLayout.Y_AXIS));
        container->layout()->addWidget(new QLabel(message));
        //I18N in ManagersBundle.properties
        /*final*/ QCheckBox* rememberSession = new QCheckBox(tr("Skip message for this session only?")); // NOI18N
        if (sessionOnly)
        {
         QFont f = rememberSession->font();
         f.setPointSize(10.);
            rememberSession->setFont(f);
            container->layout()->addWidget(rememberSession);
        }
        //I18N in ManagersBundle.properties
        /*final*/ QCheckBox* remember = new QCheckBox(tr("Skip message in future?")); // NOI18N
        if (alwaysRemember) {
         QFont f = remember->font();
         f.setPointSize(10.);
            remember->setFont(f);
            container->layout()->addWidget(remember);
        }
//        JOptionPane.showMessageDialog(NULL, // center over parent component
//                container,
//                title,
//                type);
        QMessageBox* box = new QMessageBox(QMessageBox::Question, title, "");
        box->exec();
        box->layout()->addWidget(container);
        if (remember->isChecked()) {
            this->setPreferenceState(strClass, item, true);
        }
        if (rememberSession->isChecked()) {
            this->setSessionPreferenceState(preference, true);
        }

    }
}
#if 0
@Override
/*public*/ void addComboBoxLastSelection(String comboBoxName, String lastValue) {
    if (getComboBoxLastSelection(comboBoxName) == NULL) {
        ComboBoxLastSelection combo = new ComboBoxLastSelection(comboBoxName, lastValue);
        _comboBoxLastSelection.add(combo);
    } else {
        setComboBoxLastSelection(comboBoxName, lastValue);
    }
    setChangeMade(false);
}

@Override
/*public*/ String getComboBoxLastSelection(String comboBoxName) {
    for (int i = 0; i < _comboBoxLastSelection.size(); i++) {
        if (_comboBoxLastSelection.get(i).getComboBoxName()==(comboBoxName)) {
            return _comboBoxLastSelection.get(i).getLastValue();
        }
    }
    return NULL;
}

@Override
/*public*/ void setComboBoxLastSelection(String comboBoxName, String lastValue) {
    for (int i = 0; i < _comboBoxLastSelection.size(); i++) {
        if (_comboBoxLastSelection.get(i).getComboBoxName()==(comboBoxName)) {
            _comboBoxLastSelection.get(i).setLastValue(lastValue);
        }
    }
    this->saveComboBoxLastSelections();
}
#endif
//@Override
/*public*/ int JmriUserPreferencesManager::getComboBoxSelectionSize() {
    return _comboBoxLastSelection.size();
}
#if 0
@Override
/*public*/ String getComboBoxName(int n) {
    try {
        return _comboBoxLastSelection.get(n).getComboBoxName();
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

@Override
/*public*/ String getComboBoxLastSelection(int n) {
    try {
        return _comboBoxLastSelection.get(n).getLastValue();
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

/*public*/ synchronized bool getChangeMade() {
    return dirty;
}
#endif
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
    showInfoMessage(tr("Reminder"), tr("ReminderLine"), getClassName(), "reminder"); // NOI18N
}
#if 0
//@Override
/*public*/ QPoint getWindowLocation(QString strClass) {
    if (windowDetails.containsKey(strClass)) {
        return windowDetails.get(strClass).getLocation();
    }
    return NULL;
}

//@Override
/*public*/ QSize getWindowSize(QString strClass) {
    if (windowDetails.containsKey(strClass)) {
        return windowDetails.get(strClass).getSize();
    }
    return NULL;
}

//@Override
/*public*/ bool getSaveWindowSize(QString strClass) {
    if (windowDetails.containsKey(strClass)) {
        return windowDetails.get(strClass).getSaveSize();
    }
    return false;
}

@Override
/*public*/ bool getSaveWindowLocation(String strClass) {
    if (windowDetails.containsKey(strClass)) {
        return windowDetails.get(strClass).getSaveLocation();
    }
    return false;
}

@Override
/*public*/ void setSaveWindowSize(String strClass, bool b) {
    if (windowDetails.containsKey(strClass)) {
        windowDetails.get(strClass).setSaveSize(b);
    }
    this->saveWindowDetails();
}

@Override
/*public*/ void setSaveWindowLocation(String strClass, bool b) {
    if (windowDetails.containsKey(strClass)) {
        windowDetails.get(strClass).setSaveLocation(b);
    }
    this->saveWindowDetails();
}
#endif
//@Override
/*public*/ void JmriUserPreferencesManager::setWindowLocation(QString strClass, QPoint location) {
    if ((strClass == NULL) || (strClass==("jmri.util.JmriJFrame"))) {
        return;
    }
    if (!windowDetails.contains(strClass)) {
        windowDetails.insert(strClass, new WindowLocations());
    }
    windowDetails.value(strClass)->setLocation(location);
    this->saveWindowDetails();
}

//@Override
/*public*/ void JmriUserPreferencesManager::setWindowSize(QString strClass, QSize dim) {
    if (strClass==("jmri.util.JmriJFrame")) {
        return;
    }
    if (!windowDetails.contains(strClass)) {
        windowDetails.insert(strClass, new WindowLocations());
    }
    windowDetails.value(strClass)->setSize(dim);
    this->saveWindowDetails();
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getWindowList() {
    return QStringList(windowDetails.keys());
}

//@Override
/*public*/ void JmriUserPreferencesManager::setProperty(QString strClass, QString key, QVariant value) {
    if (strClass==("JmriJFrame")) {
        return;
    }
    if (!windowDetails.contains(strClass)) {
        windowDetails.insert(strClass, new WindowLocations());
    }
    windowDetails.value(strClass)->setProperty(key, value);
    this->saveWindowDetails();
}

//@Override
/*public*/ QVariant JmriUserPreferencesManager::getProperty(QString strClass, QString key) {
    if (windowDetails.contains(strClass)) {
        return windowDetails.value(strClass)->getProperty(key);
    }
    return QVariant();
}

//@Override
/*public*/ QSet<QString> JmriUserPreferencesManager::getPropertyKeys(QString strClass) {
    if (windowDetails.contains(strClass)) {
        return windowDetails.value(strClass)->getPropertyKeys();
    }
    return QSet<QString>();
}

//@Override
/*public*/ bool JmriUserPreferencesManager::isWindowPositionSaved(QString strClass) {
    return windowDetails.contains(strClass);
}

//@Override
/*public*/ QString JmriUserPreferencesManager::getClassDescription(QString strClass) {
    if (classPreferenceList.contains(strClass)) {
        return classPreferenceList.value(strClass)->getDescription();
    }
    return "";
}

//@Override
/*public*/ QStringList JmriUserPreferencesManager::getPreferencesClasses() {
    return QStringList(this->classPreferenceList.keys());
}

/**
 * Given that we know the class as a string, we will try and attempt to
 * gather details about the preferences that has been added, so that we can
 * make better sense of the details in the preferences window.
 * <p>
 * This looks for specific methods within the class called
 * "getClassDescription" and "setMessagePreferenceDetails". If found it will
 * invoke the methods, this will then trigger the class to send details
 * about its preferences back to this code.
 */
//@Override
/*public*/ void JmriUserPreferencesManager::setClassDescription(QString strClass) {
//    try {
//        Class<?> cl = Class.forName(strClass);
//        Object t = cl.newInstance();
  QObject* cl;
  int id = QMetaType::type(strClass.toLocal8Bit());
  if(id != 0)
  {
#if QT_VERSION < 0x050000
   cl = (QObject*)QMetaType::construct(id);
#else
   cl = (QObject*)QMetaType::create(id);
#endif

        bool classDesFound;
        bool classSetFound;
        QString desc = NULL;
        //Method method;
        //look through declared methods first, then all methods
        //try {
//            method = cl.getDeclaredMethod("getClassDescription");
        if(cl->metaObject()->indexOfMethod("getClassDescription") < 0)
        {
         log->error(tr("class %1 method %2 not found").arg(strClass).arg("getClassDescription"));
        }
//            desc = (String) method.invoke(t);
        desc = QMetaObject::invokeMethod(cl, "getClassDescription");
            classDesFound = true;
//        } catch (IllegalAccessException | IllegalArgumentException | java.lang.reflect.InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
//            log->warn(ex.toString());
//            classDesFound = false;
//        }
#if 0
        if (!classDesFound) {
            //try {
                method = cl.getMethod("getClassDescription");
                desc = (String) method.invoke(t);
//            } catch (IllegalAccessException | IllegalArgumentException | java.lang.reflect.InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
//                log->warn(ex.toString());
//                classDesFound = false;
//            }
        }
#endif
        if (classDesFound) {
            if (!classPreferenceList.contains(strClass)) {
                classPreferenceList.insert(strClass, new ClassPreferences(desc));
            } else {
                classPreferenceList.value(strClass)->setDescription(desc);
            }
            this->savePreferencesState();
        }

        //try {
//            method = cl.getDeclaredMethod("setMessagePreferencesDetails");
//            method.invoke(t);
        if(cl->metaObject()->indexOfMethod("setMessagePreferencesDetails")>= 0)
        {
          QMetaObject::invokeMethod(cl,"setMessagePreferencesDetails");
            classSetFound = true;
        }
        else
        {
         log->error(tr("class %1 method %2 not found").arg(strClass).arg("setMessagePreferencesDetails"));
        }
//        } catch (IllegalAccessException | IllegalArgumentException | java.lang.reflect.InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
//            log->debug(ex.toString()); // *TableAction.setMessagePreferencesDetails() method is routinely not present in multiple classes
//            classSetFound = false;
//        }
//        if (!classSetFound) {
//            //try {
//                method = cl.getMethod("setMessagePreferencesDetails");
//                method.invoke(t);
////            } catch (IllegalAccessException | IllegalArgumentException | java.lang.reflect.InvocationTargetException | NullPointerException | ExceptionInInitializerError | NoSuchMethodException ex) {
////                log->warn(ex.toString());
////            }
//        }
//        else
        if (!classSetFound)
        {
         log->error(tr("class name \"%1\" is invalid").arg(strClass)); //, ex);
        }

//    } catch (java.lang.ClassNotFoundException ex) {
//        log->error("class name \"{}\" is invalid", strClass, ex);
  }
//    } catch (java.lang.IllegalAccessException ex) {
//        log->error("unable to access class \"{}\"", strClass, ex);
//    } catch (InstantiationException ex) {
//        log->error("unable to get a class name \"{}\"", strClass, ex);
//    }
}
#if 0
/**
 * Add descriptive details about a specific message box, so that if it needs
 * to be reset in the preferences, then it is easily identifiable. displayed
 * to the user in the preferences GUI.
 *
 * @param strClass      String value of the calling class/group
 * @param item          String value of the specific item this is used for.
 * @param description   A meaningful description that can be used in a label
 *                      to describe the item
 * @param msgOption     Description of each option valid option.
 * @param msgNumber     The references number against which the Description
 *                      is refering too.
 * @param defaultOption The default option for the given item.
 */
@Override
/*public*/ void messageItemDetails(String strClass, String item, String description, String[] msgOption, int[] msgNumber, int defaultOption) {
    HashMap<Integer, String> options = new HashMap<>(msgOption.length);
    for (int i = 0; i < msgOption.length; i++) {
        options.put(msgNumber[i], msgOption[i]);
    }
    messageItemDetails(strClass, description, item, options, defaultOption);
}

/**
 * Add descriptive details about a specific message box, so that if it needs
 * to be reset in the preferences, then it is easily identifiable. displayed
 * to the user in the preferences GUI.
 *
 * @param strClass      String value of the calling class/group
 * @param item          String value of the specific item this is used for.
 * @param description   A meaningful description that can be used in a label
 *                      to describe the item
 * @param options       A map of the integer value of the option against a
 *                      meaningful description.
 * @param defaultOption The default option for the given item.
 */
@Override
/*public*/ void messageItemDetails(String strClass, String item, String description, HashMap<Integer, String> options, int defaultOption) {
    if (!classPreferenceList.containsKey(strClass)) {
        classPreferenceList.put(strClass, new ClassPreferences());
    }
    ArrayList<MultipleChoice> a = classPreferenceList.get(strClass).getMultipleChoiceList();
    for (int i = 0; i < a.size(); i++) {
        if (a.get(i).getItem()==(item)) {
            a.get(i).setMessageItems(description, options, defaultOption);
            return;
        }
    }
    a.add(new MultipleChoice(description, item, options, defaultOption));
}

@Override
/*public*/ HashMap<Integer, String> getChoiceOptions(String strClass, String item) {
    if (classPreferenceList.containsKey(strClass)) {
        ArrayList<MultipleChoice> a = classPreferenceList.get(strClass).getMultipleChoiceList();
        for (int i = 0; i < a.size(); i++) {
            if (a.get(i).getItem()==(item)) {
                return a.get(i).getOptions();
            }
        }
    }
    return new HashMap<>();
}

@Override
/*public*/ int getMultipleChoiceSize(String strClass) {
    if (classPreferenceList.containsKey(strClass)) {
        return classPreferenceList.get(strClass).getMultipleChoiceListSize();
    }
    return 0;
}

@Override
/*public*/ QStringList getMultipleChoiceList(String strClass) {
    if (classPreferenceList.containsKey(strClass)) {
        ArrayList<MultipleChoice> a = classPreferenceList.get(strClass).getMultipleChoiceList();
        QStringList list = new ArrayList<>();
        for (int i = 0; i < a.size(); i++) {
            list.add(a.get(i).getItem());
        }
        return list;
    }
    return new ArrayList<>();
}

@Override
/*public*/ String getChoiceName(String strClass, int n) {
    if (classPreferenceList.containsKey(strClass)) {
        return classPreferenceList.get(strClass).getChoiceName(n);
    }
    return NULL;
}

@Override
/*public*/ String getChoiceDescription(String strClass, String item) {
    if (classPreferenceList.containsKey(strClass)) {
        ArrayList<MultipleChoice> a = classPreferenceList.get(strClass).getMultipleChoiceList();
        for (int i = 0; i < a.size(); i++) {
            if (a.get(i).getItem()==(item)) {
                return a.get(i).getOptionDescription();
            }
        }
    }
    return NULL;
}

@Override
/*public*/ int getMultipleChoiceOption(String strClass, String item) {
    if (classPreferenceList.containsKey(strClass)) {
        ArrayList<MultipleChoice> a = classPreferenceList.get(strClass).getMultipleChoiceList();
        for (int i = 0; i < a.size(); i++) {
            if (a.get(i).getItem()==(item)) {
                return a.get(i).getValue();
            }
        }
    }
    return 0x00;
}

@Override
/*public*/ int getMultipleChoiceDefaultOption(String strClass, String choice) {
    if (classPreferenceList.containsKey(strClass)) {
        ArrayList<MultipleChoice> a = classPreferenceList.get(strClass).getMultipleChoiceList();
        for (int i = 0; i < a.size(); i++) {
            if (a.get(i).getItem()==(choice)) {
                return a.get(i).getDefaultValue();
            }
        }
    }
    return 0x00;
}
#endif
//@Override
/*public*/ void JmriUserPreferencesManager::setMultipleChoiceOption(QString strClass, QString choice, QString value) {
    if (!classPreferenceList.contains(strClass)) {
        classPreferenceList.insert(strClass, new ClassPreferences());
    }
    foreach (MultipleChoice* mc, classPreferenceList.value(strClass)->getMultipleChoiceList()) {
        if (mc->getItem()==(choice)) {
            mc->setValue(value);
        }
    }
    this->savePreferencesState();
}
#if 0
@Override
/*public*/ void setMultipleChoiceOption(String strClass, String choice, int value) {
    if (!classPreferenceList.containsKey(strClass)) {
        classPreferenceList.put(strClass, new ClassPreferences());
    }
    bool set = false;
    for (MultipleChoice mc : classPreferenceList.get(strClass).getMultipleChoiceList()) {
        if (mc.getItem()==(choice)) {
            mc.setValue(value);
            set = true;
        }
    }
    if (!set) {
        classPreferenceList.get(strClass).getMultipleChoiceList().add(new MultipleChoice(choice, value));
        setClassDescription(strClass);
    }
    displayRememberMsg();
    this->savePreferencesState();
}
#endif
//@Override
/*public*/ void JmriUserPreferencesManager::setTableColumnPreferences(QString table, QString column, int order, int width, int sort, bool hidden) {
    if (!tableColumnPrefs.contains(table)) {
        tableColumnPrefs.insert(table, QMap<QString, TableColumnPreferences*>());
    }
    QMap<QString, TableColumnPreferences*> columnPrefs = tableColumnPrefs.value(table);
    columnPrefs.insert(column, new TableColumnPreferences(order, width, sort, hidden));
    this->saveTableColumnPreferences();
}
#if 0
@Override
/*public*/ int getTableColumnOrder(String table, String column) {
    if (tableColumnPrefs.containsKey(table)) {
        HashMap<String, TableColumnPreferences> columnPrefs = tableColumnPrefs.get(table);
        if (columnPrefs.containsKey(column)) {
            return columnPrefs.get(column).getOrder();
        }
    }
    return -1;
}

@Override
/*public*/ int getTableColumnWidth(String table, String column) {
    if (tableColumnPrefs.containsKey(table)) {
        HashMap<String, TableColumnPreferences> columnPrefs = tableColumnPrefs.get(table);
        if (columnPrefs.containsKey(column)) {
            return columnPrefs.get(column).getWidth();
        }
    }
    return -1;
}

@Override
/*public*/ SortOrder getTableColumnSort(String table, String column) {
    if (tableColumnPrefs.containsKey(table)) {
        HashMap<String, TableColumnPreferences> columnPrefs = tableColumnPrefs.get(table);
        if (columnPrefs.containsKey(column)) {
            return columnPrefs.get(column).getSort();
        }
    }
    return SortOrder.UNSORTED;
}

@Override
/*public*/ bool getTableColumnHidden(String table, String column) {
    if (tableColumnPrefs.containsKey(table)) {
        HashMap<String, TableColumnPreferences> columnPrefs = tableColumnPrefs.get(table);
        if (columnPrefs.containsKey(column)) {
            return columnPrefs.get(column).getHidden();
        }
    }
    return false;
}

@Override
/*public*/ String getTableColumnAtNum(String table, int i) {
    if (tableColumnPrefs.containsKey(table)) {
        HashMap<String, TableColumnPreferences> columnPrefs = tableColumnPrefs.get(table);
        for (Map.Entry<String, TableColumnPreferences> e : columnPrefs.entrySet()) {
            Map.Entry<String, TableColumnPreferences> entry = e;
            if ((entry.getValue()).getOrder() == i) {
                return entry.getKey();
            }
        }

    }
    return NULL;
}

@Override
/*public*/ List<String> getTablesList() {
    return new ArrayList<>(tableColumnPrefs.keySet());
}

@Override
/*public*/ List<String> getTablesColumnList(String table) {
    if (tableColumnPrefs.containsKey(table)) {
        HashMap<String, TableColumnPreferences> columnPrefs = tableColumnPrefs.get(table);
        return new ArrayList<>(columnPrefs.keySet());
    }
    return new ArrayList<>();
}

/*public*/ String getClassDescription() {
    return "Preference Manager";
}
#endif
/*protected*/ /*final*/ QString JmriUserPreferencesManager::getClassName() {
    //return this->getClass().getName();
 return QString(this->metaObject()->className());
}
#if 0
/*protected*/ /*final*/ ClassPreferences getClassPreferences(String strClass) {
    return this->classPreferenceList.get(strClass);
}

//@Override
/*public*/ int getPreferencesSize(String strClass) {
    if (classPreferenceList.containsKey(strClass)) {
        return classPreferenceList.get(strClass).getPreferencesSize();
    }
    return 0;
}
#endif
/*public*/ /*final*/ void JmriUserPreferencesManager::readUserPreferences() {
    this->_allowSave = false;
    this->loading = true;
    File* perNodeConfig = NULL;
    try {
        perNodeConfig = FileUtil::getFile(FileUtil::PROFILE + Profile::PROFILE + "/" + NodeIdentity::identity() + "/" + Profile::UI_CONFIG); // NOI18N
        if (!perNodeConfig->canRead()) {
            perNodeConfig = NULL;
        }
    } catch (FileNotFoundException ex) {
        // ignore - this only means that sharedConfig does not exist.
    }
    if (perNodeConfig != NULL) {
        file = perNodeConfig;
        this->readComboBoxLastSelections();
        this->readPreferencesState();
        this->readSimplePreferenceState();
        this->readTableColumnPreferences();
        this->readWindowDetails();
    } else {
        try {
            file = FileUtil::getFile(FileUtil::PROFILE + Profile::UI_CONFIG_FILENAME);
            if (file->exists()) {
                log->debug(tr("start load user pref file: %1").arg(file->getPath()));
                //try {
                    ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->load(file, true);
                    this->_allowSave = true;
                    this->savePreferences(); // write new preferences format immediately
//                } catch (JmriException e) {
//                    log->error("Unhandled problem loading configuration: " + e);
//                } catch (NullPointerException e) {
//                    log->error("NPE when trying to load user pref " + file);
//                }
            } else {
                // if we got here, there is no saved user preferences
                log->info("No saved user preferences file");
            }
        } catch (FileNotFoundException ex) {
            // ignore - this only means that UserPrefsProfileConfig.xml does not exist.
        }
    }
    this->loading = false;
    this->_allowSave = true;
}

/*private*/ void JmriUserPreferencesManager::readComboBoxLastSelections() {
    QDomElement element = this->readElement(COMBOBOX_ELEMENT, COMBOBOX_NAMESPACE);
    if (element != QDomElement())
    {
        //element.getChildren("comboBox").stream().forEach((combo) -> {
     QDomNodeList combos = element.elementsByTagName("comboBox");
     for(int i = 0; i < combos.size(); i ++)
     {
      QDomElement combo = combos.at(i).toElement();
            _comboBoxLastSelection.append(new ComboBoxLastSelection(combo.attribute("name"), combo.attribute("lastSelected")));
        };//);
    }
}

/*private*/ void JmriUserPreferencesManager::saveComboBoxLastSelections() {
    this->setChangeMade(false);
    if (this->_allowSave && getComboBoxSelectionSize() > 0) {
        QDomElement element = doc.createElementNS(COMBOBOX_ELEMENT, COMBOBOX_NAMESPACE);
        // Do not store blank last entered/selected values
        //_comboBoxLastSelection.stream().filter((cbls) -> (cbls.getLastValue() != NULL && !cbls.getLastValue().isEmpty())).map((cbls) -> {
        foreach (ComboBoxLastSelection* cbls, _comboBoxLastSelection)
        {
         if(cbls != NULL && cbls->getLastValue()!= NULL)
         {
            QDomElement combo = doc.createElement("comboBox");
            combo.setAttribute("name", cbls->getComboBoxName());
            combo.setAttribute("lastSelected", cbls->getLastValue());
//            return combo;
//        }).forEach((combo) -> {
            element.appendChild(combo);
//        });
         }
        }
        this->saveElement(element);
        this->resetChangeMade();
    }
}

/*private*/ void JmriUserPreferencesManager::readPreferencesState() {
    QDomElement element = this->readElement(CLASSPREFS_ELEMENT, CLASSPREFS_NAMESPACE);
    if (element != QDomElement())
    {
        //element.getChildren("preferences").stream().forEach((preferences) -> {
     QDomNodeList elements = element.elementsByTagName("preferences");
     for(int i = 0; i < elements.size(); i++)
     {
      QDomElement preferences = elements.at(i).toElement();
            QString clazz = preferences.attribute("class");
            log->debug(tr("Reading class preferences for \"%1\"").arg(clazz));
            //preferences.getChildren("multipleChoice").stream().forEach((mc) -> {
            QDomNodeList multipleChoices = preferences.elementsByTagName("multipleChoice");
            for(int j = 0; j < multipleChoices.size(); j++)
            {
             QDomElement mc = multipleChoices.at(j).toElement();
                //mc.getChildren("option").stream().forEach((option) -> {
             QDomNodeList options = mc.elementsByTagName("option");
             for(int k = 0; k < options.size(); k++)
             {
              QDomElement option = options.at(k).toElement();
                    int value = 0;
                    bool ok;
                        option.attribute("value").toInt(&ok);
                    if(!ok) {
                        log->error("failed to convert positional attribute");
                    }
                    this->setMultipleChoiceOption(clazz, option.attribute("item"), option.attribute("value"));
                }//);
            } //);
            //preferences.getChildren("reminderPrompts").stream().forEach((rp) -> {
            QDomNodeList reminderPrompts = preferences.elementsByTagName("reminderPrompts");
            for(int j = 0; j < reminderPrompts.size(); j++ )
            {
             QDomElement rp = reminderPrompts.at(j).toElement();
                //rp.getChildren("reminder").stream().forEach((reminder) -> {
             QDomNodeList reminders = rp.elementsByTagName("reminder");
             for(int j = 0; j < reminders.size(); j++)
             {
              QDomElement reminder = reminders.at(j).toElement();
                    log->debug(tr("Setting preferences state \"true\" for \"%1\", \"%2\"").arg(clazz).arg(reminder.text()));
                    this->setPreferenceState(clazz, reminder.text(), true);
                };//);
            };//);
        };//);
    }
}

/*private*/ void JmriUserPreferencesManager::savePreferencesState() {
    this->setChangeMade(true);
    if (this->_allowSave) {
        QDomElement element = doc.createElementNS(CLASSPREFS_ELEMENT, CLASSPREFS_NAMESPACE);
        //this->classPreferenceList.keySet().stream().forEach((name) -> {
          QStringList names = this->classPreferenceList.keys();
        foreach(QString name, names)
        {
            ClassPreferences* cp = this->classPreferenceList.value(name);
            if (!cp->multipleChoiceList.isEmpty() || !cp->preferenceList.isEmpty()) {
                QDomElement clazz = doc.createElement("preferences");
                clazz.setAttribute("class", name);
                if (!cp->multipleChoiceList.isEmpty()) {
                    QDomElement choices = doc.createElement("multipleChoice");
                    // only save non-default values
                    //cp.multipleChoiceList.stream().filter((mc) -> (mc.getDefaultValue() != mc.getValue())).forEach((mc) -> {
                    foreach(MultipleChoice* mc, cp->multipleChoiceList)
                    {
                     QDomElement elem;
                        choices.appendChild(elem= doc.createElement("option"));
                                elem.setAttribute("item", mc->getItem());
                                elem.setAttribute("value", (mc->getValue()));
                    };//);
                    if (!choices.childNodes().isEmpty()) {
                        clazz.appendChild(choices);
                    }
                }
                if (!cp->preferenceList.isEmpty()) {
                    QDomElement reminders = doc.createElement("reminderPrompts");
                    //cp.preferenceList.stream().filter((pl) -> (pl.getState())).forEach((pl) ->
                    foreach(PreferenceList* pl, cp->getPreferenceList())
                    {
                     QDomElement e;
                        reminders.appendChild(e = doc.createElement("reminder"));
                        e.appendChild(doc.createTextNode(pl->getItem()));
                    };//);
                    if (!reminders.childNodes().isEmpty()) {
                        clazz.appendChild(reminders);
                    }
                }
                element.appendChild(clazz);
            }
        };//);
        if (!element.childNodes().isEmpty()) {
            this->saveElement(element);
        }
    }
}

/*private*/ void JmriUserPreferencesManager::readSimplePreferenceState() {
    QDomElement element = this->readElement(SETTINGS_ELEMENT, SETTINGS_NAMESPACE);
    if (element != QDomElement())
    {
        //element.getChildren("setting").stream().forEach((setting) -> {
     QDomNodeList settings = element.elementsByTagName("setting");
     for(int i = 0; i < settings.size(); i++)
     {
      QDomElement setting = settings.at(i).toElement();
            this->simplePreferenceList.append(setting.text());
        };//);
    }
}

/*private*/ void JmriUserPreferencesManager::saveSimplePreferenceState() {
    this->setChangeMade(false);
    if (this->_allowSave) {
        QDomElement element = doc.createElementNS(SETTINGS_ELEMENT, SETTINGS_NAMESPACE);
//        getSimplePreferenceStateList().stream().forEach((setting) -> {
//            element.addContent(new Element("setting").addContent(setting));
//        });
        QStringList sl = getSimplePreferenceStateList();
        foreach (QString setting , sl)
        {
         QDomElement elem = doc.createElement("setting");

         element.appendChild(elem.appendChild(doc.createTextNode(setting)));
        }
        this->saveElement(element);
        this->resetChangeMade();
    }
}

/*private*/ void JmriUserPreferencesManager::readTableColumnPreferences() {
    QDomElement element = this->readElement(TABLES_ELEMENT, TABLES_NAMESPACE);
    if (element != QDomElement())
    {
        //element.getChildren("table").stream().forEach((table) -> {
     QDomNodeList tables = element.elementsByTagName("table");
     for(int i = 0; i < tables.size(); i ++)
     {
      QDomElement table = tables.at(i).toElement();
            QString tableName = table.attribute("name");
            int sortColumn = -1;
            /*SortOrder*/int sortOrder = UNSORTED;
            QDomElement sortKeys = table.firstChildElement("sortOrder");
            if (sortKeys != QDomElement())
            {
             QDomNodeList keys = sortKeys.childNodes();
                //for (Element sortKey : sortKeys.getChildren())
             for(int j = 0; j < keys.size(); j++)
             {
              QDomElement sortKey = keys.at(j).toElement();
                    sortOrder = sortKey.attribute("sortOrder").toInt();
                    bool ok;
                        sortColumn = sortKey.attribute("column").toInt(&ok);
                    if(!ok) {
                        log->error("Unable to get sort column as integer");
                    }
                }
            }
//            log->trace(tr("Table %1 column %2 is sorted %3").arg(tableName).arg(sortColumn).arg(sortOrder));
            //for (Element column : table.getChild("columns").getChildren())
            QDomNodeList columns = table.elementsByTagName("columns");
            for(int i = 0; i < columns.size(); i ++)
            {
             QDomElement column = columns.at(i).toElement();
                QString columnName = column.attribute("name");
                int order = -1;
                int width = -1;
                bool hidden = false;
                bool ok = true, ok1;
                    if (column.attribute("order") != NULL) {
                        order = column.attribute("order").toInt(&ok1);
                        if(!ok1) ok = false;
                    }
                    if (column.attribute("width") != NULL) {
                        width = column.attribute("width").toInt(&ok1);
                        if(!ok1) ok = false;
                    }
                    if (column.attribute("hidden") != NULL) {
                        hidden = (column.attribute("hidden").toLower()== "true");
                    }
                if(!ok) {
                    log->error(tr("Unable to parse column \"%1\"").arg(columnName));
                    continue;
                }
                if (sortColumn == order) {
                    this->setTableColumnPreferences(tableName, columnName, order, width, sortOrder, hidden);
                } else {
                    this->setTableColumnPreferences(tableName, columnName, order, width, (int)UNSORTED, hidden);
                }
            }
        };//);
    }
}

/*private*/ void JmriUserPreferencesManager::saveTableColumnPreferences()
{
 this->setChangeMade(false);
 if (this->_allowSave)
 {
  if (!this->tableColumnPrefs.isEmpty())
  {
   QDomElement element = doc.createElementNS(TABLES_ELEMENT, TABLES_NAMESPACE);
    //this->tableColumnPrefs.entrySet().stream().map((entry) -> {
   QMapIterator<QString, QMap<QString, TableColumnPreferences*> > entry(this->tableColumnPrefs);
   while(entry.hasNext())
   {
    entry.next();
    QDomElement table = doc.createElement("table");
    table.setAttribute("name", entry.key());
//    RowSorter.SortKey sortKey = new RowSorter.SortKey(0, UNSORTED);
    QDomElement columns = doc.createElement("columns");
    //for (Entry<String, TableColumnPreferences> column : entry.getValue().entrySet())
    QMapIterator<QString, TableColumnPreferences*> column(entry.value());
    while(column.hasNext())
    {
     column.next();
     QDomElement columnElement = doc.createElement("column"); columnElement.setAttribute("name", column.key());
     if (column.value()->getOrder() != -1)
     {
         columnElement.setAttribute("order", QString::number(column.value()->getOrder()));
     }
     if (column.value()->getWidth() != -1)
     {
         columnElement.setAttribute("width", QString::number(column.value()->getWidth()));
     }
     columnElement.setAttribute("hidden", column.value()->getHidden());
     columns.appendChild(columnElement);
     if (column.value()->getSort() != UNSORTED)
     {
//         sortKey = new RowSorter.SortKey(column.getValue().getOrder(), column.getValue().getSort());
      //sortKey = column.value()->getOrder();
     }
    }
    table.appendChild(columns);
#if 0
    if (sortKey.getSortOrder() != (int)UNSORTED)
    {
     QDomElement elem;
        table.appendChild(doc.createElement("sortOrder").appendChild(elem=doc.createElement("sortKey")));
                elem.setAttribute("column", QString::number(sortKey.getColumn()));
                elem.setAttribute("sortOrder", sortKey.getSortOrder().name());
    }
#endif
    //return table;
   //}).forEach((table) -> {
       element.appendChild(table);
   };//);
   this->saveElement(element);
   this->resetChangeMade();
  }
 }
}

/*private*/ void JmriUserPreferencesManager::readWindowDetails() {
    // TODO: COMPLETE!
    QDomElement element = this->readElement(WINDOWS_ELEMENT, WINDOWS_NAMESPACE);
    if (element != QDomElement())
    {
        //element.getChildren("window").stream().forEach((window) -> {
     QDomNodeList windows = element.elementsByTagName("window");
     for(int i = 0; i < windows.size(); i ++)
     {
      QDomElement window = windows.at(i).toElement();
            QString reference = window.attribute("class");
            bool ok = true, ok1;
                if (window.attribute("locX") != NULL && window.attribute("locX") != NULL) {
                    double x = window.attribute("locX").toDouble(&ok1);
                    if(!ok1) ok =false;
                    double y = window.attribute("locY").toDouble(&ok1);
                    if(!ok1) ok =false;
                    this->setWindowLocation(reference, QPoint((int) x, (int) y));
                }
                if (window.attribute("width") != NULL && window.attribute("height") != NULL) {
                    double width = window.attribute("width").toDouble(&ok1);
                    if(!ok1) ok =false;
                    double height = window.attribute("height").toDouble(&ok1);
                    if(!ok1) ok =false;
                    this->setWindowSize(reference, QSize((int) width, (int) height));
                }
            if(!ok) {
                log->error(tr("Unable to read dimensions of window \"%1\"").arg(reference));
            }
            if (!element.elementsByTagName("properties").isEmpty())
            {
                //element.getChild("properties").getChildren().stream().forEach((property) -> {
             QDomNodeList properties = element.elementsByTagName("properties");
             for(int i = 0; i < properties.size(); i++)
             {
              QDomElement property = properties.at(i).toElement();
                    QString key = property.firstChildElement("key").text();
#if 0
                    try {
                        Class<?> cl = Class.forName(property.getChild("value").attribute("class"));
                        Constructor<?> ctor = cl.getConstructor(new Class<?>[]{String.class});
                        Object value = ctor.newInstance(new Object[]{property.getChild("value").getText()});
                        this->setProperty(reference, key, value);
                    } catch (ClassNotFoundException | NoSuchMethodException | SecurityException | InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException ex) {
                        log->error("Unable to retrieve property \"{}\" for window \"{}\"", key, reference);
                    }
#endif
                };//);
            }
        };//);
    }
}

/*private*/ void JmriUserPreferencesManager::saveWindowDetails()
{
 this->setChangeMade(false);
 if (this->_allowSave)
 {
  if (!windowDetails.isEmpty())
  {
   QDomElement element = doc.createElementNS(WINDOWS_ELEMENT, WINDOWS_NAMESPACE);
   //for (Entry<String, WindowLocations> entry : windowDetails.entrySet())
   QMapIterator<QString, WindowLocations*> entry(windowDetails);
   while(entry.hasNext())
   {
    entry.next();
    QDomElement window = doc.createElement("window");
    window.setAttribute("class", entry.key());
    if (entry.value()->saveLocation)
    {
     if(entry.value() != NULL)
     {
         window.setAttribute("locX", QString::number(entry.value()->getLocation().x()));
         window.setAttribute("locY", QString::number(entry.value()->getLocation().y()));
     }
     else
     {
         // Expected if the location has not been set or the window is open
     }
    }
    if (entry.value()->saveSize)
    {
     if(!entry.value()->getSize().isValid())
     {
      double height = entry.value()->getSize().height();
      double width = entry.value()->getSize().width();
      // Do not save the width or height if set to zero
      if (!(height == 0.0 && width == 0.0))
      {
       window.setAttribute("width", QString::number(width));
       window.setAttribute("height", QString::number(height));
      }
     }
     else
     {
         // Expected if the size has not been set or the window is open
     }
    }
    if (!entry.value()->parameters.isEmpty())
    {
        QDomElement properties = doc.createElement("properties");
        //entry.getValue().parameters.entrySet().stream().map((property) -> {
        QMapIterator<QString, QVariant> property(entry.value()->parameters);
        while(property.hasNext())
        {
         property.next();
            QDomElement propertyElement = doc.createElement("property");
            propertyElement.appendChild(doc.createElement("key").appendChild(doc.createTextNode(property.key())));
            QVariant value = property.value();
            if (value != QVariant())
            {
             QDomElement e;
             propertyElement.appendChild(e = doc.createElement("value"));
                        e.setAttribute("class", /*value.getClass().getName()*/value.typeToName(value.type()));
                        e.appendChild(doc.createTextNode(value.toString()));
            }
            //return propertyElement;
        //}).forEach((propertyElement) -> {
            properties.appendChild(propertyElement);
        };//);
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
 * @return an Element or NULL if the requested element does not exist
 */
//@Nullable
/*private*/ QDomElement JmriUserPreferencesManager::readElement(/*@NonNULL*/ QString elementName, /*@NonNULL*/ QString _namespace)
 {
    QDomElement element = ProfileUtils::getUserInterfaceConfiguration(ProfileManager::getDefault()->getActiveProfile())->getConfigurationFragment(elementName, _namespace, false);
    if (element != QDomElement()) {
        //return JDOMUtil.toJDOMElement(element);
     return element;
    }
    return QDomElement();
}

/*protected*/ void JmriUserPreferencesManager::saveElement(/*@NonNULL */ QDomElement element) {
    log->debug(tr("Saving %1 element.").arg(element.tagName()));
    try {
        ProfileUtils::getUserInterfaceConfiguration(ProfileManager::getDefault()->getActiveProfile())->putConfigurationFragment(/*JDOMUtil.toW3CElement*/(element), false);
    } catch (JDOMException ex) {
        log->error("Unable to save user preferences"/*, ex*/);
    }
}

/*private*/ void JmriUserPreferencesManager::savePreferences() {
    this->saveComboBoxLastSelections();
    this->savePreferencesState();
    this->saveSimplePreferenceState();
    this->saveTableColumnPreferences();
    this->saveWindowDetails();
}

///*private*/ static class ComboBoxLastSelection {

//    String comboBoxName = NULL;
//    String lastValue = NULL;

    JmriUserPreferencesManager::ComboBoxLastSelection::ComboBoxLastSelection(QString comboBoxName, QString lastValue) {
        this->comboBoxName = comboBoxName;
        this->lastValue = lastValue;
    }

    QString JmriUserPreferencesManager::ComboBoxLastSelection::getLastValue() {
        return lastValue;
    }

    void JmriUserPreferencesManager::ComboBoxLastSelection::setLastValue(QString lastValue) {
        this->lastValue = lastValue;
    }

    QString JmriUserPreferencesManager::ComboBoxLastSelection::getComboBoxName() {
        return comboBoxName;
    }

//};

/**
 * Holds details about the speific class.
 */
//protected static class ClassPreferences {

//    String classDescription;

//    ArrayList<MultipleChoice> multipleChoiceList = new ArrayList<MultipleChoice>();
//    ArrayList<PreferenceList> preferenceList = new ArrayList<PreferenceList>();

    JmriUserPreferencesManager::ClassPreferences::ClassPreferences() {
      multipleChoiceList = QList<MultipleChoice*>();
     preferenceList = QList<PreferenceList*>();
    }

    JmriUserPreferencesManager::ClassPreferences::ClassPreferences(QString classDescription) {
     multipleChoiceList = QList<MultipleChoice*>();
     preferenceList = QList<PreferenceList*>();
        this->classDescription = classDescription;
    }

    QString JmriUserPreferencesManager::ClassPreferences::getDescription() {
        return classDescription;
    }

    void JmriUserPreferencesManager::ClassPreferences::setDescription(QString description)
    {
        classDescription = description;
    }

    QList<JmriUserPreferencesManager::PreferenceList*> JmriUserPreferencesManager::ClassPreferences::getPreferenceList()  {
        return preferenceList;
    }

    int JmriUserPreferencesManager::ClassPreferences::getPreferenceListSize() {
        return preferenceList.size();
    }

    QList<JmriUserPreferencesManager::MultipleChoice*> JmriUserPreferencesManager::ClassPreferences::getMultipleChoiceList() {
        return multipleChoiceList;
    }

    int JmriUserPreferencesManager::ClassPreferences::getPreferencesSize() {
        return multipleChoiceList.size() + preferenceList.size();
    }

    /*public*/ QString JmriUserPreferencesManager::ClassPreferences::getPreferenceName(int n) {
        try {
            return preferenceList.value(n)->getItem();
        } catch (IndexOutOfBoundsException ioob) {
            return NULL;
        }
    }

    int JmriUserPreferencesManager::ClassPreferences::getMultipleChoiceListSize() {
        return multipleChoiceList.size();
    }

    /*public*/ QString JmriUserPreferencesManager::ClassPreferences::getChoiceName(int n) {
        try {
            return multipleChoiceList.value(n)->getItem();
        } catch (IndexOutOfBoundsException ioob) {
            return NULL;
        }
    }
//}

//static class MultipleChoice {

//    HashMap<Integer, String> options;
//    String optionDescription;
//    String item;
//    int value = -1;
//    int defaultOption = -1;

    JmriUserPreferencesManager::MultipleChoice::MultipleChoice(QString description, QString item, QMap<int, QString> options, int defaultOption) {
     value = -1;
     this->defaultOption = -1;
        this->item = item;
        setMessageItems(description, options, defaultOption);
    }

    JmriUserPreferencesManager::MultipleChoice::MultipleChoice(QString item, int value) {
     this->value = -1;
     defaultOption = -1;
        this->item = item;
        this->value = value;

    }

    void JmriUserPreferencesManager::MultipleChoice::setValue(int value) {
        this->value = value;
    }

    void JmriUserPreferencesManager::MultipleChoice::setValue(QString value) {
        foreach (int o, options.keys()) {
            if (options.value(o)==value) {
                this->value =  o;
            }
        }
    }

    void JmriUserPreferencesManager::MultipleChoice::setMessageItems(QString description, QMap<int, QString> options, int defaultOption) {
        optionDescription = description;
        this->options = options;
        this->defaultOption = defaultOption;
        if (value == -1) {
            value = defaultOption;
        }
    }

    int JmriUserPreferencesManager::MultipleChoice::getValue() {
        return value;
    }

    int JmriUserPreferencesManager::MultipleChoice::getDefaultValue() {
        return defaultOption;
    }

    QString JmriUserPreferencesManager::MultipleChoice::getItem() {
        return item;
    }

    QString JmriUserPreferencesManager::MultipleChoice::getOptionDescription() {
        return optionDescription;
    }

    QMap<int, QString> JmriUserPreferencesManager::MultipleChoice::getOptions() {
        return options;
    }

//}

//static class PreferenceList {

//    // need to fill this with bits to get a meaning full description.
//    bool set = false;
//    String item = "";
//    String description = "";

    JmriUserPreferencesManager::PreferenceList::PreferenceList(QString item) {
     item = "";
     description = "";
        this->item = item;
    }

    JmriUserPreferencesManager::PreferenceList::PreferenceList(QString item, bool state) {
     item = "";
     description = "";
        this->item = item;
        set = state;
    }

    JmriUserPreferencesManager::PreferenceList::PreferenceList(QString item, QString description) {
     item = "";
     description = "";
        this->description = description;
        this->item = item;
    }

    void JmriUserPreferencesManager::PreferenceList::setDescription(QString desc) {
        description = desc;
    }

    QString JmriUserPreferencesManager::PreferenceList::getDescription() {
        return description;
    }

    bool JmriUserPreferencesManager::PreferenceList::getState() {
        return set;
    }

    void JmriUserPreferencesManager::PreferenceList::setState(bool state) {
        this->set = state;
    }

    QString JmriUserPreferencesManager::PreferenceList::getItem() {
        return item;
    }

//}

//static class WindowLocations {

//    Point xyLocation = new Point(0, 0);
//    Dimension size = new Dimension(0, 0);
//    bool saveSize = false;
//    bool saveLocation = false;

    JmriUserPreferencesManager::WindowLocations::WindowLocations() {
     xyLocation = QPoint(0, 0);
     size = QSize(0, 0);
     saveSize = false;
     saveLocation = false;
     parameters = QMap<QString, QVariant>();
    }

   QPoint JmriUserPreferencesManager::WindowLocations::getLocation() {
        return xyLocation;
    }

    QSize JmriUserPreferencesManager::WindowLocations::getSize() {
        return size;
    }

    void JmriUserPreferencesManager::WindowLocations::setSaveSize(bool b) {
        saveSize = b;
    }

    void JmriUserPreferencesManager::WindowLocations::setSaveLocation(bool b) {
        saveLocation = b;
    }

    bool JmriUserPreferencesManager::WindowLocations::getSaveSize() {
        return saveSize;
    }

    bool JmriUserPreferencesManager::WindowLocations::getSaveLocation() {
        return saveLocation;
    }

    void JmriUserPreferencesManager::WindowLocations::setLocation(QPoint xyLocation) {
        this->xyLocation = xyLocation;
        saveLocation = true;
    }

    void JmriUserPreferencesManager::WindowLocations::setSize(QSize size) {
        this->size = size;
        saveSize = true;
    }

    void JmriUserPreferencesManager::WindowLocations::setProperty(QString key, QVariant value) {
        parameters.insert(key, value);
    }

    QVariant JmriUserPreferencesManager::WindowLocations::getProperty(QString key) {
        return parameters.value(key);
    }

    QSet<QString> JmriUserPreferencesManager::WindowLocations::getPropertyKeys() {
        return parameters.keys().toSet();
    }

//    /*final*/ HashMap<String, Object> parameters = new HashMap<>();

//}

//static class TableColumnPreferences {

//    int order;
//    int width;
//    SortOrder sort;
//    bool hidden;

    JmriUserPreferencesManager::TableColumnPreferences::TableColumnPreferences(int order, int width, int sort, bool hidden) {
        this->order = order;
        this->width = width;
        this->sort = sort;
        this->hidden = hidden;
    }

    int JmriUserPreferencesManager::TableColumnPreferences::getOrder() {
        return order;
    }

    int JmriUserPreferencesManager::TableColumnPreferences::getWidth() {
        return width;
    }

    int JmriUserPreferencesManager::TableColumnPreferences::getSort() {
        return sort;
    }

    bool JmriUserPreferencesManager::TableColumnPreferences::getHidden() {
        return hidden;
    }
//}
