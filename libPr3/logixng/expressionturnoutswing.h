#ifndef EXPRESSIONTURNOUTSWING_H
#define EXPRESSIONTURNOUTSWING_H

#include "abstractdigitalexpressionswing.h"

class JComboBox;
class BeanSelectPanel;
class JTabbedPane;
class ExpressionTurnoutSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE ExpressionTurnoutSwing(QObject* parent = nullptr);
  ~ExpressionTurnoutSwing() {}
  ExpressionTurnoutSwing(const ExpressionTurnoutSwing&) {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself()override {return this;}

 private:
  /*private*/ JTabbedPane* _tabbedPaneTurnout;
  /*private*/ BeanSelectPanel/*<Turnout>*/* turnoutBeanPanel;
  /*private*/ JPanel* _panelTurnoutDirect;
  /*private*/ JPanel* _panelTurnoutReference;
  /*private*/ JPanel* _panelTurnoutLocalVariable;
  /*private*/ JPanel* _panelTurnoutFormula;
  /*private*/ JTextField* _turnoutReferenceTextField;
  /*private*/ JTextField* _turnoutLocalVariableTextField;
  /*private*/ JTextField* _turnoutFormulaTextField;

  /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;

  /*private*/ JTabbedPane* _tabbedPaneTurnoutState;
  /*private*/ JComboBox/*<TurnoutState>*/* _stateComboBox;
  /*private*/ JPanel* _panelTurnoutStateDirect;
  /*private*/ JPanel* _panelTurnoutStateReference;
  /*private*/ JPanel* _panelTurnoutStateLocalVariable;
  /*private*/ JPanel* _panelTurnoutStateFormula;
  /*private*/ JTextField* _turnoutStateReferenceTextField;
  /*private*/ JTextField* _turnoutStateLocalVariableTextField;
  /*private*/ JTextField* _turnoutStateFormulaTextField;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ExpressionTurnoutSwing)
#endif // EXPRESSIONTURNOUTSWING_H
