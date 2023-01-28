#ifndef EXPRESSIONREPORTERSWING_H
#define EXPRESSIONREPORTERSWING_H

#include "abstractdigitalexpressionswing.h"

class ReporterOperation;
class BeanSelectPanel;
class JComboBox;
class JTabbedPane;
class JCheckBox;
class ExpressionReporterSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE ExpressionReporterSwing(QObject* parent = nullptr) {}
  ~ExpressionReporterSwing() {}
  ExpressionReporterSwing(const ExpressionReporterSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object);
  /*public*/  QString toString()override;
  /*public*/  void dispose() override;

  QObject* sself() override {return this;}

 private:
  /*private*/ BeanSelectPanel/*<Reporter*>*/* _reporterBeanPanel;
  /*private*/ JComboBox/*<ReporterValue>*/* _reporterValueComboBox;
  /*private*/ JComboBox/*<ReporterOperation>*/* _reporterOperationComboBox;
  /*private*/ JCheckBox* _caseInsensitiveCheckBox;

  /*private*/ JTabbedPane* _tabbedPane;

  /*private*/ JTabbedPane* _tabbedPaneCompareTo;
  /*private*/ BeanSelectPanel/*<Memory>*/* _compareToMemoryBeanPanel;
  /*private*/ JPanel* _reporterValuePanel;
  /*private*/ JPanel* _compareToConstant;
  /*private*/ JPanel* _compareToMemory;
  /*private*/ JPanel* _compareToLocalVariable;
  /*private*/ JPanel* _compareToRegEx;
  /*private*/ JTextField* _compareToConstantTextField;
  /*private*/ JTextField* _compareToLocalVariableTextField;
  /*private*/ JTextField* _compareToRegExTextField;
  /*private*/ void enableDisableCompareTo();


 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};

#endif // EXPRESSIONREPORTERSWING_H
