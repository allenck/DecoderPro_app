#ifndef ACTIONLIGHTSWING_H
#define ACTIONLIGHTSWING_H

#include "abstractdigitalactionswing.h"

class JTabbedPane;
class JComboBox;
class BeanSelectPanel;
class ActionLightSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  explicit ActionLightSwing(QObject *parent = nullptr);
  ~ActionLightSwing() {}
  ActionLightSwing(const ActionLightSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}
 private:
  /*private*/ JTabbedPane* _tabbedPaneLight;
  /*private*/ BeanSelectPanel/*<Light>*/* lightBeanPanel;
  /*private*/ JPanel* _panelLightDirect;
  /*private*/ JPanel* _panelLightReference;
  /*private*/ JPanel* _panelLightLocalVariable;
  /*private*/ JPanel* _panelLightFormula;
  /*private*/ JTextField* _lightReferenceTextField;
  /*private*/ JTextField* _lightLocalVariableTextField;
  /*private*/ JTextField* _lightFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneLightState;
  /*private*/ JComboBox/*<LightState>*/* _stateComboBox;
  /*private*/ JPanel* _panelLightStateDirect;
  /*private*/ JPanel* _panelLightStateReference;
  /*private*/ JPanel* _panelLightStateLocalVariable;
  /*private*/ JPanel* _panelLightStateFormula;
  /*private*/ JTextField* _lightStateReferenceTextField;
  /*private*/ JTextField* _lightStateLocalVariableTextField;
  /*private*/ JTextField* _lightStateFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPaneData;
  /*private*/ JPanel* _panelDataDirect;
  /*private*/ JPanel* _panelDataReference;
  /*private*/ JPanel* _panelDataLocalVariable;
  /*private*/ JPanel* _panelDataFormula;
  /*private*/ JTextField* _lightDataDirectTextField;
  /*private*/ JTextField* _lightDataReferenceTextField;
  /*private*/ JTextField* _lightDataLocalVariableTextField;
  /*private*/ JTextField* _lightDataFormulaTextField;
  /*private*/ void setDataPanelState();

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionLightSwing)
#endif // ACTIONLIGHTSWING_H
