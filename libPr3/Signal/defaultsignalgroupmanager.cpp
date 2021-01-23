#include "defaultsignalgroupmanager.h"
#include "defaultsignalgroup.h"
#include "signalgroup.h"
#include <QFileInfo>
#include <QDir>
#include "instancemanager.h"

DefaultSignalGroupManager::DefaultSignalGroupManager(InternalSystemConnectionMemo* memo, QObject *parent) :
    SignalGroupManager(memo, parent)
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

/*public*/ int DefaultSignalGroupManager::getXMLOrder() const{
    return Manager::SIGNALGROUPS;
}

/*public*/ QString DefaultSignalGroupManager::getSystemPrefix() const { return "I"; }
/*public*/ char DefaultSignalGroupManager::typeLetter() const { return 'F'; }

/*public*/ SignalGroup* DefaultSignalGroupManager::getSignalGroup(QString name) {
    SignalGroup* t = getByUserName(name);
    if (t!=NULL) return t;

    return getBySystemName(name);
}

/*public*/ SignalGroup* DefaultSignalGroupManager::getBySystemName(QString key) const {
    return (SignalGroup*)_tsys->value(key);
}

/*public*/ SignalGroup* DefaultSignalGroupManager::getByUserName(QString key) const{
    return (SignalGroup*)_tuser->value(key);
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

/**
 * {@inheritDoc}
 * @deprecated 4.15.2 use newSignaGroupWithUserName
 */
//@Nonnull
//@Override
//@Deprecated //  4.15.2 use newSignaGroupWithUserName
/*public*/ SignalGroup* DefaultSignalGroupManager::newSignalGroup(QString userName){
 //jmri.util.LoggingUtil.deprecationWarning(log, "newSignalGroup");
 return newSignaGroupWithUserName(userName);
}
/**
 * {@inheritDoc}
 *
 * Keep autostring in line with {@link #provideSignalGroup(String, String)},
 * {@link #getSystemPrefix()} and {@link #typeLetter()}
 */
//@Nonnull
//@Override
/*public*/ SignalGroup* DefaultSignalGroupManager::newSignaGroupWithUserName(/*@Nonnull*/ QString userName) {
    return provideSignalGroup(getAutoSystemName(), userName);
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

/*static*/ /*public*/ DefaultSignalGroupManager* DefaultSignalGroupManager::instance()
{
 return (DefaultSignalGroupManager*)InstanceManager::getDefault("DefaultSignalGroupManager");
}

/*public*/ void DefaultSignalGroupManager::deleteSignalGroup(SignalGroup* s) {
 deregister(s);
}
