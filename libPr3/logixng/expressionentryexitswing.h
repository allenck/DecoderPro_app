#ifndef EXPRESSIONENTRYEXITSWING_H
#define EXPRESSIONENTRYEXITSWING_H

#include "abstractdigitalexpressionswing.h"

class BeanSelectPanel;
class JComboBox;
class JTabbedPane;
class JTextField;
class ExpressionEntryExitSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE ExpressionEntryExitSwing(QObject* parent = nullptr) : AbstractDigitalExpressionSwing(parent){}
  ~ExpressionEntryExitSwing() {}
  ExpressionEntryExitSwing(const ExpressionEntryExitSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  QString getAutoSystemName()override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return this;}

  /*public*/  JTabbedPane* _tabbedPaneEntryExit;
  /*public*/  BeanSelectPanel/*<DestinationPoints>*/* destinationPointsBeanPanel;
  /*public*/  JPanel* _panelEntryExitDirect;
  /*public*/  JPanel* _panelEntryExitReference;
  /*public*/  JPanel* _panelEntryExitLocalVariable;
  /*public*/  JPanel* _panelEntryExitFormula;
  /*public*/  JTextField* _entryExitReferenceTextField;
  /*public*/  JTextField* _entryExitLocalVariableTextField;
  /*public*/  JTextField* _entryExitFormulaTextField;

  /*public*/  JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;

  /*public*/  JTabbedPane* _tabbedPaneEntryExitState;
  /*public*/  JComboBox/*<EntryExitState>*/* _stateComboBox;
  /*public*/  JPanel* _panelEntryExitStateDirect;
  /*public*/  JPanel* _panelEntryExitStateReference;
  /*public*/  JPanel* _panelEntryExitStateLocalVariable;
  /*public*/  JPanel* _panelEntryExitStateFormula;
  /*public*/  JTextField* _entryExitStateReferenceTextField;
  /*public*/  JTextField* _entryExitStateLocalVariableTextField;
  /*public*/  JTextField* _entryExitStateFormulaTextField;

 private:

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel);

};
Q_DECLARE_METATYPE(ExpressionEntryExitSwing)
#endif // EXPRESSIONENTRYEXITSWING_H
