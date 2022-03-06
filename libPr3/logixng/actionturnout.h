#ifndef ACTIONTURNOUT_H
#define ACTIONTURNOUT_H

#include "abstractdigitalaction.h"
#include "turnout.h"
#include "namedbeanhandlemanager.h"
#include "namedbeanhandle.h"
#include "namedbeanaddressing.h"
#include "expressionnode.h"
#include "instancemanager.h"

class ActionTurnout : public AbstractDigitalAction
{
  Q_OBJECT
 public:
  explicit ActionTurnout(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  class TurnoutState {
//      Closed(Turnout.CLOSED, InstanceManager.getDefault(TurnoutManager.class).getClosedText()),
//      Thrown(Turnout.THROWN, InstanceManager.getDefault(TurnoutManager.class).getThrownText()),
//      Toggle(TOGGLE_ID, Bundle.getMessage("TurnoutToggleStatus"));
   public:
   enum TYPE {Closed, Thrown, Toggle};

//      /*private*/ /*final*/ int _id;
//      /*private*/ /*final*/ String _text;

//      /*private*/ TurnoutState(int id, String text) {
//          this._id = id;
//          this._text = text;
//      }

      static /*public*/  TurnoutState::TYPE get(int id) {
          switch (id) {
              case Turnout::CLOSED:
                  return Closed;

              case Turnout::THROWN:
                  return Thrown;

//              case TOGGLE_ID:
//                  return Toggle;

              default:
                  throw new IllegalArgumentException("invalid turnout state");
          }
      }

//      /*public*/ static int getID( TYPE _id) {
//          return _id;
//      }

      //@Override
      /*public*/  static QString toString(TYPE _id) {
           switch(_id)
           {
            case Closed:
             ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getClosedText();
           case Thrown:
            ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getThrownText();
           case Toggle:
            return tr("Toggle");

           }
      };

  };

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Turnout*>* _turnoutHandle;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ TurnoutState::TYPE _turnoutState = TurnoutState::Thrown;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode;

};


#endif // ACTIONTURNOUT_H
