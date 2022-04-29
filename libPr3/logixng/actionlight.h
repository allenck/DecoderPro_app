#ifndef ACTIONLIGHT_H
#define ACTIONLIGHT_H

#include "abstractdigitalaction.h"
#include "namedbeanaddressing.h"
#include "light.h"
#include "namedbeanhandle.h"
#include "expressionnode.h"
#include "vetoablechangelistener.h"
#include "threadingutil.h"
#include "turnout.h"
#include "variablelight.h"

class ActionLight : public AbstractDigitalAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  explicit ActionLight(QString sys, QString user, QObject *parent = nullptr);
  /*public*/ /*enum*/class LightState {
//      Off(Light.OFF, Bundle.getMessage("StateOff")),
//      On(Light.ON, Bundle.getMessage("StateOn")),
//      Toggle(TOGGLE_ID, Bundle.getMessage("LightToggleStatus")),
//      Intensity(INTENSITY_ID, Bundle.getMessage("LightIntensity")),
//      Interval(INTERVAL_ID, Bundle.getMessage("LightInterval"));
   public:
    enum STATE {Off, On, Toggle, Intensity, Interval};
    /*public*/static QList<STATE> values() {return QList<STATE>{Off, On, Toggle, Intensity, Interval};}
    enum Light {OFF, ON, TOGGLE_ID, INTENSITY_ID, INTERVAL_ID};

//      private final int _id;
//      private final String _text;

//      private LightState(int id, String text) {
//          this._id = id;
//          this._text = text;
//      }

      static /*public*/ LightState::STATE get(int id) {
          switch (id) {
              case Light::OFF:
                  return Off;

              case Light::ON:
                  return On;

              case TOGGLE_ID:
                  return Toggle;

              default:
                  throw new IllegalArgumentException("invalid light state");
          }
      }

      /*public*/ static int getID(STATE state) {
         switch(state)
         {
         case Off: return Light::OFF;
         case On: return Light::ON;
         case Toggle: return  TOGGLE_ID;
         case Intensity: return INTENSITY_ID;
         case Interval: return INTERVAL_ID;
         }
      }

      //@Override
      /*public*/ static QString toString(STATE id) {
       switch (id) {
           case Off:
               return tr("Off");
           case On:
               return tr("On");
           case Toggle:
               return tr("Toggle");
           case Intensity:
               return tr("Intensity");
           case Interval:
               return tr("Interval");
           default:
               throw new IllegalArgumentException("invalid light state");
      }
    }
      /*public*/ static STATE valueOf(QString s)
      {
       if(s==tr("Off")) return Off ;
       if(s==tr("On")) return On;
       if(s==tr("Toggle")) return Toggle;
       if(s==tr("Intensity")) return Intensity;
       if(s==tr("Interval")) return Interval;
      }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/;
  /*public*/  void setLight(/*@Nonnull*/ QString lightName);
  /*public*/  void setLight(/*@Nonnull*/ NamedBeanHandle<Light*>* handle);
  /*public*/  void setLight(/*@Nonnull*/ Light* light);
  /*public*/  void removeLight() ;
  /*public*/  NamedBeanHandle<Light*>* getLight();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference) ;
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula();
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*public*/  void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getStateAddressing();
  /*public*/  void setBeanState(ActionLight::LightState::STATE state);
  /*public*/  ActionLight::LightState::STATE getBeanState();
  /*public*/  void setStateReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getStateReference();
  /*public*/  void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getStateLocalVariable() ;
  /*public*/  void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getStateFormula();
  /*public*/  void setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getDataAddressing();
  /*public*/  void setDataReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getDataReference();
  /*public*/  void setDataLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getDataLocalVariable();
  /*public*/  void setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
  /*public*/  QString getDataFormula();
  /*public*/  void setLightValue(int value) ;
  /*public*/  int getLightValue() ;
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;
  /*public*/  Category* getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Light*>* _lightHandle = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode = nullptr;

  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ LightState::STATE _lightState = LightState::On;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode = nullptr;

  /*private*/ NamedBeanAddressing::TYPE _dataAddressing = NamedBeanAddressing::Direct;
  /*private*/ QString _dataReference = "";
  /*private*/ QString _dataLocalVariable = "";
  /*private*/ QString _dataFormula = "";
  /*private*/ ExpressionNode* _dataExpressionNode = nullptr;

  /*private*/ int _lightValue= 0;

  /*private*/ static /*final*/ int TOGGLE_ID;// = -1;
  /*private*/ static /*final*/ int INTENSITY_ID;// = -2;
  /*private*/ static /*final*/ int INTERVAL_ID;// = -3;
  /*private*/ void parseStateFormula() /*throws ParserException*/;
  /*private*/ void parseDataFormula() /*throws ParserException*/;
  /*private*/ QString getNewState() /*throws JmriException*/;
  /*private*/ int getNewData() /*throws JmriException*/;
  friend class ActionLight_Run;
};
class ActionLight_Run : public ThreadActionWithJmriException
{
  Q_OBJECT
  ActionLight::LightState::STATE state;
  Light* light;
  ActionLight* act;
 public:
  ActionLight_Run(ActionLight::LightState::STATE state, Light* light, ActionLight* act) {this->state == state; this->light = light; this->act =act;}
  void run()
  {
   if (state == ActionLight::LightState::Toggle) {
       if (light->getKnownState() == Turnout::CLOSED) {
           light->setCommandedState(Turnout::THROWN);
       } else {
           light->setCommandedState(Turnout::CLOSED);
       }

   } else if (state == ActionLight::LightState::Intensity) {
       if (qobject_cast<VariableLight*>(light)) {
           ((VariableLight*)light)->setTargetIntensity(act->getNewData() / 100.0);
       } else {
           light->setCommandedState(act->getNewData() > 50 ? Light::ON : Light::OFF);
       }
   } else if (state == ActionLight::LightState::Interval) {
       if (qobject_cast<VariableLight*>(light)) {
           ((VariableLight*)light)->setTransitionTime(act->getNewData());
       }
   } else {
       light->setCommandedState(ActionLight::LightState::getID(state));
   }

  }
};

#endif // ACTIONLIGHT_H
