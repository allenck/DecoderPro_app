#ifndef ACTIONSENSORSWING_H
#define ACTIONSENSORSWING_H

#include "abstractdigitalactionswing.h"

class JTabbedPane;
class BeanSelectPanel;
class JComboBox;
class ActionSensorSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionSensorSwing(QObject *parent = nullptr);
  ~ActionSensorSwing() {}
  ActionSensorSwing(const ActionSensorSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  QString getAutoSystemName()override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName);
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
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
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel);

};
Q_DECLARE_METATYPE(ActionSensorSwing)
#endif // ACTIONSENSORSWING_H
