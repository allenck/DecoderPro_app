#include "defaultconditional.h"
#include "conditional.h"
#include "conditionalaction.h"
#include "conditionalvariable.h"
#include "exceptions.h"
#include "signalhead.h"
#include "signalmast.h"
#include "logix.h"
#include "light.h"
#include "proxyturnoutmanager.h"
#include "abstractsignalhead.h"
#include "defaultroute.h"
#include "logixmanager.h"
#include "defaultlogixmanager.h"
#include "defaultlogix.h"
#include "abstractmemory.h"
#include "abstractlightmanager.h"
#include "defaultconditional.h"
#include "defaultconditionalmanager.h"
#include "defaultconditionalaction.h"
#include "defaultsignalmastmanager.h"
#include "abstractsignalmast.h"
#include "abstractmemorymanager.h"
#include "abstractsignalheadmanager.h"
#include "oblockmanager.h"
#include "oblock.h"
#include "warrant.h"
#include "warrantmanager.h"
#include "instancemanager.h"
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "jlist.h"
#include "sound.h"
#include "fileutil.h"
#include "scripts/jmriscriptenginemanager.h"
#include "file.h"
#include "audiosource.h"
#include "scriptoutput.h"
#include "scriptexception.h"

//DefaultConditional::DefaultConditional(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * Class providing the basic logic of the Conditional interface.
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author	Dave Duchamp Copyright (C) 2007
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011
 * @author      Matthew Harris copyright (c) 2009
 * @version     $Revision: 22323 $
 */
///*public*/ class DefaultConditional extends AbstractNamedBean
//    implements Conditional, java.io.Serializable {

    /*public*/ /*static*/ /*final*/ bool DefaultConditional::PARKS_DEBUG = false;

//	static final java.util.ResourceBundle rbx = java.util.ResourceBundle.getBundle("jmri.jmrit.beantable.LogixTableBundle");

/*public*/ DefaultConditional::DefaultConditional(QString systemName, QString userName, QObject *parent) : Conditional(systemName, userName,parent)
{
 //super(systemName, userName);
    // boolean expression of state variables
 _antecedent = "";
 _logicType = Conditional::ALL_AND;
    // variables (antecedent) parameters
  _variableList = new QList<ConditionalVariable*>();
    // actions (consequent) parameters
  _actionList = new QList<ConditionalAction*>();

 _currentState = Conditional::UNKNOWN;
 _triggerActionsOnChange = true;
 log = new Logger("DefaultConditional");

}

//    /*public*/ DefaultConditional(String systemName) {
//        super(systemName);
//    }

/**
*  Inverse map
*/
/*public*/ /*static*/ int DefaultConditional::getIndexInTable(QList<int> table, int entry) {
    for (int i=0; i<table.length(); i++) {
        if (entry == table.at(i)) {
            return i;
        }
    }
    return -1;
}

/**
 * Get antecedent (boolean expression) of Conditional
 */
/*public*/ QString DefaultConditional::getAntecedentExpression() {
    return _antecedent;
}

/**
 * Get type of operators in the antecedent statement
 */
/*public*/ int DefaultConditional::getLogicType() {
    return _logicType;
}

/**
* set the logic type (all AND's all OR's or mixed AND's and OR's
* set the antecedent expression - should be a well formed boolean
* statement with parenthesis indicating the order of evaluation
*/
/*public*/ void DefaultConditional::setLogicType(int type, QString antecedent) {
    _logicType = type;
    _antecedent = antecedent;
    setState(Conditional::UNKNOWN);
}

/*public*/  bool DefaultConditional::getTriggerOnChange() {
    return _triggerActionsOnChange;
}

/*public*/  void DefaultConditional::setTriggerOnChange(bool trigger) {
    _triggerActionsOnChange = trigger;
}

/**
 * Set State Variables for this Conditional:: Each state variable will
 * evaluate either True or False when this Conditional is calculated.
 *<P>
 * This method assumes that all
 * information has been validated.
 */
/*public*/ void DefaultConditional::setStateVariables(QList <ConditionalVariable*>* arrayList) {
    if (log->isDebugEnabled()) log->debug("Conditional \""+getUserName()+"\" ("+getSystemName()+
              ") updated ConditionalVariable list.");
    _variableList = arrayList;
}

/**
 * Make deep clone of variables
 */
/*public*/ QList <ConditionalVariable*>* DefaultConditional::getCopyOfStateVariables() {
    QList <ConditionalVariable*>* variableList = new QList <ConditionalVariable*> ();
    for (int i = 0; i<_variableList->size(); i++) {
        ConditionalVariable* variable = _variableList->at(i);
        ConditionalVariable* clone = new ConditionalVariable();
        clone->setNegation(variable->isNegated());
        clone->setOpern(variable->getOpern());
        clone->setType(variable->getType());
        clone->setName(variable->getName());
        clone->setDataString(variable->getDataString());
        clone->setNum1(variable->getNum1());
        clone->setNum2(variable->getNum2());
        clone->setTriggerActions(variable->doTriggerActions());
        clone->setState(variable->getState());
        variableList->append(clone);
    }
    return variableList;
}

/**
 * Get the list of state variables for this Conditional.
 *
 * @return the list of state variables
 */
/*public*/ QList<ConditionalVariable*>* DefaultConditional::getStateVariableList() {
    return _variableList;
}

/**
 * Set list of actions
 */
//@Override
/*public*/ void DefaultConditional::setAction (QList <ConditionalAction*>* arrayList) {
    _actionList = arrayList;
}

/**
 * Make deep clone of actions
 */
/*public*/ QList <ConditionalAction*>* DefaultConditional::getCopyOfActions () {
    QList <ConditionalAction*>* actionList = new QList <ConditionalAction*> ();
    for (int i = 0; i<_actionList->size(); i++) {
        ConditionalAction* action = _actionList->at(i);
        ConditionalAction* clone = new DefaultConditionalAction();
        clone->setType(action->getType());
        clone->setOption(action->getOption());
        clone->setDeviceName(action->getDeviceName());
        clone->setActionData(action->getActionData());
        clone->setActionString(action->getActionString());
        actionList->append(clone);
    }
    return actionList;
}

/**
 * Get the list of actions for this conditional.
 *
 * @return the list of actions
 */
/*public*/ QList<ConditionalAction*> DefaultConditional::getActionList() {
    return *_actionList;
}

/**
 * Calculate this Conditional::
* When _enabled is false, Conditional::calculate will compute the state of the conditional,
* but will not trigger its actions. When _enabled is true, the state is computed
* and if the state has changed, will trigger all its actions.
*/
/*public*/ int DefaultConditional::calculate (bool enabled, PropertyChangeEvent* evt)
{
 if (log->isTraceEnabled()) log->trace("calculate starts for "+getSystemName());

 // check if  there are no state variables
 if (_variableList->isEmpty())
 {
  // if there are no state variables, no state can be calculated
  setState(Conditional::UNKNOWN);
  return _currentState;
 }
 bool result = true;
 switch (_logicType)
 {
  case Conditional::ALL_AND:
   for (int i=0; (i<_variableList->size()) && result; i++)
   {
       result = _variableList->at(i)->evaluate();
   }
   break;
  case Conditional::ALL_OR:
   result = false;
   for (int k=0; (k<_variableList->size()) && !result; k++)
   {
       result = _variableList->at(k)->evaluate();
   }
   break;
  case Conditional::MIXED:
  {
   QByteArray ch = _antecedent.toLatin1();
   int n = 0;
   for (int j=0; j<ch.length(); j++)
   {
    if (ch.at(j) != ' ')
    {
     if (ch.at(j) == '{' || ch.at(j) == '[')
     {
      ch.replace(j,'(');
     }
     else if (ch.at(j) == '}' || ch.at(j) == ']')
     {
      ch.replace(j, ')');
     }
     ch.replace(n++, ch.at(j));
    }
   }
   try
   {
       //DataPair* dp = parseCalculate(new QString(ch, 0, n), _variableList);
    DataPair* dp = parseCalculate(QString(ch), _variableList);
    result = dp->result;
   }
   catch ( NumberFormatException nfe)
   {
    result = false;
    log->error(getDisplayName()+" parseCalculation error antecedent= "+_antecedent+ ", ex= " + nfe.getMessage());
   }
   catch ( IndexOutOfBoundsException ioob)
   {
    result = false;
    log->error(getDisplayName()+" parseCalculation error antecedent= "+_antecedent+ ", ex= " + ioob.getMessage());
   }
   catch ( JmriException je)
   {
    result = false;
    log->error(getDisplayName()+" parseCalculation error antecedent= "+_antecedent+ ", ex= " + je.getMessage());
   }
   break;
  }
  default :
   log->warn("Conditional "+getSystemName()+" fell through switch in calculate");
   break;
  }
  int newState = Conditional::_FALSE;
  if (log->isDebugEnabled())
   log->debug(tr("Conditional \"%1\" (%2) has calculated its state to be %3. current state is %4. enabled= %5").arg(
                                               getUserName()).arg(getSystemName()).arg(result?"true":"faslse").arg(_currentState).arg(enabled));  // NOI18N

  if (result) newState = Conditional::_TRUE;

  if (log->isTraceEnabled()) log->trace(QString("   enabled starts at ")+(enabled?"true":"false"));

  if (enabled)
  {
  if (evt != nullptr)
  {
   // check if the current listener wants to (NOT) trigger actions
   enabled = wantsToTrigger(evt);
   if (log->isTraceEnabled()) log->trace(QString("   wantsToTrigger sets enabled to ")+(enabled?"true":"false"));
  }
}
if (_triggerActionsOnChange) {
  // pre 1/15/2011 on change only behavior
  if (newState == _currentState) {
      enabled = false;
      if (log->isTraceEnabled()) log->trace("   _triggerActionsOnChange sets enabled to false");
  }
 }
 setState(newState);
 if (enabled) {
     takeActionIfNeeded();
 }
 return _currentState;
}

/**
* Find out if the state variable is willing to cause the actions to execute
*/
bool DefaultConditional::wantsToTrigger(PropertyChangeEvent* evt) {
//    try {
        QString sysName = ((NamedBean*)evt->getSource())->getSystemName();
        QString userName = ((NamedBean*)evt->getSource())->getUserName();
        for (int i=0; i<_variableList->size(); i++) {
            if (sysName ==(_variableList->at(i)->getName())) {
                return _variableList->at(i)->doTriggerActions();
            }
        }
        if (userName != nullptr) {
            for (int i=0; i<_variableList->size(); i++) {
                if (userName ==(_variableList->at(i)->getName())) {
                    return _variableList->at(i)->doTriggerActions();
                }
            }
        }
//    } catch ( ClassCastException e) {
//        log->error(getDisplayName()+" PropertyChangeEvent source of unexpected type: "+ evt);
//    }
    return true;
}

#if 1
/**
*  Check that an antecedent is well formed
*
*/
/*public*/ QString DefaultConditional::validateAntecedent(QString ant, QList <ConditionalVariable*>* variableList) {
    QByteArray ch = ant.toLatin1();
    int n = 0;
    for (int j=0; j<ch.length(); j++) {
        if (ch.at(j) != ' ') {
            if (ch.at(j) == '{' || ch.at(j) == '[')  {
                ch.replace(j,'(');
            } else if (ch.at(j) == '}' || ch.at(j) == ']')  {
                ch.replace(j, ')');
            }
            ch.replace(n++, ch.at(j));
        }
    }
    int count = 0;
    for (int j=0; j<n; j++)  {
        if (ch.at(j) == '(') {
            count++;
        }
        if (ch.at(j) == ')') {
            count--;
        }
    }
    if (count > 0) {
//        return java.text.MessageFormat.format(
//                        tr("ParseError7"), new Object[] { ')' });
        return tr("Unmatched parenthesis, missing < %1 >.").arg(')');
    }
    if (count < 0) {
//        return java.text.MessageFormat.format(
//                        tr("ParseError7"), new Object[] { '(' });
        return tr("Unmatched parenthesis, missing < %1 >.").arg('(');
    }
    try {
        QString s = QString(ch);
        DataPair* dp = parseCalculate( s.mid(0,n), variableList);
        if (n != dp->indexCount) {
//            return java.text.MessageFormat.format(
//                        tr("ParseError4"), new Object[] { ch[dp.indexCount-1] });
            return tr("Antecedent parsing error: Unexpected character found. < %1 >\n").arg(ch.at(dp->indexCount-1));
        }
        int index = dp->argsUsed->nextClearBit(0);
        if ( index >= 0 && index < variableList->size() ) {
//            return java.text.MessageFormat.format(
//                        tr("ParseError5"),
//                        new Object[] { Integer.valueOf(variableList.size()),
//                                        Integer.valueOf(index+1) });
            return tr("Antecedent parsing error: All %1 rows must be used.  Row %1 is missing.").arg(variableList->size()).arg(index+1);
        }
    } catch ( NumberFormatException nfe) {
        return tr("ParseError6") + nfe.getMessage();
    } catch ( IndexOutOfBoundsException ioob) {
        return tr("ParseError6") + ioob.getMessage();
    }  catch ( JmriException je) {
        return tr("ParseError6") + je.getMessage();
    }
    return nullptr;
}
#endif
/**
* Parses and computes one parenthesis level of a boolean statement.
* <p>
* Recursively calls inner parentheses levels.
* Note that all logic operators are dectected by the parsing, therefore the
* internal negation of a variable is washed.
* @param s The expression to be parsed
* @param variableList ConditionalVariables for R1, R2, etc
* @return a data pair consisting of the truth value of the level
* a count of the indices consumed to parse the level and a
* bitmap of the variable indices used.
*/
DataPair* DefaultConditional::parseCalculate(QString s, QList <ConditionalVariable*>* variableList)
throw (JmriException)
{

    // for simplicity, we force the string to upper case before scanning
    s = s.toUpper();

    BitSet* argsUsed = new BitSet(_variableList->size());
    DataPair* dp = nullptr;
    bool leftArg = false;
    bool rightArg = false;
    int oper = Conditional::OPERATOR_NONE;
    int k = -1;
    int i = 0;      // index of String s
    //int numArgs = 0;
    if (s.at(i) == '(')  {
        dp = parseCalculate(s.mid(++i), variableList);
        leftArg = dp->result;
        i += dp->indexCount;
        argsUsed->_or( dp->argsUsed);
    } else {
        // cannot be '('.  must be either leftArg or notleftArg
        if (s.at(i) == 'R') {
//            try {
                k = s.mid(i+1, i+3).toInt();
                i += 2;
//            } catch (NumberFormatException nfe) {
//                k = Integer.parseInt(String.valueOf(s.charAt(++i)));
//            } catch (IndexOutOfBoundsException ioob) {
//                k = Integer.parseInt(String.valueOf(s.charAt(++i)));
//            }
            leftArg = variableList->at(k-1)->evaluate();
            if (variableList->at(k-1)->isNegated())
            {
                leftArg = !leftArg;
            }
            i++;
            argsUsed->set(k-1);
        } else if (tr("NOT") ==(s.mid(i, i+3)) ) {
            i += 3;
            //not leftArg
            if (s.at(i) == '(')  {
                dp = parseCalculate(s.mid(++i), variableList);
                leftArg = dp->result;
                i += dp->indexCount;
                argsUsed->_or( dp->argsUsed);
            } else if (s.at(i) == 'R') {
//                try {
                    k = s.mid(i+1, i+3).toInt();
                    i += 2;
//                } catch (NumberFormatException nfe) {
//                    k = Integer.parseInt(String.valueOf(s.charAt(++i)));
//                } catch (IndexOutOfBoundsException ioob) {
//                    k = Integer.parseInt(String.valueOf(s.charAt(++i)));
//                }
                leftArg = variableList->at(k-1)->evaluate();
                if (variableList->at(k-1)->isNegated())
                {
                    leftArg = !leftArg;
                }
                i++;
                argsUsed->set(k-1);
            } else {
                throw  JmriException(
                            tr("Could not find expected Left argument. < %1 >").arg(s.mid(i) ));
            }
            leftArg = !leftArg;
        } else {
            throw JmriException(
                tr("Unexpected operator or characters. < %1 >").arg (s ));
        }
    }
    // crank away to the right until a matching paren is reached
    while ( i<s.length() ) {
        if ( s.at(i) != ')' ) {
            // must be either AND or OR
            if (tr("AND") ==(s.mid(i, i+3)))  {
                i += 3;
                oper = Conditional::OPERATOR_AND;
            } else if (tr("OR") ==(s.mid(i, i+2))) {
                i += 2;
                oper = Conditional::OPERATOR_OR;
            }else {
                throw  JmriException(
                            tr("Could not find expected operator. < %1 >").arg( s.mid(i) ));
            }
            if (s.at(i) == '(')  {
                dp = parseCalculate(s.mid(++i), variableList);
                rightArg =dp->result;
                i += dp->indexCount;
                argsUsed->_or( dp->argsUsed);
            } else {
                // cannot be '('.  must be either rightArg or notRightArg
                if (s.at(i) == 'R') {
//                    try {
                        k = s.mid(i+1, i+3).toInt();
                        i += 2;
//                    } catch (NumberFormatException nfe) {
//                        k = Integer.parseInt(String.valueOf(s.charAt(++i)));
//                    } catch (IndexOutOfBoundsException ioob) {
//                        k = Integer.parseInt(String.valueOf(s.charAt(++i)));
//                    }
                    rightArg = variableList->at(k-1)->evaluate();
                    if (variableList->at(k-1)->isNegated())
                    {
                        rightArg = !rightArg;
                    }
                    i++;
                    argsUsed->set(k-1);
                } else if ((i+3)<s.length() && tr("NOT") ==(s.mid(i, i+3)) )
                {
                    i += 3;
                    //not rightArg
                    if (s.at(i) == '(')  {
                        dp = parseCalculate(s.mid(++i), variableList);
                        rightArg = dp->result;
                        i += dp->indexCount;
                        argsUsed->_or( dp->argsUsed);
                    } else if (s.at(i) == 'R') {
//                        try {
                            k = s.mid(i+1, i+3).toInt();
                            i += 2;
//                        } catch (NumberFormatException nfe) {
//                            k = Integer.parseInt(String.valueOf(s.charAt(++i)));
//                        } catch (IndexOutOfBoundsException ioob) {
//                            k = Integer.parseInt(String.valueOf(s.charAt(++i)));
//                        }
                        rightArg = variableList->at(k-1)->evaluate();
                        if (variableList->at(k-1)->isNegated())
                        {
                            rightArg = !rightArg;
                        }
                        i++;
                        argsUsed->set(k-1);
                    } else {
                        throw new JmriException(
                            tr("Could not find expected Right argument. < %1 >").arg(s.mid(i)));
                    }
                    rightArg = !rightArg;
                } else {
                    throw new JmriException(
                                tr("Unexpected operator or characters. < {0} >").arg(s.mid(i) ));
                }
            }
            if (oper == Conditional::OPERATOR_AND)   {
                leftArg = (leftArg && rightArg);
            } else if (oper == Conditional::OPERATOR_OR) {
                leftArg = (leftArg || rightArg);
            }
        }
        else {  // This level done, pop recursion
            i++;
            break;
        }
    }
    dp = new DataPair();
    dp->result = leftArg;
    dp->indexCount = i;
    dp->argsUsed = argsUsed;
    return dp;
}

/**
 * Compares action options, and takes action if appropriate
 * <P>
 * Only get here if a change in state has occurred when calculating this Conditional
 */
//@SuppressWarnings({ "deprecation", "fallthrough" })
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
// it's unfortunate that this is such a huge method, because these annotation
// have to apply to more than 500 lines of code - jake
/*private*/ void DefaultConditional::takeActionIfNeeded()
{
 if (log->isTraceEnabled())
  log->trace("takeActionIfNeeded starts for "+getSystemName());
 int actionCount = 0;
 int actionNeeded = 0;
 int act = 0;
 int state = 0;
 QStringList errorList =  QStringList();
 // Use a local copy of state to guarantee the entire list of actions will be fired off
 // before a state change occurs that may block their completion.
 int currentState = _currentState;
 for (int i = 0; i < _actionList->size(); i++)
 {
  ConditionalAction* action = _actionList->at(i);
  int neededAction = actionNeeded;
  int option = action->getOption();
  if (log->isTraceEnabled())
   log->trace(" takeActionIfNeeded considers action "+QString::number(i)+" with currentState: "+QString::number(currentState)+" and option: "+QString::number(option));
  if ( ((currentState==Conditional::_TRUE) && (option==Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE)) ||
      ((currentState==Conditional::_FALSE) && (option==Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE)) ||
          (option==Conditional::ACTION_OPTION_ON_CHANGE) )
  {
   // need to take this action
   actionNeeded++;
   SignalHead* h = nullptr;
   SignalMast* f = nullptr;
   Logix* x = nullptr;
   Light* lgt = nullptr;
   Warrant* w = nullptr;
   OBlock* b = nullptr;
   NamedBean* nb = nullptr;
   if (action->getNamedBean() != nullptr)
   {
    nb = (NamedBean*) action->getNamedBean()->getBean();
   }
   int value = 0;
   QTimer* timer = nullptr;
   int type = action->getType();
   QString devName = getDeviceName(action);
   if (devName==nullptr)
   {
    errorList.append("invalid memory name in action - "+devName);
    continue;
   }
   if (log->isDebugEnabled()) log->debug("getDeviceName()="+action->getDeviceName()+" devName= "+devName);
   switch (type)
   {
    case Conditional::ACTION_NONE:
        break;
    case Conditional::ACTION_SET_TURNOUT:
    {
     Turnout* t =(Turnout*) nb;
     if (t == nullptr)
     {
      errorList.append("invalid turnout name in action - "+action->getDeviceName());
     }
     else
     {
      act = action->getActionData();
      if (act == Route::TOGGLE)
      {
       state = ((AbstractTurnout*)t)->getKnownState();
       if (state == Turnout::CLOSED)
        act = Turnout::THROWN;
       else
        act = Turnout::CLOSED;
      }
      ((AbstractTurnout*)t)->setCommandedState(act);
      actionCount++;
     }
     break;
    }
    case Conditional::ACTION_RESET_DELAYED_TURNOUT:
     action->stopTimer();
     // fall through
    case Conditional::ACTION_DELAYED_TURNOUT:
     if (!action->isTimerActive())
     {
      // Create a timer if one does not exist
      timer = action->getTimer();
      if (timer==nullptr)
      {
       action->setListener(new TimeTurnout(i,this));
       //timer = new QTimer(2000, action->getListener());
       timer = new QTimer();
       timer->setSingleShot(false);
      }
      // Start the Timer to set the turnout
      value = getIntegerValue(action);
      if (value<0) {
          break;
      }
      //timer->setInitialDelay(value*1000);
      timer->setInterval(2000);
      action->setTimer(timer);
      action->startTimer();
      actionCount++;
     }
     else
     {
      log->warn("timer already active on request to start delayed turnout action - "+ devName);
     }
     break;
    case Conditional::ACTION_CANCEL_TURNOUT_TIMERS:
    {
     ConditionalManager* cmg = static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"));
     QStringListIterator iter( cmg->getSystemNameList());
     while (iter.hasNext())
     {
      QString sname = iter.next();
      if (sname==nullptr)
          errorList.append("Conditional system name nullptr during cancel turnput timers for "
                                  + action->getDeviceName());
      Conditional* c = cmg->getBySystemName(sname);
      if (c==nullptr)
          errorList.append("Conditional nullptr during cancel turnout timers for "
                                  + action->getDeviceName());
      else
      {
       c->cancelTurnoutTimer(devName);
       actionCount++;
      }
     }
     break;
    }
    case Conditional::ACTION_LOCK_TURNOUT:
    {
     Turnout* tl = (Turnout*) nb;
     if (tl == nullptr)
     {
      errorList.append("invalid turnout name in action - "+action->getDeviceName());
     }
     else
     {
      act = action->getActionData();
      if (act == Route::TOGGLE)
      {
       if (((AbstractTurnout*)tl)->getLocked(Turnout::CABLOCKOUT) )
           act = Turnout::UNLOCKED;
       else
           act = Turnout::LOCKED;
      }
      if (act == Turnout::LOCKED)
      {
       ((AbstractTurnout*)tl)->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
      }
      else if (act == Turnout::UNLOCKED)
      {
       ((AbstractTurnout*)tl)->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, false);
      }
      actionCount++;
     }
     break;
    }
    case Conditional::ACTION_SET_SIGNAL_APPEARANCE:
     h = (SignalHead*) nb;
     if (h == nullptr)
     {
      errorList.append("invalid signal head name in action - "+action->getDeviceName());
     }
     else {
         h->setAppearance(action->getActionData());
         actionCount++;
     }
     break;
    case Conditional::ACTION_SET_SIGNAL_HELD:
     h = (SignalHead*) nb;
     if (h == nullptr)
     {
      errorList.append("invalid signal head name in action - "+action->getDeviceName());
     }
     else {
         ((AbstractSignalHead*)h)->setHeld(true);
         actionCount++;
     }
     break;
    case Conditional::ACTION_CLEAR_SIGNAL_HELD:
     h = (SignalHead*) nb;
     if (h == nullptr) {
         errorList.append("invalid signal head name in action - "+action->getDeviceName());
     }
     else
     {
      ((AbstractSignalHead*)h)->setHeld(false);
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_SIGNAL_DARK:
     h = (SignalHead*) nb;
     if (h == nullptr)
     {
      errorList.append("invalid signal head name in action - "+action->getDeviceName());
     }
     else
     {
      ((AbstractSignalHead*)h)->setLit(false);
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_SIGNAL_LIT:
     h = (SignalHead*) nb;
     if (h == nullptr) {
         errorList.append("invalid signal head name in action - "+action->getDeviceName());
     }
     else
     {
      ((AbstractSignalHead*)h)->setLit(true);
      actionCount++;
     }
     break;
    case Conditional::ACTION_TRIGGER_ROUTE:
    {
     Route* r = (Route*) nb;
     if (r == nullptr) {
         errorList.append("invalid route name in action - "+action->getDeviceName());
     }
     else
     {
      ((DefaultRoute*)r)->setRoute();
      actionCount++;
     }
     break;
    }
    case Conditional::ACTION_SET_SENSOR:
    {
     Sensor* sn = (Sensor*) nb;
     if (sn == nullptr)
     {
      errorList.append("invalid sensor name in action - "+action->getDeviceName());
     }
     else
     {
      act = action->getActionData();
      if (act == Route::TOGGLE)
      {
       state = sn->getState();
       if (state == Sensor::ACTIVE)
        act = Sensor::INACTIVE;
       else
        act = Sensor::ACTIVE;
      }
      try
      {
          sn->setKnownState(act);
          actionCount++;
      }
      catch (JmriException e)
      {
          log->warn("Exception setting sensor "+devName+" in action");
      }
     }
     break;
    }
    case Conditional::ACTION_RESET_DELAYED_SENSOR:
     action->stopTimer();
     // fall through
 case Conditional::ACTION_DELAYED_SENSOR:
     if (!action->isTimerActive())
     {
      // Create a timer if one does not exist
      timer = action->getTimer();
      if (timer==nullptr)
      {
       action->setListener(new TimeSensor(i, this));
       //timer = new QTimer(2000, action->getListener());
       timer = new QTimer();
       timer->setSingleShot(false);
      }
      // Start the Timer to set the turnout
      value = getIntegerValue(action);
      if (value<0) {
          break;
      }
      timer->setInterval(value*1000);
      action->setTimer(timer);
      action->startTimer();
      actionCount++;
     }
     else
     {
      log->warn("timer already active on request to start delayed sensor action - "+ devName);
     }
     break;
    case Conditional::ACTION_CANCEL_SENSOR_TIMERS:
    {
     ConditionalManager* cm = static_cast<ConditionalManager*>(InstanceManager::getDefault("CondtionalManager"));
     QStringListIterator itr( cm->getSystemNameList());
     while (itr.hasNext())
     {
      QString sname = itr.next();
      if (sname==nullptr)
          errorList.append("Conditional system name nullptr during cancel sensor timers for "
                                  + action->getDeviceName());
      Conditional* c = cm->getBySystemName(sname);
      if (c==nullptr)
          errorList.append("Conditional nullptr during cancel sensor timers for "
                                  + action->getDeviceName());
      else
      {
       ((DefaultConditional*)c)->cancelSensorTimer(devName);
       actionCount++;
      }
     }
     break;
    }
    case Conditional::ACTION_SET_LIGHT:
     lgt = (Light*)nb;
     if (lgt == nullptr)
     {
      errorList.append("invalid light name in action - "+action->getDeviceName());
     }
     else
     {
      act = action->getActionData();
      if (act == Route::TOGGLE)
      {
       state = ((AbstractLight*)lgt)->getState();
       if (state == Light::ON)
           act = Light::OFF;
       else
           act =Light::ON;
      }
      ((AbstractLight*)lgt)->setState(act);
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_LIGHT_INTENSITY:
     lgt = (Light*)nb;
     if (lgt == nullptr)
     {
      errorList.append("invalid light name in action - "+action->getDeviceName());
     }
     else
     {
      try
      {
       value = getIntegerValue(action);
       if (value<0)
       {
        break;
       }
       ((AbstractLight*)lgt)->setTargetIntensity((value)/100.0);
       actionCount++;
      }
      catch (IllegalArgumentException e)
      {
       errorList.append("Exception in set light intensity action - "+action->getDeviceName());
      }
     }
     break;
   case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
    lgt = (Light*)nb;
    if (lgt == nullptr)
    {
         errorList.append("invalid light name in action - "+action->getDeviceName());
    }
    else
    {
     try
     {
      value = getIntegerValue(action);
      if (value<0)
      {
        break;
      }
      ((AbstractLight*)lgt)->setTransitionTime(value);
      actionCount++;
     }
     catch (IllegalArgumentException e)
     {
      errorList.append("Exception in set light transition time action - "+action->getDeviceName());
     }
    }
    break;
   case Conditional::ACTION_SET_MEMORY:
   {
     Memory* m = (Memory*) nb;
     if (m == nullptr) {
         errorList.append("invalid memory name in action - "+action->getDeviceName());
     }
     else {
         ((AbstractMemory*)m)->setValue(action->getActionString());
         actionCount++;
     }
     break;
    }
   case Conditional::ACTION_COPY_MEMORY:
   {
     Memory* mFrom = (Memory*) nb;
    if (mFrom == nullptr)
    {
        errorList.append("invalid memory name in action - "+action->getDeviceName());
    }
    else
    {
     Memory* mTo = getMemory(action->getActionString());
     if (mTo == nullptr)
     {
      errorList.append("invalid memory name in action - "+action->getActionString());
     }
     else
     {
      ((AbstractMemory*)mTo)->setValue(mFrom->getValue());
      actionCount++;
     }
    }
    break;
   }
   case Conditional::ACTION_ENABLE_LOGIX:
    x = static_cast<LogixManager*>(InstanceManager::getDefault("LogixManager"))->getLogix(devName);
    if (x == nullptr) {
        errorList.append("invalid logix name in action - "+action->getDeviceName());
    }
    else {
        ((DefaultLogix*)x)->setEnabled(true);
        actionCount++;
    }
    break;
   case Conditional::ACTION_DISABLE_LOGIX:
    x = static_cast<LogixManager*>(InstanceManager::getDefault("LogixManager"))->getLogix(devName);
    if (x == nullptr) {
        errorList.append("invalid logix name in action - "+action->getDeviceName());
    }
    else {
        ((DefaultLogix*)x)->setEnabled(false);
        actionCount++;
    }
    break;
#if 1
   case Conditional::ACTION_PLAY_SOUND:
   {
    QString path = getActionString(action);
    if (!path.isEmpty()) {
        Sound* sound = action->getSound();
        if (sound == nullptr) {
            try {
                sound = new Sound(path);
            } catch (NullPointerException ex) {
                errorList.append("invalid path to sound: " + path);  // NOI18N
            }
        }
        if (sound != nullptr) {
            sound->play();
        }
        actionCount++;
    }
    break;
   }
   case Conditional::ACTION_RUN_SCRIPT:
    if (!(getActionString(action) == (""))) {
        JmriScriptEngineManager::getDefault()->runScript(new File(FileUtil::getExternalFilename(getActionString(action))));
        actionCount++;
       }
       break;
#endif
   case Conditional::ACTION_SET_FAST_CLOCK_TIME:
   {
    QDateTime date = static_cast<Timebase*>(InstanceManager::getDefault("Timebase"))->getTime();
//                    date.setHours(action->getActionData()/60);
//                    date.setMinutes(action->getActionData() - ((action->getActionData()/60)*60));
//                    date.setSeconds(0);
    date.setTime(QTime(action->getActionData()/60,action->getActionData() - ((action->getActionData()/60)*60),0));
    static_cast<Timebase*>(InstanceManager::getDefault("Timebase"))->userSetTime(date);
    actionCount++;
    break;
   }
   case Conditional::ACTION_START_FAST_CLOCK:
   {
    static_cast<Timebase*>(InstanceManager::getDefault("Timebase"))->setRun(true);
    actionCount++;
    break;
   }
   case Conditional::ACTION_STOP_FAST_CLOCK:
   {
    static_cast<Timebase*>(InstanceManager::getDefault("Timebase"))->setRun(false);
    actionCount++;
    break;
   }
#if 1
   case Conditional::ACTION_CONTROL_AUDIO:
   {
    Audio* audio = static_cast<AudioManager*>(InstanceManager::getDefault("AudioManager"))->getAudio(devName);
    if (audio->getSubType()==Audio::SOURCE)
    {
     AudioSource* audioSource = (AudioSource*) audio;
     switch (action->getActionData())
     {
      case Audio::CMD_PLAY:
          audioSource->play();
          break;
      case Audio::CMD_STOP:
          audioSource->stop();
          break;
      case Audio::CMD_PLAY_TOGGLE:
          audioSource->togglePlay();
          break;
      case Audio::CMD_PAUSE:
          audioSource->pause();
          break;
      case Audio::CMD_RESUME:
          audioSource->resume();
          break;
      case Audio::CMD_PAUSE_TOGGLE:
          audioSource->togglePause();
          break;
      case Audio::CMD_REWIND:
          audioSource->rewind();
          break;
      case Audio::CMD_FADE_IN:
          audioSource->fadeIn();
          break;
      case Audio::CMD_FADE_OUT:
          audioSource->fadeOut();
          break;
      case Audio::CMD_RESET_POSITION:
          audioSource->resetCurrentPosition();
          break;
      default : break;
      }
     }
     else if (audio->getSubType()==Audio::LISTENER)
     {
      AudioListener* audioListener = (AudioListener*) audio;
      switch (action->getActionData()) {
          case Audio::CMD_RESET_POSITION:
              audioListener->resetCurrentPosition();
              break;
      }
     }
    }
    break;
   case Conditional::ACTION_JYTHON_COMMAND:
     if (!(getActionString(action).isEmpty()))
     {
         // add the text to the output frame
         ScriptOutput::writeScript(getActionString(action));
         // and execute
         try {
             JmriScriptEngineManager::getDefault()->eval(getActionString(action), JmriScriptEngineManager::getDefault()->getEngine(JmriScriptEngineManager::PYTHON));
         } catch (ScriptException ex) {
             log->error(tr("Error executing script:"), ex);  // NOI18N
         }
         actionCount++;
     }
    break;
#endif
   case Conditional::ACTION_ALLOCATE_WARRANT_ROUTE:
     w = (Warrant*) nb;
     if (w == nullptr)
     {
      errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      QString msg = w->allocateRoute(false, nullptr);
      if (msg !=nullptr)
      {
       log->info("Warrant "+action->getDeviceName()+" - "+msg);
      }
      actionCount++;
     }
     break;
    case Conditional::ACTION_DEALLOCATE_WARRANT_ROUTE:
     w = (Warrant*) nb;
     if (w == nullptr)
     {
      errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      w->deAllocate();
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_ROUTE_TURNOUTS:
     w = (Warrant*) nb;
     if (w == nullptr)
     {
         errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      QString msg = w->setRoute(0, nullptr);
      if (msg!=nullptr)
      {
       log->info("Warrant "+action->getDeviceName()+" unable to Set Route - "+msg);
      }
      actionCount++;
     }
     break;
    case Conditional::ACTION_THROTTLE_FACTOR:
     w = (Warrant*) nb;
     if (w == nullptr)
     {
      errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      QString msg = w->setThrottleFactor(getActionString(action));
      if (msg!=nullptr)
      {
       log->info("Warrant "+action->getDeviceName()+" unable to Set Throttle Factor - "+msg);
      }
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_TRAIN_ID:
     w = (Warrant*) nb;
     if (w == nullptr)
     {
      errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      if (!w->setTrainId(getActionString(action)))
      {
       QString s = "Unable to find train Id "+action->getActionString()+" in Roster  - "+action->getDeviceName();
       log->info(s);
       errorList.append(s);	// could be serious - display error to UI
      }
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_TRAIN_NAME:
     w = (Warrant*) nb;
     if (w == nullptr)
     {
      errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      w->setTrainName(getActionString(action));
      actionCount++;
     }
     break;
    case Conditional::ACTION_AUTO_RUN_WARRANT:
     w = (Warrant*) nb;
     if (w == nullptr)
     {
      errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      QString err = w->setRoute(0, nullptr);
      err = w->setRunMode(Warrant::MODE_RUN, nullptr, nullptr, nullptr, false);
      if (err!=nullptr) {
          errorList.append("runAutoTrain error - "+err);
      }
      actionCount++;
     }
     break;
    case Conditional::ACTION_MANUAL_RUN_WARRANT:
     w = (Warrant*) nb;
     if (w == nullptr)
     {
      errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      QString err = w->setRoute(0, nullptr);
      err = w->setRunMode(Warrant::MODE_MANUAL, nullptr, nullptr, nullptr, false);
      if (err!=nullptr)
      {
       errorList.append("runManualTrain error - "+err);
      }
      actionCount++;
     }
     break;
    case Conditional::ACTION_CONTROL_TRAIN:
     w = (Warrant*) nb;
     if (w == nullptr) {
         errorList.append("invalid Warrant name in action - "+action->getDeviceName());
     }
     else
     {
      if (!w->controlRunTrain(action->getActionData()))
      {
       log->info("Train "+w->getTrainId()+" not running  - "+devName);
      }
      actionCount++;
     }
     break;

    case Conditional::ACTION_SET_SIGNALMAST_ASPECT:
     f = (SignalMast*) nb;
     if (f == nullptr)
     {
      errorList.append("invalid signal mast name in action - "+action->getDeviceName());
     }
     else
     {
      ((AbstractSignalMast*)f)->setAspect(getActionString(action));
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_SIGNALMAST_HELD:
     f = (SignalMast*) nb;
     if (f == nullptr) {
         errorList.append("invalid signal mast name in action - "+action->getDeviceName());
     }
     else {
         ((AbstractSignalMast*)f)->setHeld(true);
         actionCount++;
     }
     break;
    case Conditional::ACTION_CLEAR_SIGNALMAST_HELD:
     f = (SignalMast*) nb;
     if (f == nullptr)
     {
      errorList.append("invalid signal mast name in action - "+action->getDeviceName());
     }
     else
     {
      ((AbstractSignalMast*)f)->setHeld(false);
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_SIGNALMAST_DARK:
     f = (SignalMast*) nb;
     if (f == nullptr) {
         errorList.append("invalid signal head name in action - "+action->getDeviceName());
     }
     else
     {
      ((AbstractSignalMast*)f)->setLit(false);
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_SIGNALMAST_LIT:
     f = (SignalMast*) nb;
     if (f == nullptr)
     {
      errorList.append("invalid signal head name in action - "+action->getDeviceName());
     }
     else
     {
      ((AbstractSignalMast*)f)->setLit(true);
      actionCount++;
     }
     break;
#if 1
    case Conditional::ACTION_SET_BLOCK_VALUE:
     b = (OBlock*) nb;
     if (b == nullptr)
     {
      errorList.append("invalid block name in action - " + action->getDeviceName());
     }
     else
     {
      b->setValue(getActionString(action));
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_BLOCK_ERROR:
     b = (OBlock*) nb;
     if (b == nullptr) {
         errorList.append("invalid block name in action - " + action->getDeviceName());
     } else {
         b->setError(true);
         actionCount++;
     }
     break;
    case Conditional::ACTION_CLEAR_BLOCK_ERROR:
     b = (OBlock*) nb;
     if (b == nullptr) {
         errorList.append("invalid block name in action - " + action->getDeviceName());
     } else {
         b->setError(false);
     }
     break;
    case Conditional::ACTION_DEALLOCATE_BLOCK:
     b = (OBlock*)nb;
     if (b == nullptr)
     {
         errorList.append("invalid block name in action - "+action->getDeviceName());
     }
     else {
         b->deAllocate(nullptr);
         actionCount++;
     }
     break;
    case Conditional::ACTION_SET_BLOCK_OUT_OF_SERVICE:
     b = (OBlock*)nb;
     if (b == nullptr)
     {
      errorList.append("invalid block name in action - "+action->getDeviceName());
     }
     else
     {
      b->setOutOfService(true);
      actionCount++;
     }
     break;
    case Conditional::ACTION_SET_BLOCK_IN_SERVICE:
     b = (OBlock*)nb;
     if (b == nullptr) {
         errorList.append("invalid block name in action - "+action->getDeviceName());
     }
     else
     {
      b->setOutOfService(false);
      actionCount++;
     }
     break;
#endif
    default :
    {
     log->warn("takeActionIfNeeded drops through switch statement for action "+QString::number(i)+" of "+getSystemName());
     break;
    }
   }
  }
  if (PARKS_DEBUG)
  { /*System.out.println*/log->error("Global state= "+QString::number(_currentState)+" Local state= "+currentState+ " - Action "+(actionNeeded>neededAction ? "WAS" : "NOT")+" taken for action = "+action->getTypeString()+" "+action->getActionString()+ " for device "+action->getDeviceName());
  }
 }
 if (errorList.size() > 0)
 {
  for (int i=0; i<errorList.size(); i++)
  {
   log->error(getDisplayName()+" - "+errorList.at(i));
  }
  //Toolkit.getDefaultToolkit().beep();
  QApplication::beep();
  if (!_skipErrorDialog) {
      new ErrorDialog(errorList, this);
  }
 }
 if (log->isDebugEnabled())
        log->debug("Conditional \""+getUserName()+"\" ("+getSystemName()+" has "+QString::number(_actionList->size())+
                                         " actions and has executed "+QString::number(actionCount)
              +" actions of "+QString::number(actionNeeded)+" actions needed on state change to "+QString::number(currentState));
 if (PARKS_DEBUG)
 {/* System.out.println*/log->error("Conditional \""+getUserName()+"\" ("+getSystemName()+" has "+QString::number(_actionList->size())+
                                         " actions and has executed "+actionCount
              +" actions of "+QString::number(actionNeeded)+" actions needed on state change to "+QString::number(currentState));
 }
}   // takeActionIfNeeded

DataPair::DataPair()
{
    result = false;
    indexCount = 0;         // index reached when parsing completed
    argsUsed = nullptr;
}

/*static*/ /*private*/ bool DefaultConditional::_skipErrorDialog = false;

//class ErrorDialog : public  QDialog {
//    JCheckBox rememberSession;
    ErrorDialog::ErrorDialog(QStringList list, DefaultConditional *cond) : JDialog()
    {
        //super();
     this->cond = cond;
        setTitle("Logix Runtime Errors");
        QWidget* contentPanel = new QWidget();
        contentPanel->setLayout(new QVBoxLayout()); //contentPanel, BoxLayout.Y_AXIS));
        QWidget* panel = new QWidget();
        panel->setLayout(new QHBoxLayout());
        panel->layout()->addWidget(new QLabel("Errors occurred executing Actions in Conditional:"));
        contentPanel->layout()->addWidget(panel);

        panel = new QWidget();
        panel->setLayout(new QHBoxLayout());
//        panel->setLayout(new QHBoxLayout());
        panel->layout()->addWidget(new QLabel(cond->getUserName()+" ("+cond->getSystemName()+")"));
        contentPanel->layout()->addWidget(panel);

        panel = new QWidget();
        JList* jlist = new JList(list);
        panel->setLayout(new QHBoxLayout());
        panel->layout()->addWidget(jlist);
        contentPanel->layout()->addWidget(panel);

        panel = new QWidget();
        panel->setLayout(new QHBoxLayout());
        rememberSession = new QCheckBox("Skip error dialog for this session only?");
        panel->layout()->addWidget(rememberSession);
        contentPanel->layout()->addWidget(panel);

        panel = new QWidget();
        panel->setLayout(new QHBoxLayout());
        QPushButton* closeButton = new QPushButton("Close");
//        closeButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    if(rememberSession.isSelected()){
//                        _skipErrorDialog = true;
//                    }
//                    dispose();
//                }
//        });
        connect(closeButton, SIGNAL(clicked(bool)),this, SLOT(onCloseButton()));
        panel->layout()->addWidget(closeButton);
        contentPanel->layout()->addWidget(panel);
        //setContentPane(contentPanel);
        this->setLayout(new QVBoxLayout());
        this->layout()->addWidget(contentPanel);
        setLocation(250, 150);
        pack();
        setVisible(true);
    }

    void ErrorDialog::onCloseButton()
    {
     if(rememberSession->isChecked()){
         cond->_skipErrorDialog = true;
     }
     this->dispose();
    }
//};

/*private*/ QString DefaultConditional::getDeviceName(ConditionalAction* action)
{
 QString devName = action->getDeviceName();
 if (devName!="" && devName.length()>0 && devName.at(0)== '@')
 {
  QString memName = devName.mid(1);
  Memory* m = getMemory(memName);
  if (m == nullptr)
  {
   log->error(getDisplayName()+" invalid memory name in action - "+devName);
   return nullptr;
  }
  devName = m->getValue().toString();
 }
 return devName;
}

/*private*/ QString DefaultConditional::getActionString(ConditionalAction* action)
{
 QString devAction = action->getActionString();
 if (devAction!="" && devAction.length()>0 && devAction.at(0)== '@')
 {
  QString memName = devAction.mid(1);
  Memory* m = getMemory(memName);
  if (m == nullptr)
  {
   log->error(getDisplayName()+" action \""+action->getDeviceName()+
             "\" has invalid memory name in actionString - "+action->getActionString());
   return "";
  }
  devAction = m->getValue().toString();
 }
 return devAction;
}

/** for backward compatibility with config files having system names in lower case
*/
/*private*/ /*static*/ Memory* DefaultConditional::getMemory(QString name) {
     return InstanceManager::memoryManagerInstance()->getMemory(name);
}

/**
 * Return int from either literal String or Internal memory reference.
 */
int DefaultConditional::getIntegerValue(ConditionalAction* action) {
    QString sNumber = action->getActionString();
    int time = 0;
    //try {
    bool bOk;
    time = sNumber.toInt(&bOk);
//    } catch (NumberFormatException e) {
    if(!bOk)
    {
     Memory* mem = getMemory(sNumber);
     if (mem == nullptr)
     {
            log->error("invalid memory name for action time variable - "+sNumber+
                      ", for Action \""+action->getTypeString()+
                      "\", in Conditional \""+getUserName()+"\" ("+getSystemName()+")");
            return -1;
     }
     else
     {
      //try {
      bool bOk;
      time = mem->getValue().toInt(&bOk);
//            } catch (NumberFormatException ex) {
      if(!bOk)
      {
                log->error("invalid action number variable from memory, \""+
                    getUserName()+"\" ("+mem->getSystemName()+"), value = "+mem->getValue().toString()
                    +", for Action \""+action->getTypeString()+
                    "\", in Conditional \""+getUserName()+"\" ("+getSystemName()+")");
                return -1;
            }
        }
    }
    return time;
}
/**
 * Stop a sensor timer if one is actively delaying setting of the specified sensor
 */
/*public*/ void DefaultConditional::cancelSensorTimer (QString sname) {
    for (int i = 0; i < _actionList->size(); i++) {
        ConditionalAction* action = _actionList->at(i);
        if ( (action->getType() == Conditional::ACTION_DELAYED_SENSOR) ||
                    (action->getType() == Conditional::ACTION_RESET_DELAYED_SENSOR) ) {
            if ( action->isTimerActive() ) {
                QString devName = getDeviceName(action);
                // have active set sensor timer - is it for our sensor?
                if ( devName ==(sname) ) {
                    // yes, names match, cancel timer
                    action->stopTimer();
                }
                else {
                    // check if same sensor by a different name
                    Sensor* sn = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(devName);
                    if (sn == nullptr) {
                        log->error(getDisplayName()+" Unknown sensor *"+action->getDeviceName()+" in cancelSensorTimer.");
                    }
                    else if (sname ==(sn->getSystemName()) ||
                                            sname ==(sn->getUserName())) {
                        // same sensor, cancel timer
                        action->stopTimer();
                    }
                }
            }
        }
    }
}

/**
 * Stop a turnout timer if one is actively delaying setting of the specified turnout
 */
/*public*/ void DefaultConditional::cancelTurnoutTimer (QString sname) {
    for (int i = 0; i < _actionList->size(); i++) {
        ConditionalAction* action = _actionList->at(i);
        if ( (action->getType() == Conditional::ACTION_DELAYED_TURNOUT) ||
                    (action->getType() == Conditional::ACTION_RESET_DELAYED_TURNOUT) ) {
            if ( action->isTimerActive() ) {
                // have active set turnout timer - is it for our turnout?
                QString devName = getDeviceName(action);
                if ( devName ==(sname) ) {
                    // yes, names match, cancel timer
                    action->stopTimer();
                }
                else {
                    // check if same turnout by a different name
                    Turnout* tn = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(devName);
                    if (tn == nullptr) {
                        log->error(getDisplayName()+" Unknown turnout *"+action->getDeviceName()+" in cancelTurnoutTimer.");
                    }
                    else if (sname ==(((AbstractTurnout*)tn)->getSystemName()) ||
                                            sname ==(((AbstractTurnout*)tn)->getUserName())) {
                        // same turnout, cancel timer
                        action->stopTimer();
                    }
                }
            }
        }
    }
}
/**
 * State of the Conditional is returned.
 * @return state value
 */
/*public*/ int DefaultConditional::getState() {
    return _currentState;
}

/**
 * State of Conditional is set. Not really public for Conditionals.
 * The state of a Conditional is only changed by its calculate method, so the state is
 *    really a read-only bound property.
 */
/*public*/ void DefaultConditional::setState(int state) {
    if (_currentState != state) {
        int oldState = _currentState;
        _currentState = state;
        firePropertyChange("KnownState", QVariant(oldState), QVariant(_currentState));
    }
}

/**
 *	Class for defining ActionListener for ACTION_DELAYED_SENSOR
 */
//class TimeSensor implements java.awt.event.ActionListener
//{
    /*public*/ TimeSensor::TimeSensor(int index, DefaultConditional* self) {
        mIndex = index;
        this->self = self;
    }

    /*public*/ void TimeSensor::actionPerformed(JActionEvent* /*event*/)
    {
        // set sensor state
        ConditionalAction* action = self->_actionList->at(mIndex);
        QString devName = self->getDeviceName(action);
        Sensor* sn = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(devName);
        if (sn==nullptr) {
            self->log->error(self->getDisplayName()+" Invalid delayed sensor name - "+action->getDeviceName());
        }
        else {
            // set the sensor
            try {
                sn->setKnownState(action->getActionData());
            }
            catch (JmriException e) {
                self->log->warn("Exception setting delayed sensor "+action->getDeviceName()+" in action");
            }
        }
        // Turn Timer OFF
        action->stopTimer();
    }
//};

/**
 *	Class for defining ActionListener for ACTION_DELAYED_TURNOUT
 */
//class TimeTurnout implements java.awt.event.ActionListener
//{
    /*public*/ TimeTurnout::TimeTurnout(int index, DefaultConditional* self) {
        mIndex = index;
    this->self = self;

    }


    /*public*/ void TimeTurnout::actionPerformed(JActionEvent* /*event*/)
    {
        // set turnout state
        ConditionalAction* action = self->_actionList->at(mIndex);
        QString devName = self->getDeviceName(action);
        Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(devName);
        if (t==nullptr) {
            self->log->error(self->getDisplayName()+" Invalid delayed turnout name - "+action->getDeviceName());
        }
        else {
            // set the turnout
            ((AbstractTurnout*)t)->setCommandedState(action->getActionData());
        }
        // Turn Timer OFF
        action->stopTimer();
    }
//}

