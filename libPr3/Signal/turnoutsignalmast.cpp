#include "turnoutsignalmast.h"
#include "defaultsignalappearancemap.h"


//TurnoutSignalMast::TurnoutSignalMast(QObject *parent) :
//    AbstractSignalMast(parent)
//{
//}
int TurnoutSignalMast::lastRef = 0;
/**
 * SignalMast implemented via Turnout objects.
 * <p>
 * A Signalmast that is built up using turnouts to control
 * a specific appearance.
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version     $Revision: 19027 $
 */
// /*public*/ class TurnoutSignalMast extends AbstractSignalMast {

/*public*/ TurnoutSignalMast::TurnoutSignalMast(QString systemName, QString userName, QObject *parent) : AbstractSignalMast(systemName, userName,parent)
{
 //super(systemName, userName);
    turnouts =  QHash<QString, TurnoutAspect*>();
    _resetPreviousStates = false;
    log = new Logger("TurnoutSignalMast");
    configureFromName(systemName);
}

///*public*/ TurnoutSignalMast(QString systemName) {
//    super(systemName);
//    configureFromName(systemName);
//}

void TurnoutSignalMast::configureFromName(QString systemName) {
    // split out the basic information
    QStringList parts = systemName.split(":");
    if (parts.length() < 3) {
        log->error("SignalMast system name needs at least three parts: "+systemName);
        throw  IllegalArgumentException("System name needs at least three parts: "+systemName);
    }
    if (parts.at(0)!=("IF$tsm")) {
        log->warn("SignalMast system name should start with IF: "+systemName);
    }
    QString system = parts.at(1);
    QString mast = parts.at(2);

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
/*public*/ void TurnoutSignalMast::setAspect(QString aspect)
{
 // check it's a choice
 if ( !map->checkAspect(aspect))
 {
    // not a valid aspect
    log->warn("attempting to set invalid aspect: "+aspect+" on mast: "+getDisplayName());
    throw new IllegalArgumentException("attempting to set invalid aspect: "+aspect+" on mast: "+getDisplayName());
 }
 else if (disabledAspects->contains(aspect))
 {
    log->warn("attempting to set an aspect that has been disabled: "+aspect+" on mast: "+getDisplayName());
    throw new IllegalArgumentException("attempting to set an aspect that has been disabled: "+aspect+" on mast: "+getDisplayName());
 }

 if(_resetPreviousStates)
 {
  //Clear all the current states, this will result in the signalmast going blank for a very short time.
  foreach(QString appearances, turnouts.keys())
  {
   if(!isAspectDisabled(appearances))
   {
    int setState = Turnout::CLOSED;
    if(turnouts.value(appearances)->getTurnoutState()==Turnout::CLOSED)
        setState = Turnout::THROWN;
    if(turnouts.value(appearances)->getTurnout()->getKnownState()!=setState){
        turnouts.value(appearances)->getTurnout()->setCommandedState(setState);
    }
   }
  }
 }
 if(turnouts.value(aspect) == nullptr)
 {
  log->error("Trying to set a state " + aspect + " on signal mast " + getDisplayName() + " which has not been configured");
  return;
 }
 Turnout* turnToSet = turnouts.value(aspect)->getTurnout();
 int stateToSet = turnouts.value(aspect)->getTurnoutState();
 //Set the new signal mast state
 if(turnToSet!=NULL){
     turnToSet->setCommandedState(stateToSet);
 }
 else
 {
     log->error("Trying to set a state " + aspect + " on signal mast " + getDisplayName() + " which has not been configured");
 }
 AbstractSignalMast::setAspect(aspect);
}

/*public*/ void TurnoutSignalMast::setUnLitTurnout(QString turnoutName, int turnoutState) {
    unLit = new TurnoutAspect(turnoutName, turnoutState);
}

/*public*/ QString TurnoutSignalMast::getUnLitTurnoutName() {
    if (unLit != nullptr) {
        return unLit->getTurnoutName();
    }
    return nullptr;
}

/*public*/ Turnout* TurnoutSignalMast::getUnLitTurnout() {
    if (unLit != nullptr) {
        return unLit->getTurnout();
    }
    return nullptr;
}

/*public*/ int TurnoutSignalMast::getUnLitTurnoutState() {
    if (unLit != nullptr) {
        return unLit->getTurnoutState();
    }
    return -1;
}

//@Override
/*public*/ void TurnoutSignalMast::setLit(bool state) {
    // set all Heads to state
    foreach(QString appearances, turnouts.keys()){
        int setState = Turnout::CLOSED;
        if(turnouts.value(appearances)->getTurnoutState()==Turnout::CLOSED)
            setState = Turnout::THROWN;
        if(turnouts.value(appearances)->getTurnout()->getKnownState()!=setState){
            turnouts.value(appearances)->getTurnout()->setCommandedState(setState);
        }
    }
    AbstractSignalMast::setLit(state);
}

/*public*/ QString TurnoutSignalMast::getTurnoutName(QString appearance){
    TurnoutAspect* aspect = turnouts.value(appearance);
    if(aspect!=NULL)
        return aspect->getTurnoutName();
    return "";
}

/*public*/ int TurnoutSignalMast::getTurnoutState(QString appearance){
    TurnoutAspect* aspect = turnouts.value(appearance);
    if(aspect!=NULL)
        return aspect->getTurnoutState();
    return -1;
}

/*public*/ void TurnoutSignalMast::setTurnout(QString appearance, QString turn, int state)
{
 if(turnouts.contains(appearance))
 {
  log->debug("Appearance " + appearance + " is already defined so will override");
  turnouts.remove(appearance);
 }
 turnouts.insert(appearance, new TurnoutAspect(turn, state));
}


/**
* If the signal mast driver requires the previous state to be cleared down before the next
* state is set.
*/
/*public*/ void TurnoutSignalMast::resetPreviousStates(bool boo) { _resetPreviousStates = boo; }

/*public*/ bool TurnoutSignalMast::resetPreviousStates() { return _resetPreviousStates; }


/*public*/ QList<NamedBeanHandle<Turnout*>*> TurnoutSignalMast::getHeadsUsed(){
    return  QList<NamedBeanHandle<Turnout*>* >();
}

/*public*/ /*static*/ int TurnoutSignalMast::getLastRef(){ return lastRef; }


