#ifndef EXPRESSIONSENSORSWING_H
#define EXPRESSIONSENSORSWING_H

#include "abstractdigitalexpressionswing.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "beanselectpanel.h"

class ExpressionSensorSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ExpressionSensorSwing(QObject *parent = nullptr)
   : AbstractDigitalExpressionSwing(parent) {setObjectName("ExpressionSensorSwing");}
  ~ExpressionSensorSwing() {}
  ExpressionSensorSwing(const ExpressionSensorSwing&) :AbstractDigitalExpressionSwing () {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  QString getAutoSystemName()override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}
 private:
  /*private*/ JTabbedPane* _tabbedPaneSensor;
  /*private*/ BeanSelectPanel/*<Sensor>*/* sensorBeanPanel;
  /*private*/ JPanel* _panelSensorDirect;
  /*private*/ JPanel* _panelSensorReference;
  /*private*/ JPanel* _panelSensorLocalVariable;
  /*private*/ JPanel* _panelSensorFormula;
  /*private*/ JTextField* _sensorReferenceTextField;
  /*private*/ JTextField* _sensorLocalVariableTextField;
  /*private*/ JTextField* _sensorFormulaTextField;

  /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;

  /*private*/ JTabbedPane* _tabbedPaneSensorState;
  /*private*/ JComboBox/*<SensorState>*/* _stateComboBox;
  /*private*/ JPanel* _panelSensorStateDirect;
  /*private*/ JPanel* _panelSensorStateReference;
  /*private*/ JPanel* _panelSensorStateLocalVariable;
  /*private*/ JPanel* _panelSensorStateFormula;
  /*private*/ JTextField* _sensorStateReferenceTextField;
  /*private*/ JTextField* _sensorStateLocalVariableTextField;
  /*private*/ JTextField* _sensorStateFormulaTextField;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ExpressionSensorSwing)
#endif // EXPRESSIONSENSORSWING_H
