#include "defaultsignalmastmanager.h"
#include "signalmast.h"
#include "signalheadsignalmast.h"
#include "signalmastrepeater.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "vetoablechangesupport.h"

DefaultSignalMastManager::DefaultSignalMastManager(QObject *parent) :
    SignalMastManager(parent)
{
 setObjectName("DefaultSignalMastManager");
 setProperty("JavaClassName", "jmri.managers.DefaultSignalMastManager");

 log = new Logger("DefaultSignalMastManager");
 repeaterList = new QList<SignalMastRepeater*>();
 registerSelf();
 //jmri.InstanceManager.getDefault(jmri.SignalHeadManager.class).addVetoableChangeListener(this);
 connect(static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->vcs, SIGNAL(vetoablePropertyChange(PropertyChangeEvent*)), this, SLOT(vetoableChange(PropertyChangeEvent*)));
 //jmri.InstanceManager.turnoutManagerInstance().addVetoableChangeListener(this);
 connect(InstanceManager::turnoutManagerInstance()->vcs, SIGNAL(vetoablePropertyChange(PropertyChangeEvent*)), this, SLOT(vetoableChange(PropertyChangeEvent*)));

}
/**
 * Default implementation of a SignalMastManager.
 * <P>
 * Note that this does not enforce any particular system naming convention
 * at the present time.  They're just names...
 *
 * @author  Bob Jacobsen Copyright (C) 2009
 * @version	$Revision: 22000 $
 */
///*public*/ class DefaultSignalMastManager extends AbstractManager
//    implements SignalMastManager, java.beans.PropertyChangeListener {

///*public*/ DefaultSignalMastManager() {
//    super();
//}

/*public*/ int DefaultSignalMastManager::getXMLOrder() const
{
 return Manager::SIGNALMASTS;
}

/*public*/ QString DefaultSignalMastManager::getSystemPrefix() const { return "I"; }

/*public*/ char DefaultSignalMastManager::typeLetter() const{ return 'F'; }

/*public*/ SignalMast* DefaultSignalMastManager::getSignalMast(QString name)
{
 if (name==NULL || name.length()==0) { return NULL; }
 SignalMast* t = getByUserName(name);
 if (t!=NULL) return t;

 return getBySystemName(name);
}

/*public*/ SignalMast* DefaultSignalMastManager::provideSignalMast(QString prefix, // nominally IF$shsm
                                    QString signalSystem,
                                    QString /*mastName*/,
                                    QStringList heads)
{
 QString name = QString(prefix);
 name.append(":");
 name.append(signalSystem);
 name.append(":");
 foreach(QString s , heads)
 {
  name.append("(");
  name.append(parenQuote(s));
  name.append(")");
 }
 return provideSignalMast(name);
}

/*public*/ SignalMast* DefaultSignalMastManager::provideSignalMast(QString name)
{
 SignalMast* m = getSignalMast(name);
 if (m == NULL)
 {
  m = (SignalMast*)new SignalHeadSignalMast(name);

  Register(m);
  emit newSignalMastCreated((AbstractSignalMast*)m);
 }
 return m;
}

/*public*/ SignalMast* DefaultSignalMastManager::getBySystemName(QString key) const {
    return (SignalMast*)_tsys->value(key);
}

/*public*/ SignalMast* DefaultSignalMastManager::getByUserName(QString key) const {
    return (SignalMast*)_tuser->value(key);
}

#if 1
/*public*/ void DefaultSignalMastManager::addRepeater(SignalMastRepeater* rp) throw (JmriException){
    foreach(SignalMastRepeater* rpeat, *repeaterList)
    {
        if(rpeat->getMasterMast()==rp->getMasterMast() &&
            rpeat->getSlaveMast() == rp->getSlaveMast()){
                log->error("Signal repeater already Exists");
                throw new JmriException("Signal mast Repeater already exists");
        }
        else if(rpeat->getMasterMast()==rp->getSlaveMast() &&
            rpeat->getSlaveMast() == rp->getMasterMast()){
                log->error("Signal repeater already Exists");
                throw new JmriException("Signal mast Repeater already exists");
            }
    }
    repeaterList->append(rp);
    firePropertyChange("repeaterlength", QVariant(), QVariant());
}

/*public*/ void DefaultSignalMastManager::removeRepeater(SignalMastRepeater* rp){
    rp->dispose();
    repeaterList->removeAt(repeaterList->indexOf(rp));
    firePropertyChange("repeaterlength", QVariant(), QVariant());
}

/*public*/ QList<SignalMastRepeater*>* DefaultSignalMastManager::getRepeaterList(){
    return repeaterList;
}

/*public*/ void DefaultSignalMastManager::initialiseRepeaters(){
    foreach(SignalMastRepeater* smr, *repeaterList){
        smr->initialise();
    }
}
#endif
/**
 * If there's an unmatched ), quote it with \,
 * and quote \ with \ too.
 */
/*private*/ QString DefaultSignalMastManager::parenQuote(QString in)
{
 if (in==("")) return "";
 // StringBuilder result = new StringBuilder();
 QString result;
 int level = 0;
 for (int i = 0; i < in.length(); i++)
 {
  QChar c = in.at(i);
  if (c == '(') level++;
  else if (c == '\\') result.append('\\');
  else if (c ==')')
  {
   level--;
   if (level < 0)
   {
    level = 0;
    result.append('\\');
   }
  }
  result.append(c);
 }
 return result;
}

//@Override
/*public*/ SignalMast* DefaultSignalMastManager::provide(QString name) throw (IllegalArgumentException) {
    return provideSignalMast(name);
}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultSignalMastManager.class.getName());
//}

/* @(#)DefaultSignalMastManager.java */
