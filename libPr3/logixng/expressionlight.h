#ifndef EXPRESSIONLIGHT_H
#define EXPRESSIONLIGHT_H

#include "abstractdigitalexpression.h"
#include "namedbeanhandle.h"
#include "namedbeanaddressing.h"
#include "is_isnot_enum.h"
#include "vetoablechangelistener.h"
#include "light.h"

class Light;
class ExpressionNode;
class ExpressionLight : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  ExpressionLight(QString sys, QString user, QObject *parent = nullptr);
  /*public*/ /*enum*/class LightState {
   public:
//    Off(Light.OFF, Bundle.getMessage("StateOff")),
//    On(Light.ON, Bundle.getMessage("StateOn")),
//    Other(-1, Bundle.getMessage("SensorOtherStatus"));
  enum VALS {Off, On, Other};
//          private final int _id;
//          private final String _text;

//          private LightState(int id, String text) {
//              this._id = id;
//              this._text = text;
//          }

  static /*public*/ LightState::VALS get(Light::STATES id) {
      switch (id) {
          case Light::OFF:
              return Off;

          case Light::ON:
              return On;

          default:
              return Other;
      }
  }
  static /*public*/ LightState::VALS valueOf(QString s) {
     if(s == tr("Off")) return Off;
     if(s== tr("On")) return On;
     return Other;
  }

//          public int getID() {
//              return _id;
//          }

          //@Override
          /*public*/ static QString toString(VALS v) {
           switch (v) {
           case Off: return tr("Off");
           case On: return tr("On");
           default:
            return tr("Other");
           }
          }

      };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
  /*public*/  void setLight(/*@Nonnull*/ QString lightName) ;
  /*public*/  void setLight(/*@Nonnull*/ NamedBeanHandle<Light*>* handle) ;
  /*public*/  void setLight(/*@Nonnull*/ Light* light) ;
  /*public*/  void removeLight();
  /*public*/  NamedBeanHandle<Light*>* getLight() ;
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */;
  /*public*/  QString getFormula();
  /*public*/  void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
  /*public*/  Is_IsNot_Enum::VAL get_Is_IsNot();
  /*public*/  void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getStateAddressing();
  /*public*/  void setBeanState(LightState::VALS state);
  /*public*/  LightState::VALS getBeanState();
  /*public*/  void setStateReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getStateReference();
  /*public*/  void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getStateLocalVariable();
  /*public*/  void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getStateFormula();
  /*public*/  Category getCategory() override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;


  QObject* bself() override{return (QObject*)this;}
  QObject* pself() override{return (QObject*)this;}

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override;// {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Light*>* _lightHandle = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ ExpressionLight::LightState::VALS _lightState = ExpressionLight::LightState::On;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode = nullptr;
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*private*/ void parseStateFormula() /*throws ParserException*/;
  /*private*/ QString getNewState() /*throws JmriException*/;

};

#endif // EXPRESSIONLIGHT_H
