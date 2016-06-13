#include "defaultusermessagepreferences.h"
#include "instancemanager.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCheckBox>
#include <QMessageBox>
#include "quietshutdowntask.h"
#include "propertychangelistener.h"
#include "defaultshutdownmanager.h"
#include "level.h"
#include <QFont>
#include <QVBoxLayout>
#include "fileutil.h"
#include <QSettings>
#include "../LayoutEditor/configxmlmanager.h"
#include "configuremanager.h"
#include "../LayoutEditor/defaultusermessagepreferencesxml.h"
#include <QLabel>
#include <QMetaType>
#include "appconfigbase.h"
#include "abstracttableaction.h"
#include "routetableaction.h"
#include "logixtableaction.h"
#include "lroutetableaction.h"
#include "sectiontableaction.h"
#include "sensortableaction.h"
#include "signalgrouptableaction.h"

//DefaultUserMessagePreferences::DefaultUserMessagePreferences(QObject *parent) :
//    UserPrefeerencesManager(parent)
//{
//}
/**
 * Basic Implementation of the User Preferences Manager.
 * <P>
 * The User Message Preference Manager keeps track of the options that a user
 * has selected in messages where they have selected "Remember this setting for next time"
 *
 * @author      Kevin Dickerson Copyright (C) 2010
 * @version	$Revision: 22539 $
 */

//@net.jcip.annotations.NotThreadSafe  // intended for access from Swing thread only
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(
//    value="ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//    justification="Class is single-threaded, and uses statics extensively")

///*public*/ class DefaultUserMessagePreferences extends jmri.jmrit.XmlFile  implements UserPreferencesManager {

/*private*/ /*static*/ /*volatile*/ bool DefaultUserMessagePreferences::_changeMade = false;
/*private*/ /*static*/ /*volatile*/ bool DefaultUserMessagePreferences::_loading = false;


// needs to be package or protected level for tests to be able to instantiate
DefaultUserMessagePreferences::DefaultUserMessagePreferences(QObject* parent) : UserPreferencesManager(parent)
{
 _allowSave = true;
 log = new Logger("DefaultUserMessagePreferences");
 setObjectName("DefaultUserMessagePreferences");
 simplePreferenceList =  QStringList();
 //sessionList is used for messages to be suppressed for the current JMRI session only
 sessionPreferenceList =  QStringList();
 _comboBoxLastSelection = QList<ComboBoxLastSelection*>();
 listeners = new QVector<PropertyChangeListener*>();
 windowDetails = QHash<QString, WindowLocations*>();
 classPreferenceList = QHash<QString, ClassPreferences*>();
 tableColumnPrefs =  QHash<QString, QHash<QString,TableColumnPreferences*> >();
 userPreferencesShutDownTask = NULL;
 file = NULL;
 // Make  sure that InstanceManager is registered!
 InstanceManager* instanceManger = InstanceManager::instance();

 // register this object to be stored as part of preferences
 if (InstanceManager::configureManagerInstance() != NULL)
    ((ConfigXmlManager*)InstanceManager::configureManagerInstance())->registerUserPrefs(this);
 if (InstanceManager::getDefault("UserPreferencesManager")==NULL)
 {
    //We add this to the instanceManager so that other components can access the preferences
    //We need to make sure that this is registered before we do the read
    InstanceManager::store(this, "UserPreferencesManager");
    //qRegisterMetaType<DefaultUserMessagePreferences>("DefaultUserMessagePreferences");
 }

 // register a shutdown task to force storing of preferences at shutdown
 if (userPreferencesShutDownTask==NULL)
 {
  userPreferencesShutDownTask = (ShutDownTask*)new UserPreferencesShutDownTask("User Preferences Shutdown", this);
//        {
//            @Override
//            /*public*/ bool doAction(){
//                if (getChangeMade()){
//                    log->info("Storing preferences as part of shutdown");
//                    if (allowSave){
//                        InstanceManager::configureManagerInstance().storeUserPrefs(file);
//                    } else {
//                        log->info("Not allowing save of changes as the user has accessed the preferences and not performed a save");
//                    }
//                }
//                return true;
//            }
//        };

  // need a shut down manager to be present
  if (InstanceManager::instance()->shutDownManagerInstance() !=NULL)
  {
   ((DefaultShutDownManager*)InstanceManager::shutDownManagerInstance())-> _register((ShutDownTask*)userPreferencesShutDownTask);
  }
  else
  {
   log->warn("Won't protect preferences at shutdown without registered ShutDownManager");
  }
 }

 preferenceItemDetails(getClassName(), "reminder", "Hide Reminder Location Message");
 classPreferenceList.value(getClassName())->setDescription("User Preferences");
 readUserPreferences();
#if 0
 qRegisterMetaType<RouteTableAction>("RouteTableAction");
 qRegisterMetaType<AppConfigBase>("AppConfigBase");
 qRegisterMetaType<LogixTableAction>("LogixTableAction");
 qRegisterMetaType<LRouteTableAction>("LRouteTableAction");
 qRegisterMetaType<SectionTableAction>("SectionTableAction");
 qRegisterMetaType<SensorTableAction>("SensorTableAction");
 qRegisterMetaType<SignalGroupTableAction>("SignalGroupTableAction");
#endif
}

UserPreferencesShutDownTask::UserPreferencesShutDownTask(QString name, DefaultUserMessagePreferences *parent) : QuietShutDownTask(name,parent)
{
  //QuietShutDownTask(name, parent);
  log = new Logger("UserPreferencesShutDownTask");
  this->parent = parent;
  setObjectName("UserPreferencesShutDownTask");
}

/*public*/ bool UserPreferencesShutDownTask::doAction()
{
 if (((DefaultUserMessagePreferences*)parent)->getChangeMade())
 {
  log->info("Storing preferences as part of shutdown");
  if (parent->_allowSave)
  {
   ConfigXmlManager* cfg = (ConfigXmlManager*)InstanceManager::configureManagerInstance();
   if(cfg == NULL)
   {
    cfg = new ConfigXmlManager();
    InstanceManager::setConfigureManager((ConfigureManager*)cfg);
   }
   if(parent->file == NULL)
   {
    QString userprefsfilename="UserPrefsDecoderProConfig2.xml";
    parent->file = new QFile(FileUtil::getUserFilesPath()+userprefsfilename);  }
   QSettings settings;
   settings.setValue("configFileName",parent->file->fileName());

   ((ConfigXmlManager*)InstanceManager::configureManagerInstance())->storeUserPrefs(new File(parent->file->fileName()));

  }
  else
  {
   log->info("Not allowing save of changes as the user has accessed the preferences and not performed a save");
  }
 }
 return true;
}

/*static*/ class DefaultUserMessagePreferencesHolder
{
public:
    static DefaultUserMessagePreferences* instance;
    DefaultUserMessagePreferencesHolder()
    {
     instance = NULL;
    }
};
/*static*/ DefaultUserMessagePreferences*
    DefaultUserMessagePreferencesHolder::instance = new DefaultUserMessagePreferences();

/*public*/  DefaultUserMessagePreferences* DefaultUserMessagePreferences::getInstance()
{
 if (DefaultUserMessagePreferencesHolder::instance == NULL) DefaultUserMessagePreferencesHolder::instance = new DefaultUserMessagePreferences();
 return DefaultUserMessagePreferencesHolder::instance;
}

/*public*/ /*synchronized*/ void DefaultUserMessagePreferences::allowSave()
{
  QMutexLocker locker(&mutex);
  DefaultUserMessagePreferencesHolder::instance->_allowSave = true;
}
/*public*/ /*synchronized*/ void DefaultUserMessagePreferences::disallowSave()
{
  QMutexLocker locker(&mutex);
  DefaultUserMessagePreferencesHolder::instance->_allowSave = false;
 }

/*public*/ QSize DefaultUserMessagePreferences::getScreen()
{
 //return Toolkit.getDefaultToolkit().getScreenSize();
 QDesktopWidget* screen = QApplication::desktop();
 return screen->size();
}

/**
 * This is used to remember the last selected state of a checkBox and thus
 * allow that checkBox to be set to a true state when it is next initialised.
 * This can also be used anywhere else that a simple yes/no, true/false type
 * preference needs to be stored.
 *
 * It should not be used for remembering if a user wants to suppress a message
 * as there is no means in the GUI for the user to reset the flag.
 * setPreferenceState() should be used in this instance
 * The name is free-form, but to avoid ambiguity it should
 * start with the package name (package.Class) for the
 * primary using class.
 * @param name A unique name to identify the state being stored
 * @param state simple bool.
 */
/*public*/ void DefaultUserMessagePreferences::setSimplePreferenceState(QString name, bool state)
{
 if (state)
 {
  if (!simplePreferenceList.contains(name))
  {
   simplePreferenceList.append(name);
  }
 }
 else
 {
  simplePreferenceList.removeAt(simplePreferenceList.indexOf(name));
 }
 setChangeMade(false);
}

/*public*/ QStringList DefaultUserMessagePreferences::getSimplePreferenceStateList() { return simplePreferenceList; }

/**
 * Enquire as to the state of a user preference.
 * <p>
 * Preferences that have not been set will be
 * considered to be false.
 *<p>
 * The name is free-form, but to avoid ambiguity it should
 * start with the package name (package.Class) for the
 * primary using class.
 */
/*public*/ bool DefaultUserMessagePreferences::getSimplePreferenceState(QString name) {
    return simplePreferenceList.contains(name);
}


/**
 * Used to save the state of checkboxes which can suppress messages from being
 * displayed.
 * This method should be used by the initiating code in conjunction with the
 * preferenceItemDetails.
 * Here the items are stored against a specific class and access to change
 * them is made available via the GUI, in the preference manager.
 * <p>
 * The strClass parameter does not have to be the exact class name of the
 * initiating code, but can be one where the information is related and therefore
 * can be grouped together with.
 * <p>
 * Both the strClass and item although free form, should make up a unique reference.
 * @param strClass The class that this preference should be stored or grouped with.
 * @param item The specific item that is to be stored
 * @param state Boolean state of the item.
 */

/*public*/ void DefaultUserMessagePreferences::setPreferenceState(QString strClass, QString item, bool state)
{
 if(!classPreferenceList.contains(strClass))
 {
  classPreferenceList.insert(strClass, new ClassPreferences());
  setClassDescription(strClass);
 }
 QList<PreferenceList*>* a = classPreferenceList.value(strClass)->getPreferenceList();
 bool found = false;
 for(int i = 0; i<a->size(); i++)
 {
  if (a->value(i)->getItem()==(item))
  {
   a->value(i)->setState(state);
   found = true;
  }
 }
 if (!found)
  a->append(new PreferenceList(item, state));
 displayRememberMsg();
 setChangeMade(true);
}

/**
* Returns the state of a given item registered against a specific class or item.
*/
/*public*/ bool DefaultUserMessagePreferences::getPreferenceState(QString strClass, QString item){
    if (classPreferenceList.contains(strClass)){
        QList<PreferenceList*>* a = classPreferenceList.value(strClass)->getPreferenceList();
        for(int i = 0; i<a->size(); i++){
            if (a->value(i)->getItem()==(item)){
                return a->value(i)->getState();
            }
        }
    }
    return false;
}

/**
* Register details about a perticular preference, so that it can be displayed
* in the GUI and provide a meaning full description when presented to the user.
* @param strClass A string form of the class that the preference is stored or grouped with
* @param item The specific item that is being stored.
* @param description A meaningful decription of the item that the user will understand.
*/
/*public*/ void DefaultUserMessagePreferences::preferenceItemDetails(QString strClass, QString item, QString description)
{
 if (!classPreferenceList.contains(strClass))
 {
  classPreferenceList.insert(strClass, new ClassPreferences());
 }
 QList<PreferenceList*>* a = classPreferenceList.value(strClass)->getPreferenceList();
 for(int i = 0; i<a->size(); i++)
 {
  if (a->value(i)->getItem()==(item))
  {
   a->value(i)->setDescription(description);
   return;
  }
 }
 a->append(new PreferenceList(item, description));
}

/**
 * Returns a list of preferences that are registered against a specific class.
 */
/*public*/ QStringList DefaultUserMessagePreferences::getPreferenceList(QString strClass){
    if (classPreferenceList.contains(strClass)){
        QList<PreferenceList*>* a = classPreferenceList.value(strClass)->getPreferenceList();
        QStringList list =  QStringList();
        for (int i = 0; i<a->size(); i++){
            list.append(a->value(i)->getItem());
        }
        return list;
    }
    //Just return a blank array list will save call code checking for NULL
    return  QStringList();
}

/**
 * Returns the itemName of the n preference in the given class
 */
/*public*/ QString DefaultUserMessagePreferences::getPreferenceItemName(QString strClass, int n){
    if (classPreferenceList.contains(strClass)){
        return classPreferenceList.value(strClass)->getPreferenceName(n);
    }
    return "";
}

/**
 * Returns the description of the given item preference in the given class
 */
/*public*/ QString DefaultUserMessagePreferences::getPreferenceItemDescription(QString strClass, QString item){
    if (classPreferenceList.contains(strClass)){
        QList<PreferenceList*>* a = classPreferenceList.value(strClass)->getPreferenceList();
        for(int i = 0; i<a->size(); i++){
            if (a->value(i)->getItem()==(item)){
                return a->value(i)->getDescription();
            }
        }
    }
    return NULL;

}

/**
* Used to surpress messages for a perticular session, the information is not
* stored, can not be changed via the GUI.
* <p>
* This can be used to help prevent over loading the user with repetitive error
* messages such as turnout not found while loading a panel file due to a connection failing.
* The name is free-form, but to avoid ambiguity it should
* start with the package name (package.Class) for the
* primary using class.
* @param name A unique identifer for preference.
* @param state
*/
/*public*/ void DefaultUserMessagePreferences::setSessionPreferenceState(QString name, bool state) {
    if (state) {
        if (!sessionPreferenceList.contains(name)){
            sessionPreferenceList.append(name);
        }
    } else {
        sessionPreferenceList.removeAt(sessionPreferenceList.indexOf(name));
    }
}


/**
 * Enquire as to the state of a user preference for the current session.
 * <p>
 * Preferences that have not been set will be
 * considered to be false.
 *<p>
 * The name is free-form, but to avoid ambiguity it should
 * start with the package name (package.Class) for the
 * primary using class.
 */
/*public*/ bool DefaultUserMessagePreferences::getSessionPreferenceState(QString name) {
    return sessionPreferenceList.contains(name);
}

/**
 * Show an info message ("don't forget ...")
 * with a given dialog title and
 * user message.
 * Use a given preference name to determine whether
 * to show it in the future.
 * The classString & item parameters should form a unique value
 * @param title Message Box title
 * @param message Message to be displayed
 * @param strClass String value of the calling class
 * @param item String value of the specific item this is used for
 */
/*public*/ void DefaultUserMessagePreferences::showInfoMessage(QString title, QString message, QString strClass, QString item) {
    showInfoMessage(title, message, strClass, item, false, true, Level::INFO);
}

/**
 * Show an info message ("don't forget ...")
 * with a given dialog title and
 * user message.
 * Use a given preference name to determine whether
 * to show it in the future.
 * added flag to indicate that the message should be suppressed
 * JMRI session only.
 * The classString & item parameters should form a unique value
 * @param title Message Box title
 * @param message Message to be displayed
 * @param strClass String value of the calling class
 * @param item String value of the specific item this is used for
 * @param sessionOnly Means this message will be suppressed in this JMRI session and not be remembered
 * @param alwaysRemember Means that the suppression of the message will be saved
 * @param level Used to determine the type of message box that will be used.
 */
/*public*/ void DefaultUserMessagePreferences::showInfoMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, Level* level)
{
 /*final*/ UserPreferencesManager* p;
 p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 int type = QMessageBox::Information;
 if (level == Level::_ERROR) {
  type = QMessageBox::Critical;
 }
 else if (level == Level::WARNING)
 {
  type = QMessageBox::Warning;
 }

 /*final*/ QString preference = strClass + "." + item;

 if (p->getSessionPreferenceState(preference))
 {
  return;
 }
 if (!p->getPreferenceState(strClass, item))
 {
  QWidget* container = new QWidget();
  container->setLayout(new QVBoxLayout(container/*, BoxLayout.Y_AXIS*/));
  container->layout()->addWidget(new QLabel(message));
  /*final*/ QCheckBox* rememberSession = new QCheckBox(tr("Skip message for this session only?"));
  if (sessionOnly)
  {
   rememberSession->setFont(rememberSession->font()/*.deriveFont(10.)*/);
   container->layout()->addWidget(rememberSession);
  }
  /*final*/ QCheckBox* remember = new QCheckBox(tr("Skip message in future?"));
  if (alwaysRemember)
  {
   remember->setFont(remember->font()/*.deriveFont(10.)*/);
   container->layout()->addWidget(remember);
  }
//        JOptionPane.showMessageDialog(NULL, // center over parent component
//                container,
//                title,
//                type);
  switch(type)
  {
   case QMessageBox::Information:
    QMessageBox::information(container, title, message);
    break;
   case QMessageBox::Warning:
    QMessageBox::warning(container, title, message);
    break;
   case QMessageBox::Critical:
    QMessageBox::critical(container, title, message);
  }
  if (remember->isChecked())
  {
   p->setPreferenceState(strClass, item, true);
  }
  if (rememberSession->isChecked())
  {
   p->setSessionPreferenceState(preference, true);
  }
 }
}

/**
 * Show an info message ("don't forget ...")
 * with a given dialog title and
 * user message.
 * Use a given preference name to determine whether
 * to show it in the future.
 * added flag to indicate that the message should be suppressed
 * JMRI session only.
 * The classString & item parameters should form a unique value
 * @param title Message Box title
 * @param message Message to be displayed
 * @param strClass String value of the calling class
 * @param item String value of the specific item this is used for
 * @param sessionOnly Means this message will be suppressed in this JMRI session and not be remembered
 * @param alwaysRemember Means that the suppression of the message will be saved
 */
/*public*/ void DefaultUserMessagePreferences::showErrorMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember) {
    this->showMessage(title, message, strClass, item, sessionOnly, alwaysRemember, 0);
}
/*private*/ void DefaultUserMessagePreferences::showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int /*type*/)
{
 UserPreferencesManager* p;
 p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");

 /*final*/ QString preference = strClass + "." + item;

 if (p->getSessionPreferenceState(preference))
 {
  return;
 }
 if (!p->getPreferenceState(strClass, item))
 {
  QWidget* container = new QWidget();
  QVBoxLayout* containerLayout;
  container->setLayout(containerLayout = new QVBoxLayout);//(container, BoxLayout.Y_AXIS));
  containerLayout->addWidget(new QLabel(message));
  /*final*/ QCheckBox* rememberSession = new QCheckBox("Skip message for this session only?");
  if (sessionOnly)
  {
//    rememberSession->setFont(rememberSession.getFont().deriveFont(10f));
    containerLayout->addWidget(rememberSession);
  }
  /*final*/ QCheckBox* remember = new QCheckBox("Skip message in future?");
  if (alwaysRemember)
  {
//    remember.setFont(remember.getFont().deriveFont(10f));
    containerLayout->addWidget(remember);
  }
//  JOptionPane.showMessageDialog(null, // center over parent component
//        container,
//        title,
//        type);
  // TODO: implement JOptionPane
  QMessageBox::warning(container, title, message);
  if (remember->isChecked())
  {
    p->setPreferenceState(strClass, item, true);
  }
  if (rememberSession->isChecked())
  {
   p->setSessionPreferenceState(preference, true);
  }
 }
}
/**
 * Adds the last selection of a combo box.
 * <p>
 * The name is free-form, but to avoid ambiguity it should
 * start with the package name (package.Class) for the
 * primary using class, followed by an identifier for the combobox
 */
/*public*/ void DefaultUserMessagePreferences::addComboBoxLastSelection(QString comboBoxName, QString lastValue)
{
 if (getComboBoxLastSelection(comboBoxName)==NULL)
 {
  ComboBoxLastSelection* combo = new ComboBoxLastSelection(comboBoxName, lastValue);
  _comboBoxLastSelection.append(combo);
 }
 else
 {
  setComboBoxLastSelection(comboBoxName, lastValue);
 }
 setChangeMade(false);
}

/**
 * returns the last selected value in a given combobox
 *
 */
/*public*/ QString DefaultUserMessagePreferences::getComboBoxLastSelection(QString comboBoxName)
{
 for (int i=0; i<_comboBoxLastSelection.size(); i++)
 {
  if( _comboBoxLastSelection.at(i)->getComboBoxName()==(comboBoxName))
  {
   return _comboBoxLastSelection.at(i)->getLastValue();
  }
 }
 return NULL;
}

/**
* sets the last selected value in a given combobox
*
*/
/*public*/ void DefaultUserMessagePreferences::setComboBoxLastSelection(QString comboBoxName, QString lastValue)
{
 for (int i=0; i<_comboBoxLastSelection.size(); i++)
 {
  if( _comboBoxLastSelection.at(i)->getComboBoxName()==(comboBoxName))
  {
   _comboBoxLastSelection.at(i)->setLastValue(lastValue);
  }
 }
 setChangeMade(false);
}

/**
* returns the number of comboBox options saved
*
*/
/*public*/ int DefaultUserMessagePreferences::getComboBoxSelectionSize() { return _comboBoxLastSelection.size(); }

/**
* returns the ComboBox Name at position n
*
*/
/*public*/ QString DefaultUserMessagePreferences::getComboBoxName(int n)
{
 try
 {
  return _comboBoxLastSelection.at(n)->getComboBoxName();
 }
 catch (IndexOutOfBoundsException ioob)
 {
  return "";
 }
}

/**
* returns the ComboBox Value at position n
*
*/
/*public*/ QString DefaultUserMessagePreferences::getComboBoxLastSelection(int n)
{
 try
 {
  return _comboBoxLastSelection.at(n)->getLastValue();
 }
 catch (IndexOutOfBoundsException ioob)
 {
  return "";
 }
}



/*public*/ /*synchronized*/ bool DefaultUserMessagePreferences::getChangeMade(){ return _changeMade; }
/*public*/ /*synchronized*/ void DefaultUserMessagePreferences::setChangeMade(bool fireUpdate) {
    _changeMade=true;
    if(fireUpdate)
        notifyPropertyChangeListener("PreferencesUpdated", QVariant(), QVariant() );
}

//The reset is used after the preferences have been loaded for the first time

/*public*/ /*synchronized*/ void DefaultUserMessagePreferences::resetChangeMade(){ _changeMade = false; }

/*public*/ void DefaultUserMessagePreferences::removePropertyChangeListener(PropertyChangeListener* l) {
    if (listeners->contains(l)) {
        listeners->remove(listeners->indexOf(l));
    }
}

/*public*/ void DefaultUserMessagePreferences::addPropertyChangeListener(PropertyChangeListener* l) {
    // add only if not already registered
    if (!listeners->contains(l)) {
        listeners->append(l);
    }
}

//@SuppressWarnings("unchecked")
/*protected*/ void DefaultUserMessagePreferences::notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue) {
#if 0
    // make a copy of the listener vector to synchronized not needed for transmit
    QVector<PropertyChangeListener*> v;
//    synchronized(this)
        {
        QMutexLocker locker(&mutex);
            v = (QVector<PropertyChangeListener*>) listeners->clone();
        }
    if (log->isDebugEnabled()) log->debug("notify "+QString::number(v.size())
                                        +" listeners about property "
                                        +property);
    // forward to all listeners
    int cnt = v.size();
    for (int i=0; i < cnt; i++) {
        PropertyChangeListener* client = v.at(i);
        client->propertyChange(new PropertyChangeEvent(this, property, oldValue, newValue));
    }

#endif
    emit propertyChange(new PropertyChangeEvent(this, property, oldValue, newValue));
}

/*public*/ void DefaultUserMessagePreferences::setLoading() { _loading = true; }
/*public*/ void DefaultUserMessagePreferences::finishLoading() {
    _loading = false;
    resetChangeMade();
}

/*public*/ void DefaultUserMessagePreferences::displayRememberMsg(){
    if (_loading) return;
    showInfoMessage("Reminder", "You can re-display this message from 'Edit|Preferences|Message' Menu.", getClassName(), "reminder");
}


/*public*/ QPoint DefaultUserMessagePreferences::getWindowLocation(QString strClass){
    if(windowDetails.contains(strClass)){
        return windowDetails.value(strClass)->getLocation();
    }
    return QPoint();
}

/*public*/ QSize DefaultUserMessagePreferences::getWindowSize(QString strClass){
    if(windowDetails.contains(strClass)){
        return windowDetails.value(strClass)->getSize();
    }
    return QSize();
}

/*public*/ bool DefaultUserMessagePreferences::getSaveWindowSize(QString strClass){
    if(windowDetails.contains(strClass)){
        return windowDetails.value(strClass)->getSaveSize();
    }
    return false;
}

/*public*/ bool DefaultUserMessagePreferences::getSaveWindowLocation(QString strClass){
    if(windowDetails.contains(strClass)){
        return windowDetails.value(strClass)->getSaveLocation();
    }
    return false;
}

/*public*/ void DefaultUserMessagePreferences::setSaveWindowSize(QString strClass, bool b)
{
 if(windowDetails.contains(strClass))
 {
  windowDetails.value(strClass)->setSaveSize(b);
 }
}

/*public*/ void DefaultUserMessagePreferences::setSaveWindowLocation(QString strClass, bool b)
{
 if(windowDetails.contains(strClass))
 {
  windowDetails.value(strClass)->setSaveLocation(b);
 }
}

/*public*/ void DefaultUserMessagePreferences::setWindowLocation(QString strClass, QPoint location)
{
 if((strClass=="") || (strClass==("JmriJFrame")))
  return;
 if(!windowDetails.contains(strClass))
 {
  windowDetails.insert(strClass, new WindowLocations());
 }
 windowDetails.value(strClass)->setLocation(location);
 setChangeMade(false);
}

/*public*/ void DefaultUserMessagePreferences::setWindowSize(QString strClass, QSize dim)
{
 if(strClass==("JmriJFrame"))
  return;
 if(!windowDetails.contains(strClass))
 {
  windowDetails.insert(strClass, new WindowLocations());
 }
 windowDetails.value(strClass)->setSize(dim);
 setChangeMade(false);
}

/*public*/ QStringList DefaultUserMessagePreferences::getWindowList()
{
 QStringList list =  QStringList();
 QStringListIterator keys( windowDetails.keys());
 while ( keys.hasNext() )
 {
  QString key = keys.next();
  list.append(key);
 } // end while
 return list;
}

/*public*/ void DefaultUserMessagePreferences::setProperty(QString strClass, QString key, QVariant value)
{
 if(strClass==("JmriJFrame"))
  return;
 if(!windowDetails.contains(strClass))
 {
  windowDetails.insert(strClass, new WindowLocations());
 }
 windowDetails.value(strClass)->setProperty(key, value);
}

/*public*/ QVariant DefaultUserMessagePreferences::getProperty(QString strClass, QString key)
{
 if(windowDetails.contains(strClass))
 {
  return windowDetails.value(strClass)->getProperty(key);
 }
 return QVariant();
}

/*public*/ QSet<QString> DefaultUserMessagePreferences::getPropertyKeys(QString strClass)
{
 if(windowDetails.contains(strClass))
 {
  return windowDetails.value(strClass)->getPropertyKeys();
 }
 return QSet<QString>();
}


/*public*/ bool DefaultUserMessagePreferences::isWindowPositionSaved(QString strClass)
{
 return windowDetails.contains(strClass);
}


/**
* Returns the description of a class/group registered with the preferences.
*/
/*public*/ QString DefaultUserMessagePreferences::getClassDescription(QString strClass){
    if(classPreferenceList.contains(strClass)){
        return classPreferenceList.value(strClass)->getDescription();
    }
    return "";
}

/**
* Returns a list of the classes registered with the preference manager.
*/
/*public*/ QStringList DefaultUserMessagePreferences::getPreferencesClasses()
{
 QStringList list =  QStringList();
 QStringListIterator keys(classPreferenceList.keys());
 while ( keys.hasNext() )
 {
  QString key = keys.next();
  list.append(key);
 } // end while
 return list;
}

/**
 * Given that we know the class as a string, we will try and attempt to gather
 * details about the preferences that has been added, so that we can make better
 * sense of the details in the preferences window.
 * <p>
 * This looks for specific methods within the class called "getClassDescription"
 * and "setMessagePreferenceDetails".  If found it will invoke the methods,
 * this will then trigger the class to send details about its preferences back
 * to this code.
 */
/*public*/ void DefaultUserMessagePreferences::setClassDescription(QString strClass)
{
#if 1
 QString className;
 if(strClass.contains("."))
  className = strClass.mid(strClass.lastIndexOf(".")+1);
 else
  className = strClass;
 //try {
 //Class<?> cl = Class.forName(strClass);
 int typeId = QMetaType::type(className.toLocal8Bit());
 if(typeId > 0)
 {
  void* t = NULL;
  //Object t = cl.newInstance();
#if QT_VERSION < 0x050000
  t = QMetaType::construct(typeId);
#else
  t = QMetaType::create(typeId);
#endif
  if(t != NULL)
  {
   bool classDesFound=false;
   bool classSetFound=false;
   QString desc = "";
   if(qobject_cast<AbstractTableAction*>((QObject*)t) != NULL)
   {
    AbstractTableAction* cl = (AbstractTableAction*)t;
    desc = cl->getClassDescription();
    classDesFound = true;
    classSetFound = true;
    cl->setMessagePreferencesDetails();
   }
   if(qobject_cast<AppConfigBase*>((QObject*)t) != NULL)
   {
    AppConfigBase* cl = (AppConfigBase*)t;
    desc = cl->getClassDescription();
    classDesFound = true;
    classSetFound = true;
    cl->setMessagePreferencesDetails();
   }

#if 0
        Method method;
        //look through declared methods first, then all methods
        try {
            method = cl.getDeclaredMethod ("getClassDescription");
            desc = (String)method.invoke(t);
            classDesFound = true;
        } catch (IllegalAccessException ex) {
            log->debug(ex.toString());
            classDesFound=false;
        } catch (IllegalArgumentException ea) {
            log->debug(ea.toString());
            classDesFound=false;
        } catch (java.lang.reflect.InvocationTargetException ei) {
            log->debug(ei.toString());
            classDesFound=false;
        } catch (NullPointerException ee) {
            log->debug(ee.toString());
            classDesFound=false;
        } catch (ExceptionInInitializerError eo) {
            log->debug(eo.toString());
            classDesFound=false;
        } catch (NoSuchMethodException en) {
            log->debug(en.toString());
            classDesFound=false;
        }
        if (!classDesFound){
            try {
                method = cl.getMethod ("getClassDescription");
                desc = (String)method.invoke(t);
            } catch (IllegalAccessException ex) {
                log->debug(ex.toString());
                classDesFound=false;
            } catch (IllegalArgumentException ea) {
                log->debug(ea.toString());
                classDesFound=false;
            } catch (java.lang.reflect.InvocationTargetException ei) {
                log->debug(ei.toString());
                classDesFound=false;
            } catch (NullPointerException ee) {
                log->debug(ee.toString());
                classDesFound=false;
            } catch (ExceptionInInitializerError eo) {
                log->debug(eo.toString());
                classDesFound=false;
            } catch (NoSuchMethodException en) {
                log->debug(en.toString());
                classDesFound=false;
            }
        }
#endif
   if(classDesFound)
   {
    if(!classPreferenceList.contains(strClass))
     classPreferenceList.insert(strClass, new ClassPreferences(desc));
    else
     classPreferenceList.value(strClass)->setDescription(desc);
   }
#if 0
        try {
            method = cl.getDeclaredMethod ("setMessagePreferencesDetails");
            method.invoke(t);
            classSetFound = true;
        } catch (IllegalAccessException ex) {
            log->debug(ex.toString());
            classSetFound=false;
        } catch (IllegalArgumentException ea) {
            log->debug(ea.toString());
            classSetFound=false;
        } catch (java.lang.reflect.InvocationTargetException ei) {
            log->debug(ei.toString());
            classSetFound=false;
        } catch (NullPointerException ee) {
            log->debug(ee.toString());
            classSetFound=false;
        } catch (ExceptionInInitializerError eo) {
            log->debug(eo.toString());
            classSetFound=false;
        } catch (NoSuchMethodException en) {
            log->debug(en.toString());
            classSetFound=false;
        }
        if (!classSetFound){
            try {
                method = cl.getMethod ("setMessagePreferencesDetails");
                method.invoke(t);
                classSetFound = true;
            } catch (IllegalAccessException ex) {
                log->debug(ex.toString());
                classSetFound=false;
            } catch (IllegalArgumentException ea) {
                log->debug(ea.toString());
                classSetFound=false;
            } catch (java.lang.reflect.InvocationTargetException ei) {
                log->debug(ei.toString());
                classSetFound=false;
            } catch (NullPointerException ee) {
                log->debug(ee.toString());
                classSetFound=false;
            } catch (ExceptionInInitializerError eo) {
                log->debug(eo.toString());
                classSetFound=false;
            } catch (NoSuchMethodException en) {
                log->debug(en.toString());
                classSetFound=false;
            }
        }
#endif
//    }
//    catch (java.lang.ClassNotFoundException ec){
//        log->error("class name "+ strClass + " is in valid " + ec);
//    }
//    catch (java.lang.IllegalAccessException ex){
//        ex.printStackTrace();
//    }
//    catch (Exception e) {
//        log->error("unable to get a class name " + e);
//    }
  }
  else
  {
   log->error("unable to create class " + strClass);
  }
 }
 else
 {
  log->error("No typeId found for " + strClass);
 }
#endif
}

/**
* Add descriptive details about a specific message box, so that if it needs
* to be reset in the preferences, then it is easily identifiable.
* displayed to the user in the preferences GUI.
* @param strClass String value of the calling class/group
* @param item String value of the specific item this is used for.
* @param description A meaningful description that can be used in a label to describe the item
* @param msgOption Description of each option valid option.
* @param msgNumber The references number against which the Description is refering too.
* @param defaultOption The default option for the given item.
*/
/*public*/ void DefaultUserMessagePreferences::messageItemDetails(QString strClass, QString item, QString description, QStringList msgOption, QList<int> msgNumber, int defaultOption)
{
 QMap<int, QString> options =  QMap<int, QString>();//msgOption.length());
 for (int i = 0; i<msgOption.length(); i++)
 {
  options.insert(msgNumber[i], msgOption[i]);
 }
 messageItemDetails(strClass, description, item, options, defaultOption);
}

/**
* Add descriptive details about a specific message box, so that if it needs
* to be reset in the preferences, then it is easily identifiable.
* displayed to the user in the preferences GUI.
* @param strClass String value of the calling class/group
* @param item String value of the specific item this is used for.
* @param description A meaningful description that can be used in a label to describe the item
* @param options A map of the integer value of the option against a meaningful description.
* @param defaultOption The default option for the given item.
*/
/*public*/ void DefaultUserMessagePreferences::messageItemDetails(QString strClass, QString item, QString description, QMap<int, QString> options, int defaultOption)
{
 if (!classPreferenceList.contains(strClass))
 {
  classPreferenceList.insert(strClass, new ClassPreferences());
 }
 QList<MultipleChoice*>* a = classPreferenceList.value(strClass)->getMultipleChoiceList();
 for (int i = 0; i<a->size(); i++)
 {
  if (a->value(i)->getItem()==(item))
  {
   a->value(i)->setMessageItems(description, options, defaultOption);
   return;
  }
 }
 a->append(new MultipleChoice(description, item, options, defaultOption));
}

/**
* Returns a map of the value against description of the different items in a
* given class.  This information can then be used to build a Combo box.
* @param strClass Class or group of the given item
* @param item the item which we wish to return the details about.
*/
/*public*/ QMap<int, QString> DefaultUserMessagePreferences::getChoiceOptions(QString strClass, QString item)
{
 if (classPreferenceList.contains(strClass))
 {
  QList<MultipleChoice*>* a = classPreferenceList.value(strClass)->getMultipleChoiceList();
  for (int i = 0; i<a->size(); i++)
  {
   if (a->value(i)->getItem()==(item))
    return a->value(i)->getOptions();
  }
 }
 return  QMap<int, QString>();
}

/**
* Returns the number of Mulitple Choice items registered with a given class.
*/
/*public*/ int DefaultUserMessagePreferences::getMultipleChoiceSize(QString strClass)
{
 if (classPreferenceList.contains(strClass))
 {
  return classPreferenceList.value(strClass)->getMultipleChoiceListSize();
 }
 return 0;
}

/**
* Returns a list of all the multiple choice items registered with a given class.
*/
/*public*/ QStringList DefaultUserMessagePreferences::getMultipleChoiceList(QString strClass)
{
 if (classPreferenceList.contains(strClass))
 {
  QList<MultipleChoice*>* a = classPreferenceList.value(strClass)->getMultipleChoiceList();
  QStringList list =  QStringList();
  for (int i = 0; i<a->size(); i++)
  {
   list.append(a->value(i)->getItem());
  }
  return list;
 }
 return  QStringList();
}

/**
* Returns the nth item name in a given class
*/
/*public*/ QString DefaultUserMessagePreferences::getChoiceName(QString strClass, int n)
{
 if (classPreferenceList.contains(strClass))
 {
  return classPreferenceList.value(strClass)->getChoiceName(n);
 }
 return "";
}

/**
* Returns the a meaningful description of a given item in a given class or group.
*/
/*public*/ QString DefaultUserMessagePreferences::getChoiceDescription(QString strClass, QString item)
{
 if (classPreferenceList.contains(strClass))
 {
  QList<MultipleChoice*>* a = classPreferenceList.value(strClass)->getMultipleChoiceList();
  for (int i = 0; i<a->size(); i++)
  {
   if (a->value(i)->getItem()==(item))
    return a->value(i)->getOptionDescription();
  }
 }
 return "";
}

/**
* Returns the current value of a given item in a given class
*/
/*public*/ int DefaultUserMessagePreferences::getMultipleChoiceOption (QString strClass, QString item)
{
 if (classPreferenceList.contains(strClass))
 {
  QList<MultipleChoice*>* a = classPreferenceList.value(strClass)->getMultipleChoiceList();
  for (int i = 0; i<a->size(); i++)
  {
   if (a->value(i)->getItem()==(item))
    return a->value(i)->getValue();
  }
 }
 return 0x00;
}

/**
* Returns the default value of a given item in a given class
*/
/*public*/ int DefaultUserMessagePreferences::getMultipleChoiceDefaultOption (QString strClass, QString choice)
{
 if (classPreferenceList.contains(strClass))
 {
  QList<MultipleChoice*>* a = classPreferenceList.value(strClass)->getMultipleChoiceList();
  for (int i = 0; i<a->size(); i++)
  {
   if (a->value(i)->getItem()==(choice))
                return a->value(i)->getDefaultValue();
  }
 }
 return 0x00;
}

/**
* Sets the value of a given item in a given class, by its string description
*/
/*public*/ void DefaultUserMessagePreferences::setMultipleChoiceOption (QString strClass, QString choice, QString value)
{
 if (!classPreferenceList.contains(strClass))
 {
  return;
 }  QList<MultipleChoice*>* a = classPreferenceList.value(strClass)->getMultipleChoiceList();
 for (int i = 0; i<a->size(); i++)
 {
  if (a->value(i)->getItem()==(choice))
  {
   a->value(i)->setValue(value);
  }
 }
}

/**
* Sets the value of a given item in a given class, by its integer value
*/
/*public*/ void DefaultUserMessagePreferences::setMultipleChoiceOption (QString strClass, QString choice, int value)
{
 if (!classPreferenceList.contains(strClass))
 {
  classPreferenceList.insert(strClass, new ClassPreferences());
 }
 QList<MultipleChoice*>* a = classPreferenceList.value(strClass)->getMultipleChoiceList();
 bool set = false;
 for (int i = 0; i<a->size(); i++)
 {
  if (a->value(i)->getItem()==(choice))
  {
   a->value(i)->setValue(value);
   set = true;
  }
 }
 if(!set)
 {
  a->append(new MultipleChoice(choice, value));
  setClassDescription(strClass);
 }
 displayRememberMsg();
 setChangeMade(true);
}

/*public*/ void DefaultUserMessagePreferences::setTableColumnPreferences(QString table, QString column, int order, int width, int sort, bool hidden)
{
 if(!tableColumnPrefs.contains(table))
 {
  tableColumnPrefs.insert(table,  QHash<QString, TableColumnPreferences*>());
 }
 QHash<QString, TableColumnPreferences*> columnPrefs = tableColumnPrefs.value(table);
 columnPrefs.insert(column,  new TableColumnPreferences(order, width, sort, hidden));
}

/*public*/ int DefaultUserMessagePreferences::getTableColumnOrder(QString table, QString column)
{
 if(tableColumnPrefs.contains(table))
 {
  QHash<QString, TableColumnPreferences*> columnPrefs = tableColumnPrefs.value(table);
  if(columnPrefs.contains(column))
  {
   return columnPrefs.value(column)->getOrder();
  }
 }
 return -1;
}

/*public*/ int DefaultUserMessagePreferences::getTableColumnWidth(QString table, QString column)
{
 if(tableColumnPrefs.contains(table))
 {
  QHash<QString, TableColumnPreferences*> columnPrefs = tableColumnPrefs.value(table);
  if(columnPrefs.contains(column))
  {
   return columnPrefs.value(column)->getWidth();
  }
 }
 return -1;
}

/*public*/ int DefaultUserMessagePreferences::getTableColumnSort(QString table, QString column)
{
 if(tableColumnPrefs.contains(table))
 {
  QHash<QString, TableColumnPreferences*> columnPrefs = tableColumnPrefs.value(table);
  if(columnPrefs.contains(column))
  {
   return columnPrefs.value(column)->getSort();
  }
 }
 return 0;
}

/*public*/ bool DefaultUserMessagePreferences::getTableColumnHidden(QString table, QString column)
{
 if(tableColumnPrefs.contains(table))
 {
  QHash<QString, TableColumnPreferences*> columnPrefs = tableColumnPrefs.value(table);
  if(columnPrefs.contains(column))
  {
   return columnPrefs.value(column)->getHidden();
  }
 }
 return false;
}

/*public*/ QString DefaultUserMessagePreferences::getTableColumnAtNum(QString table, int i)
{
 if(tableColumnPrefs.contains(table))
 {
  QHash<QString, TableColumnPreferences*> columnPrefs = tableColumnPrefs.value(table);
//  foreach(Map.Entry<QString, TableColumnPreferences*> e, columnPrefs.values()){
//            Map.Entry<String, TableColumnPreferences> entry = e;
//   if((entry->getValue()).getOrder()==i){
//                return entry.getKey();
//            }
//        }
  QHashIterator<QString, TableColumnPreferences*> it(columnPrefs);
  while(it.hasNext())
  {
   it.next();
   if(it.value()->getOrder() == i)
       return it.key();
  }
 }
 return "";
}

/*public*/ QStringList DefaultUserMessagePreferences::getTablesList()
{
 return  QStringList(tableColumnPrefs.keys());
}

/*public*/ QStringList DefaultUserMessagePreferences::getTablesColumnList(QString table)
{
 if(tableColumnPrefs.contains(table))
 {
  QHash<QString, TableColumnPreferences*> columnPrefs = tableColumnPrefs.value(table);
  return  QStringList(columnPrefs.keys());
 }
 return  QStringList();
}

/*public*/ QString DefaultUserMessagePreferences::getClassDescription()
{ return "Preference Manager"; }

/*protected*/ QString DefaultUserMessagePreferences::getClassName() { return "jmri.managers.DefaultUserMessagePreferences"; }

/**
* returns the combined size of both types of items registered.
*/
/*public*/ int DefaultUserMessagePreferences::getPreferencesSize(QString strClass)
{
 if(classPreferenceList.contains(strClass))
 {
  return classPreferenceList.value(strClass)->getPreferencesSize();
 }
 return 0;
}

/*public*/ void DefaultUserMessagePreferences::readUserPreferences()
{
 QSettings settings("ACK Software", "LocoNetMonitor");
 QStringList groups = settings.childGroups();
 settings.beginGroup("Main");
 //if(System.getProperty("configFilename")==NULL)
 QString fileName = settings.value("configFileName").toString();
 if(fileName == "")
 {
  log->warn("No Configuration file set, unable to save or load user preferences");
  return;
 }
 settings.endGroup();
 //QFileInfo* configFileName = new QFileInfo(System.getProperty("configFilename"));
 QFileInfo* configFileName = new QFileInfo(fileName);
 QString userprefsfilename;
 if (!configFileName->isAbsolute())
 {
  // must be relative, but we want it to
  // be relative to the preferences directory
  userprefsfilename =/* "UserPrefs"+*/settings.value("configFilename").toString();
  file = new QFile(FileUtil::getUserFilesPath()+userprefsfilename);
 }
 else
 {
  userprefsfilename="UserPrefs"+configFileName->fileName();
  //file = new QFile(fileName/*->path()+QDir::separator()+userprefsfilename*/);
  file = new QFile(configFileName->absolutePath() + QDir::separator()+ userprefsfilename);
 }

 if (file->exists())
 {
  log->debug("start load user pref file: " + file->fileName());
  try
  {
   if(InstanceManager::configureManagerInstance() == NULL)
    InstanceManager::setConfigureManager((ConfigureManager*)new ConfigXmlManager());

   ((ConfigXmlManager*)InstanceManager::configureManagerInstance())->load(new File(file->fileName()), true);
  }
  catch (JmriException e)
  {
   log->error("Unhandled problem loading configuration: "+e.getMessage());
  }
  catch (NullPointerException e)
  {
   log->error("NPE when trying to load user pref " + file->fileName());
  }
 }
 else
 {
  log->info("No saved user preferences file " + file->fileName());
 }
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultUserMessagePreferences.class.getName());
//}
ShutDownTask* DefaultUserMessagePreferences::getShutDownTask() { return userPreferencesShutDownTask;}
