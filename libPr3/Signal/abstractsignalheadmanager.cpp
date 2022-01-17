#include "abstractsignalheadmanager.h"
#include "signalhead.h"
#include "abstractsignalhead.h"
#include "instancemanager.h"
#include "turnoutmanager.h"

AbstractSignalHeadManager::AbstractSignalHeadManager(InternalSystemConnectionMemo* memo, QObject *parent) :
    AbstractManager(memo, parent)
{
 setObjectName("AbstractSignalHeadManager");
 registerSelf();
 setProperty("JavaClassName", "jmri.managers.AbstractSignalHeadManager");
 // TODO: InstanceManager::turnoutManagerInstance()->addVetoableChangeListener(this);
}
/**
 * Abstract partial implementation of a SignalHeadManager.
 * <P>
 * Not truly an abstract class, this might have been better named
 * DefaultSignalHeadManager.  But we've got it here for the eventual
 * need to provide system-specific implementations.
 * <P>
 * Note that this does not enforce any particular system naming convention
 * at the present time.  They're just names...
 *
 * @author      Bob Jacobsen Copyright (C) 2003
 * @version	$Revision: 18102 $
 */
///*public*/ class AbstractSignalHeadManager extends AbstractManager
//    implements SignalHeadManager, java.beans.PropertyChangeListener {

///*public*/ AbstractSignalHeadManager() {
//    //super();
//}

/*final*/ void AbstractSignalHeadManager::init(){
    ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->addVetoableChangeListener(this);
}

/*public*/ int AbstractSignalHeadManager::getXMLOrder() const{
    return Manager::SIGNALHEADS;
}

/*public*/ QChar AbstractSignalHeadManager::typeLetter() { return 'H'; }

/*public*/ SignalHead* AbstractSignalHeadManager::getSignalHead(QString name)
{
 if (name==NULL || name.trimmed().length()==0)
 {
  return NULL;
 }
 SignalHead* t = (SignalHead*)AbstractSignalHeadManager::getByUserName(name);
 if (t!=NULL)
  return t;

 return (SignalHead*)AbstractSignalHeadManager::getBySystemName(name);
}

/** {@inheritDoc} */
//@Override
//@Nonnull
/*public*/ QString AbstractSignalHeadManager::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "SignalHeads" : "SignalHead");
}
#if 0
/*public*/ SignalHead* AbstractSignalHeadManager::getBySystemName(QString name) const
{
 return (SignalHead*)_tsys->value(name);
}

/*public*/ SignalHead* AbstractSignalHeadManager::getByUserName(QString key) const
{
 return (SignalHead*)_tuser->value(key);
}

void AbstractSignalHeadManager::Register(NamedBean *s)
{
 AbstractManager::Register(s);
// emit newSignalHeadCreated((AbstractSignalHead*)s);
// emit propertyChange(new PropertyChangeEvent((QObject*)this, "length", QVariant(), QVariant(_tsys->count())));
}

QCompleter* AbstractSignalHeadManager::getCompleter(QString text, bool bIncludeUserNames)
{
 if(text.length()>2)
 {
  QStringList nameList = getSystemNameList();
  QStringList completerList;
  foreach(QString systemName, nameList)
  {
   SignalHead* b = (SignalHead*)getBySystemName(systemName);
   if(systemName.startsWith(text))
    completerList.append(b->getUserName());
   else if(bIncludeUserNames)
   {
    if(b->getUserName().startsWith(text))
     completerList.append(b->getUserName());
   }
  }
  if(completerList.size() > 0)
  {
   QCompleter* completer = new QCompleter(completerList, this);
    return completer;
  }
 }
 return NULL;
}
#endif
