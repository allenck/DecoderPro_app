#ifndef ACTIONPOWER_H
#define ACTIONPOWER_H

#include "abstractdigitalaction.h"
#include "abstractpowermanager.h"
#include "threadingutil.h"
#include "instancemanager.h"
#include "jmriexception.h"
#include "atomicreference.h"
class ActionPower : public AbstractDigitalAction
{
  Q_OBJECT
 public:
  /*public*/  /*enum*/class PowerState {
//      Off(PowerManager.OFF, Bundle.getMessage("PowerStateOff")),
//      On(PowerManager.ON, Bundle.getMessage("PowerStateOn"));
public:
   enum STATE {Off, On};
   static /*public*/ QList<STATE> values() {return QList<STATE>{Off, On};}
//      private final int _id;
//      private final String _text;

//      private PowerState(int id, String text) {
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
                  throw new IllegalArgumentException("invalid power state");
          }
      }
          static /*public*/  STATE valueOf(QString s) {
           if(s == tr("Off")) return Off;
           if(s == tr("On")) return On;
           throw new IllegalArgumentException("invalid power state");
      }

//      /*public*/  int getID() {
//          return _id;
//      }

      //@Override
      /*public*/ static QString toString(STATE id) {
           switch (id) {
               case Off:
                   return tr("Off");

               case On:
                   return tr("On");

               default:
                   throw new IllegalArgumentException("invalid power state");
           }
      }
  };
  ActionPower(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
  /*public*/  void setBeanState(PowerState::STATE state);
  /*public*/  PowerState::STATE getBeanState();
  /*public*/  Category* getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* bself() override {return (QObject*)this;}
  QObject* self() override {return (QObject*)this;}

 private:
  /*private*/ PowerState::STATE _powerState = PowerState::On;

  friend class ActionPower_run;
};

class ActionPower_run : public ThreadActionWithJmriException
{
  Q_OBJECT
  AtomicReference<JmriException*>* exception;
  ActionPower::PowerState::STATE _powerState;
 public:
  ActionPower_run(ActionPower::PowerState::STATE _powerState, AtomicReference<JmriException*>*exception) {
   this->_powerState = _powerState; this->exception = exception;}
  void run()
  {
   try {
       ((AbstractPowerManager*)InstanceManager::getDefault("PowerManager"))->setPower(ActionPower::PowerState::get(_powerState));
   } catch (JmriException* e) {
       exception->set(e);
   }
  }
};

#endif // ACTIONPOWER_H
