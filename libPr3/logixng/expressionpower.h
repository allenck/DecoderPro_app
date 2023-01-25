#ifndef EXPRESSIONPOWER_H
#define EXPRESSIONPOWER_H

#include "abstractdigitalexpression.h"
#include "powermanager.h"
#include "is_isnot_enum.h"
#include "propertychangelistener.h"

class ExpressionPower : public AbstractDigitalExpression, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
  /*public*/  /*enum*/class PowerState {
//      On(PowerManager.ON, Bundle.getMessage("PowerStateOn")),
//      Off(PowerManager.OFF, Bundle.getMessage("PowerStateOff")),
//      Other(-1, Bundle.getMessage("PowerStateOther"));
   public:
      enum STATE {On, Off, Other};
      static /*public*/ QList<STATE> values()
      {
       return QList<STATE>{On, Off, Other};
      }
//      /*private*/ final int _id;
//      /*private*/ final String _text;

//      /*private*/ PowerState(int id, String text) {
//          this._id = id;
//          this._text = text;
//      }

      static /*public*/  PowerState::STATE get(int id) {
          switch (id) {
              case PowerManager::OFF:
                  return Off;

              case PowerManager::ON:
                  return On;

              default:
                  return Other;
          }
      }

//      /*public*/  int getID() {
//          return _id;
//      }

      //@Override
      /*public*/static  QString toString(STATE state) {
       switch (state) {
       case On: return tr("On");
       case Off: return tr("Off");
       default:
        return tr("Other");
       }
      }
      /*public*/static STATE valueOf(QString s)
      {
       if(s==tr("On")) return On;
       if(s==tr("Off")) return Off;
       return Other;
      }
  };
   ExpressionPower(QString sys, QString user, QObject *parent = nullptr);
   /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
   /*public*/  void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) ;
   /*public*/  Is_IsNot_Enum::VAL get_Is_IsNot();
   /*public*/  void setBeanState(PowerState::STATE state);
   /*public*/  PowerState::STATE getBeanState();
   /*public*/  Category getCategory() override;
   /*public*/  bool evaluate() /*throws JmriException */override;
   /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
   /*public*/  int getChildCount()override;
   /*public*/  QString getShortDescription(QLocale locale)override;
   /*public*/  QString getLongDescription(QLocale locale)override;
   /*public*/  void registerListenersForThisClass() override;
   /*public*/  void unregisterListenersForThisClass()override;
   /*public*/  void propertyChange(PropertyChangeEvent* evt) override;
   /*public*/  void disposeMe()override;

   QObject* bself() override {return (QObject*)this;}
   QObject* pself() override {return (QObject*)this;}

 private:
   /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
   /*private*/ PowerState::STATE _powerState = PowerState::On;

};

#endif // EXPRESSIONPOWER_H
