#ifndef EXPRESSIONSENSOR_H
#define EXPRESSIONSENSOR_H

#include "abstractdigitalexpression.h"
#include "vetoablechangelistener.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "sensor.h"
#include "expressionnode.h"
#include "is_isnot_enum.h"

class ExpressionSensor : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  explicit ExpressionSensor(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  /*enum*/class SensorState {
//      Inactive(Sensor.INACTIVE, Bundle.getMessage("SensorStateInactive")),
//      Active(Sensor.ACTIVE, Bundle.getMessage("SensorStateActive")),
//      Other(-1, Bundle.getMessage("SensorOtherStatus"));
public:
    enum STATE {Inactive, Active, Other};
//      /*private*/ /*final*/ int _id;
//      /*private*/ /*final*/ String _text;

//      /*private*/ SensorState(int id, String text) {
//          this._id = id;
//          this._text = text;
//      }
    static QList<STATE> values() {return QList<STATE> {Inactive, Active, Other};}

     static /*public*/  SensorState::STATE get(int id) {
          switch (id) {
              case Sensor::INACTIVE:
                  return Inactive;

              case Sensor::ACTIVE:
                  return Active;

              default:
                  return Other;
          }
      }

//      /*public*/  int getID() {
//          return _id;
//      }
      static STATE valueOf(QString s)
      {
       if(s == tr("Inactive")) return Inactive;
       if(s== tr("Active")) return Active;
       if(s == tr("other")) return Other;
       throw new IllegalArgumentException("invalid sensor state");
      }

      //@Override
      /*public*/static   QString toString(STATE s) {
          switch(s)
          {
          case Inactive: return tr("Inactive");
          case Active: return tr("Active");
          case Other: return tr("Other");
          }
          throw new IllegalAccessException("invaltd state");
      }

  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/override;
  /*public*/  void setSensor(/*@Nonnull*/ QString sensorName);
  /*public*/  void setSensor(/*@Nonnull*/ NamedBeanHandle<Sensor*>* handle);
  /*public*/  void setSensor(/*@Nonnull*/ Sensor* sensor);
  /*public*/  void removeSensor();
  /*public*/  NamedBeanHandle<Sensor*>* getSensor() ;
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull */QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */;
  /*public*/  QString getFormula();
  /*public*/  void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
  /*public*/  Is_IsNot_Enum::VAL get_Is_IsNot() ;
  /*public*/  void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */;
  /*public*/  NamedBeanAddressing::TYPE getStateAddressing();
  /*public*/  void setBeanState(SensorState::STATE state);
  /*public*/  SensorState::STATE getBeanState();
  /*public*/  void setStateReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getStateReference();
  /*public*/  void setStateLocalVariable(/*@Nonnull*/ QString localVariable) ;
  /*public*/  QString getStateLocalVariable();
  /*public*/  void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getStateFormula();
  /*public*/  Category* getCategory()override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass();
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Sensor*>* _sensorHandle;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ SensorState::STATE _sensorState = SensorState::Active;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode;
  /*private*/ void parseFormula() /*throws ParserException */;
  /*private*/ void parseStateFormula() /*throws ParserException*/;
  /*private*/ QString getNewState() /*throws JmriException*/;

};

#endif // EXPRESSIONSENSOR_H
