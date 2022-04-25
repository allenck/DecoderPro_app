#ifndef EXPRESSIONLOCALVARIABLESWING_H
#define EXPRESSIONLOCALVARIABLESWING_H

#include "abstractdigitalexpressionswing.h"

class JTextField;
class JComboBox;
class JCheckBox;
class JTabbedPane;
class BeanSelectPanel;
class ExpressionLocalVariableSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ExpressionLocalVariableSwing(QObject *parent = nullptr);
  ~ExpressionLocalVariableSwing() {}
  ExpressionLocalVariableSwing(const ExpressionLocalVariableSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 private:
  /*private*/ JTextField* _localVariableTextField;
  /*private*/ JComboBox/*<VariableOperation>*/* _variableOperationComboBox;
  /*private*/ JCheckBox* _caseInsensitiveCheckBox;

  /*private*/ JTabbedPane* _tabbedPane;

  /*private*/ JTabbedPane* _tabbedPaneCompareTo;
  /*private*/ BeanSelectPanel/*<Memory>*/* _compareToMemoryBeanPanel;
  /*private*/ JPanel* _compareToConstant;
  /*private*/ JPanel* _compareToMemory;
  /*private*/ JPanel* _compareToLocalVariable;
  /*private*/ JPanel* _compareToRegEx;
  /*private*/ JTextField* _compareToConstantTextField;
  /*private*/ JTextField* _compareToLocalVariableTextField;
  /*private*/ JTextField* _compareToRegExTextField;
  /*private*/ void enableDisableCompareTo();

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel);

};
Q_DECLARE_METATYPE(ExpressionLocalVariableSwing)
#endif // EXPRESSIONLOCALVARIABLESWING_H
