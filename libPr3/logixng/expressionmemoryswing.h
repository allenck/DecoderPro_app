#ifndef EXPRESSIONMEMORYSWING_H
#define EXPRESSIONMEMORYSWING_H

#include "abstractdigitalexpressionswing.h"

class BeanSelectPanel;
class JTabbedPane;
class JTextField;
class JComboBox;
class JCheckBox;
class ExpressionMemorySwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ExpressionMemorySwing(QObject *parent = nullptr);
  ~ExpressionMemorySwing() {}
  ExpressionMemorySwing(const ExpressionMemorySwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString() override;
  /*public*/  void dispose() override;

  QObject* sself() override{return (QObject*)this;}

 private:
  /*private*/ BeanSelectPanel/*<Memory>*/* _memoryBeanPanel;
  /*private*/ JComboBox/*<MemoryOperation>*/* _memoryOperationComboBox;
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
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object,/*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ExpressionMemorySwing);
#endif // EXPRESSIONMEMORYSWING_H
