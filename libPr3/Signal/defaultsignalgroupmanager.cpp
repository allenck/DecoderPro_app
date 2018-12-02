#include "defaultsignalgroupmanager.h"
#include "defaultsignalgroup.h"
#include "signalgroup.h"
#include <QFileInfo>
#include <QDir>

DefaultSignalGroupManager::DefaultSignalGroupManager(QObject *parent) :
    SignalGroupManager()
{
 setObjectName("DefaultSignalGroupManager");
 setProperty("JavaClassName", "jmri.managers.DefaultSignalGroupManager");

 log = new Logger("DefaultSignalGroupManager");
 registerSelf();
}
/**
 * Default implementation of a SignalGroupManager.
 * <P>
 * This loads automatically the first time used.
 * <p>
 *
 *
 * @author  Bob Jacobsen Copyright (C) 2009
 * @version	$Revision: 18102 $
 */
///*public*/ class DefaultSignalGroupManager extends AbstractManager
//    implements SignalGroupManager, java.beans.PropertyChangeListener {

///*public*/ DefaultSignalGroupManager() {
//    super();

//    // load when created, which will generally
//    // be the first time referenced
//    //load();
//}

/*public*/ int DefaultSignalGroupManager::getXMLOrder(){
    return Manager::SIGNALGROUPS;
}

/*public*/ QString DefaultSignalGroupManager::getSystemPrefix() { return "I"; }
/*public*/ char DefaultSignalGroupManager::typeLetter() { return 'F'; }

/*public*/ SignalGroup* DefaultSignalGroupManager::getSignalGroup(QString name) {
    SignalGroup* t = getByUserName(name);
    if (t!=NULL) return t;

    return getBySystemName(name);
}

/*public*/ SignalGroup* DefaultSignalGroupManager::getBySystemName(QString key) {
    return (SignalGroup*)_tsys->value(key);
}

/*public*/ SignalGroup* DefaultSignalGroupManager::getByUserName(QString key) {
    return (SignalGroup*)_tuser->value(key);
}

/*public*/ SignalGroup* DefaultSignalGroupManager::newSignalGroup(QString sys){
    SignalGroup* g;
    g = (SignalGroup*)new DefaultSignalGroup(sys);
    Register(g);
    return g;

}

/*public*/ SignalGroup* DefaultSignalGroupManager::provideSignalGroup(QString systemName, QString userName) {
    SignalGroup* r;
    r = getByUserName(systemName);
    if (r!=NULL) return r;
    r = getBySystemName(systemName);
    if (r!=NULL) return r;
    // Route does not exist, create a new group
    r = (SignalGroup*)new DefaultSignalGroup(systemName,userName);
    // save in the maps
    Register(r);
    return r;
}

QStringList DefaultSignalGroupManager::getListOfNames()
{
 QStringList retval =  QStringList();
 // first locate the signal system directory
 // and get names of systems
 QFileInfo* signalDir = new QFileInfo("xml"+QString(QDir::separator())+"signals");
 QFileInfoList files = signalDir->dir().entryInfoList();
 for (int i=0; i<files.length(); i++)
 {
  if (files.at(i).isDir())
  {
   // check that there's an aspects.xml file
   QFileInfo aspects = QFileInfo(files.at(i).path()+QString(QDir::separator())+"aspects.xml");
   if (aspects.exists())
   {
    log->debug("found system: "+files.at(i).absoluteFilePath());
    retval.append(files.at(i).absoluteFilePath());
   }
  }
 }
 return retval;
}


/*static*/ DefaultSignalGroupManager* DefaultSignalGroupManager::_instance = NULL;

/*static*/ /*public*/ DefaultSignalGroupManager* DefaultSignalGroupManager::instance()
{
 if (_instance == NULL)
 {
  _instance = new DefaultSignalGroupManager();
 }
 return (_instance);
}

/*public*/ void DefaultSignalGroupManager::deleteSignalGroup(SignalGroup* s) {
 deregister(s);
}
