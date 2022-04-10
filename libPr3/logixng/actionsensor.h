#ifndef ACTIONSENSOR_H
#define ACTIONSENSOR_H

#include "abstractdigitalaction.h"
#include <QWidget>
#include "vetoablechangelistener.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "sensor.h"
#include "threadingutil.h"

class ExpressionNode;
class ActionSensor : public AbstractDigitalAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
  /*private*/ static /*final*/ int TOGGLE_ID;

 public:
  ActionSensor(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  /*enum*/class SensorState {
//      (Sensor.INACTIVE, Bundle.getMessage("SensorStateInactive")),
//      Active(Sensor.ACTIVE, Bundle.getMessage("SensorStateActive")),
//      Toggle(TOGGLE_ID, Bundle.getMessage("SensorToggleStatus"));
   public:
    enum STATE {Inactive, Active, Toggle};

//      /*private*/ /*final*/ int _id;
//      /*private*/ /*final*/ String _text;

//      /*private*/ SensorState(int id, String text) {
//          this._id = id;
//          this._text = text;
//      }

      static /*public*/  SensorState::STATE get(int id) {
          switch ((Sensor::STATES)id) {
              case Sensor::INACTIVE:
                  return Inactive;

              case Sensor::ACTIVE:
                  return Active;

              //case Sensor::TOGGLE_ID:
                  default:
                  return Toggle;

//              default:
//                  throw new IllegalArgumentException("invalid sensor state");
          }
      }

      /*public*/ static int getID(STATE _id) {
          return _id;
      }

      /*public*/ static STATE valueOf(QString(s))
      {
       if(s == tr("Inactive")) return Inactive;
       if(s == tr("Active")) return Active;
       if(s == tr("Toggle")) return Toggle;
       throw new IllegalArgumentException();
      }
      //@Override
      /*public*/ static QString toString(STATE s) {
          switch(s)
          {
          case Inactive: return tr("Inactive");
          case Active: return tr("Active");
          case Toggle: return tr("Toggle");
          }
          throw new IllegalArgumentException();
      }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException */override;
  /*public*/  void setSensor(/*@Nonnull*/ QString sensorName);
  /*public*/  void setSensor(/*@Nonnull*/ NamedBeanHandle<Sensor*>* handle);
  /*public*/  void setSensor(/*@Nonnull*/ Sensor* sensor);
  /*public*/  void removeSensor() ;
  /*public*/  NamedBeanHandle<Sensor*>* getSensor() ;
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference) ;
  /*public*/  QString getReference() ;
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula() ;
  /*public*/  void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getStateAddressing();
  /*public*/  void setBeanState(SensorState::STATE state);
  /*public*/  ActionSensor::SensorState::STATE  getBeanState();
  /*public*/  void setStateReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getStateReference();
  /*public*/  void setStateLocalVariable(/*@Nonnull*/ QString localVariable) ;
  /*public*/  QString getStateLocalVariable();
  /*public*/  void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getStateFormula() ;
  /*public*/  Category* getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<Sensor*>* _sensorHandle;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ SensorState::STATE _sensorState = SensorState::Active;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode;
  /*private*/ void parseFormula() /*throws ParserException*/ ;
  /*private*/ void parseStateFormula() /*throws ParserException*/;
  /*private*/ QString getNewState() /*throws JmriException*/;

  friend class ASRun;
};

class ASRun : public ThreadActionWithJmriException
{
  Sensor* sensor;
  ActionSensor::SensorState::STATE state;
 public:
  ASRun(Sensor* sensor, ActionSensor::SensorState::STATE state) {this->sensor = sensor; this->state = state;}
 void run();
};

#endif // ACTIONSENSOR_H
