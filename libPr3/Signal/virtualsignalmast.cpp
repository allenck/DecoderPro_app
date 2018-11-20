#include "virtualsignalmast.h"
#include "defaultsignalappearancemap.h"

//VirtualSignalMast::VirtualSignalMast(QObject *parent) :
//    AbstractSignalMast(parent)
//{
//}
 int VirtualSignalMast::lastRef = 0;
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
 * @version     $Revision: 19027 $
 */
// /*public*/ class VirtualSignalMast extends AbstractSignalMast {

/*public*/ VirtualSignalMast::VirtualSignalMast(QString systemName, QString userName, QObject *parent) : AbstractSignalMast(systemName, userName,parent)
{
 //super(systemName, userName);
 log = new Logger("VirtualSignalMast");
 configureFromName(systemName);
}

///*public*/ VirtualSignalMast(QString systemName) {
//    super(systemName);
//    configureFromName(systemName);
//}

void VirtualSignalMast::configureFromName(QString systemName)
{
    // split out the basic information
    QStringList parts = systemName.split(":");
    if (parts.length() < 3) {
        log->error("SignalMast system name needs at least three parts: "+systemName);
        throw  IllegalArgumentException("System name needs at least three parts: "+systemName);
    }
    if (parts.at(0)!=("IF$vsm")) {
        log->warn("SignalMast system name should start with IF: "+systemName);
    }

    QString system = parts.at(1);
    QString mast = parts.at(2);
    // new style
    mast = mast.mid(0, mast.indexOf("("));
    setMastType(mast);
    QString tmp = parts.at(2).mid(parts.at(2).indexOf("($")+2, parts.at(2).indexOf(")"));
    try {
        int autoNumber = tmp.toInt();
        if (autoNumber > lastRef) {
            lastRef = autoNumber;
        }
    } catch (NumberFormatException e){
        log->warn("Auto generated SystemName "+ systemName + " is not in the correct format");
    }
    configureSignalSystemDefinition(system);
    configureAspectTable(system, mast);
}

//@Override
/*public*/ void VirtualSignalMast::setAspect(QString aspect) {
    // check it's a choice
    if ( !map->checkAspect(aspect)) {
        // not a valid aspect
        log->warn("attempting to set invalid aspect: "+aspect+" on mast: "+getDisplayName());
        throw  IllegalArgumentException("attempting to set invalid aspect: "+aspect+" on mast: "+getDisplayName());
    }  else if (disabledAspects->contains(aspect)){
        log->warn("attempting to set an aspect that has been disabled: "+aspect+" on mast: "+getDisplayName());
        throw  IllegalArgumentException("attempting to set an aspect that has been disabled: "+aspect+" on mast: "+getDisplayName());
    }
    AbstractSignalMast::setAspect(aspect);
}

/*public*/ /*static*/ int VirtualSignalMast::getLastRef(){ return lastRef; }


//static final protected org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(VirtualSignalMast.class.getName());
//}

///* @(#)VirtualSignalMast.java */
