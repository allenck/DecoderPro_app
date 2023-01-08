#include "appconfigbase.h"
#include "jmrixconfigpane.h"
#include <QMessageBox>
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include "QApplication"
#include <QCheckBox>
#include <QBoxLayout>
#include <QLabel>
#include "apps.h"
#include "managingpreferencespanel.h"
#include "configuremanager.h"
#include "connectionconfigmanager.h"
#include "connectionconfig.h"
#include "joptionpane.h"
#include "shutdownmanager.h"
#include "jmriconfigurationmanager.h"

AppConfigBase::AppConfigBase(QWidget *parent) :
    JmriPanel(parent) //JmriPanel(parent)
{
 preferencesPanels = new QMap<QString, PreferencesPanel*>();
 log = new Logger("AppConfigBase");
}
/**
 * Basic configuration infrastructure, to be used by specific GUI
 * implementations
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2008, 2010
 * @author Matthew Harris copyright (c) 2009
 * @author	Ken Cameron Copyright (C) 2011
 * @version	$Revision: 28168 $
 */
// /*public*/ class AppConfigBase extends JmriPanel {

/**
 *
 */
// /*private*/ static final long serialVersionUID = -341194769406457667L;

// /*protected*/ static final ResourceBundle rb = ResourceBundle.getBundle("apps.AppsConfigBundle");

/**
 * Construct a configuration panel for inclusion in a preferences or
 * configuration dialog with default number of connections.
 */
///*public*/ AppConfigBase() {
//}
#if 0
/*public*/ /*static*/ QString AppConfigBase::getManufacturerName(int index) {
    return JmrixConfigPane::instance(index)->getCurrentManufacturerName();
}

/*public*/ /*static*/ QString AppConfigBase::getConnection(int index) {
    return JmrixConfigPane::instance(index)->getCurrentProtocolName();
}

/*public*/ /*static*/ QString AppConfigBase::getPort(int index) {
    return JmrixConfigPane::instance(index)->getCurrentProtocolInfo();
}

/*public*/ /*static*/ QString AppConfigBase::getConnectionName(int index) {
    return JmrixConfigPane::instance(index)->getConnectionName();
}

/*public*/ /*static*/ bool AppConfigBase::getDisabled(int index) {
    return JmrixConfigPane::instance(index)->getDisabled();
}
#endif
/**
 * Detect duplicate connection types It depends on all connections have the
 * first word be the same if they share the same type. So LocoNet ... is a
 * fine example.
 * <p>
 * This also was broken when the names for systems were updated before JMRI
 * 2.9.4, so it should be revisited.
 *
 * @return true if OK, false if duplicates present.
 */
/*private*/ bool AppConfigBase::checkDups()
{
 QMap<QString, QList<ConnectionConfig*>* > ports = QMap<QString, QList<ConnectionConfig*>* >();
 QVector<ConnectionConfig*> connections = ((ConnectionConfigManager*)InstanceManager::getDefault("ConnectionConfigManager"))->getConnections();
 for (ConnectionConfig* connection : connections)
 {
  if (!connection->getDisabled())
  {
   QString port = connection->getInfo();
   if (port!=(JmrixConfigPane::NONE))
   {
    if (!ports.contains(port)) {
        QList<ConnectionConfig*>* arg1 = new QList<ConnectionConfig*>();
        arg1->append(connection);
        ports.insert(port, arg1);
    } else {
        ports.value(port)->append(connection);
    }
   }
  }
 }
 bool ret = true;
 /* one or more dups or NONE, lets see if it is dups */
 //for (Map.Entry<String, List<JmrixConfigPane>> e : ports.entrySet())
 QList<QList<ConnectionConfig*>*>  entries = ports.values();
#if 1
 foreach(QList<ConnectionConfig*>* e, entries)
 {
  if (e->size() > 1)
  {
   /* dup port found */
   ret = false;
   QString nameB;// = new StringBuilder();
   for (int n = 0; n < e->size(); n++)
   {
    nameB.append(e->at(n)->getManufacturer());
    nameB.append("|");
   }
   QString instanceNames =  QString(nameB);
   instanceNames = instanceNames.mid(0, instanceNames.lastIndexOf("|"));
   instanceNames = instanceNames.replace("[|]", ", ");
   log->error("Duplicate ports found on: " + instanceNames + " for port: " /*+ e->key()*/);
  }
 }
#endif
 return ret;
}

/**
 * Checks to see if user selected a valid serial port
 *
 * @return true if okay
 */
/*private*/ bool AppConfigBase::checkPortNames()
{
 for (ConnectionConfig* connection : ((ConnectionConfigManager*)InstanceManager::getDefault("ConnectionConfigManager"))->getConnections()) {
     QString port = connection->getInfo();
     if (port == (JmrixConfigPane::NONE_SELECTED) || port == (JmrixConfigPane::NO_PORTS_FOUND)) {
         if (JOptionPane::YES_OPTION != JOptionPane::showConfirmDialog(
                 nullptr,
                 tr("%1 is not a valid serial port for system connection %2. Do you want to save anyway?").arg(port).arg(connection->getConnectionName()),
                 tr("Serial port isn't valid, save anyway?"),
                 JOptionPane::YES_NO_OPTION,
                 JOptionPane::ERROR_MESSAGE)) {
             return false;
         }
     }
 }
 return true;
}

//@Override
/*public*/ void AppConfigBase::dispose() {
    preferencesPanels->clear();
}

/*public*/ void AppConfigBase::saveContents()
{
 // remove old prefs that are registered in ConfigManager
 ConfigureManager* cm = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
 if (cm != nullptr)
 {
  cm->removePrefItems();
 }
 // put the new GUI managedPreferences on the persistance list
 //this->getPreferencesPanels()->values().stream().forEach((panel) ->
 foreach(PreferencesPanel* panel, this->getPreferencesPanels()->values())
 {
  Q_UNUSED(panel);
     QObject* obj = panel->ppself();
  this->registerWithConfigureManager(panel);
 }//);
 if (cm != nullptr)
 {
  cm->storePrefs();
 }
}

/*private*/ void AppConfigBase::registerWithConfigureManager(PreferencesPanel* panel)
{
 if (panel->isPersistant())
 {
  ConfigureManager* cm = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
 if (cm != nullptr) {
     cm->registerPref(panel->ppself());
 }
}
 //if (panel instanceof ManagingPreferencesPanel)
 if(qobject_cast<ManagingPreferencesPanel*>(panel->ppself()) != nullptr)
 {
  log->debug(tr("Iterating over managed panels within %1/%2").arg(panel->getPreferencesItemText()).arg( panel->getTabbedPreferencesTitle()));
//     ((ManagingPreferencesPanel*) panel).getPreferencesPanels().stream().forEach((managed) -> {
  foreach (PreferencesPanel* managed, ((ManagingPreferencesPanel*) panel->ppself())->getPreferencesPanels())
  {
//   log->debug(tr("Registering %1 with the ConfigureManager").arg(managed->metaObject()->className()));
   this->registerWithConfigureManager(managed);
  }
 }
}
/**
 * Handle the Save button: Backup the file, write a new one, prompt for what
 * to do next. To do that, the last step is to present a dialog box
 * prompting the user to end the program, if required.
 *
 * @param restartRequired true if JMRI should prompt user to restart
 */
/*public*/ void AppConfigBase::savePressed(bool restartRequired)
{
 // true if port name OK
 if (!checkPortNames())
 {
  return;
 }
 // true if there aren't any duplicates
 if (!checkDups())
 {
//  if (!(JOptionPane.showConfirmDialog(NULL, tr("MessageLongDupsWarning"), tr("MessageShortDupsWarning"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION))
  if (!(JOptionPane::showConfirmDialog(nullptr, tr("You have duplicates in ports or connections. This can cause problems. Do you want to save anyway?"), tr("Duplicates, save anyway?"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION))
  {
   return;
  }
 }
  saveContents();
  /*final*/ UserPreferencesManager* p;
     p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
     p->resetChangeMade();
     if (restartRequired && !((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->isShuttingDown()) {
             QString question =tr("<html><b>You must restart %1.</b><br>Your new settings will not take effect until you restart this application.</html>").arg(QApplication::applicationName());
             QVariantList options = {tr("Restart"), tr("Later")};
             int retVal = JOptionPane::showOptionDialog(this,
                     question,
                     tr("Restart %1").arg(QApplication::applicationName()),
                     JOptionPane::YES_NO_OPTION,
                     JOptionPane::QUESTION_MESSAGE,
                     QIcon(),
                     options,
                     QVariant());
             switch (retVal) {
                 case JOptionPane::YES_OPTION:
                     dispose();
                     Apps::handleRestart();
                     break;
                 case JOptionPane::NO_OPTION:
                     break;
                 default:
                     break;
             }
         }
 // don't restart the program, just close the window
// if (getTopLevelAncestor() != NULL)
// {
//  ((JFrame) getTopLevelAncestor()).setVisible(false);
// }
}

/*public*/ QString AppConfigBase::getClassDescription() {
    return tr("Application");
}
#if 1
/*public*/ void AppConfigBase::setMessagePreferencesDetails()
{
 QMap<int, QString>* options = new QMap<int, QString>(); // 3
 options->insert(0x00, tr("Always Ask"));
 options->insert(0x01, tr("Never Quit"));
 options->insert(0x02, tr("Always Quit"));
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMessageItemDetails(getClassName(),
                                            "quitAfterSave", tr("Quit after saving preferences"), options, 0x00);
}
#endif
/*public*/ QString AppConfigBase::getClassName() {
    return"apps.AppConfigBase"; //.class.getName();
}

/**
 * @return the preferencesPanels
 */
/*public*/ QMap<QString, PreferencesPanel*>* AppConfigBase::getPreferencesPanels()
{
 return preferencesPanels;
}

QString AppConfigBase::getName()
{
 return "apps.AppConfigBase";
}
