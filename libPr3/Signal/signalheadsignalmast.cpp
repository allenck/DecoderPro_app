#include "signalheadsignalmast.h"
#include "instancemanager.h"
#include "signalmast.h"
#include "signalmastmanager.h"
#include "defaultsignalmastmanager.h"
#include "abstractsignalheadmanager.h"
#include "signalheadsignalmast.h"
#include "abstractsignalmast.h"
#include "defaultsignalappearancemap.h"
#include "signalhead.h"
#include "defaultsignalhead.h"
#include "defaultsignalsystem.h"
#include "signalheadmanager.h"

//SignalHeadSignalMast::SignalHeadSignalMast(QObject *parent) :
//    AbstractSignalMast(parent)
//{
//}
/**
 * SignalMast implemented via one SignalHead object.
 * <p>
 * System name specifies the creation information:
<pre>
IF:basic:one-searchlight:(IH1)(IH2)
</pre>
 * The name is a colon-separated series of terms:
 * <ul>
 * <li>IF$shsm - defines signal masts of this type
 * <li>basic - name of the signaling system
 * <li>one-searchlight - name of the particular aspect map
 * <li>(IH1)(IH2) - colon-separated list of names for SignalHeads
 * </ul>
 * There was an older form where the names where colon separated:  IF:basic:one-searchlight:IH1:IH2
 * This was deprecated because colons appear in e.g. SE8c system names.
 * <ul>
 * <li>IF$shsm - defines signal masts of this type
 * <li>basic - name of the signaling system
 * <li>one-searchlight - name of the particular aspect map
 * <li>IH1:IH2 - colon-separated list of names for SignalHeads
 * </ul>
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version     $Revision: 22226 $
 */
///*public*/ class SignalHeadSignalMast extends AbstractSignalMast {

/*public*/ SignalHeadSignalMast::SignalHeadSignalMast(QString systemName, QString userName, QObject *parent) : AbstractSignalMast(systemName, userName, parent)
{
    //super(systemName, userName);
    log =new Logger("SignalHeadSignalMast");
    configureFromName(systemName);
}

///*public*/ SignalHeadSignalMast(QString systemName) {
//    super(systemName);
//    configureFromName(systemName);
//}

void SignalHeadSignalMast::configureFromName(QString systemName) {
    // split out the basic information
    QStringList parts = systemName.split(":");
    if (parts.length() < 3) {
        log->error("SignalMast system name needs at least three parts: "+systemName);
        throw new IllegalArgumentException("System name needs at least three parts: "+systemName);
    }
    if (parts.at(0)!=("IF$shsm")) {
        log->warn("SignalMast system name should start with IF: "+systemName);
    }
    QString prefix = parts[0];
    QString system = parts[1];
    QString mast = parts[2];

    // if "mast" contains (, it's new style
    if (mast.indexOf('(') == -1) {
        // old style
        configureSignalSystemDefinition(system);
        configureAspectTable(system, mast);
        configureHeads(parts, 3);
    }
    else
    {
        // new style
        mast = mast.mid(0, mast.indexOf("("));
        QString interim = systemName.mid(prefix.length()+1+system.length()+1);
        QString parenstring = interim.mid(interim.indexOf("("), interim.length());
        QList<QString> parens = splitParens(parenstring);
        configureSignalSystemDefinition(system);
        configureAspectTable(system, mast);
        QVector<QString> heads =  QVector<QString>(parens.size());
        int i=0;
        foreach (QString p , parens)
        {
            heads.replace(i, p.mid(1, p.length()-2)); // was 1 ACK
            i++;
        }
        configureHeads(heads.toList(), 0);
    }
}

void SignalHeadSignalMast::configureHeads(QStringList parts, int start)
{
 heads = new QList<NamedBeanHandle<SignalHead*>* >();
 for (int i = start; i < parts.length(); i++)
 {
  QString name = parts.at(i);
  NamedBeanHandle<SignalHead*>* s
          = new NamedBeanHandle<SignalHead*>(parts.at(i),
              static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name));
  heads->append(s);
 }
}

//@Override
/*public*/ void SignalHeadSignalMast::setAspect(QString aspect) {
    // check it's a choice
    if ( !map->checkAspect(aspect)) {
        // not a valid aspect
        log->warn("attempting to set invalid aspect: "+aspect+" on mast: "+getDisplayName());
        throw new IllegalArgumentException("attempting to set invalid aspect: "+aspect+" on mast: "+getDisplayName());
    } else if (disabledAspects->contains(aspect)){
        log->warn("attempting to set an aspect that has been disabled: "+aspect+" on mast: "+getDisplayName());
        throw new IllegalArgumentException("attempting to set an aspect that has been disabled: "+aspect+" on mast: "+getDisplayName());
    }

    // set the outputs
    if (log->isDebugEnabled()) log->debug("setAspect \""+aspect+"\", numHeads= "+(QString::number(heads->size())));
    setAppearances(aspect);
    // do standard processing
    AbstractSignalMast::setAspect(aspect);
}

//@Override
/*public*/ void SignalHeadSignalMast::setHeld(bool state) {
    // set all Heads to state
    foreach (NamedBeanHandle<SignalHead*>* h , *heads) {
        try {
            ((DefaultSignalHead*)h->getBean())->setHeld(state);
        } catch (NullPointerException ex){
            log->error("NPE caused when trying to set Held due to missing signal head in mast " + getDisplayName());
        }
    }
    AbstractSignalMast::setHeld(state);
}

//@Override
/*public*/ void SignalHeadSignalMast::setLit(bool state) {
    // set all Heads to state
    foreach (NamedBeanHandle<SignalHead*>* h , *heads) {
        try {
            ((DefaultSignalHead*)h->getBean())->setLit(state);
        }  catch (NullPointerException ex){
            log->error("NPE caused when trying to set Dark due to missing signal head in mast " + getDisplayName());
        }
    }
    AbstractSignalMast::setLit(state);
}

/*public*/ QList<NamedBeanHandle<SignalHead*>* >* SignalHeadSignalMast::getHeadsUsed(){
    return heads;
}

//taken out of the defaultsignalappearancemap
/*public*/ void SignalHeadSignalMast::setAppearances(QString aspect) {
    if (map==NULL){
        log->error("No appearance map defined, unable to set appearance " + getDisplayName());
        return;
    }
#if 0 // TODO: SignalSystem not defined, causes crash.
    if (map->getSignalSystem() !=NULL && ((DefaultSignalSystem*)map->getSignalSystem())->checkAspect(aspect) && map->getAspectSettings(aspect)!=NULL)
        log->warn("Attempt to set "+getSystemName()+" to undefined aspect: "+aspect);
    else if ((map->getAspectSettings(aspect)!=NULL) && (heads->size() > map->getAspectSettings(aspect)->count()))
        log->warn("setAppearance to \""+aspect+"\" finds "+QString::number(heads->size())+" heads but only "+map->getAspectSettings(aspect)->count()+" settings");
#endif
    int delay = 0;
    try {
        if(map->getProperty(aspect, "delay")!=NULL){
            delay = map->getProperty(aspect, "delay").toInt();
        }
    } catch (Exception e){
        log->debug("No delay set");
        //can be considered normal if does not exists or is invalid
    }
    QHash<SignalHead*, int>* delayedSet = new QHash<SignalHead*, int>(/*heads->size()*/);
    for (int i = 0; i < heads->size(); i++)
    {
        // some extensive checking
        bool error = false;
        if (heads->at(i) == NULL){
            log->error("Null head "+QString::number(i)+" in setAppearances");
            error = true;
        }
        if (heads->at(i)->getBean() == NULL){
            log->error("Could not get bean for head "+QString::number(i)+" in setAppearances");
            error = true;
        }
        if (map->getAspectSettings(aspect) == NULL){
            log->error("Couldn't get table array for aspect \""+aspect+"\" in setAppearances");
            error = true;
        }

        if(!error){
            SignalHead* head = heads->at(i)->getBean();
            int toSet = map->getAspectSettings(aspect)->at(i);
            if(delay == 0){
                ((DefaultSignalHead*)head)->setAppearance(toSet);
                if (log->isDebugEnabled()) log->debug("Setting "+head->getSystemName()+" to "+
                                ((DefaultSignalHead*)head)->getAppearanceName(toSet));
            } else {
                delayedSet->insert(head, toSet);
            }
        }
        else
            log->error("head appearance not set due to an error");
    }
    if(delay!=0){
        //If a delay is required we will fire this off into a seperate thread and let it get on with it.
        /*final*/ QHash<SignalHead*, int>* thrDelayedSet = delayedSet;
        /*final*/ int thrDelay = delay;
//        Runnable r = new Runnable() {
//            /*public*/ void run() {
//                setDelayedAppearances(thrDelayedSet, thrDelay);
//            }
//        };
        Runnable1* r = new Runnable1(thrDelayedSet, thrDelay, this);
        QThread* thr = new QThread(r);
        thr->setObjectName(getDisplayName() + " delayed set appearance");
        //try{
            thr->start();
//        } catch (IllegalThreadStateException ex){
//            log->error(ex.toQString());
//        }
    }
    return;
}

/*private*/ void SignalHeadSignalMast::setDelayedAppearances(/*final*/ QHash<SignalHead*, int>* delaySet, /*final*/ int delay){
    foreach(SignalHead* head, delaySet->keys())
    {
        /*final*/ SignalHead* thrHead = head;
//        Runnable r = new Runnable() {
//            /*public*/ void run() {
//                try {
//                    thrHead.setAppearance(delaySet.get(thrHead));
//                    if (log->isDebugEnabled()) log->debug("Setting "+thrHead->getSystemName()+" to "+
//                            thrHead.getAppearanceName(delaySet.get(thrHead)));
//                    Thread.sleep(delay);
//                } catch (InterruptedException ex) {
//                    Thread.currentThread().interrupt();
//                }
//            }
//        };
        Runnable2* r = new Runnable2(delaySet, thrHead,delay, this);
        QThread* thr = new QThread(r);
        thr->setObjectName(getDisplayName());
//        try{
            thr->start();
            //thr->join();
//        } catch (IllegalThreadStateException ex){
//            log->error(ex.toQString());
//        } catch (InterruptedException ex) {
//            log->error(ex.toQString());
//        }
    }
}

/*public*/ /*static*/ QList<SignalHead*>* SignalHeadSignalMast::getSignalHeadsUsed()
{
 QList<SignalHead*>* headsUsed = new QList<SignalHead*>();
 foreach(QString val , (static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSystemNameList()))
 {
  SignalMast* mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(val);
  if(qobject_cast<SignalHeadSignalMast*>(mast)!=NULL)
  {
   QList<NamedBeanHandle<SignalHead*>*>* masthead = ((SignalHeadSignalMast*)mast)->getHeadsUsed();
   foreach(NamedBeanHandle<SignalHead*>* bean , *masthead)
   {
    headsUsed->append(bean->getBean());
   }
  }
 }
 return headsUsed;
}

/*public*/ /*static*/ QString SignalHeadSignalMast::isHeadUsed(SignalHead* head){
    foreach(QString val,  static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSystemNameList())
    {
        SignalMast* mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(val);
        if( qobject_cast<SignalHeadSignalMast*>(mast)!= NULL)
        {
            QList<NamedBeanHandle<SignalHead*>* >* masthead = ((SignalHeadSignalMast*)mast)->getHeadsUsed();
            foreach(NamedBeanHandle<SignalHead*>* bean , *masthead){
                if((bean->getBean())==head)
                    return ((SignalHeadSignalMast*)mast)->getDisplayName();
            }
        }
    }
    return NULL;
}
QStringList SignalHeadSignalMast::splitParens(QString in) {
        QStringList result = QStringList();
        if (in==("")) return result;
        int level = 0;
        QString temp = "";
        for (int i = 0; i < in.length(); i++) {
            QChar c = in.at(i);
            if (c == '(') {
                level++;
            } else if (c == '\\') {
                temp+=c;
                i++;
                c = in.at(i);
            } else if (c ==')') {
                level--;
            }
            temp+=c;
            if (level == 0) {
                result.append(temp);
                temp = "";
            }
        }
        return result;
    }
/*public*/ QString SignalHeadSignalMast::className() {return "jmri.implementation.SignalHeadSignalMast";}

//static final protected org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SignalHeadSignalMast.class.getName());
//}
